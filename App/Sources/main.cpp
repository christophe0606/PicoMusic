/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <math.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "hardware/dma.h"
#include "hardware/clocks.h"

#include "pico/util/queue.h"

#include "pico/binary_info.h"
#include "pico/multicore.h"

#include "arm_math.h"
#include "cg_status.h"

#include "AudioGraph/audio_scheduler.h"
#include "LCDGraph/lcd_scheduler.h"


#include "lcd_python_graph_config.h"
#include "Nodes/RP2/pwm_audio/c_component.h"
#include "Songs/songs.h"

/* start_lcd() */
extern "C" {
#include "st7789_lcd.h"

#include "arm_2d_helper.h"
#include "arm_2d_disp_adapters.h"
}

queue_t audio_queue;
q15_t hanningQ15[FFTSIZE];
float hanning[FFTSIZE];
#define NB_TAPS 5
// 0.2 ...
const q15_t coefs[NB_TAPS]={6553,6553,6553,6553,6553};



void lcd_graph()
{
    int error=CG_SUCCESS;
    uint32_t nbSched = 0;

    error = init_lcd_scheduler(&audio_queue,NB_TAPS,coefs);
    nbSched=lcd_scheduler(&error,&audio_queue,NB_TAPS,coefs);
    free_lcd_scheduler(&audio_queue,NB_TAPS,coefs);

    printf("End LCD graph : nb=%d, err=%d\n",nbSched,error);

}

uint32_t offState=0;

int main() {
    stdio_init_all();
    sleep_ms(2000);

    start_lcd();

    arm_irq_safe {
        arm_2d_init();
    }

    disp_adapter0_init();

#ifdef DEBUG_TRACE
    printf("Beep boop, listening...\n");

    uint f_clk_sys = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS);
    printf("SYS Clock = %d\n",f_clk_sys);
    
    uint f_clk_adc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_ADC);
    printf("ADC Clock = %d\n",f_clk_adc);

#endif
    bi_decl(bi_program_description("CMSIS-Stream and CMSIS-DSP example for Raspberry Pi Pico")); // for picotool
    //bi_decl(bi_1pin_with_name(ADC_PIN, "ADC input pin"));

    int error=CG_SUCCESS;
    uint32_t nbSched = 0;


    
    // Same buffering as audio to ensure
    // display and played sound are in sync
    queue_init (&audio_queue,AUDIO_BLOCK_LENGTH,PWM_AUDIO_BUFFER_COUNT);

    arm_hanning_f32(hanning,FFTSIZE);
    arm_float_to_q15(hanning,hanningQ15,FFTSIZE);
    error = init_audio_scheduler(&offState,&audio_queue,allSongs,names);

   
    if (error == CG_SUCCESS)
    {
        
        multicore_launch_core1(lcd_graph);

        nbSched=audio_scheduler(&error,&offState,&audio_queue,allSongs,names);

        printf("Number of schedule iterations = %d\n\r",nbSched);
    }
    if (error !=CG_SUCCESS)
    {
        switch(error)
        {
            case CG_BUFFER_UNDERFLOW:
                printf("Error : buffer underflow\n");
            break;
            case CG_BUFFER_OVERFLOW:
                printf("Error : buffer overflow\n");
            break;
            case CG_MEMORY_ALLOCATION_FAILURE:
                printf("Error : Memory allocation failure\n");
            break;
            case CG_INIT_FAILURE:
                printf("Error : Scheduler init failure\n");
            break;
            case CG_BUFFER_ERROR:
                printf("Error : buffer error\n");
            break;
            case CG_OS_ERROR:
                printf("Error : RTOS error\n");
            break;
            case CG_STOP_SCHEDULER:
                printf("Force stop of the scheduler\n");
            break;
            default:
               printf("Unknown error\n");
        }
    }

    

    free_audio_scheduler(&offState,&audio_queue,allSongs,names);
    queue_free(&audio_queue);


    printf("End\n\r");
    while (true) {
        tight_loop_contents();
    }
}
