#include "arm_2d.h"
#include "arm_extra_controls.h"
#include "arm_math_types.h"

#define BINWIDTH 1UL
#define PADX 4
#define PADY 0
#define PADFFT 6
void draw_spectrum(arm_2d_tile_t *ptTile,
	q15_t *fftSpectrum,
	int inputSize)
{
     int16_t iWidth  = ptTile->tRegion.tSize.iWidth;
     int16_t iHeight = ptTile->tRegion.tSize.iHeight;
     memset(ptTile->pchBuffer,0xFF,iWidth*iHeight*sizeof(uint16_t));


   
    iWidth -= 2*PADX;
    iHeight -= 2*PADY;
    

    
    draw_round_corner_box(  ptTile, 
                                    &ptTile->tRegion, 
                                    GLCD_COLOR_OLIVE, 
                                    70,
                                    1);

    arm_2d_op_wait_async(NULL);
    
    
    // Conjugate part ignored
    uint32_t nbPts=(inputSize);
    if (nbPts > 0)
    {
       // 0x40000000 / 8192 
       uint32_t dx = (0x20000UL / nbPts)*(iWidth-2*PADFFT);
       //printf("%x\n",dx);
       uint32_t max=fftSpectrum[0];
       uint32_t pos=0;
       uint32_t lastPixel = PADFFT;
       arm_2d_region_t bar;

       for(int i=0;i<nbPts;i++)
       {
          if (fftSpectrum[i]>max)
          {
            max = fftSpectrum[i];
          }
          pos += dx;
          uint32_t deltaPixel = (pos >> 17);
          if (deltaPixel >= BINWIDTH)
          {
             uint32_t dy = ((uint32_t)iHeight * max) / 32767; 
             if (dy>=iHeight)
             {
                dy = iHeight;
             }
             bar.tSize.iHeight=dy;
             bar.tSize.iWidth=deltaPixel;;
             bar.tLocation.iX = lastPixel;
             bar.tLocation.iY = iHeight-dy;

#if 0
             arm_2d_fill_colour_with_opacity(ptTarget, 
                                            &bar, 
                                            (__arm_2d_color_t) {GLCD_COLOR_RED},
                                            170);
#endif
             if (dy>0)
             {
                 arm_2d_fill_colour(ptTile, &bar, GLCD_COLOR_RED);
             }

             lastPixel += deltaPixel;
             pos = pos - (deltaPixel<<17);
             max = 0;
          }
       }
    }
    
    arm_2d_op_wait_async(NULL);

    
    draw_round_corner_border(   ptTile, 
                              &ptTile->tRegion, 
                                GLCD_COLOR_BLACK, 
                                (arm_2d_border_opacity_t)
                                {255,255,255,255},
                                (arm_2d_corner_opacity_t)
                                {255,255,255,255});
    
    arm_2d_op_wait_async(NULL);
    

}