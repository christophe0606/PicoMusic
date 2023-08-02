/*

Generated with CMSIS-Stream python scripts.
The generated code is not covered by CMSIS-Stream license.

The support classes and code are covered by CMSIS-Stream license.

*/


#include "arm_math.h"
#include "lcd_graph_config.h"
#include "GenericNodes.h"
#include "cg_status.h"
#include "LCDGraphNodes.h"
#include "lcd_scheduler.h"

#if !defined(CHECKERROR)
#define CHECKERROR       if (cgStaticError < 0) \
       {\
         goto errorHandling;\
       }

#endif

#if !defined(CG_BEFORE_ITERATION)
#define CG_BEFORE_ITERATION
#endif 

#if !defined(CG_AFTER_ITERATION)
#define CG_AFTER_ITERATION
#endif 

#if !defined(CG_BEFORE_SCHEDULE)
#define CG_BEFORE_SCHEDULE
#endif

#if !defined(CG_AFTER_SCHEDULE)
#define CG_AFTER_SCHEDULE
#endif

#if !defined(CG_BEFORE_BUFFER)
#define CG_BEFORE_BUFFER
#endif

#if !defined(CG_BEFORE_FIFO_BUFFERS)
#define CG_BEFORE_FIFO_BUFFERS
#endif

#if !defined(CG_BEFORE_FIFO_INIT)
#define CG_BEFORE_FIFO_INIT
#endif

#if !defined(CG_BEFORE_NODE_INIT)
#define CG_BEFORE_NODE_INIT
#endif

#if !defined(CG_AFTER_INCLUDES)
#define CG_AFTER_INCLUDES
#endif

#if !defined(CG_BEFORE_SCHEDULER_FUNCTION)
#define CG_BEFORE_SCHEDULER_FUNCTION
#endif

#if !defined(CG_BEFORE_NODE_EXECUTION)
#define CG_BEFORE_NODE_EXECUTION
#endif

#if !defined(CG_AFTER_NODE_EXECUTION)
#define CG_AFTER_NODE_EXECUTION
#endif



CG_AFTER_INCLUDES


/*

Description of the scheduling. 

*/
static uint8_t schedule[136]=
{ 
7,3,6,4,5,3,6,4,5,3,6,4,5,3,6,4,5,3,6,4,5,3,6,4,5,3,6,4,5,3,6,4,5,3,6,4,5,3,6,4,
5,3,6,4,5,3,6,4,5,3,6,4,5,3,6,4,5,3,6,4,5,3,6,4,5,3,6,4,5,3,6,4,5,3,6,4,5,3,6,4,
5,3,6,4,5,3,6,4,5,3,6,4,5,3,6,4,5,3,6,4,5,3,6,4,5,3,6,4,5,3,6,4,5,3,6,4,5,3,6,4,
5,3,6,4,5,3,6,4,1,5,2,11,8,9,0,10,
};

/***********

Node identification

************/
static void * identifiedNodes[LCD_NB_IDENTIFIED_NODES]={0};

CG_BEFORE_FIFO_BUFFERS
/***********

FIFO buffers

************/
#define FIFOSIZE0 256
#define FIFOSIZE1 1
#define FIFOSIZE2 256
#define FIFOSIZE3 256
#define FIFOSIZE4 512
#define FIFOSIZE5 512
#define FIFOSIZE6 256
#define FIFOSIZE7 1
#define FIFOSIZE8 1
#define FIFOSIZE9 128
#define FIFOSIZE10 128
#define FIFOSIZE11 128

#define BUFFERSIZE0 256
CG_BEFORE_BUFFER
uint8_t lcd_buf0[BUFFERSIZE0]={0};

#define BUFFERSIZE1 1024
CG_BEFORE_BUFFER
uint8_t lcd_buf1[BUFFERSIZE1]={0};

#define BUFFERSIZE2 1024
CG_BEFORE_BUFFER
uint8_t lcd_buf2[BUFFERSIZE2]={0};

#define BUFFERSIZE3 256
CG_BEFORE_BUFFER
uint8_t lcd_buf3[BUFFERSIZE3]={0};

