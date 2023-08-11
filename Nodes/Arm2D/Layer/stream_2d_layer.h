#ifndef _STREAM_2D_LAYER_
#define _STREAM_2D_LAYER_

#include "arm_2d.h"


typedef struct {
  arm_2d_tile_t tile; 
  arm_2d_location_t pos; 
  arm_2d_region_t dirty_region;
  uint16_t layer;
  int16_t alpha;
  uint16_t color;
  int16_t copy_only_mode; /* Copy only or not */
} stream_2d_layer_t;


#endif