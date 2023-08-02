#pragma once

/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "hardware/pio.h"
#include "st7789_lcd.pio.h"
#include "hardware/gpio.h"

#include "c_component.h"

#define LCD_PIN_DIN 11
#define LCD_PIN_CLK 10
#define LCD_PIN_CS 9
#define LCD_PIN_DC 8
#define LCD_PIN_RESET 12
#define LCD_PIN_BL 13

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 240

#define SERIAL_CLK_DIV 1.f

/*

37-38 ms refresh

*/

// Format: cmd length (including cmd byte), post delay in units of 5 ms, then cmd payload
// Note the delays have been shortened a little
static const uint8_t st7789_init_seq[] = {
        1, 20, 0x01,                        // Software reset
        1, 10, 0x11,                        // Exit sleep mode
        2, 2, 0x3a, 0x55,                   // Set colour mode to 16 bit
        2, 0, 0x36, 0x00,                   // Set MADCTL: row then column, refresh is bottom to top ????
        5, 0, 0x2a, 0x00, 0x00, SCREEN_WIDTH >> 8, SCREEN_WIDTH & 0xff,   // CASET: column addresses
        5, 0, 0x2b, 0x00, 0x00, SCREEN_HEIGHT >> 8, SCREEN_HEIGHT & 0xff, // RASET: row addresses
        1, 2, 0x21,                         // Inversion on, then 10 ms delay (supposedly a hack?)
        1, 2, 0x13,                         // Normal display on, then 10 ms delay
        1, 2, 0x29,                         // Main screen turn on, then wait 500 ms
        0                                   // Terminate list
};


static inline void lcd_set_dc_cs(bool dc, bool cs) {
    sleep_us(1);
    gpio_put_masked((1u << LCD_PIN_DC) | (1u << LCD_PIN_CS), !!dc << LCD_PIN_DC | !!cs << LCD_PIN_CS);
    sleep_us(1);
}

static inline void lcd_write_cmd(PIO pio, uint sm, const uint8_t *cmd, size_t count) {
    st7789_lcd_wait_idle(pio, sm);
    lcd_set_dc_cs(0, 0);
    st7789_lcd_put(pio, sm, *cmd++);
    if (count >= 2) {
        st7789_lcd_wait_idle(pio, sm);
        lcd_set_dc_cs(1, 0);
        for (size_t i = 0; i < count - 1; ++i)
            st7789_lcd_put(pio, sm, *cmd++);
    }
    st7789_lcd_wait_idle(pio, sm);
    lcd_set_dc_cs(1, 1);
}

static inline void lcd_init(PIO pio, uint sm, const uint8_t *init_seq) {
    const uint8_t *cmd = init_seq;
    while (*cmd) {
        lcd_write_cmd(pio, sm, cmd + 2, *cmd);
        sleep_ms(*(cmd + 1) * 5);
        cmd += *cmd + 2;
    }
}

static inline void st7789_start_pixels(PIO pio, uint sm) {
    uint8_t cmd = 0x2c; // RAMWR
    lcd_write_cmd(pio, sm, &cmd, 1);
    lcd_set_dc_cs(1, 0);
}


template<typename IN,int inputSize>
class LCD;


template<>
class LCD<image_t,1>: 
public GenericSink<image_t,1>
{
public:
    LCD(FIFOBase<image_t> &dst):
    GenericSink<image_t,1>(dst){
    
    pio = pio0;
    sm = 0;
    uint offset = pio_add_program(pio, &st7789_lcd_program);
    st7789_lcd_program_init(pio, sm, offset, LCD_PIN_DIN, LCD_PIN_CLK, SERIAL_CLK_DIV);

    gpio_init(LCD_PIN_CS);
    gpio_init(LCD_PIN_DC);
    gpio_init(LCD_PIN_RESET);
    gpio_init(LCD_PIN_BL);
    gpio_set_dir(LCD_PIN_CS, GPIO_OUT);
    gpio_set_dir(LCD_PIN_DC, GPIO_OUT);
    gpio_set_dir(LCD_PIN_RESET, GPIO_OUT);
    gpio_set_dir(LCD_PIN_BL, GPIO_OUT);

    gpio_put(LCD_PIN_CS, 1);
    gpio_put(LCD_PIN_RESET, 1);
    lcd_init(pio, sm, st7789_init_seq);
    gpio_put(LCD_PIN_BL, 1);
       
    };

   

    int prepareForRunning() final
    {
        if (this->willUnderflow())
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };

    int run() final{
        image_t *input=this->getReadBuffer();
        q15_t* p =input->pixels;
        
        //absolute_time_t ta = get_absolute_time();
        st7789_start_pixels(pio, sm);
        for (int y = 0; y < SCREEN_HEIGHT; ++y) {
            for (int x = 0; x < SCREEN_WIDTH; ++x) {
                uint16_t colour = *p++;
                st7789_lcd_put(pio, sm, colour >> 8);
                st7789_lcd_put(pio, sm, colour & 0xff);
            }
        }
        //absolute_time_t tb = get_absolute_time();
        //int32_t ms = to_ms_since_boot (tb)-to_ms_since_boot (ta);
        //printf("%d\n",ms);
        return(CG_SUCCESS);
    };

protected:
   PIO pio;
   uint sm;
};


