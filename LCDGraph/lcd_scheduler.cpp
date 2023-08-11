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
static uint8_t schedule[139]=
{ 
2,5,3,11,6,9,7,8,6,9,7,8,6,9,7,8,6,9,7,8,6,9,7,8,6,9,7,8,6,9,7,8,6,9,7,8,6,9,7,8,
6,9,7,8,6,9,7,8,6,9,7,8,6,9,7,8,6,9,7,8,6,9,7,8,6,9,7,8,6,9,7,8,6,9,7,8,6,9,7,8,
6,9,7,8,6,9,7,8,6,9,7,8,6,9,7,8,6,9,7,8,6,9,7,8,6,9,7,8,6,9,7,8,6,9,7,8,6,9,7,8,
6,9,7,8,6,9,7,8,6,9,7,1,8,4,14,10,12,13,0,
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
#define FIFOSIZE1 256
#define FIFOSIZE2 256
#define FIFOSIZE3 512
#define FIFOSIZE4 512
#define FIFOSIZE5 128
#define FIFOSIZE6 1
#define FIFOSIZE7 1
#define FIFOSIZE8 1
#define FIFOSIZE9 1
#define FIFOSIZE10 1
#define FIFOSIZE11 1
#define FIFOSIZE12 128
#define FIFOSIZE13 128
#define FIFOSIZE14 128

#define BUFFERSIZE0 36
CG_BEFORE_BUFFER
uint8_t lcd_buf0[BUFFERSIZE0]={0};

#define BUFFERSIZE1 36
CG_BEFORE_BUFFER
uint8_t lcd_buf1[BUFFERSIZE1]={0};

#define BUFFERSIZE2 256
CG_BEFORE_BUFFER
uint8_t lcd_buf2[BUFFERSIZE2]={0};

#define BUFFERSIZE3 1024
CG_BEFORE_BUFFER
uint8_t lcd_buf3[BUFFERSIZE3]={0};

#define BUFFERSIZE4 1024
CG_BEFORE_BUFFER
uint8_t lcd_buf4[BUFFERSIZE4]={0};

#define BUFFERSIZE5 256
CG_BEFORE_BUFFER
uint8_t lcd_buf5[BUFFERSIZE5]={0};

#define BUFFERSIZE6 256
CG_BEFORE_BUFFER
q15_t lcd_buf6[BUFFERSIZE6]={0};

#define BUFFERSIZE7 256
CG_BEFORE_BUFFER
q15_t lcd_buf7[BUFFERSIZE7]={0};


typedef struct {
FIFO<q15_t,FIFOSIZE0,0,0> *fifo0;
FIFO<q15_t,FIFOSIZE1,0,0> *fifo1;
FIFO<q15_t,FIFOSIZE2,1,0> *fifo2;
FIFO<q15_t,FIFOSIZE3,1,0> *fifo3;
FIFO<q15_t,FIFOSIZE4,1,0> *fifo4;
FIFO<q15_t,FIFOSIZE5,1,0> *fifo5;
FIFO<stream_2d_layer_t,FIFOSIZE6,1,0> *fifo6;
FIFO<stream_2d_layer_t,FIFOSIZE7,1,0> *fifo7;
FIFO<stream_2d_layer_t,FIFOSIZE8,1,0> *fifo8;
FIFO<stream_2d_layer_t,FIFOSIZE9,1,0> *fifo9;
FIFO<stream_2d_layer_t,FIFOSIZE10,1,0> *fifo10;
FIFO<stream_2d_layer_t,FIFOSIZE11,1,0> *fifo11;
FIFO<q15_t,FIFOSIZE12,1,0> *fifo12;
FIFO<q15_t,FIFOSIZE13,1,0> *fifo13;
FIFO<q15_t,FIFOSIZE14,1,0> *fifo14;
} fifos_t;

typedef struct {
    Arm2D<stream_2d_layer_t,1> *Compositor;
    AmplitudeWidget<q15_t,256,stream_2d_layer_t,1,stream_2d_layer_t,1> *amp;
    Layer<stream_2d_layer_t,1> *ampLayer;
    Animate<stream_2d_layer_t,1,stream_2d_layer_t,1> *animate;
    ROLayer<stream_2d_layer_t,1> *cmsis;
    FromOtherCore<q15_t,128> *core0;
    FilterAndDecimate<q15_t,128,q15_t,8> *decimateAmp;
    FilterAndDecimate<q15_t,128,q15_t,8> *decimateFFT;
    Duplicate<q15_t,128,q15_t,128> *dup0;
    CFFT<q15_t,512,q15_t,512> *fft;
    Layer<stream_2d_layer_t,1> *fftLayer;
    FFTAmplitude<q15_t,512,q15_t,128> *fftMag;
    SpectrumWidget<q15_t,128,stream_2d_layer_t,1,stream_2d_layer_t,1> *spectrum;
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
                              const int nbTaps,
                              const q15_t* coefs)
{
    CG_BEFORE_FIFO_INIT;
    fifos.fifo0 = new FIFO<q15_t,FIFOSIZE0,0,0>(lcd_buf6);
    if (fifos.fifo0==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo1 = new FIFO<q15_t,FIFOSIZE1,0,0>(lcd_buf7);
    if (fifos.fifo1==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo2 = new FIFO<q15_t,FIFOSIZE2,1,0>(lcd_buf4);
    if (fifos.fifo2==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo3 = new FIFO<q15_t,FIFOSIZE3,1,0>(lcd_buf3);
    if (fifos.fifo3==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo4 = new FIFO<q15_t,FIFOSIZE4,1,0>(lcd_buf4);
    if (fifos.fifo4==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo5 = new FIFO<q15_t,FIFOSIZE5,1,0>(lcd_buf3);
    if (fifos.fifo5==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo6 = new FIFO<stream_2d_layer_t,FIFOSIZE6,1,0>(lcd_buf3);
    if (fifos.fifo6==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo7 = new FIFO<stream_2d_layer_t,FIFOSIZE7,1,0>(lcd_buf1);
    if (fifos.fifo7==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo8 = new FIFO<stream_2d_layer_t,FIFOSIZE8,1,0>(lcd_buf1);
    if (fifos.fifo8==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo9 = new FIFO<stream_2d_layer_t,FIFOSIZE9,1,0>(lcd_buf2);
    if (fifos.fifo9==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo10 = new FIFO<stream_2d_layer_t,FIFOSIZE10,1,0>(lcd_buf4);
    if (fifos.fifo10==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo11 = new FIFO<stream_2d_layer_t,FIFOSIZE11,1,0>(lcd_buf0);
    if (fifos.fifo11==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo12 = new FIFO<q15_t,FIFOSIZE12,1,0>(lcd_buf2);
    if (fifos.fifo12==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo13 = new FIFO<q15_t,FIFOSIZE13,1,0>(lcd_buf5);
    if (fifos.fifo13==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo14 = new FIFO<q15_t,FIFOSIZE14,1,0>(lcd_buf4);
    if (fifos.fifo14==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }

    CG_BEFORE_NODE_INIT;
    nodes.Compositor = new Arm2D<stream_2d_layer_t,1>({fifos.fifo9,fifos.fifo10,fifos.fifo11});
    if (nodes.Compositor==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[LCD_COMPOSITOR_ID]=(void*)nodes.Compositor;
    nodes.Compositor->setID(LCD_COMPOSITOR_ID);
    nodes.amp = new AmplitudeWidget<q15_t,256,stream_2d_layer_t,1,stream_2d_layer_t,1>(*(fifos.fifo0),*(fifos.fifo6),*(fifos.fifo9));
    if (nodes.amp==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[LCD_AMP_ID]=(void*)nodes.amp;
    nodes.amp->setID(LCD_AMP_ID);
    nodes.ampLayer = new Layer<stream_2d_layer_t,1>(*(fifos.fifo6),1,20,10,65535,255,false,200,100);
    if (nodes.ampLayer==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[LCD_AMPLAYER_ID]=(void*)nodes.ampLayer;
    nodes.ampLayer->setID(LCD_AMPLAYER_ID);
    nodes.animate = new Animate<stream_2d_layer_t,1,stream_2d_layer_t,1>(*(fifos.fifo8),*(fifos.fifo11));
    if (nodes.animate==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[LCD_ANIMATE_ID]=(void*)nodes.animate;
    nodes.animate->setID(LCD_ANIMATE_ID);
    nodes.cmsis = new ROLayer<stream_2d_layer_t,1>(*(fifos.fifo8),0,40,87,65535,255,true,&c_tilecmsisLOGORGB565);
    if (nodes.cmsis==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[LCD_CMSIS_ID]=(void*)nodes.cmsis;
    nodes.cmsis->setID(LCD_CMSIS_ID);
    nodes.core0 = new FromOtherCore<q15_t,128>(*(fifos.fifo12),audio_queue,1);
    if (nodes.core0==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[LCD_CORE0_ID]=(void*)nodes.core0;
    nodes.core0->setID(LCD_CORE0_ID);
    nodes.decimateAmp = new FilterAndDecimate<q15_t,128,q15_t,8>(*(fifos.fifo13),*(fifos.fifo0),nbTaps,coefs);
    if (nodes.decimateAmp==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[LCD_DECIMATEAMP_ID]=(void*)nodes.decimateAmp;
    nodes.decimateAmp->setID(LCD_DECIMATEAMP_ID);
    nodes.decimateFFT = new FilterAndDecimate<q15_t,128,q15_t,8>(*(fifos.fifo14),*(fifos.fifo1),nbTaps,coefs);
    if (nodes.decimateFFT==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[LCD_DECIMATEFFT_ID]=(void*)nodes.decimateFFT;
    nodes.decimateFFT->setID(LCD_DECIMATEFFT_ID);
    nodes.dup0 = new Duplicate<q15_t,128,q15_t,128>(*(fifos.fifo12),{fifos.fifo13,fifos.fifo14});
    if (nodes.dup0==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.fft = new CFFT<q15_t,512,q15_t,512>(*(fifos.fifo3),*(fifos.fifo4));
    if (nodes.fft==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[LCD_FFT_ID]=(void*)nodes.fft;
    nodes.fft->setID(LCD_FFT_ID);
    nodes.fftLayer = new Layer<stream_2d_layer_t,1>(*(fifos.fifo7),2,20,130,65535,200,false,200,100);
    if (nodes.fftLayer==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[LCD_FFTLAYER_ID]=(void*)nodes.fftLayer;
    nodes.fftLayer->setID(LCD_FFTLAYER_ID);
    nodes.fftMag = new FFTAmplitude<q15_t,512,q15_t,128>(*(fifos.fifo4),*(fifos.fifo5));
    if (nodes.fftMag==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[LCD_FFTMAG_ID]=(void*)nodes.fftMag;
    nodes.fftMag->setID(LCD_FFTMAG_ID);
    nodes.spectrum = new SpectrumWidget<q15_t,128,stream_2d_layer_t,1,stream_2d_layer_t,1>(*(fifos.fifo5),*(fifos.fifo7),*(fifos.fifo10));
    if (nodes.spectrum==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[LCD_SPECTRUM_ID]=(void*)nodes.spectrum;
    nodes.spectrum->setID(LCD_SPECTRUM_ID);
    nodes.toCmplx = new ToComplex<q15_t,256,q15_t,512>(*(fifos.fifo2),*(fifos.fifo3));
    if (nodes.toCmplx==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[LCD_TOCMPLX_ID]=(void*)nodes.toCmplx;
    nodes.toCmplx->setID(LCD_TOCMPLX_ID);

    return(CG_SUCCESS);

}

void free_lcd_scheduler(queue_t *audio_queue,
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
    if (fifos.fifo12!=NULL)
    {
       delete fifos.fifo12;
    }
    if (fifos.fifo13!=NULL)
    {
       delete fifos.fifo13;
    }
    if (fifos.fifo14!=NULL)
    {
       delete fifos.fifo14;
    }

    if (nodes.Compositor!=NULL)
    {
        delete nodes.Compositor;
    }
    if (nodes.amp!=NULL)
    {
        delete nodes.amp;
    }
    if (nodes.ampLayer!=NULL)
    {
        delete nodes.ampLayer;
    }
    if (nodes.animate!=NULL)
    {
        delete nodes.animate;
    }
    if (nodes.cmsis!=NULL)
    {
        delete nodes.cmsis;
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
    if (nodes.fft!=NULL)
    {
        delete nodes.fft;
    }
    if (nodes.fftLayer!=NULL)
    {
        delete nodes.fftLayer;
    }
    if (nodes.fftMag!=NULL)
    {
        delete nodes.fftMag;
    }
    if (nodes.spectrum!=NULL)
    {
        delete nodes.spectrum;
    }
    if (nodes.toCmplx!=NULL)
    {
        delete nodes.toCmplx;
    }
}


CG_BEFORE_SCHEDULER_FUNCTION
uint32_t lcd_scheduler(int *error,queue_t *audio_queue,
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
        for(unsigned long id=0 ; id < 139; id++)
        {
            CG_BEFORE_NODE_EXECUTION;

            switch(schedule[id])
            {
                case 0:
                {
                   cgStaticError = nodes.Compositor->run();
                }
                break;

                case 1:
                {
                   cgStaticError = nodes.amp->run();
                }
                break;

                case 2:
                {
                   cgStaticError = nodes.ampLayer->run();
                }
                break;

                case 3:
                {
                   cgStaticError = nodes.animate->run();
                }
                break;

                case 4:
                {
                   
                  {

                   q15_t* i0;
                   q15_t* o2;
                   i0=fifos.fifo1->getReadBuffer(256);
                   o2=fifos.fifo2->getWriteBuffer(256);
                   arm_mult_q15(i0,hanningQ15,o2,256);
                   cgStaticError = 0;
                  }
                }
                break;

                case 5:
                {
                   cgStaticError = nodes.cmsis->run();
                }
                break;

                case 6:
                {
                   cgStaticError = nodes.core0->run();
                }
                break;

                case 7:
                {
                   cgStaticError = nodes.decimateAmp->run();
                }
                break;

                case 8:
                {
                   cgStaticError = nodes.decimateFFT->run();
                }
                break;

                case 9:
                {
                   cgStaticError = nodes.dup0->run();
                }
                break;

                case 10:
                {
                   cgStaticError = nodes.fft->run();
                }
                break;

                case 11:
                {
                   cgStaticError = nodes.fftLayer->run();
                }
                break;

                case 12:
                {
                   cgStaticError = nodes.fftMag->run();
                }
                break;

                case 13:
                {
                   cgStaticError = nodes.spectrum->run();
                }
                break;

                case 14:
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
