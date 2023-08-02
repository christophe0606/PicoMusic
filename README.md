# PicoMusic
Music generation and spectrum visualization on RP2040 with [CMSIS-Stream](https://github.com/ARM-software/CMSIS-Stream) and [CMSIS-DSP](https://github.com/ARM-software/CMSIS-DSP).

## Introduction

The demo is made of 2 CMSIS-Stream graphs. Core0 is running an audio graph.

Core1 is running an LCD graph.

The audio graph is synthesizing the sound and sending it to the PWM driver and Core 1.

The LCD graph is reading the audio data and generating a framebuffer to display a spectrum, amplitude and texture background (with some animation and blending).

[Arm-2D](https://github.com/ARM-software/Arm-2D) is not yet integrated.

![PicoMusic](/Users/cfavergeon/Documents/Pico/MyPicoProjects/PicoMusic/Documentation/PicoMusic.jpeg)



## Audio graph

![audio_graph](/Users/cfavergeon/Documents/Pico/MyPicoProjects/PicoMusic/Pictures/audio_graph.svg)

## LCD Graph

![lcd_graph](/Users/cfavergeon/Documents/Pico/MyPicoProjects/PicoMusic/Pictures/lcd_graph.svg)

## Connection to speaker

![PicoAmp_bb](/Users/cfavergeon/Documents/Pico/MyPicoProjects/PicoMusic/Documentation/PicoAmp_bb.jpg)

The transistor is a NPN 2222A

Speaker has a resistance of 4 Ω

## How to build

First, you need to be able to build the Pico examples. Refer to the Pico documentation to know what to install.

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

The MIDI part is coming from the [Playtune_synth 
   project](https://github.com/LenShustek/Playtune_synth) Copyright (C) 2016, Len Shustek

The Playtune_synth files have been strongly modified and refactored to be integrated in the CMSIS-Stream framework. They are crealy identified (always inside a Playtune_synth folder) and Copyright (C) 2016, Len Shustek.

Playtune_synth files are covered by their original MIT license. Other files are covered by an Apache licence.

