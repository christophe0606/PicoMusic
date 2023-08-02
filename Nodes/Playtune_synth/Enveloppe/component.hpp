/* CMSIS-Stream nodes made from Playtune_synth 
   project at https://github.com/LenShustek/Playtune_synth

   Copyright (C) 2016, Len Shustek

   Some parts of synth_Playtune.cpp
   Modified for the PicoMusic demo by Arm (simplified)

*/

#pragma once

#include "Nodes/Playtune_synth/Playtune.h"

enum envState {
  kIdle,
  kDelay,
  kAttack,
  kHold,
  kDecay,
  kSustain,
  kRelease,
  kForced
};

#define Q31_MIDRANGE 0x40000000

template<typename IN1,int inputSize1,
         typename IN2,int inputSize2,
         typename OUT,int outputSize>
class Enveloppe;

template<int outputSize>
class Enveloppe<midi_cmd_t,1,
              q15_t,outputSize,
              q15_t,outputSize>: 
GenericNode21<midi_cmd_t,1,
              q15_t,outputSize,
              q15_t,outputSize>
{
public:
    Enveloppe(FIFOBase<midi_cmd_t> &src1,
    	    FIFOBase<q15_t> &src2,
            FIFOBase<q15_t> &dst,
            int channel_nb,
            uint32_t *offState):
    GenericNode21<midi_cmd_t,1,
                q15_t,outputSize,
                q15_t,outputSize>(src1,src2,dst),
                mChannelNb(channel_nb),
                mOffState(offState){
      
        on = false;
        mNbSamplesPerMs = (int32_t)(SAMPLINGFREQ / 1000);
        state = kIdle;

        delay(0);  // default values...
        attack(40);
        hold(5);
        decay(35);
        sustain(22282); // q15_t
        release(40);
        releaseNoteOn(40);

        nb = 0;
        drum = false;
                };

    void setDrum(bool r)
    {
        drum = r;
    }

    void noteOn(void)
    {
        //printf("Note on %d\n",nb);
        if (state == kIdle || state == kDelay || release_forced_count == 0) {
            count = delay_count;
            attenuation = 0;
            if (count > 0) {
                state = kDelay;
                attenuationInc = 0;
            } else {
                state = kAttack;
                count = attack_count;
                attenuationInc = Q31_MIDRANGE / (int32_t)count;
            }
        } else if (state != kForced) {
            state = kForced;
            count = release_forced_count;
            attenuationInc = (-attenuation) / (int32_t)count;
        }
    }

    void noteOff(void)
    {
        //printf("Note off %d\n",nb);
        if (state != kIdle && state != kForced) {
            state = kRelease;
            count = release_count;
            attenuationInc = (-attenuation) / (int32_t)count;
        }
    }

    int prepareForRunning() final
    {
        if (this->willOverflow())
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(CG_SUCCESS);
    };

    __attribute__((section(".time_critical.MIDIEnv")))
    int run() final 
    {
        midi_cmd_t *src1=this->getReadBuffer1();
        q15_t *a=this->getReadBuffer2();
        q15_t *b=this->getWriteBuffer();
        q31_t v,out;

        
        if (src1->cmd == NOTE_OFF)
        {
        	noteOff();
            drum = false;
        }
        if (src1->cmd == NOTE_ON)
        {
        	noteOn();
            if (src1->inst>=129)
            {
                drum = true;
            }
            else 
            {
                drum=false;
            }
        }


        
        if (drum)
        {
            memcpy(b,a,sizeof(q15_t)*outputSize);
            nb += outputSize;
            return(CG_SUCCESS);
        }

        if (state == kIdle)
        {
            memset(b,0,sizeof(q15_t)*outputSize);
            nb += outputSize;
            return(CG_SUCCESS);
        }

        for(int i=0;i<outputSize;i++)
        {
            if (count == 0)
            {
               //printf("End state %d at %d\n",state,nb);

               switch(state)
               {
                 case kAttack:
                   count = hold_count;
                   if (count > 0)
                   {
                    state = kHold;
                    attenuation = Q31_MIDRANGE;
                    attenuationInc = 0;
                   }
                   else
                   {
                     state = kDecay;
                     count = decay_count;
                     attenuationInc = (sustain_mult - Q31_MIDRANGE) / (int32_t)count;
                   }
                 break;

                 case kHold:
                     state = kDecay;
                     count = decay_count;
                     attenuationInc = (sustain_mult - Q31_MIDRANGE) / (int32_t)count;
                 break;

                 case kDecay:
                   state = kSustain;
                   count = 0xFFFF;
                   attenuation = sustain_mult;
                   attenuationInc = 0;
                 break;

                 case kSustain:
                    count = 0xFFFF;
                 break;

                 case kRelease:
                    state = kIdle;
                 break;

                 case kForced:
                   attenuation = 0;
                   count = delay_count;
                   if (count > 0)
                   {
                    state = kDelay;
                    attenuationInc = 0;
                   }
                   else
                   {
                    state = kAttack;
                    count = attack_count;
                    attenuationInc = Q31_MIDRANGE / (int32_t)count;
                   }
                 break;

                 case kDelay:
                    state = kAttack;
                    count = attack_count;
                    attenuationInc = Q31_MIDRANGE / count;
                 break;

                 case kIdle:
                       count = 0xFFFF;
                 break;
               }
            }
            if (state == kIdle)
            {
               b[i] = 0;
               *mOffState = *mOffState | (1 << mChannelNb);
            }
            else
            {
               v = a[i];
               out = ((q63_t) v * attenuation) >> 31;
               b[i] = __SSAT(out, 16);
            }
            attenuation += attenuationInc;
            count--;
            nb++;
        }

        return(CG_SUCCESS);
    };

    void delay(uint16_t milliseconds) {
        delay_count = milliseconds2count(milliseconds);
    }
    void attack(uint16_t milliseconds) {
        attack_count = milliseconds2count(milliseconds);
        if (attack_count == 0) attack_count = 1;
    }
    void hold(uint16_t milliseconds) {
        hold_count = milliseconds2count(milliseconds);
    }
    void decay(uint16_t milliseconds) {
        decay_count = milliseconds2count(milliseconds);
        if (decay_count == 0) decay_count = 1;
    }
    void sustain(q15_t level) {
        if (level < 0) level = 0;
        
        // Max level will correspond to Q31_MIDRANGE
        // so we shift by 15 and not 16
        sustain_mult = level<<15;
    }
    void release(uint16_t milliseconds) {
        release_count = milliseconds2count(milliseconds);
        if (release_count == 0) release_count = 1;
    }
    void releaseNoteOn(uint16_t milliseconds) {
        release_forced_count = milliseconds2count(milliseconds);
        if (release_count == 0) release_count = 1;
    }

    uint16_t milliseconds2count(uint16_t milliseconds) {
        if (milliseconds < 0) milliseconds = 0;
        uint32_t c = milliseconds*mNbSamplesPerMs;
        if (c > 65535) c = 65535; // allow up to 11.88 seconds
        return c;
    }

protected:
	bool on;
	int32_t mNbSamplesPerMs;
    enum envState state;
    uint16_t count;      // how much time remains in this state, in 8 sample units


    uint16_t delay_count;
    uint16_t attack_count;
    uint16_t hold_count;
    uint16_t decay_count;
    int32_t  sustain_mult;
    uint16_t release_count;
    uint16_t release_forced_count;

    q31_t  attenuation;
    q31_t  attenuationInc;

    int nb;
    bool drum;

    int mChannelNb;
    uint32_t *mOffState;
};