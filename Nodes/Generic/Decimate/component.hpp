#pragma once

template<typename IN,int inputSize,
         typename OUT,int outputSize>
class Decimate;

template<typename IN,int inputSize,int outputSize>
class Decimate<IN,inputSize,IN,outputSize>:
public GenericNode<IN,inputSize,
                   IN,outputSize>
{
public:
    Decimate(FIFOBase<IN> &src,FIFOBase<IN> &dst):
    GenericNode<IN,inputSize,IN,outputSize>(src,dst){
        inc = inputSize / outputSize;
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
        IN *in = this->getReadBuffer();
        IN *out = this->getWriteBuffer();
        int i=0;
        int k=0;
        for(i=0;i<inputSize;i+=inc)
        {
            out[k]=in[i];
            k++;
        }

        return(CG_SUCCESS);
    }
protected:
    uint32_t inc;
};