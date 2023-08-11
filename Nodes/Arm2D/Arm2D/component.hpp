#pragma once 

#ifdef HOST
#include "Virtual_TFT_Port.h"
#endif 

#include "stream_2d_layer.h"
#include "arm_2d_scene_cmsis_stream.h"

#include <algorithm>


template<typename IN, int inputSize>
class Arm2D;

struct
{
        bool operator()(stream_2d_layer_t *a, stream_2d_layer_t *b) const 
        { 
            return (a->layer < b->layer); 
        }
}
layerBelow;

template<>
class Arm2D<stream_2d_layer_t,1>:public NodeBase
{
public:
    Arm2D(std::initializer_list<FIFOBase<stream_2d_layer_t>*> src):
    mSrcList(src)
    {
        mArm2DList = std::vector<stream_2d_layer_t*>{src.size(),NULL};

        mScene = (user_scene_cmsis_stream_t *)malloc(sizeof(user_scene_cmsis_stream_t));
        scene_cmsis_stream_loader(mScene);
        
    };

    ~Arm2D()
    {
       free(mScene);
    }

    // Used in asynchronous mode. In case of underflow on
    // the input, the execution of this node will be skipped
    int prepareForRunning() final
    {
        if (this->willUnderflow())
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(CG_SUCCESS);
    };

    void update_tiles()
    {
        if (mScene)
        {
            for(int i=0;i<numberOfReadBuffers();i++)
            {
                // This is valid only until the FIFO is updated again
                // so the graph must control the Arm2D refresh
                // to be sure than Arm2D can work on those
                // addresses
                mArm2DList[i]=getReadBuffer(i);
            }
            std::sort(mArm2DList.begin(),mArm2DList.end(),layerBelow);
            
            arm2d_scene_cmsis_stream_new_layers(mScene,
                mArm2DList.data(),numberOfReadBuffers());
        }
    }

#ifdef HOST
    int run() final
    {
        wait_for_display();
        VT_sdl_flush(1);
        update_tiles();
        
        return(CG_SUCCESS);
    };
#else 

    int run() final
    {
        wait_for_display();
        update_tiles();
        return(CG_SUCCESS);
    };
#endif

protected:
    user_scene_cmsis_stream_t *mScene;
private:
  std::vector<FIFOBase<stream_2d_layer_t>*> mSrcList;
  std::vector<stream_2d_layer_t*> mArm2DList;

  stream_2d_layer_t*getReadBuffer(int id=1){return mSrcList[id]->getReadBuffer(1);};
  bool willUnderflow(int id=1){return mSrcList[id]->willUnderflowWith(1);};
  
  int numberOfReadBuffers(){return mSrcList.size();};

};
