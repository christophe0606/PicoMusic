from cmsis_stream.cg.scheduler import *

class Gain(GenericNode):
    def __init__(self,name,theType,ioLength,gain=1.0):
        GenericNode.__init__(self,name)
        self.addInput("i",theType,ioLength)
        self.addOutput("o",theType,ioLength)
        self.addLiteralArg(gain)

    @property
    def typeName(self):
        return "Gain"