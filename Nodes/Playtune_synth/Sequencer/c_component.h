#ifndef _SEQUENCER_H_
#define _SEQUENCER_H_ 

enum midi_cmd_k {
 CMD_PLAYNOTE =  0x90,    /* play a note: low nibble is generator #, note is next byte */
 CMD_STOPNOTE =   0x80,    /* stop a note: low nibble is generator # */
 CMD_RESTART =   0xe0,    /* restart the score from the beginning */
 CMD_INSTRUMENT= 0xc0,
 CMD_STOP =   0xf0
};

#endif