#pragma once

#include "CFFT.h"
#include "dsp/transform_functions.h"


template<>
class CFFT<q15_t,512,
           q15_t,512>: 
public GenericNode<q15_t,512,
                   q15_t,512>
{
public:
    CFFT(FIFOBase<q15_t> &src,FIFOBase<q15_t> &dst):
    GenericNode<q15_t,512,
                q15_t,512>(src,dst){
         status=arm_cfft_init_256_q15(&sfft);
    };

    int prepareForRunning() final
    {
        if (this->willOverflow() ||
            this->willUnderflow()
           )
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(CG_SUCCESS);
    };
    
    int run() final
    {
        if (status!=ARM_MATH_SUCCESS)
        {
            return(CG_INIT_FAILURE);
        }
        q15_t *a=this->getReadBuffer();
        q15_t *b=this->getWriteBuffer();
        memcpy((void*)b,(void*)a,512*sizeof(q15_t));
        arm_cfft_q15(&sfft,b,0,1);
        return(CG_SUCCESS);
    };

    arm_cfft_instance_q15 sfft;
    arm_status status;

};