# PicoMusic
Music generation and spectrum visualization on RP2040 with [CMSIS-Stream](https://github.com/ARM-software/CMSIS-Stream) and [CMSIS-DSP](https://github.com/ARM-software/CMSIS-DSP).

## Introduction

The demo is made of 2 CMSIS-Stream graphs. Core0 is running an audio graph.

Core1 is running an LCD graph.

The audio graph is synthesizing the sound and sending it to the PWM driver and Core 1.

The LCD graph is reading the audio data and generating a framebuffer to display a spectrum, amplitude and texture background (with some animation and blending).

[Arm-2D](https://github.com/ARM-software/Arm-2D) is not yet integrated.

![PicoMusic](Documentation/PicoMusic.jpg)

https://github.com/christophe0606/PicoMusic/assets/48906714/ff16c501-edd5-4abd-ae0b-3ffc5eb22457

## Audio graph

![audio_graph](Pictures/audio_graph.svg)

## LCD Graph

![lcd_graph](Pictures/lcd_graph.svg)

## Connection to speaker

![PicoAmp_bb](Documentation/PicoAmp_bb.png)

![PicoAmp_scheme](Documentation/PicoAmp_scheme.jpg)

The transistor is a NPN 2222A

Speaker has a resistance of 4 Ω

The LCD is https://www.waveshare.com/wiki/Pico-LCD-1.3

And we are using a https://www.waveshare.com/pico-quad-expander.htm to connect the LCD



## How to build

First, you need to be able to build the Pico examples and have the pico-extra since the demo is using audio drivers from pico-extra. Refer to the Pico documentation to know what to install.

```shell
mkdir build.tmp
cd build.tmp
cmake -DDSP=/root/CMSIS-DSP \
  -DSTREAM=/root/CMSIS-Stream \
  -DCMSISCORE=/root/CMSIS_5/CMSIS/Core \
  ..
make
```

Where `root` is the path where you have installed the CMSIS libraries.

You can clone the CMSIS libraries with:

```shell
git clone https://github.com/ARM-software/CMSIS-DSP.git
git clone https://github.com/ARM-software/CMSIS-Stream.git
git clone https://github.com/ARM-software/CMSIS_5.git
```



## Copyright and licensing information

## MIDI Project

The MIDI part is coming from the [Playtune_synth 
   project](https://github.com/LenShustek/Playtune_synth) Copyright (C) 2016, Len Shustek

The Playtune_synth files have been strongly modified and refactored to be integrated in the CMSIS-Stream framework. They are clearly identified (always inside a Playtune_synth folder) and Copyright (C) 2016, Len Shustek.

Playtune_synth files are covered by their original MIT license. 

## Pico SDK and Extras

The LCD Node is based upon an example of PIO driver from the Pico examples. The example has been modified to be integrated in CMSIS-Stream.

It is Copyright (c) 2020 Raspberry Pi (Trading) Ltd and covered by a BSD-3 license.

The PWM node is based upon a Pico playground audio example using the drivers from pico-extra.The example has been modified to be integrated in CMSIS-Stream.

It is Copyright (c) 2020 Raspberry Pi (Trading) Ltd and covered by a BSD-3 license.

## Other files

Other files are covered by an Apache licence and have been developped by Arm.

