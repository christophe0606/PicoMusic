from cmsis_stream.cg.scheduler import *

from ..types import imageType

class ImageBuffer(GenericSource):
    def __init__(self,name,width,height,
        texture=None,texture_width=0,texture_height=0):
        GenericSource.__init__(self,name)
        self.addOutput("o",imageType,1)
        self.addLiteralArg(width,height)
        if texture is not None:
            self.addVariableArg(texture)
        else:
            self.addVariableArg("NULL")
        self.addLiteralArg(texture_width,texture_height)

    @property
    def typeName(self):
        return "ImageBuffer"
