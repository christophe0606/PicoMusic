#pragma once 

#include "hardware/interp.h"

template<typename IN1,int inputSize1,
         typename IN2,int inputSize2,
         typename OUT,int outputSize>
class BlockWidget;

template<int inputSize>
class BlockWidget<image_t,1,q15_t,inputSize,image_t,1>:
public GenericNode21<image_t,1,q15_t,inputSize,image_t,1>
{
public:
    BlockWidget(FIFOBase<image_t> &src1,
              FIFOBase<q15_t> &src2,
              FIFOBase<image_t> &dst,
              int y=0,int col=0):
    GenericNode21<image_t,1,q15_t,inputSize,image_t,1>(src1,src2,dst),
    mYPos(y),mCol(col){
        dx = (uint32_t)(1<<15) * 240 / inputSize;

        interp_config cfg = interp_default_config();
        interp_config_set_blend(&cfg, true);
        interp_set_config(interp0, 0, &cfg);
    
        cfg = interp_default_config();
        interp_set_config(interp0, 1, &cfg);

        interp0->accum[1] = 127;
    }

    int prepareForRunning() final
    {
        if (this->willOverflow() ||
            this->willUnderflow1() ||
            this->willUnderflow2())
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };
    int run() final{
        q15_t *in = this->getReadBuffer2();
        image_t *img=this->getReadBuffer1();
        image_t *b=this->getWriteBuffer();


        b[0] = img[0];
        uint32_t pixel=0;
        int lastPos=0;

        
        for(int i=0;i<inputSize;i++)
        {
            int pos = pixel >> 15;

            // >> 16 because half scale of LCD
            q15_t r = (q15_t) __SSAT((((q31_t) in[i] * img[0].h) >> 16), 16);
            if (r<0)
            {
                r=-r;
            }
            for(int k=lastPos+1;k<=pos && k<240;k++)
            {
               for(int v=0;v<=r;v++)
               {
                  q15_t y = img[0].h-1-(v+mYPos); 
                  if (y<0)
                  {
                    y=0;
                  }
                  if (y>=240)
                  {
                    y=239;
                  }
                  int rs,gs,bs;
                  int rd,gd,bd;
                  int srcCol = img[0].pixels[k+img[0].w*y];

                  bs = (srcCol) & 0x1F;
                  gs = (srcCol>>5) & 0x3F;
                  rs = (srcCol>>11) & 0x1F;

                  bd = (mCol) & 0x1F;
                  gd = (mCol>>5) & 0x3F;
                  rd = (mCol>>11) & 0x1F;

                  interp0->base[0] = bs<<11;
                  interp0->base[1] = bd<<11;
                  bd = (interp0->peek[1]>>11) & 0x1F;

                  interp0->base[0] = gs<<10;
                  interp0->base[1] = gd<<10;
                  gd = (interp0->peek[1]>>10) & 0x3F;

                  interp0->base[0] = rs<<11;
                  interp0->base[1] = rd<<11;
                  rd = (interp0->peek[1]>>11) & 0x1F;

                  //mCol = (rd << 11) | (gd << 5) | bd;

                  img[0].pixels[k+img[0].w*y] = (rd << 11) | (gd << 5) | bd;
               }
            }
            lastPos = pos;

            pixel += dx;
        }
        
        
        return(0);
    };
protected:
    uint32_t dx;
    int mYPos;
    int mCol;
    interp_config cfg;
};