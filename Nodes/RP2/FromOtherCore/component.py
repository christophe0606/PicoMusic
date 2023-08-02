from cmsis_stream.cg.scheduler import *

class FromOtherCore(GenericSource):
    def __init__(self,name,theType,inLength,queue="audio_queue",blocking=False):
        GenericSource.__init__(self,name)
        self.addOutput("o",theType,inLength)
        self.addVariableArg(queue)
        if blocking:
            self.addLiteralArg(1)
        else:
            self.addLiteralArg(0)

    @property
    def typeName(self):
        return "FromOtherCore"