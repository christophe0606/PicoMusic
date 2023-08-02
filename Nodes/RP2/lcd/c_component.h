#ifndef LCD_C_COMPONENT_H
#define LCD_C_COMPONENT_H



#ifdef   __cplusplus
extern "C"
{
#endif

typedef struct {
  q15_t *pixels;
  int32_t x,y,w,h; 
  int32_t refCount;
} image_t;

#ifdef   __cplusplus
}
#endif

#endif