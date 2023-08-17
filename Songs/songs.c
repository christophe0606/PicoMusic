#include <stdint.h>

#include "songs.h"
#include "Nodes/Playtune_synth/Sequencer/c_component.h"
#include <stdlib.h>

extern const uint8_t empire[];
extern const uint8_t dorian[];

//#define DEBUG_MIDI 

// 440 Hz signal
/*
const uint8_t debugSong[] = {CMD_INSTRUMENT,48,
CMD_PLAYNOTE,69,60,0x7F,0xFF,CMD_STOP
};
*/

const uint8_t debugSong[] = {CMD_INSTRUMENT,0,
CMD_PLAYNOTE,40,127,0x7F,0xFF,CMD_STOP
};


#ifdef DEBUG_MIDI 
static const uint8_t* _allSongs[]={debugSong,NULL};
static const char* _names[]={"debug\n",NULL};
#else
static const uint8_t* _allSongs[]={dorian,empire,NULL};
static const char* _names[]={"Dorian\n","The Empire strikes back\n",NULL};

//static const uint8_t* _allSongs[NBSONG]={empire,overture,toccata,pink,bohemian,champion};
//static const char* _names[NBSONG]={"empire\n","overture\n","toccata\n","pink\n","bohemian\n","champion\n"};
#endif 

const uint8_t** allSongs=(const uint8_t**)_allSongs;
const char** names=(const char**)_names;
