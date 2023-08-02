from cmsis_stream.cg.scheduler import *
from ..types import midCmdType

class Waveform(GenericNode):
    NODEID=0

    def __init__(self,nb,channel_nb):
        GenericNode.__init__(self,f"Waveform{Waveform.NODEID}")

        Waveform.NODEID = Waveform.NODEID + 1

        self.addInput("i",midCmdType,1)
        self.addOutput("o",CType(Q15),nb)

        self.addLiteralArg(channel_nb)
        self.addVariableArg("offState")

    @property
    def typeName(self):
        return "Waveform"