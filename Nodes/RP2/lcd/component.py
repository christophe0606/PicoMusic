from cmsis_stream.cg.scheduler import *

from ...Generic.types import imageType

class LCD(GenericSink):
    def __init__(self,name):
        GenericSink.__init__(self,name)
        self.addInput("i",imageType,1)

    @property
    def typeName(self):
        return "LCD"

