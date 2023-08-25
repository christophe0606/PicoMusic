#pragma once 


#include "arm_math_types.h"
#include "pico/multicore.h"
#include "pico/util/queue.h"

#include "global_config.h"
#include "lcd_python_graph_config.h"


#include "GenericNodes.h"
#include "cg_status.h"

using namespace arm_cmsis_stream;

#include "Nodes/Generic/Gain/component.hpp"
#include "Nodes/Playtune_synth/Sequencer/component.hpp"

#ifndef KEYA_ID
#define KEYA_ID 21
#endif

#ifndef KEYB_ID
#define KEYB_ID 19
#endif

#ifndef KEYC_ID
#define KEYC_ID 17
#endif

#ifndef KEYD_ID
#define KEYD_ID 15
#endif


using DigitalGainNode = Gain<q15_t,AUDIO_BLOCK_LENGTH,q15_t,AUDIO_BLOCK_LENGTH>;
using SequencerNode = Sequencer<midi_cmd_t,1>;

extern void initKeyControl(DigitalGainNode *&dg,SequencerNode *&s);
extern void processKey(DigitalGainNode *dg,SequencerNode *s);
