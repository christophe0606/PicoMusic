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


#define LCD_NB_IDENTIFIED_NODES 13
#define LCD_COMPOSITOR_ID 0
#define LCD_AMP_ID 1
#define LCD_AMPLAYER_ID 2
#define LCD_ANIMATE_ID 3
#define LCD_CMSIS_ID 4
#define LCD_CORE0_ID 5
#define LCD_DECIMATEAMP_ID 6
#define LCD_DECIMATEFFT_ID 7
#define LCD_FFT_ID 8
#define LCD_FFTLAYER_ID 9
#define LCD_FFTMAG_ID 10
#define LCD_SPECTRUM_ID 11
#define LCD_TOCMPLX_ID 12

extern void *get_lcd_scheduler_node(int32_t nodeID);

extern int init_lcd_scheduler(queue_t *audio_queue,
                              const int nbTaps,
                              const q15_t* coefs);
extern void free_lcd_scheduler(queue_t *audio_queue,
                              const int nbTaps,
                              const q15_t* coefs);
extern uint32_t lcd_scheduler(int *error,queue_t *audio_queue,
                              const int nbTaps,
                              const q15_t* coefs);

#ifdef   __cplusplus
}
#endif

#endif

