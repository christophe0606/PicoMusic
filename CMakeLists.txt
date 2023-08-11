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
        App/Sources/cmsis_logo.c 
        AudioGraph/audio_scheduler.cpp 
        LCDGraph/lcd_scheduler.cpp
        Playtune_synth/instruments.cpp 
        Playtune_synth/synth_Playtune_waves.cpp
        Songs/empire.c
        Songs/songs.c
        Nodes/Arm2D/Arm2D/arm_2d_scene_cmsis_stream.c
        Nodes/Arm2D/AmplitudeWidget/draw_amplitude.c
        Nodes/Arm2D/SpectrumWidget/draw_spectrum.c
        )

target_include_directories(stream PUBLIC . 
    ${CMSISSTREAM}/Include/cg/nodes/cpp
    App/Includes
    Nodes
    Nodes/Arm2D/Layer
    Configuration/Includes
    AudioGraph
    LCDGraph
    Songs
    )

# Disable Arm-2D C++ warnings for C types that are not used 
# from C++ side
set_source_files_properties(LCDGraph/lcd_scheduler.cpp PROPERTIES COMPILE_FLAGS -Wno-subobject-linkage)
set_source_files_properties(App/Sources/main.cpp PROPERTIES COMPILE_FLAGS -Wno-subobject-linkage)

# Add Arm-2D and indirectely CMSIS-DSP that is also used by Arm-2D
option(ARM2D_CONTROLS "" ON)
option(ARM2D_HELPER "" ON)
option(ARM2D_LCD_PRINTF "" ON)
option(ARM2D_BENCHMARK_GENERIC "" OFF)
option(ARM2D_BENCHMARK_WATCHPANEL "" OFF)
option(ARM2D_ALPHA_BLENDING "" ON)
option(ARM2D_TRANSFORM "" ON)
add_subdirectory(${ARM2D_RP2040} arm2d_rp2040_bin)
# Disable partial framebuffer
target_compile_definitions(ARM2D PUBLIC 
    __ARM_2D_CFG_UNSAFE_IGNORE_ALPHA_255_COMPENSATION__ 
    __DISP0_CFG_PFB_BLOCK_HEIGHT__=240 
    __DISP0_CFG_DISABLE_NAVIGATION_LAYER__=1)


target_compile_definitions(stream PUBLIC PICO_AUDIO_PWM_PIO=1)
# pull in common dependencies and adc hardware support
target_link_libraries(stream 
    pico_stdlib 
    pico_audio_pwm
    pico_multicore
    hardware_pio
    hardware_dma 
    hardware_adc
    hardware_irq
    hardware_interp
    hardware_clocks
    arm2d_rp2040
    )


# enable usb output, disable uart output
    pico_enable_stdio_usb(stream 1)
    pico_enable_stdio_uart(stream 0)
    
# create map/bin/hex file etc.
pico_add_extra_outputs(stream)

# add url via pico_set_program_url

