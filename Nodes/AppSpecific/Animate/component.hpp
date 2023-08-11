#pragma once 

#include "stream_2d_layer.h"

template<typename IN, int inputSize,
         typename OUT,int outputSize>
class Animate;




template<>
class Animate<stream_2d_layer_t,1,
              stream_2d_layer_t,1>:
public GenericNode<stream_2d_layer_t,1,
                  stream_2d_layer_t,1>
{
public:
    /* Constructor needs the input and output FIFOs */
    Animate(FIFOBase<stream_2d_layer_t> &src,
            FIFOBase<stream_2d_layer_t> &dst):
    GenericNode<stream_2d_layer_t,1,
                stream_2d_layer_t,1>(src,dst)
    {
       float r = 30.0;
       nbPts = 25; 
       dx=(int16_t*)malloc(sizeof(int16_t)*nbPts);
       dy=(int16_t*)malloc(sizeof(int16_t)*nbPts);

       for(int i =0;i<nbPts;i++)
       {
          float x,y;
          x = (r*cos(2.0 * 3.14 * i / nbPts ));
          y = (r*sin(2.0 * 3.14 * i / nbPts));
          dx[i] = (int16_t)x;
          dy[i] = (int16_t)y;
       }
       index=0;
    };

    ~Animate(){
       free(dx);
       free(dy);
    }

    int prepareForRunning() final
    {
        if (this->willOverflow() ||
            this->willUnderflow())
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };
    
    
    int run() final{
        stream_2d_layer_t *a=this->getReadBuffer();
        stream_2d_layer_t *b=this->getWriteBuffer();


        b[0] = a[0];

        b[0].pos.iX = a[0].pos.iX + dx[index];
        b[0].pos.iY = a[0].pos.iY + dy[index];

        index++;
        if (index == nbPts)
        {
            index = 0;
        }
        return(0);
    };
protected:
    int16_t *dx;
    int16_t *dy;
    int nbPts;
    int index;
};
