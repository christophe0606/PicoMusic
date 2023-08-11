from cmsis_stream.cg.scheduler import *

from ...Arm2D.types import *

class Animate(GenericNode):
    def __init__(self,name):
        GenericNode.__init__(self,name)
        self.addInput("l",layer_type,1)
        self.addOutput("o",layer_type,1)

    @property
    def typeName(self):
        return "Animate"