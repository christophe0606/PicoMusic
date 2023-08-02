#pragma once

#include "pico/util/queue.h"

template<typename IN, int inputSize>
class ToOtherCore:public GenericSink<IN, inputSize>
{
public:
    ToOtherCore(FIFOBase<IN> &src,queue_t *queue,int blocking=0):
    GenericSink<IN,inputSize>(src),mQueue(queue),mBlocking(blocking==1){};

    // Used in asynchronous mode. In case of underflow on
    // the input, the execution of this node will be skipped
    int prepareForRunning() final
    {
        if (this->willUnderflow())
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };

    __attribute__((section(".time_critical.ToOtherCore")))
    int run() final
    {
        IN *b=this->getReadBuffer();
        /* Non blocking add */
        if (mBlocking)
        {
            queue_add_blocking(mQueue,(void*)b);
        }
        else
        {
            bool res = queue_try_add(mQueue,(void*)b);
            (void)res;
        }
     
        return(0);
    };
protected:
    queue_t *mQueue;
    bool mBlocking;
};
