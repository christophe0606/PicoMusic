/* Originally synth_Playtune.cpp

    The header file for synth_Playtune, an audio object for the PJRC Teensy Audio Library.
    See synth_Playtune.cpp for more information.

    Copyright (C) 2016, Len Shustek

    Modified a lot by Arm for this Pico demo. The header has been
    split into several different headers and some part of the code
    has been removed.

    Copyright (C) 2023, Arm
*/
#ifndef _PLAYTUNE_H_ 
#define _PLAYTUNE_H_

#include <cstdint>


extern const int16_t sine[257];
extern const int16_t waveform_aguitar_0033[257];
extern const int16_t waveform_altosax_0001[257];
extern const int16_t waveform_birds_0011[257];
extern const int16_t waveform_cello_0005[257];
extern const int16_t waveform_clarinett_0001[257];
extern const int16_t waveform_clavinet_0021[257];
extern const int16_t waveform_dbass_0015[257];
extern const int16_t waveform_ebass_0037[257];
extern const int16_t waveform_eguitar_0002[257];
extern const int16_t waveform_eorgan_0064[257];
extern const int16_t waveform_epiano_0044[257];
extern const int16_t waveform_flute_0001[257];
extern const int16_t waveform_oboe_0002[257];
extern const int16_t waveform_piano_0013[257];
extern const int16_t waveform_violin_0003[257];

extern const int16_t waveform_base_drum_04[];
extern const int16_t waveform_snare_drum_1[];
extern const int16_t waveform_mid_high_tom[];
extern const int16_t waveform_cymbal_2[];
extern const int16_t waveform_hi_bongo[];
extern const int16_t waveform_steel_bell_c6[];

extern const uint16_t drum_waveform_size[6];

extern const int16_t *getInstrumentWaveForm (int16_t instrumentID);
extern const int16_t *getDrumWaveForm (int16_t instrumentID);
extern const uint16_t getDrumWaveFormFrequency (int16_t instrumentID);
extern const uint16_t getDrumEndingSampleIndex (int16_t instrumentID);
extern const uint32_t getDrumWaveFormPhaseIncrement(int16_t instrumentID);

#endif