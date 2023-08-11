#pragma once 

#include "stream_2d_layer.h"

template<typename OUT,int outputSize>
class CommonLayer;

template<>
class CommonLayer<stream_2d_layer_t,1>: 
public GenericSource<stream_2d_layer_t,1>
{
public:
    CommonLayer(FIFOBase<stream_2d_layer_t> &dst,
        int layer,
        int x,
        int y,
        uint16_t color, 
        int16_t alpha,
        bool copy_only_mode):
    GenericSource<stream_2d_layer_t,1>(dst){
        memset(&mLayer,0,sizeof(mLayer));

        mLayer.tile.tInfo.bIsRoot = true;
        mLayer.tile.tInfo.bHasEnforcedColour = true;
        mLayer.tile.tInfo.tColourInfo.chScheme = ARM_2D_COLOUR_RGB565;
   
        mLayer.layer=layer;
        mLayer.pos.iX=x; 
        mLayer.pos.iY=y; 

        mLayer.color=color; 
        mLayer.alpha=alpha; 

        if (copy_only_mode)
        {
            mLayer.copy_only_mode=1;
        }
        else
        {
            mLayer.copy_only_mode=0;
        }
    };

    ~CommonLayer() {
    }

    int prepareForRunning() final
    {
        if (this->willOverflow())
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };

    int run() final{
        stream_2d_layer_t *b=this->getWriteBuffer();
        b[0] = mLayer;

        return(0);
    };
protected:
    stream_2d_layer_t mLayer;

};

template<typename OUT,int outputSize>
class Layer;

template<>
class Layer<stream_2d_layer_t,1>: 
public CommonLayer<stream_2d_layer_t,1>
{
public:
    Layer(FIFOBase<stream_2d_layer_t> &dst,
        int layer,
        int x,
        int y,
        uint16_t color, 
        int16_t alpha,
        bool copy_only_mode,
        int width,
        int height):
    CommonLayer<stream_2d_layer_t,1>(dst,layer,x,y,color,alpha,copy_only_mode){
        
        mLayer.tile.tRegion = {
            .tSize = {(int16_t)(width), (int16_t)(height)},
        };

        mLayer.tile.pchBuffer = (uint8_t*)malloc(width*height*sizeof(uint16_t));
   
    };

    ~Layer() {
       free(mLayer.tile.pchBuffer);
    }

};

template<typename OUT,int outputSize>
class ROLayer;

template<>
class ROLayer<stream_2d_layer_t,1>: 
public CommonLayer<stream_2d_layer_t,1>
{
public:
    ROLayer(FIFOBase<stream_2d_layer_t> &dst,
        int layer,
        int x,
        int y,
        uint16_t color, 
        int16_t alpha,
        bool copy_only_mode,
        const arm_2d_tile_t* texture):
    CommonLayer<stream_2d_layer_t,1>(dst,layer,x,y,color,alpha,copy_only_mode){

        mLayer.tile = *texture;
  
    };

};


