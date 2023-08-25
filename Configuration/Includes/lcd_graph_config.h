#ifndef _LCD_GRAPH_CONFIG_H_
#define _LCD_GRAPH_CONFIG_H_ 


#include "arm_math_types.h"

#include "global_config.h"
#include "lcd_python_graph_config.h"

#include <cstdio>

extern q15_t hanningQ15[FFTSIZE];

#include "key_control.h"


#define CG_BEFORE_SCHEDULE \
  int nb_stdin=0; \
  DigitalGainNode *g; \
  SequencerNode *seq; \
  initKeyControl(g,seq);

  


#define CG_BEFORE_ITERATION \
  nb_stdin++; \
  if (nb_stdin == 4) \
  { \
     processKey(g,seq); \
     nb_stdin = 0; \
  }
  
#endif