#define BUFFERSIZE4 256
CG_BEFORE_BUFFER
q15_t lcd_buf4[BUFFERSIZE4]={0};

#define BUFFERSIZE5 256
CG_BEFORE_BUFFER
q15_t lcd_buf5[BUFFERSIZE5]={0};


typedef struct {
FIFO<q15_t,FIFOSIZE0,0,0> *fifo0;
FIFO<image_t,FIFOSIZE1,1,0> *fifo1;
FIFO<q15_t,FIFOSIZE2,0,0> *fifo2;
FIFO<q15_t,FIFOSIZE3,1,0> *fifo3;
FIFO<q15_t,FIFOSIZE4,1,0> *fifo4;
FIFO<q15_t,FIFOSIZE5,1,0> *fifo5;
FIFO<q15_t,FIFOSIZE6,1,0> *fifo6;
FIFO<image_t,FIFOSIZE7,1,0> *fifo7;
FIFO<image_t,FIFOSIZE8,1,0> *fifo8;
FIFO<q15_t,FIFOSIZE9,1,0> *fifo9;
FIFO<q15_t,FIFOSIZE10,1,0> *fifo10;
FIFO<q15_t,FIFOSIZE11,1,0> *fifo11;
} fifos_t;

typedef struct {
    BlockWidget<image_t,1,q15_t,256,image_t,1> *FFTW;
    LineWidget<image_t,1,q15_t,256,image_t,1> *ampW;
    FromOtherCore<q15_t,128> *core0;
    FilterAndDecimate<q15_t,128,q15_t,8> *decimateAmp;
    FilterAndDecimate<q15_t,128,q15_t,8> *decimateFFT;
    Duplicate<q15_t,128,q15_t,128> *dup0;
    ImageBuffer<image_t,1> *fb;
    CFFT<q15_t,512,q15_t,512> *fft;
    FFTAmplitude<q15_t,512,q15_t,256> *fftMag;
    LCD<image_t,1> *lcd;
    ToComplex<q15_t,256,q15_t,512> *toCmplx;
} nodes_t;

CG_BEFORE_BUFFER
static fifos_t fifos={0};

CG_BEFORE_BUFFER
static nodes_t nodes={0};

void *get_lcd_scheduler_node(int32_t nodeID)
{
    if (nodeID >= LCD_NB_IDENTIFIED_NODES)
    {
        return(NULL);
    }
    if (nodeID < 0)
    {
        return(NULL);
    }
    return(identifiedNodes[nodeID]);
}

