/* CMSIS-Stream nodes made from Playtune_synth 
   project at https://github.com/LenShustek/Playtune_synth

   Copyright (C) 2016, Len Shustek

   Some parts of synth_Playtune.cpp
   Modified for the PicoMusic demo by Arm (simplified)

*/

#pragma once 


#include <cstdio>

#include "Nodes/Playtune_synth/Playtune.h"

#include "pico/time.h"
#include "pico/sync.h"

#include "c_component.h"



#define MIN_NOTE 21 // we only do the piano range
#define MAX_NOTE 108
#define NUM_NOTES (MAX_NOTE - MIN_NOTE + 1)

#define NB_VELOCITY 128
#define NB_TUNES 128

static const q15_t velocity2amplitude[NB_VELOCITY] = {0, 258, 516, 774, 1032, 1290, 1548, 1806, 2064, 2322, 2580, 2838, 
3096, 3354, 3612, 3870, 4128, 4386, 4644, 4902, 5160, 5418, 5676, 
5934, 6192, 6450, 6708, 6966, 7224, 7482, 7740, 7998, 8256, 8514, 
8772, 9030, 9288, 9546, 9804, 10062, 10320, 10578, 10836, 11094, 
11352, 11610, 11868, 12126, 12384, 12642, 12900, 13158, 13416, 13674, 
13932, 14190, 14448, 14706, 14964, 15222, 15480, 15738, 15996, 16254, 
16512, 16770, 17028, 17286, 17544, 17802, 18060, 18318, 18576, 18834, 
19092, 19350, 19608, 19866, 20124, 20382, 20640, 20898, 21156, 21414, 
21672, 21930, 22188, 22446, 22704, 22962, 23220, 23478, 23736, 23994, 
24252, 24510, 24768, 25026, 25284, 25542, 25800, 26058, 26316, 26574, 
26832, 27090, 27348, 27606, 27864, 28122, 28380, 28638, 28896, 29154, 
29412, 29670, 29928, 30186, 30444, 30702, 30960, 31218, 31476, 31734, 
31992, 32250, 32508, 32767};


static const uint32_t tune_to_phase_increment[NUM_NOTES] = {
2056081,2178342,2307873,2445107,2590500,2744540,2907738,3080641,3263826,3457903,
3663521,3881365,4112163,4356685,4615747,4890213,5181001,5489079,5815477,6161283,
6527652,6915806,7327041,7762730,8224326,8713370,9231494,9780427,10362001,10978158,
11630953,12322566,13055304,13831612,14654083,15525460,16448652,17426740,18462987,19560854,
20724003,21956316,23261907,24645131,26110607,27663225,29308166,31050920,32897304,34853479,
36925975,39121708,41448005,43912632,46523813,49290263,52221214,55326449,58616331,62101840,
65794607,69706958,73851950,78243415,82896011,87825264,93047626,98580526,104442429,110652899,
117232663,124203680,131589215,139413917,147703900,156486830,165792022,175650528,186095252,197161052,
208884858,221305798,234465325,248407359,263178429,278827833,295407799,312973661};

#define NO_MIDI_CMD 0
#define NOTE_OFF 2
#define NOTE_ON 3

typedef struct {
uint32_t cmd;
uint32_t inst;
uint32_t note;
q15_t amp;
uint32_t phaseIncrement;
} midi_cmd_t;



template<typename OUT,int outputSize>
class Sequencer;

template<>
class Sequencer<midi_cmd_t,1>:public NodeBase
{
public:
    Sequencer(std::initializer_list<FIFOBase<midi_cmd_t>*> dst,
    const uint8_t** allSongs,
    const char** names ):
    mAllSongs(allSongs),mNames(names),mDstList(dst){
    	done=false;
        inst = 0;
        mPos=0;
        delayState = false;
        delay=0;
        nb_channels=mDstList.size();
        nbSong=0;
        mMusic = mAllSongs[nbSong];
        mutex_init(&my_mutex);
        forceNextSong = false;
        updateTime();
        printf(mNames[nbSong]);
    };

    int prepareForRunning() final
    {
        if (this->willOverflow())
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(CG_SUCCESS);
    };

    void nextSong()
    {
        mutex_enter_blocking(&my_mutex);
        forceNextSong=true;
        mutex_exit(&my_mutex);
    }

