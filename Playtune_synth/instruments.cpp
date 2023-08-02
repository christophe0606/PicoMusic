/*  From Playtune_synth project at https://github.com/LenShustek/Playtune_synth

    Copyright (C) 2016, Len Shustek

    Some parts of synth_Playtune.cpp
    Modified for the PicoMusic demo by Arm
*/

#include <cstdint>
#include <cstdlib>
#include "Nodes/Playtune_synth/Playtune.h"

const int16_t * instrument_waveforms[15] = {// this order must match the enum below
  waveform_aguitar_0033,
  waveform_altosax_0001,  
  waveform_birds_0011, 
  waveform_cello_0005, 
  waveform_clarinett_0001 ,
  waveform_clavinet_0021, 
  waveform_dbass_0015, 
  waveform_ebass_0037, 
  waveform_eguitar_0002,  
  waveform_eorgan_0064, 
  waveform_epiano_0044, 
  waveform_flute_0001,  
  waveform_oboe_0002,  
  waveform_piano_0013, 
  waveform_violin_0003,
};



enum  instrument_index_t { // instrument indexes
  I_AGUITAR, I_SAX, I_BIRDS, I_CELLO, I_CLARINET, I_CLAVINET, I_DBASS, I_EBASS,
  I_EGUITAR, I_ORGAN, I_EPIANO, I_FLUTE, I_OBOE, I_PIANO, I_VIOLIN
};

const uint8_t instrument_patch_map[128]  = { // map from MIDI patch numbers to instrument indexes
  /*1-8: DBASS*/ I_DBASS, I_DBASS, I_EBASS, I_DBASS, I_EBASS, I_EBASS, I_EBASS, I_EBASS,
  /*9-16: chromatic percussion*/ I_CLAVINET, I_CLAVINET, I_CLAVINET, I_CLAVINET, I_CLAVINET, I_CLAVINET, I_CLAVINET, I_CLAVINET,
  /*17-24: Organ*/ I_ORGAN, I_ORGAN, I_ORGAN, I_ORGAN, I_ORGAN, I_ORGAN, I_ORGAN, I_ORGAN,
  /*25-32: guitar*/ I_AGUITAR, I_EGUITAR, I_EGUITAR, I_EGUITAR, I_EGUITAR, I_EGUITAR, I_EGUITAR, I_AGUITAR,
  /*33-40: bass*/ I_DBASS, I_EBASS, I_EBASS, I_DBASS, I_DBASS, I_DBASS, I_EBASS, I_EBASS,
  /*41-48: strings*/ I_VIOLIN, I_VIOLIN, I_CELLO, I_CELLO, I_VIOLIN, I_VIOLIN, I_VIOLIN, I_VIOLIN,
  /*49-56: ensemble*/ I_VIOLIN, I_VIOLIN, I_VIOLIN, I_VIOLIN, I_VIOLIN, I_VIOLIN, I_VIOLIN, I_VIOLIN,
  /*57-66: brass*/ I_DBASS, I_DBASS, I_DBASS, I_DBASS, I_DBASS, I_DBASS, I_DBASS, I_DBASS,
  /*65-72: reed*/ I_SAX, I_SAX, I_SAX, I_OBOE, I_OBOE, I_SAX, I_SAX, I_OBOE,
  /*73-80: pipe*/ I_FLUTE, I_FLUTE, I_FLUTE, I_FLUTE, I_FLUTE, I_FLUTE, I_FLUTE, I_FLUTE,
  /*81-88: synth lead*/ I_EGUITAR, I_EGUITAR, I_EGUITAR, I_EGUITAR, I_EGUITAR, I_EGUITAR, I_EGUITAR, I_EGUITAR,
  /*89-96: synth pad*/ I_VIOLIN, I_VIOLIN, I_VIOLIN, I_VIOLIN, I_VIOLIN, I_VIOLIN, I_VIOLIN, I_VIOLIN,
  /*97-104: synth effects*/ I_BIRDS, I_BIRDS, I_BIRDS, I_BIRDS, I_BIRDS, I_BIRDS, I_BIRDS, I_BIRDS,
  /*105-112: ethnic*/ I_ORGAN, I_ORGAN, I_ORGAN, I_ORGAN, I_ORGAN, I_ORGAN, I_ORGAN, I_ORGAN,
  /*113-120: percussive*/ I_EBASS, I_EBASS, I_EBASS, I_EBASS, I_EBASS, I_EBASS, I_EBASS, I_EBASS,
  /*121-128: sound effects*/ I_BIRDS, I_BIRDS, I_BIRDS, I_BIRDS, I_BIRDS, I_BIRDS, I_BIRDS, I_BIRDS
};

#ifdef DEBUG_MIDI 
extern const int16_t sine[257];
#endif

const int16_t *getInstrumentWaveForm (int16_t instrumentID)
{
  #ifdef DEBUG_MIDI 
    return(sine);
  #else
  return(instrument_waveforms[instrument_patch_map[instrumentID]]);
  #endif
}

const int16_t *drum_waveforms[] = {
  waveform_base_drum_04, waveform_snare_drum_1, waveform_mid_high_tom,
  waveform_cymbal_2, waveform_hi_bongo, waveform_steel_bell_c6,
  NULL /* stopper so we can iterate over drum indexes */
};

const uint16_t drum_waveform_frequencies[] = {
  4000, 8000, 8000, 8000, 4000, 4000
};


static const uint32_t drum_waveform_phase_increment[6] = {
1168228,2336456,2336456,2336456,1168228,1168228,};

// (5) add a symbolic index name for the percussion instrument at the end of this list

enum drum_index_t { // drum indexes
  D_BASS, D_SNARE, D_TOM, D_CYMBAL, D_BONGO, D_BELL
};

const int16_t drum_patch_map[128]  =  { // map from MIDI percussion instruments to drum indexes
  /*01-16*/ D_BASS, D_SNARE, D_TOM, D_CYMBAL, D_BONGO, D_BELL, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS,
  /*17-32*/ D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS,
  /*33-48*/ D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_SNARE, D_SNARE, D_SNARE, D_TOM, D_CYMBAL, D_TOM, D_CYMBAL, D_TOM, D_CYMBAL, D_TOM, D_TOM,
  /*49-64*/ D_CYMBAL, D_TOM, D_CYMBAL, D_CYMBAL, D_BELL, D_SNARE, D_CYMBAL, D_BELL, D_CYMBAL, D_CYMBAL, D_CYMBAL, D_BONGO, D_BONGO, D_BONGO, D_BONGO, D_BONGO,
  /*65-80*/ D_TOM, D_TOM, D_BELL, D_BELL, D_CYMBAL, D_CYMBAL, D_BELL, D_BELL, D_BONGO, D_BONGO, D_BONGO, D_BONGO, D_BONGO, D_TOM, D_TOM, D_BELL,
  /*81-96*/ D_BELL, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS,
  /*97-112*/ D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS,
  /*113-128*/ D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS, D_BASS
};

const int16_t *getDrumWaveForm (int16_t instrumentID)
{
  return(drum_waveforms[drum_patch_map[instrumentID]]);
}

const uint32_t getDrumWaveFormPhaseIncrement(int16_t instrumentID)
{
  return(drum_waveform_phase_increment[drum_patch_map[instrumentID]]);
}

const uint16_t getDrumWaveFormFrequency (int16_t instrumentID)
{
  return(drum_waveform_frequencies[drum_patch_map[instrumentID]]);
}

const uint16_t getDrumEndingSampleIndex (int16_t instrumentID)
{
 return (drum_waveform_size[instrumentID] - 1);
}

