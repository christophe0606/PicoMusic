from cmsis_stream.cg.scheduler import *
from ..types import *

class CommonLayer(GenericSource):
    def __init__(self,name,
        layer=0,
        x=0,
        y=0,
        color=0xFFFF,
        alpha=255,
        copy_only_mode=False,
        width=240,
        height=240):
        GenericSource.__init__(self,name)

        self.width = width
        self.height = height

        self.addOutput("o",layer_type,1)

        if isinstance(layer,int):
           self.addLiteralArg(layer)
        else:
           self.addVariableArg(layer)

        if isinstance(x,int):
           self.addLiteralArg(x)
        else:
           self.addVariableArg(x)

        if isinstance(y,int):
           self.addLiteralArg(y)
        else:
           self.addVariableArg(y)

        if isinstance(color,int):
           self.addLiteralArg(color)
        else:
           self.addVariableArg(color)

        if isinstance(alpha,int):
           self.addLiteralArg(alpha)
        else:
           self.addVariableArg(alpha)

        self.addLiteralArg(copy_only_mode)

    def setX(self,x):
        self.schedArgs[1]= ArgLiteral(x)

    def setY(self,y):
        self.schedArgs[2]= ArgLiteral(y)



class ROLayer(CommonLayer):
    def __init__(self,name,texture="",
        layer=0,
        x=0,
        y=0,
        width=240,
        height=240,
        color=0xFFFF,
        alpha=255,
        copy_only_mode=False):
        CommonLayer.__init__(self,name,
            layer=layer,
            x=x,
            y=y,
            color=color,
            alpha=alpha,
            copy_only_mode=copy_only_mode,
            width=width,
            height=height)

        self.addVariableArg(texture)
        

    @property
    def typeName(self):
        return "ROLayer"

class Layer(CommonLayer):
    def __init__(self,name,width=240,
        height=240,
        layer=0,
        x=0,
        y=0,
        color=0xFFFF,
        alpha=255,
        copy_only_mode=False):
        CommonLayer.__init__(self,name,
            layer=layer,
            x=x,
            y=y,
            color=color,
            alpha=alpha,
            copy_only_mode=copy_only_mode,
            width=width,
            height=height)

        
        if isinstance(width,int):
           self.addLiteralArg(width)
        else:
           self.addVariableArg(height)

        if isinstance(height,int):
           self.addLiteralArg(height)
        else:
           self.addVariableArg(height)
        

    @property
    def typeName(self):
        return "Layer"

