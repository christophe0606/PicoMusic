from cmsis_stream.cg.scheduler import *

from ..types import *

class AmplitudeWidget(GenericNode):
    def __init__(self,name,inLength):
        GenericNode.__init__(self,name)
        self.addInput("i",CType(Q15),inLength)
        self.addInput("l",layer_type,1)
        self.addOutput("o",layer_type,1)

    @property
    def typeName(self):
        return "AmplitudeWidget"

