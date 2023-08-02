#pragma once 

template<typename OUT,int outputSize>
class ImageBuffer;

template<>
class ImageBuffer<image_t,1>:
public GenericSource<image_t,1>
{
public:
    ImageBuffer(FIFOBase<image_t> &dst,
        int width,
        int height,
        const q15_t*texture=NULL,
        int texture_width=0,
        int texture_height=0):
    GenericSource<image_t,1>(dst),mTexture(texture),
    mTextureWidth(texture_width),
    mTextureHeight(texture_height){
        
        q15_t* buf = (q15_t*)malloc(sizeof(q15_t)*width*height);
        memset(&img,0,sizeof(image_t));

        img.pixels = buf;
        img.x=0;
        img.y=0;
        img.w=width;
        img.h=height; 
        img.refCount=1;

        //mDstX = (img.w - mTextureWidth)>>1;
        mDstX = img.w - mTextureWidth-1;
        mDstY = (img.h - mTextureHeight)>>1;

        translationDX = 5;
        translationX=0;
    };

    ~ImageBuffer()
    {
        free(img.pixels);
    }

    int prepareForRunning() final
    {
        if (this->willOverflow())
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };

    __attribute__((section(".time_critical.MIDISeq")))
    int run() final{
        image_t *b=this->getWriteBuffer();
        memset(img.pixels,0xFF,sizeof(q15_t)*img.w*img.h);
        if (mTexture)
        {
           q15_t *pDst = img.pixels;
           const q15_t *pSrc = mTexture;

           pDst = pDst + translationX;
           pDst += img.w * mDstY;
           for(int y=0;y<mTextureHeight;y++)
           {
              memcpy(pDst,pSrc,sizeof(q15_t)*mTextureWidth);
              pSrc += mTextureWidth;
              pDst += img.w;
           }
        }

        translationX += translationDX;
        if (translationX>mDstX)
        {
            translationX -= translationDX;
            translationDX = -translationDX;
        }
        if (translationX<0)
        {
            translationX -= translationDX;
            translationDX = -translationDX;
        }

        

        b[0] = img;
        
        return(0);
    };
protected:
    image_t img;
    const q15_t *mTexture;
    const int mTextureWidth;
    const int mTextureHeight;
    int mDstX,mDstY;
    int translationX;
    int translationDX;
};

