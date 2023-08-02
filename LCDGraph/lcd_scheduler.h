/*

Generated with CMSIS-Stream python scripts.
The generated code is not covered by CMSIS-Stream license.

The support classes and code are covered by CMSIS-Stream license.

*/

#ifndef _LCD_SCHEDULER_H_ 
#define _LCD_SCHEDULER_H_

#ifdef   __cplusplus
extern "C"
{
#endif


#define LCD_NB_IDENTIFIED_NODES 10
#define LCD_FFTW_ID 0
#define LCD_AMPW_ID 1
#define LCD_CORE0_ID 2
#define LCD_DECIMATEAMP_ID 3
#define LCD_DECIMATEFFT_ID 4
#define LCD_FB_ID 5
#define LCD_FFT_ID 6
#define LCD_FFTMAG_ID 7
#define LCD_LCD_ID 8
#define LCD_TOCMPLX_ID 9

extern void *get_lcd_scheduler_node(int32_t nodeID);

extern int init_lcd_scheduler(queue_t *audio_queue,
                              const q15_t* cmsis_texture,
                              const int nbTaps,
                              const q15_t* coefs);
extern void free_lcd_scheduler(queue_t *audio_queue,
                              const q15_t* cmsis_texture,
                              const int nbTaps,
                              const q15_t* coefs);
extern uint32_t lcd_scheduler(int *error,queue_t *audio_queue,
                              const q15_t* cmsis_texture,
                              const int nbTaps,
                              const q15_t* coefs);

#ifdef   __cplusplus
}
#endif

#endif

