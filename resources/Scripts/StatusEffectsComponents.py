from EntityModule import *
from ComponentModule import *
from StatusEffectsModule import *
from CharacterModule import *
from ActionModule import *
from BattleModule import *
import copy

CopyKey = "copy";

class SingleStatBoostApply(ApplyEffectComponent):
  def __init__(self, *args, **kwargs):
    if (CopyKey in kwargs):
      self.Stat = kwargs[CopyKey].Stat
      self.Multiplier = kwargs[CopyKey].Multiplier
      ApplyEffectComponent.__init__(self, kwargs[CopyKey])
    else:
      #Expect Arguments in form:  owner, stat, multiplier
      argc = len(args)
      ApplyEffectComponent.__init__(self, None if argc < 1 else args[0])
      self.Stat = Stat.Vitality if argc < 2 else args[1]
      self.Multiplier = 1 if argc < 3 else args[2]

  def Apply(self, Character):
    SM = Character.GetStatsManager()
    SM.IncrementStatusEffectStatMultiplier(self.Stat, self.Multiplier)
  
  def UnApply(self, Character):
    SM = Character.GetStatsManager()
    SM.IncrementStatusEffectStatMultiplier(self.Stat, -self.Multiplier)
    
  def Clone(self):
    return SingleStatBoostApply(copy = self)

class MultiStatBoostApply(ApplyEffectComponent):
  def __init__(self, *args, **kwargs):
    if (CopyKey in kwargs):
      self.StatBoosts = copy.deepcopy(kwargs[CopyKey])
      ApplyEffectComponent.__init__(self, kwargs[CopyKey])
    else:
      #Expects Arguments in form: owner, statmultipliers
      argc = len (args)
      ApplyEffectComponent.__init__(self, None if argc < 1 else args[0])
      self.StatBoosts = None if argc < 2 else args[1]

  def Apply(self, Character):
    if (self.StatBoosts != None):
      SM = Character.GetStatsManager()
      for stat, boost in self.StatBoosts.iteritems():
        SM.IncrementStatusEffectStatMultiplier(stat, boost)
  def UnApply(self, Character):
    SM = Character.GetStatsManager()
    for stat, boost in self.StatBoosts.iteritems():
        SM.IncrementStatusEffectStatMultiplier(stat, -boost)
        
  def Clone(self):
    return MultiStatBoostApply(copy = self)

class MultiApply(ApplyEffectComponent):
  def __init__(self, *args, **kwargs):
    if (CopyKey in kwargs):
      if (kwargs[CopyKey].Components != None):
        self.Components = list()
        for name, comp in kwargs[CopyKey].Components:
          self.Components[name] = comp.Clone()
      else:
        self.Components = dict()
      ApplyEffectComponent.__init__(kwargs[CopyKey])
    else:
      #Expects arguments in form owner, components
      argc = len(args)
      ApplyEffectComponent.__init__(self, None if argc < 1 else args[0])
      self.Components = dict() if argc < 2 else args[1]

  def AddComponent(self, name, comp, replace = True):
    if (replace or name not in self.Components):
      self.Components[name] = comp
    
  def RemoveComponent(self, name):
    if name in self.Components:
      del self.Components[name]

  def Apply(self, Character):
    for name, comp in self.Components.itemitems():
      comp.Apply(Character)

  def UnApply(self, Character):
    for name, comp in self.Components.itemitems():
      comp.UnApply(Character)    

  def Clone(self):
    return MultiApply(copy = self)

class StatusResBoostApply(ApplyEffectComponent):
  def __init__(self, *args, **kwargs):
    if (CopyKey in kwargs):
      self.StatusBoosts = copy.deepcopy(kwargs[CopyKey].StatusBoosts)
      ApplyEffectComponent.__init__(self, kwargs[CopyKey])
    else:
      #Expect Arguments in form   owner, statusboosts
      argc = len(args)
      ApplyEffectComponent.__init__(self, None if argc < 1 else args[0])
      self.StatusBoosts = dict() if argc < 2 else args[1]

  def IncrementBoost(self, name, boost):
    if (name in self.StatusBoosts):
      self.StatusBoosts[name] += boost
    else:
      self.StatusBoosts[name] = boost

  def GetBoost(self, name):
    if (name in self.StatusBoosts):
      return self.StatusBoosts[name]
    return 0.0

  def ClearBoost(self, name):
    if (name in self.StatusBoosts):
      del self.StatusBoosts[name]

  def Apply(self, Character):
    SEM = Character.GetStatusEffectsManager()
    for status, boost in self.StatusBoosts.iteritems():
      if (status == "All"):
        SEM.IncrementBaseResistance(boost)
      else:
        SEM.IncrementStatusResistance(status, boost)

  def UnApply(self, Character):
    SEM = Character.GetStatusEffectsManager()
    for status, boost in self.StatusBoosts.itemitems():
      SEM.IncrementStatusResistance(status, -boost)

  def Clone(self):
    return StatusResBoostApply(copy = self)




