#pragma once

#include "dsp/basic_math_functions.h"
#include "dsp/complex_math_functions.h"

template<typename IN,int inputSize,
         typename OUT,int outputSize>
class FFTAmplitude;

/* FFT spectrum in complex to half FFT amplitude
because the conjugate part is ignored.
*/
template<int ioSize>
class FFTAmplitude<q15_t,4*ioSize,q15_t,ioSize>:
public GenericNode<q15_t,4*ioSize,
                   q15_t,ioSize>
{
public:
    FFTAmplitude(FIFOBase<q15_t> &src,FIFOBase<q15_t> &dst):
    GenericNode<q15_t,4*ioSize,q15_t,ioSize>(src,dst){
    };

  
    int prepareForRunning() final
    {
        if (this->willOverflow())
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };
 
    int run() final
    {
        q15_t *in = this->getReadBuffer();
        q15_t *out = this->getWriteBuffer();
        
        arm_cmplx_mag_q15(in,out,ioSize);
        arm_shift_q15(out,6,in,ioSize);
        /* Remove conjugate part */
        for(int i=0;i<ioSize;i++)
        {
             out[2*i] = in[i];
             out[2*i+1] = in[i];
        }
        
        return(CG_SUCCESS);
    }

};