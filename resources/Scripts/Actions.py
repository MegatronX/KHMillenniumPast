from ComponentModule import *
from EntityModule import *
from ActionModule import *
from ElementModule import *

#import os, sys
#lib_path = os.path.abspath('../../../resources/Scripts')
#sys.path.append(lib_path)

import ActionComponents

import xml.etree.cElementTree as xml

ElementMap = {}
ElementMap["Air"] = Element.Air
ElementMap["Dark"] = Element.Dark
ElementMap["Earth"] = Element.Earth
ElementMap["Elementless"] = Element.Elementless
ElementMap["Fire"] = Element.Fire
ElementMap["Ice"] = Element.Ice
ElementMap["Light"] = Element.Light
ElementMap["SpaceTime"] = Element.SpaceTime
ElementMap["Thunder"] = Element.Thunder
ElementMap["Water"] = Element.Water

def get_class( kls ):
    parts = kls.split('.')
    module = ".".join(parts[:-1])
    m = __import__( module )
    for comp in parts[1:]:
        m = getattr(m, comp)            
    return m

def AttackFactory(AttackNode):
    atkName = AttackNode.attrib["name"];
    displayName = atkName
    if ("displayname" in AttackNode.attrib):
        displayName = AttackNode.attrib["displayname"]
    print "name: " + atkName
    mp = GetMP(AttackNode)
    sp = GetSP(AttackNode)
    power = GetPower(AttackNode)
    accr = GetAccuracy(AttackNode)
    targetting = GetTargetting(AttackNode)
    FlagList = GetFlags(AttackNode)
    print "Mp: " + str(mp)
    
    CurrentAtk = Attack(atkName, displayName, power, mp, sp, accr)
   # for flag in FlagList:
    for flag in FlagList:
        CurrentAtk.AddFlag(flag)
    
    componentNode = AttackNode.find("Components")
    if (componentNode != None):
        UsedIndexes = set()
        MultiCompSet = set()
        components = componentNode.getchildren()
        for component in components:
            currentComp = ComponentFactory(component, CurrentAtk)
            if (currentComp != None):
                Indexer = component.tag
                if "index" in component.attrib:
                    Indexer = component.attrib["index"]
                CurrentAtk.RegisterComponent(Indexer, currentComp)
            #if (not (Indexer in UsedIndexes)):
            #    CurrentAtk.RegisterComponent(Indexer, currentComp)
            #    UsedIndexes.add(Indexer)
            #else:
            #    CurrentComp = CurrentAtk.GetComponent(Indexer)
                    
                
        #Sync up components. Used to deal with improper order/inter component reliance
       # CurrentAttack.SyncComponents()
    return CurrentAtk

def GetFlags(FlagNode):
    FlagList = []
    flagNode = FlagNode.find("Flags")
    if (flagNode != None):
        flags = flagNode.getchildren()
        for flag in flags:
            FlagList.append(flag.tag)
    return FlagList

def GetPower(PowerNode):
    if "power" in PowerNode.attrib:
        return int(PowerNode.attrib["power"])
    elif "Power" in PowerNode.attrib:
        return int(PowerNode.attrib["Power"])
    return 0

def GetAccuracy(AccuracyNode):
    acr = "1.0";
    if "accuracy" in AccuracyNode.attrib:
        acr = AccuracyNode.attrib["accuracy"];
    elif "Accuracy" in AccuracyNode.attrib:
        acr = PowerNode.attrib["Accuracy"]
    if (acr == "Infinite" or acr == "infinite"):
        acr="100000.0"
    return float(acr);

def GetMP(MPNode):
    if "mp" in MPNode.attrib:
        return int(MPNode.attrib["mp"])
    elif "MP" in MPNode.attrib:
        return int(MPNode.attrib["MP"])
    return 0

def GetSP(SPNode):
    if "sp" in SPNode.attrib:
        return int(SPNode.attrib["sp"])
    elif "SP" in SPNode.attrib:
        return int(SPNode.attrib["SP"])
    return 0

