from cmsis_stream.cg.scheduler import *
from ..types import midCmdType

class Enveloppe(GenericNode):

    NODEID=0
    def __init__(self,nb,channel_nb):
        GenericNode.__init__(self,f"Enveloppe_{Enveloppe.NODEID}")

        Enveloppe.NODEID = Enveloppe.NODEID + 1

        self.addInput("i",CType(Q15),nb)
        self.addInput("c",midCmdType,1)

        self.addOutput("o",CType(Q15),nb)

        self.addLiteralArg(channel_nb)
        self.addVariableArg("offState")



    @property
    def typeName(self):
        return "Enveloppe"