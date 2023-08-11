from cmsis_stream.cg.scheduler import *

from ..types import *

class Arm2D(GenericSink):
    def __init__(self,nb_layers=1):
        GenericSink.__init__(self,"Compositor")



        for i in range(nb_layers):
            self.addInput(chr(ord('A')+i),layer_type,1)


    @property
    def args(self):
        """String of fifo args for object initialization
            with literal argument and variable arguments"""
        allArgs=self.listOfargs
        nb = len(allArgs) 
        others = "{" + "".join(joinit([x.pointer for x in allArgs],",")) + "}"
        # Add specific argrs after FIFOs
        sched = []
        if self.schedArgs:
            for lit in self.schedArgs:
                sched.append(lit.arg)
        if sched:
            return (others + "," + "".join(joinit(sched,",")))
        else:
           return (others)

    def ioTemplate(self):
        """ioTemplate is different for window
        """
        theType=self._inputs[self.inputNames[0]].ctype  
        ios="%s,%d" % (theType,1)
        return(ios)


    @property
    def typeName(self):
        return "Arm2D"

