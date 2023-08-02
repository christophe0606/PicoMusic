#ifndef _AUDIO_GRAPH_CONFIG_H_
#define _AUDIO_GRAPH_CONFIG_H_ 

#include "arm_math_types.h"

#include "pico/multicore.h"
#include "pico/util/queue.h"

#include "global_config.h"
#include "audio_python_graph_config.h"

#define CG_BEFORE_SCHEDULER_FUNCTION __attribute__((section(".time_critical.audio_scheduler")))



//#define DEBUG_MIDI
#endif