/*

Generated with CMSIS-Stream python scripts.
The generated code is not covered by CMSIS-Stream license.

The support classes and code are covered by CMSIS-Stream license.

*/


#include "arm_math.h"
#include "audio_graph_config.h"
#include "GenericNodes.h"
#include "cg_status.h"
#include "AudioGraphNodes.h"
#include "audio_scheduler.h"

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
#define CG_BEFORE_NODE_EXECUTION(ID)
#endif

#if !defined(CG_AFTER_NODE_EXECUTION)
#define CG_AFTER_NODE_EXECUTION(ID)
#endif



CG_AFTER_INCLUDES


using namespace arm_cmsis_stream;

/*

Description of the scheduling. 

*/
static uint8_t schedule[28]=
{ 
6,22,9,2,25,12,5,20,7,0,21,8,1,14,15,23,10,3,24,11,4,16,17,13,27,26,18,19,
};

/***********

Node identification

************/
static void * identifiedNodes[AUDIO_NB_IDENTIFIED_NODES]={0};

CG_BEFORE_FIFO_BUFFERS
/***********

FIFO buffers

************/
#define FIFOSIZE0 128
#define FIFOSIZE1 128
#define FIFOSIZE2 128
#define FIFOSIZE3 128
#define FIFOSIZE4 128
#define FIFOSIZE5 128
#define FIFOSIZE6 128
#define FIFOSIZE7 128
#define FIFOSIZE8 128
#define FIFOSIZE9 128
#define FIFOSIZE10 128
#define FIFOSIZE11 128
#define FIFOSIZE12 128
#define FIFOSIZE13 128
#define FIFOSIZE14 128
#define FIFOSIZE15 128
#define FIFOSIZE16 128
#define FIFOSIZE17 1
#define FIFOSIZE18 1
#define FIFOSIZE19 1
#define FIFOSIZE20 1
#define FIFOSIZE21 1
#define FIFOSIZE22 1
#define FIFOSIZE23 1
#define FIFOSIZE24 1
#define FIFOSIZE25 1
#define FIFOSIZE26 1
#define FIFOSIZE27 1
#define FIFOSIZE28 1
#define FIFOSIZE29 1
#define FIFOSIZE30 1
#define FIFOSIZE31 1
#define FIFOSIZE32 1
#define FIFOSIZE33 1
#define FIFOSIZE34 1
#define FIFOSIZE35 128
#define FIFOSIZE36 128
#define FIFOSIZE37 128

#define BUFFERSIZE0 256
CG_BEFORE_BUFFER
uint8_t audio_buf0[BUFFERSIZE0]={0};

#define BUFFERSIZE1 256
CG_BEFORE_BUFFER
uint8_t audio_buf1[BUFFERSIZE1]={0};

#define BUFFERSIZE2 256
CG_BEFORE_BUFFER
uint8_t audio_buf2[BUFFERSIZE2]={0};

#define BUFFERSIZE3 256
CG_BEFORE_BUFFER
uint8_t audio_buf3[BUFFERSIZE3]={0};

#define BUFFERSIZE4 256
CG_BEFORE_BUFFER
uint8_t audio_buf4[BUFFERSIZE4]={0};

#define BUFFERSIZE5 256
CG_BEFORE_BUFFER
uint8_t audio_buf5[BUFFERSIZE5]={0};

#define BUFFERSIZE6 256
CG_BEFORE_BUFFER
uint8_t audio_buf6[BUFFERSIZE6]={0};

#define BUFFERSIZE7 256
CG_BEFORE_BUFFER
uint8_t audio_buf7[BUFFERSIZE7]={0};

#define BUFFERSIZE8 20
CG_BEFORE_BUFFER
uint8_t audio_buf8[BUFFERSIZE8]={0};


