#pragma once 

#include "pico/util/queue.h"

template<typename OUT, int outputSize>
class FromOtherCore:
public GenericSource<OUT, outputSize>
{
public:
    FromOtherCore(FIFOBase<OUT> &dst,queue_t *queue,int blocking=0):
    GenericSource<OUT,outputSize>(dst),mQueue(queue),mBlocking(blocking==1){};

    // Used in asynchronous mode. In case of underflow on
    // the input, the execution of this node will be skipped
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
        OUT *b=this->getWriteBuffer();
        if (mBlocking)
        {
            queue_remove_blocking(mQueue,(void*)b);
        }
        else
        {
            bool res = queue_try_remove(mQueue,(void*)b);
            (void)res;
        }
        
        
        return(0);
    };
protected:
    queue_t *mQueue;
    bool mBlocking;
};