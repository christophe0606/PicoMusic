/* CMSIS-Stream nodes made from Playtune_synth 
   project at https://github.com/LenShustek/Playtune_synth

   Copyright (C) 2016, Len Shustek

   Some parts of synth_Playtune.cpp
   Modified for the PicoMusic demo by Arm (simplified)

*/

#pragma once 

#include "Nodes/Playtune_synth/Playtune.h"

template<typename IN,int inputSize,
         typename OUT,int outputSize>
class Waveform;

template<int outputSize>
class Waveform<midi_cmd_t,1,
           q15_t,outputSize>: 
GenericNode<midi_cmd_t,1,
              q15_t,outputSize>
{
public:
    Waveform(FIFOBase<midi_cmd_t> &src,
            FIFOBase<q15_t> &dst,
            int channel_nb,
            uint32_t *offState):
    GenericNode<midi_cmd_t,1,
                q15_t,outputSize>(src,dst),
                mChannelNb(channel_nb),
                mOffState(offState){
      
             on = false;
             magnitude = 0;
             phase=0;
             waveform = getInstrumentWaveForm(0);
             mPhaseIncrement=0;
                };

    int prepareForRunning() final
    {
        if (this->willOverflow())
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(CG_SUCCESS);
    };


    __attribute__((section(".time_critical.MIDIWav")))
    int run() final 
    {
        midi_cmd_t *c=this->getReadBuffer();
        q15_t *b=this->getWriteBuffer();

        //memset(b,0,sizeof(float)*outputSize);
        //return(CG_SUCCESS);

        // Off is controlled indirectly by the
        // enveloppe generator so that we do not
        // stop in middle of a wave and create
        // clicks on the speaker
        if (*mOffState & (1<<mChannelNb))
        {
        	 on = false;
             magnitude = 0;
             phase=0;
             waveform = getInstrumentWaveForm(0);
             mPhaseIncrement=0;
        }
        if (c->cmd == NOTE_ON)
        {
            *mOffState = *mOffState & ~((1<<mChannelNb));
        	on = true;
            phase = 0;

        	magnitude = c->amp;

        	

        	if (c->inst>=129)
            {
               isDrum = true;
               instrumentID = c->inst - 129;
               waveform = getDrumWaveForm(instrumentID);
  
               mPhaseIncrement =getDrumWaveFormPhaseIncrement(instrumentID);
               phase = 0; // start at the beginning
               drum_ending_sample_index = getDrumEndingSampleIndex(instrumentID); // remember the end of the waveform
            }
            else
            {
               isDrum = false;
               instrumentID = c->inst;
               waveform = getInstrumentWaveForm(instrumentID);
            }

            if (!isDrum)
            {
              //printf("%f\r\n",c->tune);
              mPhaseIncrement = c->phaseIncrement;
            }
        }

        // With memory sharing the buffer may
        // contain garbage. So we need to write
        // something to it.
        if (!on)
        {
        	memset(b,0,sizeof(q15_t)*outputSize);
        	return(CG_SUCCESS);

        }

        if ((c->cmd == NO_MIDI_CMD) || (c->cmd == NOTE_ON))
        {
            //printf("%d %d\r\n",mPhaseIncrement,magnitude);
                if (isDrum)
                {
                    #if 0
                    int16_t d,val1,val2;
                    int32_t frac;
                    #endif
                    int16_t val1;
                    int16_t index1,index2;
            
                    for(int i=0;i<outputSize;i++)
                    {
                        index1 = phase >> 20;
                        index2 = index1 + 1;
                        if (index2 >= drum_ending_sample_index)
                        {
                           b[i] = 0;
                        }
                        else
                        {
                           val1 = waveform[index1];
                           // The Pico HW interpolator could be used
                           // here to interpolate between sample at index1
                           // and index2 using the fractional part of the
                           // phase increment
                           b[i] = __SSAT((val1 * magnitude) >> 15,16);
                        }
                        phase = (phase + mPhaseIncrement);
            
                    }
                }
                else
                {
                    //int16_t d,val1,val2;
                    int16_t val1;
                    //int32_t frac;
            
                    for(int i=0;i<outputSize;i++)
                    {
                        val1 = waveform[phase>>24];
                        // The Pico HW interpolator could be used
                        // here to interpolate between sample at index1
                        // and index2 using the fractional part of the
                        // phase increment
                        b[i] = __SSAT(((q31_t)val1 * magnitude) >> 15,16);
            
                        phase = (phase + mPhaseIncrement);
            
                    }
                }
        }

        
        return(CG_SUCCESS);
    };
protected:
	bool on;
	uint32_t mPhaseIncrement;
    uint32_t phase;
    q15_t magnitude;
    const int16_t* waveform;
    uint16_t drum_ending_sample_index;
    bool isDrum;
    int instrumentID;
    int mChannelNb;
    uint32_t *mOffState;
};