from cmsis_stream.cg.scheduler import *


# RP2 dependent
from Nodes.RP2.FromOtherCore.component import *

# Arm2D nodes
from Nodes.Arm2D.AmplitudeWidget.component import *
from Nodes.Arm2D.SpectrumWidget.component import *
from Nodes.Arm2D.Arm2D.component import *
from Nodes.Arm2D.Layer.component import *

# Generic
from Nodes.Generic.FilterAndDecimate.component import *
from Nodes.Generic.Decimate.component import *

# App Specific
from Nodes.AppSpecific.Animate.component import *
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



AMPLITUDE_DECIMATE_FACTOR = GRAPH_INPUT // AMP_OUTPUT
print(f"Amplitude decimation factor = {AMPLITUDE_DECIMATE_FACTOR}")


FFT_DECIMATE_FACTOR = GRAPH_INPUT // FFTSIZE
print(f"FFT decimation factor = {FFT_DECIMATE_FACTOR}")


CONFIG="""#ifndef _LCD_PYTHON_GRAPH_CONFIG_H_ 
#define _LCD_PYTHON_GRAPH_CONFIG_H_

#define FFTSIZE %d 
#define AUDIO_BLOCK_LENGTH %d

#endif
"""

with open("Configuration/Includes/lcd_python_graph_config.h","w") as f:
    print(CONFIG % (FFTSIZE,AUDIO_BLOCK_LENGTH), file=f)

hann=Constant("hanningQ15")
win = Binary("arm_mult_q15",CType(Q15),FFTSIZE)

core0 = FromOtherCore("core0",CType(Q15),AUDIO_BLOCK_LENGTH,
                      queue="audio_queue",
                      blocking=True)

# If you cange the decimation ratio, you'll need to use a different
# filter
decimateForAmp = FilterAndDecimate("decimateAmp",CType(Q15),
    AUDIO_BLOCK_LENGTH,AUDIO_BLOCK_LENGTH//AMPLITUDE_DECIMATE_FACTOR,
    "nbTaps","coefs")
decimateForFFT = FilterAndDecimate("decimateFFT",CType(Q15),
    AUDIO_BLOCK_LENGTH,AUDIO_BLOCK_LENGTH//FFT_DECIMATE_FACTOR,
    "nbTaps","coefs")


ampLayer = Layer("ampLayer",
                 width=200,
                 height=100,
                 layer=1,
                 x=(WIDTH-200)//2,
                 y=((HEIGHT>>1)-100)//2)

fftLayer = Layer("fftLayer",
                 width=200,
                 height=100,
                 layer=2,
                 x=(WIDTH-200)//2,
                 y=(HEIGHT>>1)+((HEIGHT>>1)-100)//2,
                 alpha=200)

cmsis = ROLayer("cmsis",
                width=160,
                height=66,
                x = (WIDTH - 160)//2,
                y = (HEIGHT - 66)//2,
                layer=0,
                texture="&c_tilecmsisLOGORGB565",
                copy_only_mode = True)

animate = Animate("animate")

amp=AmplitudeWidget("amp",256)
spectrum=SpectrumWidget("spectrum",128)

arm2d=Arm2D(nb_layers=3)


toCmplx=ToComplex("toCmplx",CType(Q15),FFTSIZE)
fft = CFFT("fft",CType(Q15),FFTSIZE)
fftMag = FFTAmplitude("fftMag",FFTSIZE>>1)


g = Graph()

# Amplitude signal
g.connect(core0.o,decimateForAmp.i)
g.connect(decimateForAmp.o,amp.i)

# FFT signal
# decimation
g.connect(core0.o,decimateForFFT.i)
g.connect(decimateForFFT.o,win.ia)

# windowing
g.connect(hann,win.ib)

# convert to complex
g.connect(win.o,toCmplx.i)
g.connect(toCmplx.o,fft.i)

# FFT and app specific FFT magnitude
g.connect(fft.o,fftMag.i)
g.connect(fftMag.o,spectrum.i)

# Display
# Layers connected to controls
g.connect(ampLayer.o,amp.l)
g.connect(fftLayer.o,spectrum.l)
g.connect(cmsis.o,animate.l)

# Controls connected to Arm-2D compositor node
g.connect(amp.o,arm2d["A"])
g.connect(spectrum.o,arm2d["B"])
g.connect(animate.o,arm2d["C"])

print("Generate graphviz and code")

conf=Configuration()

conf.CAPI=True
conf.CMSISDSP=True
conf.memoryOptimization=True
#conf.switchCase=False
conf.heapAllocation = True
conf.nodeIdentification = True

conf.cOptionalArgs=["queue_t *audio_queue",
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

# If you regenerate the graphs with a newer version of CMSIS-Stream
# you should uncomment those lines to be sure you are also using the
# latest version of those 2 C++ headers

generateGenericNodes("./App/Includes")
generateCGStatus("./App/Includes")

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
        elif node.typeName == "Layer" or node.typeName == "ROLayer" or node.typeName == "Arm2D":
            return("orchid1")
        else:
            super().node_color(node)


with open("./Dot/lcd_graph.dot","w") as f:
    sched.graphviz(f,style=MyStyle())

