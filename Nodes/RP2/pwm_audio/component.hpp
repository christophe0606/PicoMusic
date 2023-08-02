#pragma once

#include "pico/audio_pwm.h"


#include "c_component.h"




template<typename IN,int inputSize>
class PWMAudio;


template<int inputSize>
class PWMAudio<q15_t,inputSize>: 
public GenericSink<q15_t,inputSize>
{
public:
    PWMAudio(FIFOBase<q15_t> &dst):
    GenericSink<q15_t,inputSize>(dst){

        audio_started=false;
        nb_prefilled_buffer = 0;

        error = CG_SUCCESS;

        audio_format = {
            .sample_freq = 57445,
            .format = AUDIO_BUFFER_FORMAT_PCM_S16,
            .channel_count = 1,
        };

        producer_format = {
            .format = &audio_format,
            .sample_stride = 2
        };
        
        producer_pool = audio_new_producer_pool(&producer_format, PWM_AUDIO_BUFFER_COUNT,inputSize);
        if (producer_pool==NULL)
        { 
            error = CG_INIT_FAILURE;
            return;
        }
        output_format = audio_pwm_setup(&audio_format, -1, &default_mono_channel_config);
        if (!output_format)
        {
            error = CG_INIT_FAILURE;
            return;
        }
        bool ok = audio_pwm_default_connect(producer_pool, false);
        if (!ok)
        {
            error = CG_INIT_FAILURE;
            return;
        }
    };

    ~PWMAudio()
    {
      if (audio_started)
      {
          audio_pwm_set_enabled(false);
      }
    }

    int prepareForRunning() final
    {
        if (this->willUnderflow())
        {
           return(CG_SKIP_EXECUTION_ID_CODE); // Skip execution
        }

        return(0);
    };

     __attribute__((section(".time_critical.PWMAudio")))
    int run() final{
        q15_t *input=this->getReadBuffer();
        if (error!=CG_SUCCESS)
        {
            return(error);
        }    

        struct audio_buffer *buffer = take_audio_buffer(producer_pool, true);
        memcpy(buffer->buffer->bytes,input,sizeof(q15_t)*inputSize);
        buffer->sample_count = inputSize;
        give_audio_buffer(producer_pool, buffer);

        if (!audio_started)
        {
            nb_prefilled_buffer ++; 
            if (nb_prefilled_buffer==PWM_AUDIO_BUFFER_COUNT)
            {
                audio_started=true;
                audio_pwm_set_enabled(true);
            }
        }
        return(CG_SUCCESS);
    };

protected:
    bool synchronize;
    audio_format_t audio_format;
    audio_buffer_format producer_format;
    struct audio_buffer_pool *producer_pool;
    const struct audio_format *output_format;
    int error;
    bool audio_started;
    int nb_prefilled_buffer;
};
