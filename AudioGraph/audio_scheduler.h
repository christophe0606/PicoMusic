/*

Generated with CMSIS-Stream python scripts.
The generated code is not covered by CMSIS-Stream license.

The support classes and code are covered by CMSIS-Stream license.

*/

#ifndef _AUDIO_SCHEDULER_H_ 
#define _AUDIO_SCHEDULER_H_

#ifdef   __cplusplus
extern "C"
{
#endif


#define AUDIO_NB_IDENTIFIED_NODES 4
#define AUDIO_NOTESEQUENCER_ID 0
#define AUDIO_AUDIO_ID 1
#define AUDIO_CORE1_ID 2
#define AUDIO_OGAIN_ID 3

extern void *get_audio_scheduler_node(int32_t nodeID);

extern int init_audio_scheduler(uint32_t *offState,
                              queue_t *audio_queue,
                              const uint8_t** allSongs,
                              const char** names);
extern void free_audio_scheduler(uint32_t *offState,
                              queue_t *audio_queue,
                              const uint8_t** allSongs,
                              const char** names);
extern uint32_t audio_scheduler(int *error,uint32_t *offState,
                              queue_t *audio_queue,
                              const uint8_t** allSongs,
                              const char** names);

#ifdef   __cplusplus
}
#endif

#endif

