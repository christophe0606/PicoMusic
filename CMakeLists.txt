cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

include(pico_extras_import_optional.cmake)

project(pico_examples C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        )
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()

# Initialize the SDK
pico_sdk_init()


add_executable(stream
        App/Sources/main.cpp
        App/Sources/cmsis_texture.c 
        AudioGraph/audio_scheduler.cpp 
        LCDGraph/lcd_scheduler.cpp
        Playtune_synth/instruments.cpp 
        Playtune_synth/synth_Playtune_waves.cpp
        Songs/empire.c
        Songs/songs.c
        )

target_include_directories(stream PUBLIC . 
    ${STREAM}/Include/cg/nodes/cpp
    App/Includes
    Nodes 
    Configuration 
    AudioGraph
    LCDGraph
    Songs
    )


pico_generate_pio_header(stream ${CMAKE_CURRENT_LIST_DIR}/Nodes/RP2/lcd/st7789_lcd.pio)

add_subdirectory(${DSP}/Source bin_dsp)

target_compile_options(CMSISDSP PRIVATE -Ofast -ffunction-sections -fdata-sections)

target_compile_definitions(stream PUBLIC PICO_AUDIO_PWM_PIO=1)
# pull in common dependencies and adc hardware support
target_link_libraries(stream 
    pico_stdlib 
    pico_audio_pwm
    pico_multicore
    hardware_dma 
    hardware_adc
    hardware_irq
    hardware_clocks
    CMSISDSP
    )


# enable usb output, disable uart output
    pico_enable_stdio_usb(stream 1)
    pico_enable_stdio_uart(stream 0)
    
# create map/bin/hex file etc.
pico_add_extra_outputs(stream)

# add url via pico_set_program_url

