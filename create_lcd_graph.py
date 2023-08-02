from cmsis_stream.cg.scheduler import *


from Nodes.RP2.FromOtherCore.component import *
from Nodes.RP2.lcd.component import *

# Block widget is doing belnding with RP2 interpolator
from Nodes.RP2.BlockWidget.component import *

from Nodes.Generic.FilterAndDecimate.component import *
from Nodes.Generic.Decimate.component import *
from Nodes.Generic.ImageBuffer.component import *
from Nodes.Generic.LineWidget.component import *
from Nodes.AppSpecific.FFTAmplitude.component import *

from Configuration.global_config import *
from Configuration.lcd_config import *

# Nb audio samples required for PAD+LCD_REFRESH milliseconds
NB_SAMPLES = SAMPLING_FREQ * (LCD_REFRESH+PAD)*1.0e-3


# Find a graph input size that is not too far
GRAPH_INPUT = 1
while(abs(GRAPH_INPUT - NB_SAMPLES) > 512):
    GRAPH_INPUT = 2*GRAPH_INPUT

print(f"Refresh rate of LCD graph is {GRAPH_INPUT/SAMPLING_FREQ*1000} ms")

# Number of samples for amplitude widget
AMP_OUTPUT = 256

AMPLITUDE_DECIMATE_FACTOR = GRAPH_INPUT // AMP_OUTPUT
print(f"Amplitude decimation factor = {AMPLITUDE_DECIMATE_FACTOR}")

# FFTSIZE
FFTSIZE = 256

FFT_DECIMATE_FACTOR = GRAPH_INPUT // FFTSIZE
print(f"FFT decimation factor = {FFT_DECIMATE_FACTOR}")


CONFIG="""#ifndef _LCD_PYTHON_GRAPH_CONFIG_H_ 
#define _LCD_PYTHON_GRAPH_CONFIG_H_

#define FFTSIZE %d 
#define AUDIO_BLOCK_LENGTH %d

#endif
"""

with open("Configuration/lcd_python_graph_config.h","w") as f:
    print(CONFIG % (FFTSIZE,AUDIO_BLOCK_LENGTH), file=f)

hann=Constant("hanningQ15")
win = Binary("arm_mult_q15",CType(Q15),FFTSIZE)

core0 = FromOtherCore("core0",CType(Q15),AUDIO_BLOCK_LENGTH,
                      queue="audio_queue",
                      blocking=True)
# increase the size from 2048 to higher to
# refresh LCD less often
#decimateForAmp = Decimate("decimateAmp",CType(Q15),NB,NB//AMPLITUDE_DECIMATE_FACTOR)
#decimateForFFT = Decimate("decimateFFT",CType(Q15),NB,NB//FFT_DECIMATE_FACTOR)

decimateForAmp = FilterAndDecimate("decimateAmp",CType(Q15),
    AUDIO_BLOCK_LENGTH,AUDIO_BLOCK_LENGTH//AMPLITUDE_DECIMATE_FACTOR,
    "nbTaps","coefs")
decimateForFFT = FilterAndDecimate("decimateFFT",CType(Q15),
    AUDIO_BLOCK_LENGTH,AUDIO_BLOCK_LENGTH//FFT_DECIMATE_FACTOR,
    "nbTaps","coefs")


fb = ImageBuffer("fb",WIDTH,HEIGHT,
    texture="cmsis_texture",
    texture_width=99,
    texture_height=240)

# audio real-time broken with the texture
#fb = ImageBuffer("fb",WIDTH,HEIGHT)

BLUE = 0x001F
RED = 0xF800

ampW = LineWidget("ampW",AMP_OUTPUT,color=BLUE)
FFTW = BlockWidget("FFTW",FFTSIZE,120,color=RED)
lcd = LCD("lcd")

toCmplx=ToComplex("toCmplx",CType(Q15),FFTSIZE)
fft = CFFT("fft",CType(Q15),FFTSIZE)
fftMag = FFTAmplitude("fftMag",FFTSIZE)


g = Graph()

g.connect(core0.o,decimateForAmp.i)
g.connect(decimateForAmp.o,ampW.i)
g.connect(fb.o,ampW.fb)

g.connect(core0.o,decimateForFFT.i)
g.connect(decimateForFFT.o,win.ia)
g.connect(hann,win.ib)


g.connect(win.o,toCmplx.i)
g.connect(toCmplx.o,fft.i)

g.connect(fft.o,fftMag.i)
g.connect(fftMag.o,FFTW.i)
g.connect(ampW.o,FFTW.fb)

g.connect(FFTW.o,lcd.i)


print("Generate graphviz and code")

conf=Configuration()

conf.CAPI=True
conf.CMSISDSP=True
conf.memoryOptimization=True
#conf.switchCase=False
conf.heapAllocation = True
conf.nodeIdentification = True

conf.cOptionalArgs=["queue_t *audio_queue",
                    "const q15_t* cmsis_texture",
                    "const int nbTaps",
                    "const q15_t* coefs"]

conf.schedName="lcd_scheduler"
conf.prefix="lcd_"
conf.customCName = "lcd_graph_config.h"
conf.schedulerCFileName = "lcd_scheduler"
conf.appNodesCName = "LCDGraphNodes.h"

with open("./Dot/pre_schedule_lcd_graph.dot","w") as f:
    g.graphviz(f)
    
sched = g.computeSchedule(config=conf)


print("Schedule length = %d" % sched.scheduleLength)
print("Memory usage %d bytes" % sched.memory)

sched.ccode("LCDGraph",conf)

#generateGenericNodes(".")
#generateCGStatus(".")

class MyStyle(Style):
    def node_color(self,node):
        # pure node is a pure function with no state
        # like some CMSIS-DSP ones
        if node.isPureNode:
           return("burlywood1")
        elif node.typeName == "FromOtherCore":
            return("firebrick1")
        elif node.typeName == "LCD":
            return("darkslategray1")
        else:
            super().node_color(node)


with open("./Dot/lcd_graph.dot","w") as f:
    sched.graphviz(f,style=MyStyle())

