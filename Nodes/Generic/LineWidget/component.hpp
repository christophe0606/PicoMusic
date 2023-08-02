#pragma once 

template<typename IN1,int inputSize1,
         typename IN2,int inputSize2,
         typename OUT,int outputSize>
class LineWidget;

template<int inputSize>
class LineWidget<image_t,1,q15_t,inputSize,image_t,1>:
public GenericNode21<image_t,1,q15_t,inputSize,image_t,1>
{
public:
    LineWidget(FIFOBase<image_t> &src1,
              FIFOBase<q15_t> &src2,
              FIFOBase<image_t> &dst,
              int y=0,int col=0):
    GenericNode21<image_t,1,q15_t,inputSize,image_t,1>(src1,src2,dst),
    mYPos(y),mCol(col){
        dx = (uint32_t)(1<<15) * 240 / inputSize;
    }

    int prepareForRunning() final
    {
        if (this->willOverflow() ||
            this->willUnderflow1() ||
            this->willUnderflow2())
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };

    void drawPoint(image_t *img,uint32_t x,q15_t y)
    {
        int i = x >> 15;
        int j = img[0].h - (y + mYPos + (img[0].h>>2));
        if (j<0)
        {
            j=0;
        }
        if (j>=img[0].h)
        {
            j=img[0].h-1;
        }

        if (i<0)
        {
            i=0;
        }
        if (i>=img[0].w)
        {
            i=img[0].w-1;
        }

        img[0].pixels[i+img[0].w*j] = mCol;
    }

    void drawLine(image_t *img,uint32_t ax,q15_t ay,q15_t by)
    {

         if (abs(by-ay)<=1)
         {
           drawPoint(img,ax,ay);
           drawPoint(img,ax+dx,by);
         }
         else
         {
            uint32_t delta = dx / abs(by-ay+1);
            uint32_t x = ax;
            int start;
            int end;
            if (ay<by)
            {
                start = ay;
                end = by;
            }
            else
            {
                start = by;
                end = ay;
            }
            for(int i=start;i<=end;i++)
            {
                drawPoint(img,x,i);
                x+=delta;
            }
         }
    }

    int run() final{
        q15_t *in = this->getReadBuffer2();
        image_t *img=this->getReadBuffer1();
        image_t *b=this->getWriteBuffer();


        b[0] = img[0];
        uint32_t currentX=0;
        q15_t currentY=0;
        currentY = (q15_t) __SSAT((((q31_t) in[0] * img[0].h) >> 17), 16);

        
        
        for(int i=1;i<inputSize;i++)
        {
            // >> 16 because half scale of LCD
            q15_t newY = (q15_t) __SSAT((((q31_t) in[i] * img[0].h) >> 17), 16);
            
            drawLine(img,currentX,currentY,newY);
                  
            currentX = currentX+dx;
            currentY = newY;
        }
        
        
        return(0);
    };
protected:
    uint32_t dx;
    int mYPos;
    int mCol;
};