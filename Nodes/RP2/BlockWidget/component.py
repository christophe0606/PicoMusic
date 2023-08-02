from cmsis_stream.cg.scheduler import *

from ...Generic.types import imageType

class BlockWidget(GenericNode):
    def __init__(self,name,length,pos=0,color=0):
        super().__init__(name)
        self.addInput("i",CType(Q15),length)
        self.addInput("fb",imageType,1)
        self.addOutput("o",imageType,1)
        self.addLiteralArg(pos,color)

    @property
    def typeName(self):
        return "BlockWidget"