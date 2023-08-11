#include "arm_2d.h"
#include "arm_extra_controls.h"
#include "arm_math_types.h"

void __draw_line(arm_2d_tile_t *ptTile,uint32_t dx, 
                     uint32_t dy,
                     uint32_t ax,
                     q15_t ay,
                     q15_t by)
    {
     arm_2d_location_t tLocation;

     if (abs(by-ay)<=1) {
       tLocation.iX = ax>>15;tLocation.iY=dy-ay;
       //arm_2d_rgb565_draw_point(ptTarget,tLocation,COLOR);
                   //printf("%d %d\n",tLocation.iX,tLocation.iY);

       arm_2d_rgb16_draw_point_fast(ptTile,tLocation,GLCD_COLOR_BLUE);
       uint32_t n=ax+dx;
       tLocation.iX = n>>15;tLocation.iY=dy-by;
       //arm_2d_rgb565_draw_point(ptTarget,tLocation,COLOR);
                  //printf("%d %d\n",tLocation.iX,tLocation.iY);

       arm_2d_rgb16_draw_point_fast(ptTile,tLocation,GLCD_COLOR_BLUE);
     } else {
        int32_t refdelta = dx / (abs(by-ay)+1);
        int32_t delta;
        uint32_t x = ax;
        int start;
        int end;
        if (ay<by) {
            start = ay;
            end = by;
            delta=refdelta;
        } else {
            start = by;
            end = ay;
            x = ax + dx;
            delta=-refdelta;
        }
        for(int i=start;i<end;i++) {
            tLocation.iX = x>>15;tLocation.iY=dy-i;
            //printf("%d %d\n",tLocation.iX,tLocation.iY);
            //arm_2d_rgb565_draw_point(ptTarget,tLocation,COLOR);
            arm_2d_rgb16_draw_point_fast(ptTile,tLocation,GLCD_COLOR_BLUE);

            x+=delta;
        }
     }
    }

void draw_amplitude(arm_2d_tile_t *ptTile,
	q15_t *values,
	int inputSize)
{
	/*
    draw_round_corner_box(ptTile, 
                             &ptTile->tRegion, 
                                GLCD_COLOR_OLIVE, 
                                127,
                                1);
*/
        int16_t iWidth  = ptTile->tRegion.tSize.iWidth;
        int16_t iHeight = ptTile->tRegion.tSize.iHeight;
        memset(ptTile->pchBuffer,0xFF,iWidth*iHeight*sizeof(uint16_t));

        uint32_t dx = (uint32_t)(1<<15) * iWidth / inputSize;
        uint32_t dy= iHeight >> 1; 

        uint32_t currentX= 0;
        q15_t currentY=0;
        currentY = (((q31_t) values[0] * ((iHeight>>1)-1)) >> 15);

        /* draw bar buffer */
        for(int i=1;i<inputSize;i++) {
            q15_t newY = (((q31_t) values[i] * ((iHeight>>1)-1)) >> 15);
            __draw_line(ptTile,dx,dy,currentX,currentY,newY);

            currentX = currentX+dx;
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