typedef struct {
FIFO<q15_t,FIFOSIZE0,1,0> *fifo0;
FIFO<q15_t,FIFOSIZE1,1,0> *fifo1;
FIFO<q15_t,FIFOSIZE2,1,0> *fifo2;
FIFO<q15_t,FIFOSIZE3,1,0> *fifo3;
FIFO<q15_t,FIFOSIZE4,1,0> *fifo4;
FIFO<q15_t,FIFOSIZE5,1,0> *fifo5;
FIFO<q15_t,FIFOSIZE6,1,0> *fifo6;
FIFO<q15_t,FIFOSIZE7,1,0> *fifo7;
FIFO<q15_t,FIFOSIZE8,1,0> *fifo8;
FIFO<q15_t,FIFOSIZE9,1,0> *fifo9;
FIFO<q15_t,FIFOSIZE10,1,0> *fifo10;
FIFO<q15_t,FIFOSIZE11,1,0> *fifo11;
FIFO<q15_t,FIFOSIZE12,1,0> *fifo12;
FIFO<q15_t,FIFOSIZE13,1,0> *fifo13;
FIFO<q15_t,FIFOSIZE14,1,0> *fifo14;
FIFO<q15_t,FIFOSIZE15,1,0> *fifo15;
FIFO<q15_t,FIFOSIZE16,1,0> *fifo16;
FIFO<midi_cmd_t,FIFOSIZE17,1,0> *fifo17;
FIFO<midi_cmd_t,FIFOSIZE18,1,0> *fifo18;
FIFO<midi_cmd_t,FIFOSIZE19,1,0> *fifo19;
FIFO<midi_cmd_t,FIFOSIZE20,1,0> *fifo20;
FIFO<midi_cmd_t,FIFOSIZE21,1,0> *fifo21;
FIFO<midi_cmd_t,FIFOSIZE22,1,0> *fifo22;
FIFO<midi_cmd_t,FIFOSIZE23,1,0> *fifo23;
FIFO<midi_cmd_t,FIFOSIZE24,1,0> *fifo24;
FIFO<midi_cmd_t,FIFOSIZE25,1,0> *fifo25;
FIFO<midi_cmd_t,FIFOSIZE26,1,0> *fifo26;
FIFO<midi_cmd_t,FIFOSIZE27,1,0> *fifo27;
FIFO<midi_cmd_t,FIFOSIZE28,1,0> *fifo28;
FIFO<midi_cmd_t,FIFOSIZE29,1,0> *fifo29;
FIFO<midi_cmd_t,FIFOSIZE30,1,0> *fifo30;
FIFO<midi_cmd_t,FIFOSIZE31,1,0> *fifo31;
FIFO<midi_cmd_t,FIFOSIZE32,1,0> *fifo32;
FIFO<midi_cmd_t,FIFOSIZE33,1,0> *fifo33;
FIFO<midi_cmd_t,FIFOSIZE34,1,0> *fifo34;
FIFO<q15_t,FIFOSIZE35,1,0> *fifo35;
FIFO<q15_t,FIFOSIZE36,1,0> *fifo36;
FIFO<q15_t,FIFOSIZE37,1,0> *fifo37;
} fifos_t;

typedef struct {
    Enveloppe<midi_cmd_t,1,q15_t,128,q15_t,128> *Enveloppe_0;
    Enveloppe<midi_cmd_t,1,q15_t,128,q15_t,128> *Enveloppe_1;
    Enveloppe<midi_cmd_t,1,q15_t,128,q15_t,128> *Enveloppe_2;
    Enveloppe<midi_cmd_t,1,q15_t,128,q15_t,128> *Enveloppe_3;
    Enveloppe<midi_cmd_t,1,q15_t,128,q15_t,128> *Enveloppe_4;
    Enveloppe<midi_cmd_t,1,q15_t,128,q15_t,128> *Enveloppe_5;
    Sequencer<midi_cmd_t,1> *NoteSequencer;
    Waveform<midi_cmd_t,1,q15_t,128> *Waveform0;
    Waveform<midi_cmd_t,1,q15_t,128> *Waveform1;
    Waveform<midi_cmd_t,1,q15_t,128> *Waveform2;
    Waveform<midi_cmd_t,1,q15_t,128> *Waveform3;
    Waveform<midi_cmd_t,1,q15_t,128> *Waveform4;
    Waveform<midi_cmd_t,1,q15_t,128> *Waveform5;
    PWMAudio<q15_t,128> *audio;
    ToOtherCore<q15_t,128> *core1;
    Duplicate<midi_cmd_t,1,midi_cmd_t,1> *dup0;
    Duplicate<midi_cmd_t,1,midi_cmd_t,1> *dup1;
    Duplicate<midi_cmd_t,1,midi_cmd_t,1> *dup2;
    Duplicate<midi_cmd_t,1,midi_cmd_t,1> *dup3;
    Duplicate<midi_cmd_t,1,midi_cmd_t,1> *dup4;
    Duplicate<midi_cmd_t,1,midi_cmd_t,1> *dup5;
    Duplicate<q15_t,128,q15_t,128> *dup6;
    Gain<q15_t,128,q15_t,128> *ogain;
} nodes_t;

