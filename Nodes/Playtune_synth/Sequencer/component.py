from cmsis_stream.cg.scheduler import *
from ..types import midCmdType

class Sequencer(GenericSource):
    def __init__(self,nb_channels=16,songList="allSongs",songNames="names"):
        GenericSource.__init__(self,"NoteSequencer")



        for i in range(nb_channels):
            self.addOutput(chr(ord('A')+i),midCmdType,1)

        self.addVariableArg(songList,songNames)


    @property
    def args(self):
        """String of fifo args for object initialization
            with literal argument and variable arguments"""
        allArgs=self.listOfargs
        nb = len(allArgs) 
        others = "{" + "".join(joinit([x.pointer for x in allArgs[1:]],",")) + "}"
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
        theType=self._outputs[self.outputNames[0]].ctype  
        ios="%s,%d" % (theType,1)
        return(ios)


    @property
    def typeName(self):
        return "Sequencer"

