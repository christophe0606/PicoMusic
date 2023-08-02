from cmsis_stream.cg.scheduler import *

class PWMAudio(GenericSink):
    def __init__(self,name,inLength):
        GenericSink.__init__(self,name)
        self.addInput("i",CType(Q15),inLength)
       

    @property
    def typeName(self):
        return "PWMAudio"