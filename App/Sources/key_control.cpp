#include "key_control.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"

// For Node IDs
#include "AudioGraph/audio_scheduler.h"


void initKeyControl(DigitalGainNode *&dg,SequencerNode *&s)
{
  void *p; 
  p=get_audio_scheduler_node(AUDIO_OGAIN_ID); 
  dg=static_cast<Gain<q15_t,AUDIO_BLOCK_LENGTH,q15_t,AUDIO_BLOCK_LENGTH>*>(p); 
  p=get_audio_scheduler_node(AUDIO_NOTESEQUENCER_ID); 
  s=static_cast<Sequencer<midi_cmd_t,1>*>(p);

  gpio_init(KEYA_ID);
  gpio_set_dir(KEYA_ID, GPIO_IN);
  gpio_pull_up(KEYA_ID);

  gpio_init(KEYB_ID);
  gpio_set_dir(KEYB_ID, GPIO_IN);
  gpio_pull_up(KEYB_ID);

  gpio_init(KEYC_ID);
  gpio_set_dir(KEYC_ID, GPIO_IN);
  gpio_pull_up(KEYC_ID);

  gpio_init(KEYD_ID);
  gpio_set_dir(KEYD_ID, GPIO_IN);
  gpio_pull_up(KEYD_ID);
}

static inline bool key_volume_up(int c)
{
   return((c == '=') || (c == '+') || !gpio_get(KEYC_ID));
   
}

static inline bool key_volume_down(int c)
{
   return((c == '-') || !gpio_get(KEYB_ID));
}

static inline bool key_next_song(int c)
{
   return((c == 'n') || !gpio_get(KEYD_ID));
}

static inline bool key_quiet(int c)
{
   return((c == 'q') || !gpio_get(KEYA_ID));
}

void processKey(DigitalGainNode *g,SequencerNode *seq)
{
    float currentGain = g->getGain();
 
    int c = getchar_timeout_us(0);

    if (key_next_song(c))
    {
        seq->nextSong();
    }

    if (key_volume_down(c))
    {
        float newGain = currentGain-0.1f;
        if (newGain>=0.0f)
        {
            g->setGain(newGain);
            printf("gain = %f\n",newGain);
        }
    }

    if (key_quiet(c))
    {
        g->setGain(0.0f);
        printf("gain = 0.0\n");
    }

    if (key_volume_up(c))
    {
        g->setGain(currentGain+0.1f);
        printf("gain = %f\n",currentGain+0.1f);
    }
}