class ReflectComponent(ActionModifierComponent):
    def __init__(self, *args, **kwargs):
        if (CopyKey in kwargs):
            self.ReflectFunc = kwargs[CopyKey].ReflectFunc
            ActionModifierComponent.__init__(self, kwargs[CopyKey])
        else:
            #Expect arguments as:  owner, ReflectFunc = None
            argc = len(args)
            ActionModifierComponent.__init__(self, None if argc < 1 else args[0])
            self.ReflectFunc = (None if argc < 2 else args[1])
    
    def ModifyAction(self, action, mechanics):
        Modified = False
        if (action.Users.GroupSize() > 0 and self.Reflects(action, mechanics)):
            owner = self.GetOwner()
            if (owner != None):
                holder = owner.GetHolder()
                if (holder != None):
                    oldtarget = action.Targets.GetTarget(holder.GetName())
                    if (oldtarget != None):
                      newtarget = action.Users.GetAt(mechanics.GenerateInt(0, action.Users.GroupSize() - 1))
                      if (newtarget != None):
                        action.Targets.RemoveMember(oldtarget)
                        action.Targets.AddMember(newtarget)
                        Modified = True
                        action.AddFlag("Reflected")
        return Modified

    def Reflects(self, action, mechanics):
        if (self.ReflectFunc != None):
            return self.ReflectFunc(self, action, mecanics)
        elif (not action.HasFlag("Unreflectable") and not action.HasFlag("Reflected")):
            return True


    def Clone(self):
        return ReflectComponent(copy = self)

class CaptureActionComponent(ActionModifierComponent):
  def __init__(self, *args, **kwargs):
    if (CopyKey in kwargs):
      self.CaptureFunction = kwargs[CopyKey].CaptureFunction
      ActionModiferComponent.__init__(self, kwargs[CopyKey])
    else:
      #Expect Arguments as owner, CaptureFunc = None
      argc = len(args)
      ActionModifierComponent.__init__(self, None if argc < 1 else args[0])
      self.CaptureFunction = None if argc < 2 else args[1]

  def ModifyAction(self, action, mechanics):
    cap = False
    if (self.CaptureFunction != None):
      cap = self.CaptureFunction(self, action, mechanics)
    return cap

  def Clone(self):
    return CaptureActionComponent(copy = self)

class CaptureElementComponent(CaptureActionComponent):
  def __init__(self, *args, **kwargs):
    if (CopyKey in kwargs):
      self.Elements = copy.deepcopy(kwargs[CopyKey].Elements)
      self.All = kwargs[CopyKey].All
      self.ElementLimit = kwargs[CopyKey].ElementLimit
      self.MustBeATarget = kwargs[CopyKey].MustBeATarget
      CaptureActionComponent.__init__(kwargs[CopyKey])
    else:
      #Expected Arguments:  owner = None, Elements = None, ElementLimit = 0.75, Replace = "All", MustBeTarget = False
      argc = len(args)
      CaptureActionComponent.__init__(self, None if argc < 1 else args[0])
      self.Elements = None if argc < 2 else args[1]
      self.ElementLimit = 0.75 if argc < 3 else args[2]
      self.Replace = "All" if argc < 4 else args[3]
      self.MustBeATarget = False if argc < 5 else args[4]
  def ModifyAction(self, action, mechanics):
    cap = False
    owner = self.GetOwner()
    if (owner != None):
      holder = owner.GetHolder()
      if (holder != None):
        if (self.Elements != None and (not self.MustBeATarget or self.IsATarget(action))):
          EleWgt = action.GetComponent("ElementalWeightComponent")
          EleWgt.Normalize()
          if (EleWgt != None):
            RunningWeight = 0.0
            for ele, wgt in self.Elements.iteritems():
              RunningWeight += EleWgt.GetElementWeight(ele) * wgt
              if (RunningWeight >= self.ElementLimit):
                break
            if (RunningWeight >= self.ElementLimit):
              cap = True
              if (self.Replace == "All"):
                action.Targets.Clear()
                action.Targets.AddMember(holder, action)
              elif (self.Replace == "Team" and holder.GetParty() != None):
                tmt = False
                for name, target in action.Targets.GetGroup().iteritems():
                  if (holder.GetParty().IsCharacterInParty(target.AttachedCharacter)):
                    action.Targets.RemoveMember(target)
                    tmt = True
                if (tmt):
                  action.Targets.AddCharacter(holder, action)          
    return cap

  def IsATarget(self, action):
    owner = self.GetOwner()
    if (owner != None):
      holder = owner.GetHolder()
      if (holder != None):
        oldtarget = action.Targets.GetTarget(holder.GetName())
        return oldtarget != None
    return False
  
  def Clone(self):
    return CaptureElementComponent(copy = self)
    						