int init_lcd_scheduler(queue_t *audio_queue,
                              const q15_t* cmsis_texture,
                              const int nbTaps,
                              const q15_t* coefs)
{
    CG_BEFORE_FIFO_INIT;
    fifos.fifo0 = new FIFO<q15_t,FIFOSIZE0,0,0>(lcd_buf4);
    if (fifos.fifo0==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo1 = new FIFO<image_t,FIFOSIZE1,1,0>(lcd_buf1);
    if (fifos.fifo1==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo2 = new FIFO<q15_t,FIFOSIZE2,0,0>(lcd_buf5);
    if (fifos.fifo2==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo3 = new FIFO<q15_t,FIFOSIZE3,1,0>(lcd_buf2);
    if (fifos.fifo3==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo4 = new FIFO<q15_t,FIFOSIZE4,1,0>(lcd_buf1);
    if (fifos.fifo4==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo5 = new FIFO<q15_t,FIFOSIZE5,1,0>(lcd_buf2);
    if (fifos.fifo5==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo6 = new FIFO<q15_t,FIFOSIZE6,1,0>(lcd_buf1);
    if (fifos.fifo6==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo7 = new FIFO<image_t,FIFOSIZE7,1,0>(lcd_buf0);
    if (fifos.fifo7==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo8 = new FIFO<image_t,FIFOSIZE8,1,0>(lcd_buf2);
    if (fifos.fifo8==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo9 = new FIFO<q15_t,FIFOSIZE9,1,0>(lcd_buf0);
    if (fifos.fifo9==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo10 = new FIFO<q15_t,FIFOSIZE10,1,0>(lcd_buf3);
    if (fifos.fifo10==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo11 = new FIFO<q15_t,FIFOSIZE11,1,0>(lcd_buf2);
    if (fifos.fifo11==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }

    CG_BEFORE_NODE_INIT;
    nodes.FFTW = new BlockWidget<image_t,1,q15_t,256,image_t,1>(*(fifos.fifo7),*(fifos.fifo6),*(fifos.fifo8),120,63488);
    if (nodes.FFTW==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[LCD_FFTW_ID]=(void*)nodes.FFTW;
    nodes.FFTW->setID(LCD_FFTW_ID);
    nodes.ampW = new LineWidget<image_t,1,q15_t,256,image_t,1>(*(fifos.fifo1),*(fifos.fifo0),*(fifos.fifo7),0,31);
    if (nodes.ampW==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[LCD_AMPW_ID]=(void*)nodes.ampW;
    nodes.ampW->setID(LCD_AMPW_ID);
    nodes.core0 = new FromOtherCore<q15_t,128>(*(fifos.fifo9),audio_queue,1);
    if (nodes.core0==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[LCD_CORE0_ID]=(void*)nodes.core0;
    nodes.core0->setID(LCD_CORE0_ID);
    nodes.decimateAmp = new FilterAndDecimate<q15_t,128,q15_t,8>(*(fifos.fifo10),*(fifos.fifo0),nbTaps,coefs);
    if (nodes.decimateAmp==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[LCD_DECIMATEAMP_ID]=(void*)nodes.decimateAmp;
    nodes.decimateAmp->setID(LCD_DECIMATEAMP_ID);
    nodes.decimateFFT = new FilterAndDecimate<q15_t,128,q15_t,8>(*(fifos.fifo11),*(fifos.fifo2),nbTaps,coefs);
    if (nodes.decimateFFT==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[LCD_DECIMATEFFT_ID]=(void*)nodes.decimateFFT;
    nodes.decimateFFT->setID(LCD_DECIMATEFFT_ID);
    nodes.dup0 = new Duplicate<q15_t,128,q15_t,128>(*(fifos.fifo9),{fifos.fifo10,fifos.fifo11});
    if (nodes.dup0==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.fb = new ImageBuffer<image_t,1>(*(fifos.fifo1),240,240,cmsis_texture,99,240);
    if (nodes.fb==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[LCD_FB_ID]=(void*)nodes.fb;
    nodes.fb->setID(LCD_FB_ID);
    nodes.fft = new CFFT<q15_t,512,q15_t,512>(*(fifos.fifo4),*(fifos.fifo5));
    if (nodes.fft==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[LCD_FFT_ID]=(void*)nodes.fft;
    nodes.fft->setID(LCD_FFT_ID);
    nodes.fftMag = new FFTAmplitude<q15_t,512,q15_t,256>(*(fifos.fifo5),*(fifos.fifo6));
    if (nodes.fftMag==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[LCD_FFTMAG_ID]=(void*)nodes.fftMag;
    nodes.fftMag->setID(LCD_FFTMAG_ID);
    nodes.lcd = new LCD<image_t,1>(*(fifos.fifo8));
    if (nodes.lcd==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[LCD_LCD_ID]=(void*)nodes.lcd;
    nodes.lcd->setID(LCD_LCD_ID);
    nodes.toCmplx = new ToComplex<q15_t,256,q15_t,512>(*(fifos.fifo3),*(fifos.fifo4));
    if (nodes.toCmplx==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[LCD_TOCMPLX_ID]=(void*)nodes.toCmplx;
    nodes.toCmplx->setID(LCD_TOCMPLX_ID);

    return(CG_SUCCESS);

}

void free_lcd_scheduler(queue_t *audio_queue,
                              const q15_t* cmsis_texture,
                              const int nbTaps,
                              const q15_t* coefs)
{
    if (fifos.fifo0!=NULL)
    {
       delete fifos.fifo0;
    }
    if (fifos.fifo1!=NULL)
    {
       delete fifos.fifo1;
    }
    if (fifos.fifo2!=NULL)
    {
       delete fifos.fifo2;
    }
    if (fifos.fifo3!=NULL)
    {
       delete fifos.fifo3;
    }
    if (fifos.fifo4!=NULL)
    {
       delete fifos.fifo4;
    }
    if (fifos.fifo5!=NULL)
    {
       delete fifos.fifo5;
    }
    if (fifos.fifo6!=NULL)
    {
       delete fifos.fifo6;
    }
    if (fifos.fifo7!=NULL)
    {
       delete fifos.fifo7;
    }
    if (fifos.fifo8!=NULL)
    {
       delete fifos.fifo8;
    }
    if (fifos.fifo9!=NULL)
    {
       delete fifos.fifo9;
    }
    if (fifos.fifo10!=NULL)
    {
       delete fifos.fifo10;
    }
    if (fifos.fifo11!=NULL)
    {
       delete fifos.fifo11;
    }

    if (nodes.FFTW!=NULL)
    {
        delete nodes.FFTW;
    }
    if (nodes.ampW!=NULL)
    {
        delete nodes.ampW;
    }
    if (nodes.core0!=NULL)
    {
        delete nodes.core0;
    }
    if (nodes.decimateAmp!=NULL)
    {
        delete nodes.decimateAmp;
    }
    if (nodes.decimateFFT!=NULL)
    {
        delete nodes.decimateFFT;
    }
    if (nodes.dup0!=NULL)
    {
        delete nodes.dup0;
    }
    if (nodes.fb!=NULL)
    {
        delete nodes.fb;
    }
    if (nodes.fft!=NULL)
    {
        delete nodes.fft;
    }
    if (nodes.fftMag!=NULL)
    {
        delete nodes.fftMag;
    }
    if (nodes.lcd!=NULL)
    {
        delete nodes.lcd;
    }
    if (nodes.toCmplx!=NULL)
    {
        delete nodes.toCmplx;
    }
}


CG_BEFORE_SCHEDULER_FUNCTION
uint32_t lcd_scheduler(int *error,queue_t *audio_queue,
                              const q15_t* cmsis_texture,
                              const int nbTaps,
                              const q15_t* coefs)
{
    int cgStaticError=0;
    uint32_t nbSchedule=0;


    /* Run several schedule iterations */
    CG_BEFORE_SCHEDULE;
    while(cgStaticError==0)
    {
        /* Run a schedule iteration */
        CG_BEFORE_ITERATION;
        for(unsigned long id=0 ; id < 136; id++)
        {
            CG_BEFORE_NODE_EXECUTION;

            switch(schedule[id])
            {
                case 0:
                {
                   cgStaticError = nodes.FFTW->run();
                }
                break;

                case 1:
                {
                   cgStaticError = nodes.ampW->run();
                }
                break;

                case 2:
                {
                   
                  {

                   q15_t* i0;
                   q15_t* o2;
                   i0=fifos.fifo2->getReadBuffer(256);
                   o2=fifos.fifo3->getWriteBuffer(256);
                   arm_mult_q15(i0,hanningQ15,o2,256);
                   cgStaticError = 0;
                  }
                }
                break;

                case 3:
                {
                   cgStaticError = nodes.core0->run();
                }
                break;

                case 4:
                {
                   cgStaticError = nodes.decimateAmp->run();
                }
                break;

                case 5:
                {
                   cgStaticError = nodes.decimateFFT->run();
                }
                break;

                case 6:
                {
                   cgStaticError = nodes.dup0->run();
                }
                break;

                case 7:
                {
                   cgStaticError = nodes.fb->run();
                }
                break;

                case 8:
                {
                   cgStaticError = nodes.fft->run();
                }
                break;

                case 9:
                {
                   cgStaticError = nodes.fftMag->run();
                }
                break;

                case 10:
                {
                   cgStaticError = nodes.lcd->run();
                }
                break;

                case 11:
                {
                   cgStaticError = nodes.toCmplx->run();
                }
                break;

                default:
                break;
            }
            CG_AFTER_NODE_EXECUTION;
            CHECKERROR;
        }
       CG_AFTER_ITERATION;
       nbSchedule++;
    }

errorHandling:
    CG_AFTER_SCHEDULE;
    *error=cgStaticError;
    return(nbSchedule);
}
