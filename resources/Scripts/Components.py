from ComponentModule import *
from EntityModule import *
from ActionModule import *

import copy

class MultiHitComponent(UseComponent):
    def __init__(self, Owner):
        UseComponent.__init__(self, Owner, False, True)

    def AddAttack(self, Atk):
        self.Attacks.append(Atk)

    def BattleUse(self, Action, Mechanics):
        for Atk in self.Attacks:
            Atk.BattleUse(self, Action, Mechanics)

    def Clone(self):
        return copy.deepcopy(self)

