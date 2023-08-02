from cmsis_stream.cg.scheduler import *

class FilterAndDecimate(GenericNode):
    def __init__(self,name,theType,inLength,outLength,nb_taps=5,coefs=None):
        GenericNode.__init__(self,name)
        self.addInput("i",theType,inLength)
        self.addOutput("o",theType,outLength)
        if isinstance(nb_taps,int):
           self.addLiteralArg(nb_taps)
        else:
           self.addVariableArg(nb_taps)
        self.addVariableArg(coefs)

    @property
    def typeName(self):
        return "FilterAndDecimate"