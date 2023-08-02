#pragma once 

#include "dsp/basic_math_functions.h"
#include "dsp/support_functions.h"

template<typename IN, int inputSize,
         typename OUT,int outputSize>
class Gain;

template<int ioSize>
class Gain<q15_t,ioSize,
           q15_t,ioSize>:
public GenericNode<q15_t,ioSize,
                   q15_t,ioSize>
{
public:
    /* Constructor needs the input and output FIFOs */
    Gain(FIFOBase<q15_t> &src,
         FIFOBase<q15_t> &dst,float defaultGain=1.0):
    GenericNode<q15_t,ioSize,
                q15_t,ioSize>(src,dst){
       mutex_init(&my_mutex);

       setGain(defaultGain);

    };

    int prepareForRunning() final
    {
        if (this->willOverflow() ||
            this->willUnderflow())
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };
    
    
    __attribute__((section(".time_critical.Gain")))
    int run() final{
        q15_t *in=this->getReadBuffer();
        q15_t *out=this->getWriteBuffer();
        mutex_enter_blocking(&my_mutex);
        if (mGain != 1.0)
        {
           arm_scale_q15(in,mScale,mShift,out,ioSize);
        }
        else
        {
            memcpy(out,in,sizeof(q15_t)*ioSize);
        }
        mutex_exit(&my_mutex);
        return(CG_SUCCESS);
    };

    float getGain() const 
    {
       return(mGain);
    }

    void setGain(float gain)
    {
        mutex_enter_blocking(&my_mutex);
        mGain = gain;
        mShift=0;
        while(fabs(gain)>1.0)
        {
            gain /= 2.0f;
            mShift++;
        }
        arm_float_to_q15(&gain,&mScale,1);
        mutex_exit(&my_mutex);
    }

protected:
   float mGain;
   int mShift;
   q15_t mScale;
   mutex_t my_mutex;
};