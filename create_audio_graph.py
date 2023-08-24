from cmsis_stream.cg.scheduler import *

from Nodes.Playtune_synth.Enveloppe.component import * 
from Nodes.Playtune_synth.Waveform.component import * 
from Nodes.Playtune_synth.Sequencer.component import * 

from Nodes.RP2.pwm_audio.component import *
from Nodes.RP2.ToOtherCore.component import *

from Nodes.Generic.Gain.component import *

from Configuration.global_config import *
from Configuration.audio_config import *

CONFIG="""#ifndef _AUDIO_PYTHON_GRAPH_CONFIG_H_ 
#define _AUDIO_PYTHON_GRAPH_CONFIG_H_

#define AUDIO_BLOCK_LENGTH %d

#endif
"""

with open("Configuration/Includes/audio_python_graph_config.h","w") as f:
    print(CONFIG % (AUDIO_BLOCK_LENGTH,), file=f)

def mixing(g,nodes):
    # Recursive case
    if len(nodes)>=4:
        mix = Binary("arm_add_q15",CType(Q15),AUDIO_BLOCK_LENGTH)
        mid = int(len(nodes)/2)
        a = mixing(g,nodes[:mid])
        b = mixing(g,nodes[mid:])
        g.connect(a.o,mix.ia)
        g.connect(b.o,mix.ib)
        return(mix)
    # Final cases
    elif len(nodes)==2:
        mix = Binary("arm_add_q15",CType(Q15),AUDIO_BLOCK_LENGTH)
        g.connect(nodes[0]["o"],mix.ia)
        g.connect(nodes[1]["o"],mix.ib)
        return(mix)
    elif len(nodes)==3:
        mixa = Binary("arm_add_q15",CType(Q15),AUDIO_BLOCK_LENGTH)
        mixb = Binary("arm_add_q15",CType(Q15),AUDIO_BLOCK_LENGTH)
        g.connect(nodes[0]["o"],mixa.ia)
        g.connect(nodes[1]["o"],mixa.ib)
        g.connect(mixa.o,mixb.ia)
        g.connect(nodes[2]["o"],mixb.ib)
        return(mixb)



g = Graph()

si = PWMAudio("audio",AUDIO_BLOCK_LENGTH)

seq = Sequencer(nb_channels=NB_CHANNELS,
                songList="allSongs",
                songNames="names")
c = []
for i in range(NB_CHANNELS):
    m = Waveform(AUDIO_BLOCK_LENGTH,i)
    e = Enveloppe(AUDIO_BLOCK_LENGTH,i)
    m.identified = False 
    e.identified = False
    c.append(e)
    seqOutput = chr(ord('A')+i)
    g.connect(seq[seqOutput],m.i)
    g.connect(seq[seqOutput],e.c)
    g.connect(m.o,e.i)


r = mixing(g,c)
gain=Gain("ogain",CType(Q15),AUDIO_BLOCK_LENGTH,gain=1.0)

g.connect(r.o,gain.i)

# In debug mode, the output sent to PWM audio has its amplitude
# forced to 0 but the amplitude sent to LCD has the right value.
if not DEBUG_AUDIO_GRAPH:
    g.connect(gain.o,si.i)
else:
    debuggain=Gain("odebuggain",CType(Q15),AUDIO_BLOCK_LENGTH,gain=0.0)
    debuggain.identified = False 
  
    g.connect(gain.o,debuggain.i)
    g.connect(debuggain.o,si.i)
    si.identified = False

core1 = ToOtherCore("core1",CType(Q15),AUDIO_BLOCK_LENGTH,queue="audio_queue")


g.connect(gain.o,core1.i)


conf=Configuration()

conf.CAPI=True
conf.CMSISDSP=True
conf.memoryOptimization=True
#conf.switchCase=False
conf.heapAllocation = True
conf.nodeIdentification = True

conf.cOptionalArgs=["uint32_t *offState",
                    "queue_t *audio_queue",
                    "const uint8_t** allSongs",
                    "const char** names"
                    ]


conf.schedName="audio_scheduler"
conf.prefix="audio_"
conf.customCName = "audio_graph_config.h"
conf.schedulerCFileName = "audio_scheduler"
conf.appNodesCName = "AudioGraphNodes.h"

with open("./Dot/pre_schedule_audio_graph.dot","w") as f:
    g.graphviz(f)
    
sched = g.computeSchedule(config=conf)


print("Schedule length = %d" % sched.scheduleLength)
print("Memory usage %d bytes" % sched.memory)

sched.ccode("AudioGraph",conf)

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
        elif node.typeName == "ToOtherCore":
            return("firebrick1")
        elif node.typeName == "PWMAudio":
            return("darkslategray1")
        else:
            super().node_color(node)


with open("./Dot/audio_graph.dot","w") as f:
    sched.graphviz(f,style=MyStyle())

