from cmsis_stream.cg.scheduler import *


class ToOtherCore(GenericSink):
    def __init__(self,name,theType,inLength,
        queue="audio_queue",blocking=False):
        GenericSink.__init__(self,name)
        self.addInput("i",theType,inLength)
        self.addVariableArg(queue)
        if blocking:
            self.addLiteralArg(1)
        else:
            self.addLiteralArg(0)

    @property
    def typeName(self):
        return "ToOtherCore"