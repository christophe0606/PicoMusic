from cmsis_stream.cg.scheduler import *

class FFTAmplitude(GenericNode):
    def __init__(self,name,length):
        super().__init__(name)
        self.addInput("i",CType(Q15),2*length)
        self.addOutput("o",CType(Q15),length)

    @property
    def typeName(self):
        return "FFTAmplitude"