    __attribute__((section(".time_critical.MIDISeq")))
    int run() final 
    {
        mutex_enter_blocking(&my_mutex);
        midi_cmd_t *b[nb_channels];
        bool cmdSet[nb_channels];

        updateTime();

        for(int i=0;i<nb_channels;i++)
        {
           b[i]=this->getWriteBuffer(i);
           b[i]->cmd = NO_MIDI_CMD;
           cmdSet[i] = false;
        }
        while (!done)
        {
            if (forceNextSong)
            {
                forceNextSong = false; 
                for(int i=0;i<nb_channels;i++)
                {
                   b[i]->cmd = NOTE_OFF;
                   cmdSet[i] = true;
                }

                _nextSong();
                mutex_exit(&my_mutex);
                return(CG_SUCCESS);
            }
            if (delayState)
            {
                if (ms >= delay)
                {
                    //printf("%f %f\n",gTime,delay);

                    delayState=false;
                }
                else 
                {
                    mutex_exit(&my_mutex);
                    return(CG_SUCCESS);
                }
            }
            uint8_t c = mMusic[mPos];
            mPos+=1;
            if (c == CMD_STOP)
            {
                //printf("Stop all \r\n");
                
                for(int i=0;i<nb_channels;i++)
                {
                   b[i]->cmd = NOTE_OFF;
                   cmdSet[i] = true;
                }

                _nextSong();
                mutex_exit(&my_mutex);
                return(CG_SUCCESS);
            }

            uint8_t opcode = c & 0xF0;
            uint8_t chan = c & 0x0F;
            if (c < 0x80)
            {
                uint8_t s = mMusic[mPos];
                mPos += 1;
                    
                uint16_t d_time = ((uint16_t)c << 8) | s;
                delay = ms + d_time;
                delayState = true;
                //printf("%d Delay %d %d\r\n",chan,c,s);

                continue;
            }
            if (opcode == CMD_STOPNOTE)
            {
                if (chan < nb_channels)
                {
                   //printf("Stop %d \r\n",chan);
                   //if (cmdSet[chan])
                   //{
                   //  mutex_exit(&my_mutex);
                   //  return(CG_SUCCESS);
                   //}
                   cmdSet[chan] = true;
                   b[chan]->cmd = NOTE_OFF;
                }
                continue;
            }
            if (opcode == CMD_INSTRUMENT)
            {
                inst = mMusic[mPos];
                mPos += 1;
                continue;
            }
            if (opcode == CMD_PLAYNOTE)
            {
                   uint8_t note = mMusic[mPos];
                   mPos += 1;
                       
                   uint8_t velocity = mMusic[mPos];
                   mPos += 1;

                   if (note < MIN_NOTE) note = MIN_NOTE;
                   if ((note > MAX_NOTE) && (note < 129)) note = MAX_NOTE;

                   
                if (chan < nb_channels)
                {
                  
                   if (cmdSet[chan])
                   {
                        mutex_exit(&my_mutex);
                        return(CG_SUCCESS);
                   }
                   if (velocity>=NB_VELOCITY)
                   {
                     velocity=NB_VELOCITY-1;
                   }

                    uint32_t phaseIncrement =0;

                   if ((note>MAX_NOTE) && (note < 129))
                   {
                     note=MAX_NOTE;
                   }
                   q15_t amp = velocity2amplitude[velocity];
                   if (note < 129)
                   {
                      phaseIncrement = tune_to_phase_increment[note-MIN_NOTE];
                   }
             
                    cmdSet[chan] = true;
   
                    b[chan]->cmd = NOTE_ON;
                    b[chan]->inst=inst;
                    b[chan]->amp=amp;
                    b[chan]->note=note; // used from percussion detection
                    b[chan]->phaseIncrement=phaseIncrement;

                    if (velocity == 0)
                    {
                        b[chan]->cmd = NOTE_OFF;
                        cmdSet[chan] = true;
                    }

                    //printf("ON %d %d %f %f\r\n",chan,inst,amp,tune);

                }
                continue;

            }
            if (opcode == CMD_RESTART)
            {
                mPos=0;
                continue;

            }
        }
        
        mutex_exit(&my_mutex);
        return(CG_SUCCESS);
    };

protected:
    mutex_t my_mutex;
    bool forceNextSong;
    const uint8_t** mAllSongs;
    const char** mNames;

    void _nextSong()
    {
                
                nbSong++;
                //printf("New song\r\n");
                if (mAllSongs[nbSong]==NULL)
                {
                    nbSong = 0;
                }
                mPos=0;
                mMusic = mAllSongs[nbSong];

                delay = ms + 500;
                delayState = true;

                done=false;
                inst = 0;

                printf(mNames[nbSong]);

    }

    void updateTime()
    {
        absolute_time_t t = get_absolute_time();
        ms = to_ms_since_boot(t);
    }
private:
    int nb_channels;
    std::vector<FIFOBase<midi_cmd_t>*> mDstList;
	const uint8_t *mMusic;
    bool delayState;
    uint32_t delay ;
	uint32_t mPos;
    bool done;
    uint8_t inst;
    int nbSong;
    int mSong;
    uint32_t ms;

    midi_cmd_t * getWriteBuffer(int id=1){return mDstList[id]->getWriteBuffer(1);};
    bool willOverflow(int id=1){return mDstList[id]->willOverflowWith(1);};


};