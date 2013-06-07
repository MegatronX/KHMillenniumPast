from StatusEffectsModule import *
from SEComponents import *
from ElementModule import *
import copy

CurrentSE = StatusEffect(None, "Haste", "Distorts time around the inflicted user, speeding up their movements", True)
Mult = SingleStatBoostApply(CurrentSE, Stat.Speed, 1.5)
CurrentSE.RegisterComponent(ApplyEffectIndex, Mult, True)
StatusEffectsModule.StatusEffectsLibrary.AddStatusEffect(CurrentSE)

CurrentSE = StatusEffect(None, "Haste+", "Greatly distorts time around the inflicted user, speeding up their movements dramatically", True)
Mult = SingleStatBoostApply(CurrentSE, Stat.Speed, 1.75)
CurrentSE.RegisterComponent(ApplyEffectIndex, Mult, True)
StatusEffectsModule.StatusEffectsLibrary.AddStatusEffect(CurrentSE)

CurrentSE = StatusEffect(None, "Juggernaut", "Energizes the inflicted's body, allowing them to deal much more damage with physical attacks", True)
Mult = SingleStatBoostApply(CurrentSE, Stat.Strength, 1.5);
CurrentSE.RegisterComponent(ApplyEffectIndex, Mult, True)
StatusEffectsModule.StatusEffectsLibrary.AddStatusEffect(CurrentSE)

CurrentSE = StatusEffect(None, "Bubble", True)
Mult = SingleStatBoostApply(CurrentSE, Stat.HP, 1.5)
CurrentSE.RegisterComponent(ApplyEffectIndex, Mult, True)
StatusEffectsModule.StatusEffectsLibrary.AddStatusEffect(CurrentSE)

CurrentSE = StatusEffect(None, "Slow", False)
Mult = SingleStatBoostApply(CurrentSE, Stat.Speed, 0.5)
CurrentSE.RegisterComponent(ApplyEffectIndex, Mult, True)
StatusEffectsModule.StatusEffectsLibrary.AddStatusEffect(CurrentSE)

CurrentSE = StatusEffect(None, "Slow+", False)
Mult = SingleStatBoostApply(CurrentSE, Stat.Speed, 0.3)
CurrentSE.RegisterComponent("ApplyEffectComponent", Mult, True)
StatusEffectsModule.StatusEffectsLibrary.AddStatusEffect(CurrentSE)

CurrentSE = StatusEffect(None, "Blind", False)
Mult = SingleStatBoostApply(CurrentSE, Stat.Accuracy, 0.3)
CurrentSE.RegisterComponent(ApplyEffectIndex, Mult, True)
StatusEffectsModule.StatusEffectsLibrary.AddStatusEffect(CurrentSE)

CurrentSE = StatusEffect(None, "Fever", False)
Mult = MultiStatBoostApply(CurrentSE, {Stat.Speed: 1.25, Stat.Vitality: 0.65, Stat.Spirit: 0.65})
CurrentSE.RegisterComponent(ApplyEffectIndex, Mult, True)
StatusEffectsModule.StatusEffectsLibrary.AddStatusEffect(CurrentSE)

CurrentSE = StatusEffect(None, "Frozen", False)
Mult = MultiStatBoostApply(CurrentSE, {Stat.Speed: 0.6, Stat.Vitality: 1.2, Stat.Spirit: 1.2})
CurrentSE.RegisterComponent(ApplyEffectIndex, Mult, True)
StatusEffectsModule.StatusEffectsLibrary.AddStatusEffect(CurrentSE)

CurrentSE = StatusEffect(None, "God Mode", "Makes target virtually idestructible", False)
Multi = MultiApply(CurrentSE)
Mult = MultiStatBoostApply(CurrentSE, {Stat.Speed: 15.0, Stat.Vitality: 15.0, Stat.Spirit: 15.0, Stat.HP: 20.0, Stat.MP: 20.0, Stat.SP: 20.0, Stat.Strength: 15.0, Stat.Magic: 15.0, Stat.Luck: 30.0})
Multi.AddComponent("MultiStatBooster", Mult)
print "Added MultiStat Booster"
SERes = StatusResBoostApply(CurrentSE, {"All": 1.0})
#Multi.AddComponent("SEBoost", SERes)
CurrentSE.RegisterComponent(ApplyEffectIndex, Multi, True)
StatusEffectsModule.StatusEffectsLibrary.AddStatusEffect(CurrentSE)

cc = CallConditionSet()
cc.append(CallCondition.FinalizingTargets)
CurrentSE = StatusEffect(None, "Reflect", False, 0, 14, cc)
RC = ReflectComponent(CurrentSE)
CurrentSE.RegisterComponent(FinalizeTargettingIndex, RC, True)
StatusEffectsModule.StatusEffectsLibrary.AddStatusEffect(CurrentSE)

CurrentSE = StatusEffect(None, "Storm Drain", False, 2, 11, cc)
Cap = CaptureElementComponent(CurrentSE, {Element.Water: 1.0}, 0.75, "All")
CurrentSE.RegisterComponent(FinalizeTargettingIndex, Cap, True)
StatusEffectsModule.StatusEffectsLibrary.AddStatusEffect(CurrentSE)


del cc[:]
cc.append(CallCondition.ApplyingDamage)
CurrentSE = StatusEffect(None, "Float", "Suspends afflicted character in the air, preventing all Earth based damage", False, 0, 10, cc)
#EleIm = ElementImmunityEffect(CurrentSE, [Element.Earth])
#CurrentSE.RegisterComponent(FinalizingDamageIndex, EleIm)
StatusEffectsModule.StatusEffectsLibrary.AddStatusEffect(CurrentSE)

del cc[:]
cc.append(CallCondition.PartyMemberOutgoingAttack)
CurrentSE = StatusEffect(None, "Ocean Guardian", "Join with the ocean", False, 0, 30, cc)
PEle = BoostPartyElementAttacks(CurrentSE, {Element.Water: 0.3, Element.Ice: 0.25})
CurrentSE.RegisterComponent("OutgoingActionModifier", PEle)
StatusEffectsModule.StatusEffectsLibrary.AddStatusEffect(CurrentSE)
print "Status Effects Imported Successfully"