class StatTurbo(ActionModifierComponent):
  def __init__(self, *args, **kwargs):
    if (CopyKey in kwargs):
      self.TargetStat = kwargs[CopyKey].TargetStat
      self.TurboRate = kwargs[CopyKey].TurboRate
      self.CostRate = kwargs[CopyKey].CostRate
      self.OnMagic = kwargs[CopyKey].OnMagic
      self.OnPhysical = kwargs[CopyKey].OnPhysical
      ActionModifierComponent.__init__(self, kwargs[CopyKey])
    else:
       #Excpect arguments in form owner, stat turborate, costrate, onmagic, onphysical
      argc = len(args)
      ActionModifierComponent.__init__(self, None if arrc < 1 else args[0])
      self.TargetStat = Stat.Speed  if argc < 2 else args[1]
      self.TurboRate = (0 if argc < 2 else 0.2) if argc < 3 else args[2]
      self.CostRate = (0 if argc < 2 else 0.07) if argc < 4 else args[3]
      self.OnMagic = (False if argc < 2 else True) if argc < 5 else args[4]
      self.OnPhysical = False if argc < 6 else args[5]
     
  def ModifyAction(self, action, mechanics):
    modded = False
    if (self.TurboRate > 0):
      owner = self.GetOwner()
      if (owner != None):
        holder = owner.GetHolder()
        if (holder != None):
          user = action.Users.GetTarget(holder.GetName())
          if (user != None):
            adder = CalcBoost(action, action.GetMagicWeight(), action.GetPhysicalWeight(), self.OnMagic, self.OnPhysical)
            cost = CalcStatCost(action, adder)
            if (adder > 0 and cost > 0):
              if (self.TargetStat == Stat.MP):
                availMP = user.GetStatsManager().GetMP()
                if ((action.GetMPCost() + cost) > availMP):
                  ratio = float(availMP) / float(action.GetMPCost() + cost)
                  adder = int(float(adder) * ratio)
                  cost = availMP - action.GetMPCost() 
                action.SetMPCost(action.GetMPCost() + cost)
                action.SetPower(action.GetPower() + adder)
              if (self.TargetStat == Stat.SP):
                availSP = user.GetStatsManager().GetSP()
                if ((action.GetSPCost() + cost) > availSP):
                  ratio = float(availSP) / float(action.GetSPCost() + cost)
                  adder = int(float(adder) * ratio)
                  cost = availMP - action.GetSPCost() 
                action.SetSPCost(action.GetSPCost() + cost)
                action.SetPower(action.GetPower() + adder)
              if (self.TargetStat == Stat.HP):
                availHP = user.GetStatsManager().GetMP()
                if ((action.GetMPCost() + cost) > availHP):
                  ratio = float(availHP) / float(action.GetHPCost() + cost)
                  adder = int(float(adder) * ratio)
                  cost = availHP - action.GetHPCost() - 1
                action.SetHPCost(action.GetHPCost() + cost)
                action.SetPower(action.GetPower() + adder)
              modded = True
    return modded
  
  def CalcBoost(self, attack, mgw, phyw, onmg = True, onphy = False):
    Adder = 0
    if (mgw > 0):
      Adder += attack.GetPower() * self.TurboRate * mgw
    if (phyw > 0):
      Adder += attack.GetPower() * self.TurboRate * phyw
    return Adder

  def CalcStatCost(self, attack, adder):
    addCost = 0
    refCost = 0
    cost = attack.GetMPCost() + attack.GetSPCost() + attack.GetHPCost()
    if (cost > 0):
      addCost = int(((attack.GetPower() + adder) / action.GetPower()) * (1 + self.TurboRate) * cost)
    if (self.TargetStat == Stat.HP):
      addCost *= 10
    return addCost
    
  def Clone(self):
    return StatTurbo(copy = self)

class DamageCutter(ActionModifierComponent):
  def __init__(self, *args, **kwargs):
    if (CopyKey in kwargs):
      #Copy Construct
      self.CutBy = kwargs[CopyKey].CutBy
      self.OnPhy = kwargs[CopyKey].OnPhy
      self.OnMg = kwargs[CopyKey].OnMg
      DamageModifierComponent.__init__(self, kwargs[CopyKey])
    else:
        #Expected Arguments:   owner, dmgcutby, onphys, onmg
      arc = len(args)
      DamageModifierComponent.__init__(self, None if argc < 1 else args[0])
      self.CutBy = 0 if argc < 2 else args[1]
      self.OnPhy = False if argc < 3 else args[2]
      self.OnMg = False if argc < 4 else args[4]
      
  def ModifyAction(self, action):
    dmg = action.GetCalcualtedDamage()
    if (not action.HasFlag("FixedDamage")):
      fdmg = int(float(calcdamage) * action.GetPhysicalWeight() * (1.0 if self.OnPhy else float(self.CutBy))) + int(float(calcdamage) * action.GetMagicWeight() * (1.0 if self.OnMg else float(self.CutBy)))
      action.SetCalculatedDamage(fdmg)
      return smg != fdmg
    return False
      
  def Clone(self):
    return DamageCutter(copy = self)
      
      
      
