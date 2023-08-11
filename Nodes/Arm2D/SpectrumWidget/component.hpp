#pragma once 

extern "C" {
#include "stream_2d_layer.h"
}

template<typename INA, int inputSizeA,
         typename INB, int inputSizeB,
         typename OUT,int outputSize>
class SpectrumWidget;

extern "C" {
extern void draw_spectrum(arm_2d_tile_t *ptTile,
    q15_t *fftSpectrum,
    int inputSize);

}
template<int inputSize>
class SpectrumWidget<int16_t,inputSize,
                     stream_2d_layer_t,1,
                     stream_2d_layer_t,1>:
public GenericNode21<int16_t,inputSize,
                   stream_2d_layer_t,1,
                   stream_2d_layer_t,1>
{
public:
    /* Constructor needs the input and output FIFOs */
    SpectrumWidget(FIFOBase<int16_t> &srcA,
                   FIFOBase<stream_2d_layer_t> &srcB,
                   FIFOBase<stream_2d_layer_t> &dst):
    GenericNode21<int16_t,inputSize,
                stream_2d_layer_t,1,
                stream_2d_layer_t,1>(srcA,srcB,dst){}

   
    int prepareForRunning() final
    {
        if (this->willOverflow() ||
            this->willUnderflow1() || 
            this->willUnderflow2())
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(CG_SUCCESS);
    };

    
    
    
    int run() final{
        int16_t *values=this->getReadBuffer1();
        stream_2d_layer_t*il=this->getReadBuffer2();
        stream_2d_layer_t*ol=this->getWriteBuffer();

        draw_spectrum(&il[0].tile,values,inputSize);

        ol[0]= il[0];
        return(CG_SUCCESS);
    };
};
