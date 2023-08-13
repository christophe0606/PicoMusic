#include "arm_2d.h"
#include "arm_extra_controls.h"
#include "arm_math_types.h"

typedef int32_t Q15_16;
#define TO_Q15_16(x) ((x)<<15)
#define TO_Q0(x) ((x+(1<<14))>>15)

static inline void __draw_line(arm_2d_tile_t *ptTile,Q15_16 dx, 
                               int32_t dy,
                               Q15_16 ax,
                               q15_t ay,
                               q15_t by)
    {
     arm_2d_location_t tLocation;

     if (abs(by-ay)<=1) {
       tLocation.iX = TO_Q0(ax);
       tLocation.iY = dy-ay;

       arm_2d_rgb16_draw_point_fast(ptTile,tLocation,GLCD_COLOR_BLUE);
       Q15_16 n = ax+dx;
       tLocation.iX = TO_Q0(n);
       tLocation.iY = dy-by;

       arm_2d_rgb16_draw_point_fast(ptTile,tLocation,GLCD_COLOR_BLUE);
     } else {
        Q15_16 refdelta = dx / (abs(by-ay));
        Q15_16 delta;
        Q15_16 x = ax;
        int start;
        int end;
        if (ay<by) {
            start = ay;
            end = by;
            delta = refdelta;
        } else {
            start = by;
            end = ay;
            x = ax + dx;
            delta= -refdelta;
        }
        for(int i=start;i<end;i++) {
            tLocation.iX = TO_Q0(x);
            tLocation.iY = dy-i;
            arm_2d_rgb16_draw_point_fast(ptTile,tLocation,GLCD_COLOR_BLUE);

            x += delta;
        }
     }
    }

void draw_amplitude(arm_2d_tile_t *ptTile,
                    q15_t *values,
                    int inputSize)
{
        int16_t iWidth  = ptTile->tRegion.tSize.iWidth;
        int16_t iHeight = ptTile->tRegion.tSize.iHeight;
        memset(ptTile->pchBuffer,0xFF,iWidth*iHeight*sizeof(uint16_t));

        Q15_16 dx = (int32_t)TO_Q15_16(1) * iWidth / inputSize;

        /* 0 Value is in middle of the graph.
            And 1 or -1 represents iHeight / 2
        */
        int32_t dy = iHeight >> 1; 

        Q15_16 currentX = 0;
        q15_t currentY = 0;
        currentY = (((q31_t) values[0] * ((iHeight>>1)-1)) >> 15);

        for(int i=1;i<inputSize;i++) {
            q15_t newY = (((q31_t) values[i] * ((iHeight>>1)-1)) >> 15);
            __draw_line(ptTile,dx,dy,currentX,currentY,newY);

            currentX = currentX + dx;
            currentY = newY;
        }

        draw_round_corner_border(   ptTile, 
                              &ptTile->tRegion, 
                                GLCD_COLOR_BLACK, 
                                (arm_2d_border_opacity_t)
                                {255,255,255,255},
                                (arm_2d_corner_opacity_t)
                                {255,255,255,255});
    
    arm_2d_op_wait_async(NULL);
}