CG_BEFORE_BUFFER
static fifos_t fifos={0};

CG_BEFORE_BUFFER
static nodes_t nodes={0};

void *get_audio_scheduler_node(int32_t nodeID)
{
    if (nodeID >= AUDIO_NB_IDENTIFIED_NODES)
    {
        return(NULL);
    }
    if (nodeID < 0)
    {
        return(NULL);
    }
    return(identifiedNodes[nodeID]);
}

int init_audio_scheduler(uint32_t *offState,
                              queue_t *audio_queue,
                              const uint8_t** allSongs,
                              const char** names)
{
    CG_BEFORE_FIFO_INIT;
    fifos.fifo0 = new FIFO<q15_t,FIFOSIZE0,1,0>(audio_buf7);
    if (fifos.fifo0==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo1 = new FIFO<q15_t,FIFOSIZE1,1,0>(audio_buf4);
    if (fifos.fifo1==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo2 = new FIFO<q15_t,FIFOSIZE2,1,0>(audio_buf7);
    if (fifos.fifo2==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo3 = new FIFO<q15_t,FIFOSIZE3,1,0>(audio_buf5);
    if (fifos.fifo3==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo4 = new FIFO<q15_t,FIFOSIZE4,1,0>(audio_buf0);
    if (fifos.fifo4==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo5 = new FIFO<q15_t,FIFOSIZE5,1,0>(audio_buf7);
    if (fifos.fifo5==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo6 = new FIFO<q15_t,FIFOSIZE6,1,0>(audio_buf5);
    if (fifos.fifo6==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo7 = new FIFO<q15_t,FIFOSIZE7,1,0>(audio_buf7);
    if (fifos.fifo7==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo8 = new FIFO<q15_t,FIFOSIZE8,1,0>(audio_buf6);
    if (fifos.fifo8==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo9 = new FIFO<q15_t,FIFOSIZE9,1,0>(audio_buf3);
    if (fifos.fifo9==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo10 = new FIFO<q15_t,FIFOSIZE10,1,0>(audio_buf2);
    if (fifos.fifo10==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo11 = new FIFO<q15_t,FIFOSIZE11,1,0>(audio_buf5);
    if (fifos.fifo11==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo12 = new FIFO<q15_t,FIFOSIZE12,1,0>(audio_buf0);
    if (fifos.fifo12==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo13 = new FIFO<q15_t,FIFOSIZE13,1,0>(audio_buf1);
    if (fifos.fifo13==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo14 = new FIFO<q15_t,FIFOSIZE14,1,0>(audio_buf4);
    if (fifos.fifo14==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo15 = new FIFO<q15_t,FIFOSIZE15,1,0>(audio_buf2);
    if (fifos.fifo15==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo16 = new FIFO<q15_t,FIFOSIZE16,1,0>(audio_buf0);
    if (fifos.fifo16==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo17 = new FIFO<midi_cmd_t,FIFOSIZE17,1,0>(audio_buf5);
    if (fifos.fifo17==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo18 = new FIFO<midi_cmd_t,FIFOSIZE18,1,0>(audio_buf8);
    if (fifos.fifo18==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo19 = new FIFO<midi_cmd_t,FIFOSIZE19,1,0>(audio_buf6);
    if (fifos.fifo19==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo20 = new FIFO<midi_cmd_t,FIFOSIZE20,1,0>(audio_buf4);
    if (fifos.fifo20==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo21 = new FIFO<midi_cmd_t,FIFOSIZE21,1,0>(audio_buf7);
    if (fifos.fifo21==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo22 = new FIFO<midi_cmd_t,FIFOSIZE22,1,0>(audio_buf6);
    if (fifos.fifo22==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo23 = new FIFO<midi_cmd_t,FIFOSIZE23,1,0>(audio_buf7);
    if (fifos.fifo23==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo24 = new FIFO<midi_cmd_t,FIFOSIZE24,1,0>(audio_buf3);
    if (fifos.fifo24==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo25 = new FIFO<midi_cmd_t,FIFOSIZE25,1,0>(audio_buf6);
    if (fifos.fifo25==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo26 = new FIFO<midi_cmd_t,FIFOSIZE26,1,0>(audio_buf2);
    if (fifos.fifo26==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo27 = new FIFO<midi_cmd_t,FIFOSIZE27,1,0>(audio_buf6);
    if (fifos.fifo27==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo28 = new FIFO<midi_cmd_t,FIFOSIZE28,1,0>(audio_buf3);
    if (fifos.fifo28==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo29 = new FIFO<midi_cmd_t,FIFOSIZE29,1,0>(audio_buf0);
    if (fifos.fifo29==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo30 = new FIFO<midi_cmd_t,FIFOSIZE30,1,0>(audio_buf5);
    if (fifos.fifo30==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo31 = new FIFO<midi_cmd_t,FIFOSIZE31,1,0>(audio_buf3);
    if (fifos.fifo31==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo32 = new FIFO<midi_cmd_t,FIFOSIZE32,1,0>(audio_buf1);
    if (fifos.fifo32==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo33 = new FIFO<midi_cmd_t,FIFOSIZE33,1,0>(audio_buf8);
    if (fifos.fifo33==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo34 = new FIFO<midi_cmd_t,FIFOSIZE34,1,0>(audio_buf6);
    if (fifos.fifo34==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo35 = new FIFO<q15_t,FIFOSIZE35,1,0>(audio_buf1);
    if (fifos.fifo35==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo36 = new FIFO<q15_t,FIFOSIZE36,1,0>(audio_buf0);
    if (fifos.fifo36==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    fifos.fifo37 = new FIFO<q15_t,FIFOSIZE37,1,0>(audio_buf2);
    if (fifos.fifo37==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }

    CG_BEFORE_NODE_INIT;
    nodes.Enveloppe_0 = new Enveloppe<midi_cmd_t,1,q15_t,128,q15_t,128>(*(fifos.fifo19),*(fifos.fifo0),*(fifos.fifo6),0,offState);
    if (nodes.Enveloppe_0==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.Enveloppe_1 = new Enveloppe<midi_cmd_t,1,q15_t,128,q15_t,128>(*(fifos.fifo22),*(fifos.fifo1),*(fifos.fifo7),1,offState);
    if (nodes.Enveloppe_1==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.Enveloppe_2 = new Enveloppe<midi_cmd_t,1,q15_t,128,q15_t,128>(*(fifos.fifo25),*(fifos.fifo2),*(fifos.fifo9),2,offState);
    if (nodes.Enveloppe_2==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.Enveloppe_3 = new Enveloppe<midi_cmd_t,1,q15_t,128,q15_t,128>(*(fifos.fifo28),*(fifos.fifo3),*(fifos.fifo10),3,offState);
    if (nodes.Enveloppe_3==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.Enveloppe_4 = new Enveloppe<midi_cmd_t,1,q15_t,128,q15_t,128>(*(fifos.fifo31),*(fifos.fifo4),*(fifos.fifo11),4,offState);
    if (nodes.Enveloppe_4==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.Enveloppe_5 = new Enveloppe<midi_cmd_t,1,q15_t,128,q15_t,128>(*(fifos.fifo34),*(fifos.fifo5),*(fifos.fifo13),5,offState);
    if (nodes.Enveloppe_5==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.NoteSequencer = new Sequencer<midi_cmd_t,1>({fifos.fifo20,fifos.fifo23,fifos.fifo26,fifos.fifo29,fifos.fifo32},allSongs,names);
    if (nodes.NoteSequencer==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[AUDIO_NOTESEQUENCER_ID]=(void*)nodes.NoteSequencer;
    nodes.NoteSequencer->setID(AUDIO_NOTESEQUENCER_ID);
    nodes.Waveform0 = new Waveform<midi_cmd_t,1,q15_t,128>(*(fifos.fifo18),*(fifos.fifo0),0,offState);
    if (nodes.Waveform0==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.Waveform1 = new Waveform<midi_cmd_t,1,q15_t,128>(*(fifos.fifo21),*(fifos.fifo1),1,offState);
    if (nodes.Waveform1==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.Waveform2 = new Waveform<midi_cmd_t,1,q15_t,128>(*(fifos.fifo24),*(fifos.fifo2),2,offState);
    if (nodes.Waveform2==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.Waveform3 = new Waveform<midi_cmd_t,1,q15_t,128>(*(fifos.fifo27),*(fifos.fifo3),3,offState);
    if (nodes.Waveform3==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.Waveform4 = new Waveform<midi_cmd_t,1,q15_t,128>(*(fifos.fifo30),*(fifos.fifo4),4,offState);
    if (nodes.Waveform4==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.Waveform5 = new Waveform<midi_cmd_t,1,q15_t,128>(*(fifos.fifo33),*(fifos.fifo5),5,offState);
    if (nodes.Waveform5==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.audio = new PWMAudio<q15_t,128>(*(fifos.fifo36));
    if (nodes.audio==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[AUDIO_AUDIO_ID]=(void*)nodes.audio;
    nodes.audio->setID(AUDIO_AUDIO_ID);
    nodes.core1 = new ToOtherCore<q15_t,128>(*(fifos.fifo37),audio_queue,0);
    if (nodes.core1==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[AUDIO_CORE1_ID]=(void*)nodes.core1;
    nodes.core1->setID(AUDIO_CORE1_ID);
    nodes.dup0 = new Duplicate<midi_cmd_t,1,midi_cmd_t,1>(*(fifos.fifo17),{fifos.fifo18,fifos.fifo19});
    if (nodes.dup0==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.dup1 = new Duplicate<midi_cmd_t,1,midi_cmd_t,1>(*(fifos.fifo20),{fifos.fifo21,fifos.fifo22});
    if (nodes.dup1==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.dup2 = new Duplicate<midi_cmd_t,1,midi_cmd_t,1>(*(fifos.fifo23),{fifos.fifo24,fifos.fifo25});
    if (nodes.dup2==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.dup3 = new Duplicate<midi_cmd_t,1,midi_cmd_t,1>(*(fifos.fifo26),{fifos.fifo27,fifos.fifo28});
    if (nodes.dup3==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.dup4 = new Duplicate<midi_cmd_t,1,midi_cmd_t,1>(*(fifos.fifo29),{fifos.fifo30,fifos.fifo31});
    if (nodes.dup4==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.dup5 = new Duplicate<midi_cmd_t,1,midi_cmd_t,1>(*(fifos.fifo32),{fifos.fifo33,fifos.fifo34});
    if (nodes.dup5==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.dup6 = new Duplicate<q15_t,128,q15_t,128>(*(fifos.fifo35),{fifos.fifo36,fifos.fifo37});
    if (nodes.dup6==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    nodes.ogain = new Gain<q15_t,128,q15_t,128>(*(fifos.fifo16),*(fifos.fifo35),1.0);
    if (nodes.ogain==NULL)
    {
        return(CG_MEMORY_ALLOCATION_FAILURE);
    }
    identifiedNodes[AUDIO_OGAIN_ID]=(void*)nodes.ogain;
    nodes.ogain->setID(AUDIO_OGAIN_ID);

    return(CG_SUCCESS);

}

void free_audio_scheduler(uint32_t *offState,
                              queue_t *audio_queue,
                              const uint8_t** allSongs,
                              const char** names)
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
    if (fifos.fifo15!=NULL)
    {
       delete fifos.fifo15;
    }
    if (fifos.fifo16!=NULL)
    {
       delete fifos.fifo16;
    }
    if (fifos.fifo17!=NULL)
    {
       delete fifos.fifo17;
    }
    if (fifos.fifo18!=NULL)
    {
       delete fifos.fifo18;
    }
    if (fifos.fifo19!=NULL)
    {
       delete fifos.fifo19;
    }
    if (fifos.fifo20!=NULL)
    {
       delete fifos.fifo20;
    }
    if (fifos.fifo21!=NULL)
    {
       delete fifos.fifo21;
    }
    if (fifos.fifo22!=NULL)
    {
       delete fifos.fifo22;
    }
    if (fifos.fifo23!=NULL)
    {
       delete fifos.fifo23;
    }
    if (fifos.fifo24!=NULL)
    {
       delete fifos.fifo24;
    }
    if (fifos.fifo25!=NULL)
    {
       delete fifos.fifo25;
    }
    if (fifos.fifo26!=NULL)
    {
       delete fifos.fifo26;
    }
    if (fifos.fifo27!=NULL)
    {
       delete fifos.fifo27;
    }
    if (fifos.fifo28!=NULL)
    {
       delete fifos.fifo28;
    }
    if (fifos.fifo29!=NULL)
    {
       delete fifos.fifo29;
    }
    if (fifos.fifo30!=NULL)
    {
       delete fifos.fifo30;
    }
    if (fifos.fifo31!=NULL)
    {
       delete fifos.fifo31;
    }
    if (fifos.fifo32!=NULL)
    {
       delete fifos.fifo32;
    }
    if (fifos.fifo33!=NULL)
    {
       delete fifos.fifo33;
    }
    if (fifos.fifo34!=NULL)
    {
       delete fifos.fifo34;
    }
    if (fifos.fifo35!=NULL)
    {
       delete fifos.fifo35;
    }
    if (fifos.fifo36!=NULL)
    {
       delete fifos.fifo36;
    }
    if (fifos.fifo37!=NULL)
    {
       delete fifos.fifo37;
    }

    if (nodes.Enveloppe_0!=NULL)
    {
        delete nodes.Enveloppe_0;
    }
    if (nodes.Enveloppe_1!=NULL)
    {
        delete nodes.Enveloppe_1;
    }
    if (nodes.Enveloppe_2!=NULL)
    {
        delete nodes.Enveloppe_2;
    }
    if (nodes.Enveloppe_3!=NULL)
    {
        delete nodes.Enveloppe_3;
    }
    if (nodes.Enveloppe_4!=NULL)
    {
        delete nodes.Enveloppe_4;
    }
    if (nodes.Enveloppe_5!=NULL)
    {
        delete nodes.Enveloppe_5;
    }
    if (nodes.NoteSequencer!=NULL)
    {
        delete nodes.NoteSequencer;
    }
    if (nodes.Waveform0!=NULL)
    {
        delete nodes.Waveform0;
    }
    if (nodes.Waveform1!=NULL)
    {
        delete nodes.Waveform1;
    }
    if (nodes.Waveform2!=NULL)
    {
        delete nodes.Waveform2;
    }
    if (nodes.Waveform3!=NULL)
    {
        delete nodes.Waveform3;
    }
    if (nodes.Waveform4!=NULL)
    {
        delete nodes.Waveform4;
    }
    if (nodes.Waveform5!=NULL)
    {
        delete nodes.Waveform5;
    }
    if (nodes.audio!=NULL)
    {
        delete nodes.audio;
    }
    if (nodes.core1!=NULL)
    {
        delete nodes.core1;
    }
    if (nodes.dup0!=NULL)
    {
        delete nodes.dup0;
    }
    if (nodes.dup1!=NULL)
    {
        delete nodes.dup1;
    }
    if (nodes.dup2!=NULL)
    {
        delete nodes.dup2;
    }
    if (nodes.dup3!=NULL)
    {
        delete nodes.dup3;
    }
    if (nodes.dup4!=NULL)
    {
        delete nodes.dup4;
    }
    if (nodes.dup5!=NULL)
    {
        delete nodes.dup5;
    }
    if (nodes.dup6!=NULL)
    {
        delete nodes.dup6;
    }
    if (nodes.ogain!=NULL)
    {
        delete nodes.ogain;
    }
}


CG_BEFORE_SCHEDULER_FUNCTION
uint32_t audio_scheduler(int *error,uint32_t *offState,
                              queue_t *audio_queue,
                              const uint8_t** allSongs,
                              const char** names)
{
    int cgStaticError=0;
    uint32_t nbSchedule=0;


    /* Run several schedule iterations */
    CG_BEFORE_SCHEDULE;
    while(cgStaticError==0)
    {
        /* Run a schedule iteration */
        CG_BEFORE_ITERATION;
        for(unsigned long id=0 ; id < 28; id++)
        {
            CG_BEFORE_NODE_EXECUTION(schedule[id]);

            switch(schedule[id])
            {
                case 0:
                {
                   cgStaticError = nodes.Enveloppe_0->run();
                }
                break;

                case 1:
                {
                   cgStaticError = nodes.Enveloppe_1->run();
                }
                break;

                case 2:
                {
                   cgStaticError = nodes.Enveloppe_2->run();
                }
                break;

                case 3:
                {
                   cgStaticError = nodes.Enveloppe_3->run();
                }
                break;

                case 4:
                {
                   cgStaticError = nodes.Enveloppe_4->run();
                }
                break;

                case 5:
                {
                   cgStaticError = nodes.Enveloppe_5->run();
                }
                break;

                case 6:
                {
                   cgStaticError = nodes.NoteSequencer->run();
                }
                break;

                case 7:
                {
                   cgStaticError = nodes.Waveform0->run();
                }
                break;

                case 8:
                {
                   cgStaticError = nodes.Waveform1->run();
                }
                break;

                case 9:
                {
                   cgStaticError = nodes.Waveform2->run();
                }
                break;

                case 10:
                {
                   cgStaticError = nodes.Waveform3->run();
                }
                break;

                case 11:
                {
                   cgStaticError = nodes.Waveform4->run();
                }
                break;

                case 12:
                {
                   cgStaticError = nodes.Waveform5->run();
                }
                break;

                case 13:
                {
                   
                  {

                   q15_t* i0;
                   q15_t* i1;
                   q15_t* o2;
                   i0=fifos.fifo14->getReadBuffer(128);
                   i1=fifos.fifo15->getReadBuffer(128);
                   o2=fifos.fifo16->getWriteBuffer(128);
                   arm_add_q15(i0,i1,o2,128);
                   cgStaticError = 0;
                  }
                }
                break;

                case 14:
                {
                   
                  {

                   q15_t* i0;
                   q15_t* i1;
                   q15_t* o2;
                   i0=fifos.fifo6->getReadBuffer(128);
                   i1=fifos.fifo7->getReadBuffer(128);
                   o2=fifos.fifo8->getWriteBuffer(128);
                   arm_add_q15(i0,i1,o2,128);
                   cgStaticError = 0;
                  }
                }
                break;

                case 15:
                {
                   
                  {

                   q15_t* i0;
                   q15_t* i1;
                   q15_t* o2;
                   i0=fifos.fifo8->getReadBuffer(128);
                   i1=fifos.fifo9->getReadBuffer(128);
                   o2=fifos.fifo14->getWriteBuffer(128);
                   arm_add_q15(i0,i1,o2,128);
                   cgStaticError = 0;
                  }
                }
                break;

                case 16:
                {
                   
                  {

                   q15_t* i0;
                   q15_t* i1;
                   q15_t* o2;
                   i0=fifos.fifo10->getReadBuffer(128);
                   i1=fifos.fifo11->getReadBuffer(128);
                   o2=fifos.fifo12->getWriteBuffer(128);
                   arm_add_q15(i0,i1,o2,128);
                   cgStaticError = 0;
                  }
                }
                break;

                case 17:
                {
                   
                  {

                   q15_t* i0;
                   q15_t* i1;
                   q15_t* o2;
                   i0=fifos.fifo12->getReadBuffer(128);
                   i1=fifos.fifo13->getReadBuffer(128);
                   o2=fifos.fifo15->getWriteBuffer(128);
                   arm_add_q15(i0,i1,o2,128);
                   cgStaticError = 0;
                  }
                }
                break;

                case 18:
                {
                   cgStaticError = nodes.audio->run();
                }
                break;

                case 19:
                {
                   cgStaticError = nodes.core1->run();
                }
                break;

                case 20:
                {
                   cgStaticError = nodes.dup0->run();
                }
                break;

                case 21:
                {
                   cgStaticError = nodes.dup1->run();
                }
                break;

                case 22:
                {
                   cgStaticError = nodes.dup2->run();
                }
                break;

                case 23:
                {
                   cgStaticError = nodes.dup3->run();
                }
                break;

                case 24:
                {
                   cgStaticError = nodes.dup4->run();
                }
                break;

                case 25:
                {
                   cgStaticError = nodes.dup5->run();
                }
                break;

                case 26:
                {
                   cgStaticError = nodes.dup6->run();
                }
                break;

                case 27:
                {
                   cgStaticError = nodes.ogain->run();
                }
                break;

                default:
                break;
            }
            CG_AFTER_NODE_EXECUTION(schedule[id]);
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
