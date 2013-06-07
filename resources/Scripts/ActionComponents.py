from ComponentModule import *
from EntityModule import *
from ActionModule import *
from ElementModule import *
from BattleModule import *
from CharacterModule import *
import copy
CopyKey = "copy";

class ConstantDamageComponent(DamageCalculationComponent):
    def __init__(self, *args, **kwargs):
        if (CopyKey in kwargs):
            self.ConstDamage = kwargs[CopyKey].ConstDamage
            DamageCalculationComponent.__init__(self, kwargs[CopyKey])
        else:
            argc = len(args)
            DamageCalculationComponent.__init__(self, None if argc < 1 else args[0])
            self.ConstDamage = 0 if argc < 2 else args[1]

    def CalculateDamage(self, action, target, mechanics):
        return self.ConstDamage

    def Clone(self):
        return ConstantDamageComponent(copy = self)

class RandomDamageComponent(DamageCalculationComponent):
    def __init__(self, *args, **kwargs):
        if (CopyKey in kwargs):
            self.Min = kwargs[CopyKey].Min
            self.Max = kwargs[CopyKey].Max
            DamageCalculationComponent.__init__(self, kwargs[CopyKey])
        else:
            argc = len(args)
            DamageCalculationComponent.__init__(self, None if argc < 1 else args[0])
            self.Min = 0 if argc < 2 else args[1]
            self.Max = 0 if argc < 3 else args[2]

    def CalculateDamage(self, action, target, mechanics):
        return 0

    def Clone(self):
        return RandomDamageComponent(copy = self)


#One off components

class WhiteWindDamageComponent(DamageCalculationComponent):
    def __init__(self, *args, **kwargs):
        if (CopyKey in kwargs):
            DamageCalculationComponent.__init__(self, kwargs[CopyKey])
        else:
            argc = len(args)
            DamageCalculationComponent.__init__(self, None if argc < 1 else args[0])

    def CalculateDamage(self, action, target, mechanics):
        Dmg = 10
        if (action.Users.GroupSize() > 0):
            Usr = action.Users.GetAt(0)
            if (Usr != None):
                SM = Usr.AttachedCharacter.GetStatsManager()
                if (SM != None):
                    Dmg = -SM.GetCurrentHP()
        return Dmg

    def Clone(self):
        return WhiteWindDamageComponent(copy = self)


#Custom Use component for Cheer action. Cheer copies positive status effects on user to the targets
class CheerUse(UseComponent):
	def __init__(self, *args, **kwargs):
		if (CopyKey in kwargs):
			DamageCalculationComponent.__init__(self, kwargs[CopyKey])
		else:
			argc = len(args)
			DamageCalculationComponent.__init__(self, None if argc < 1 else args[0])

	def Use(self, action, mechanics, inbattle):
		if (action.Users.GroupSize() > 0):
			Usr = action.Users.GetAt(0)
			if (Usr != None):
				SEM = Usr.AttachedCharacter.GetStatusEffectsManager()
				if (SEM != None):
					posSE = SEM.GetPositiveStatusEffects()
					Trgs = action.Targets.GetGroup()
					for targets in Trgs:
						targetSEM = target.GetStatusEffectManager()
						for effect in posSE:
							targetSEM.AddStatusEffect(effect.Clone(), effect.GetRemainingTurns())
					#for effect in posSE:
						

#class MultiHitComponent