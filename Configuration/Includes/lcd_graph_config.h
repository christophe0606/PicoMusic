#ifndef _LCD_GRAPH_CONFIG_H_
#define _LCD_GRAPH_CONFIG_H_ 


#include "arm_math_types.h"
#include "pico/multicore.h"
#include "pico/util/queue.h"

#include "pico/sync.h"
#include "pico/stdlib.h"

#include "global_config.h"
#include "lcd_python_graph_config.h"

#include <cstdio>

extern q15_t hanningQ15[FFTSIZE];

/* To control audio graph from LCD core */

#include "GenericNodes.h"
#include "cg_status.h"

using namespace arm_cmsis_stream;

#include "Nodes/Generic/Gain/component.hpp"
#include "Nodes/Playtune_synth/Sequencer/component.hpp"

// For Node IDs
#include "AudioGraph/audio_scheduler.h"


#define CG_BEFORE_SCHEDULE \
  void *p; \
  int nb_stdin=0; \
  Gain<q15_t,AUDIO_BLOCK_LENGTH,q15_t,AUDIO_BLOCK_LENGTH> *g; \
  Sequencer<midi_cmd_t,1> *seq; \
  p=get_audio_scheduler_node(AUDIO_OGAIN_ID); \
  g=reinterpret_cast<Gain<q15_t,AUDIO_BLOCK_LENGTH,q15_t,AUDIO_BLOCK_LENGTH>*>(p); \
  p=get_audio_scheduler_node(AUDIO_NOTESEQUENCER_ID); \
  seq=reinterpret_cast<Sequencer<midi_cmd_t,1>*>(p);


#define CG_BEFORE_ITERATION \
  nb_stdin++; \
  if (nb_stdin == 4) \
  { \
    nb_stdin = 0; \
    float currentGain = g->getGain(); \
 \
    int c = getchar_timeout_us(0); \
    if (c == 'n') \
    { \
        seq->nextSong(); \
    } \
    if (c == '-') \
    { \
        float newGain = currentGain-0.1f; \
        if (newGain>=0.0f) \
        { \
            g->setGain(newGain); \
            printf("gain = %f\n",newGain);\
        } \
    } \
    if (c == 'q')  \
    { \
        g->setGain(0.0f); \
        printf("gain = 0.0\n");\
    } \
    if ((c == '=' || c == '+')) \
    { \
        g->setGain(currentGain+0.1f); \
        printf("gain = %f\n",currentGain+0.1f); \
    } \
  }
  
#endif