def GetTargetting(TrgtNode):
    if "targetting" in TrgtNode.attrib:
        return TrgtNode.attrib["targetting"]
    return "Any"

def ComponentFactory(ComponentNode, Owner):
    print "Making component " + ComponentNode.tag + "\n"
    if ComponentNode.tag == "ElementalWeightComponent":
        #elemap = ElementWeightMap()
        currentComponent = ElementWeightComponent(Owner)
        elements = ComponentNode.findall("Element")
        for element in elements:
            if "name" in element.attrib and "weight" in element.attrib:
                if element.attrib["name"] in ElementMap:
                    currentComponent.AddWeight(ElementMap[element.attrib["name"]], float(element.attrib["weight"]))
                #elemap.AddWeightse.attrib["name"]] = se.attrib["weight"]
        return currentComponent
    elif ComponentNode.tag == "ConstantDamageCalculationComponent":
        if ("damage" in ComponentNode.attrib):
            dmg = int(ComponentNode.attrib["damage"])
            CurrentComponent = ActionComponents.ConstantDamageComponent(Owner, dmg);
            return CurrentComponent;
    else:
        argus = ComponentNode.findall("Arguments")
        argc = len(argus)
        print "Argument size is " + str(argc)
        if (argc < 1 and ComponentNode.tag == "WhiteWindDamageComponent"):
            print "Trying to make " + ComponentNode.tag +"\n"
            return getattr(ActionComponents, ComponentNode.tag)(Owner)
            
            #return get_class(ComponentNode.tag)
        else:
            print "No Support Yet"
            return None
    '''elif ComponentNode.tag == "SEChanceComponent" or ComponentNode.tag == "SERemovalComponent":
        semap = {}
        ses = ComponentNode.findall("StatusEffect")
        for se in ses:
            if "name" in se.attrib and "chance" in se.attrib:
                semap[se.attrib["name"]] = se.attrib["chance"]
        currentComponent = SEChanceComponent(Owner, semap)
        return currentComponent
    
    elif ComponentNode.tag == "ActionModifierComponent":
        return Component()     
    #Damage Calculators
    elif ComponentNode.tag == "CustomComponent":
        Code = ComponentNode.text
        return eval(Code, locals())
        #return CustomDamageCalculatorComponent(Owner, dmgFunc)
    elif ComponentNode.tag == "ConstantDamageCalculatorComponent":
        dmg = 1;
        if "damage" in ComponentNode.attrib:
            dmg = ComponentNode.attrib["damage"]
        return ConstantDamageCalculatorComponent(Owner, dmg)
    
    #Multi Components
    elif ComponentNode.tag == "MultiUseComponent":
        MU = MultiUseComponent(Owner)
        SubComp = ComponentNode.findall("Components")
        for comp in SubComp:
            MU.AddComponent(ComponentFactory(comp))
            
    elif ComponentNode.tag == "MultiHitComponent":
        multiHit = 1
        if "hits" in ComponentNode.attrib:
            multiHit = ComponentNode.attrib["hits"]
        hits = ComponentNode.findall("Hit")
        
        if len(hits) > 0:
            MH = MultiHitComponent(Owner, multiHit)
            for hit in hits:
                if "asattack" in hit.attrib:
                    MH.AddAttack(hit.attrib["asattack"])
                else:
                    power = 0;
                    accuracy = 1.0;
        #MH.AddAttack(Attack())'''
    #else:
    print "No matching Component found for " + ComponentNode.tag
    return None #Component(Owner, False)
  
actionTree = xml.parse("..\\..\\..\\resources\\XML Databases\\Actions.xml")
actionRoot = actionTree.getroot()
actionList = actionRoot.findall("Action")



attackList = actionRoot.findall("Attack")

if (attackList != None):
    for attack in attackList:
        atk = AttackFactory(attack)
        ActionModule.ActionLibrary.AddAction(atk)



