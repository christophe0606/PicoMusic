/*****************************************************************************************************************

   synth_Playtune

   This an audio object for the PJRC Teensy Audio Library that reads an encoded "Playtune" bytestream
   created from a MIDI file. It has up to 16 simultaneous sound generators that are internally mixed to
   produce one monophonic audio stream.

   Sounds are created from sampled one-cycle waveforms for any number of instruments, each with its own
   attack-hold-decay-sustain-release envelope. Percussion sounds (from MIDI channel 10) are generated from
   longer sampled waveforms of a complete instrument strike. Each generator's volume is independently
   adjusted according to the MIDI velocity of the note being played before all channels are mixed.

   The public member functions of this class are:

     begin(const byte *bytestream)
        Play the specified bytestream, which we expect to be in PROGMEM (flash) memory.

     begin(const byte *bytestream, unsigned int num_gens)
        Play the specified bytesteam using num_gens sound generators.
        This is helpful only for old Playtune bytestream files that don't contain this information.

     isPlaying()
        Return true if the bytestream is still playing.

     stop()
        Stop playing the bytestream now.

   There are instructions in the code for adding more regular and percussion instruments,
   for changing the AHDSR amplitude envelope, and for changing the mixer levels.

   The bytestream is a compact series of commands that turn notes on and off, start a waiting
   period until the next note change, and specify instruments. The details are below.
   The easiest way to create the bytestream from a MIDI file is to use the Miditones program,
   which is open source at https://github.com/lenshustek/miditones.
   The best options to use for this version of Playtune are: -v -i -pt -d, and also -tn if you
   want to generate notes on more than the default 6 channels.

   This is the latest in a series of Playtune music generators for Arduino and Teensy
   microcontrollers dating back to 2011. Here are links to some of the others:
      https://github.com/LenShustek/arduino-playtune
      https://github.com/LenShustek/ATtiny-playtune
      https://github.com/LenShustek/playtune_poll
      https://github.com/LenShustek/playtune_samp

  -- Len Shustek, 23 August 2016
**********************************************************************************************************/
