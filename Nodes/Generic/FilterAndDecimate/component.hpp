#pragma once

#include "dsp/filtering_functions.h"

template<typename IN,int inputSize,
         typename OUT,int outputSize>
class FilterAndDecimate;

template<typename IN,int inputSize,int outputSize>
class FilterAndDecimate<IN,inputSize,IN,outputSize>:
public GenericNode<IN,inputSize,
                   IN,outputSize>
{
public:
    FilterAndDecimate(FIFOBase<IN> &src,FIFOBase<IN> &dst,
        const int nbTaps,const q15_t *coefs):
    GenericNode<IN,inputSize,IN,outputSize>(src,dst),
    mNbTaps(nbTaps),
    mCoefs(coefs){

    pState = (q15_t*)malloc(sizeof(q15_t)*(mNbTaps+inputSize-1));

    arm_status status = arm_fir_decimate_init_q15(&S,
       mNbTaps,
       inputSize/outputSize,
       mCoefs,
       pState,
       inputSize 
    ) ;
    (void)status;

    };

    ~FilterAndDecimate(){
        free(pState);
    }

  
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
        IN *in = this->getReadBuffer();
        IN *out = this->getWriteBuffer();
        
        arm_fir_decimate_q15(&S,
        in,
        out,
        inputSize); 

        return(CG_SUCCESS);
    }
protected:
    const int mNbTaps;
    const q15_t *mCoefs;
    arm_fir_decimate_instance_q15 S;
    q15_t *     pState;
};