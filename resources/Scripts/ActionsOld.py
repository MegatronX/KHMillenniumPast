from ComponentModule import *
from EntityModule import *
from ActionModule import *
import xml.etree.cElementTree as xml
import copy

def AttackFactory(AttackNode):
    atkName = AttackNode.attrib["name"];
    displayName = atkName
    if ("displayname" in AttackNode.attrib):
        displayName = AttackNode.attrib["displayname"]
    mp = GetMP(AttackNode)
    sp = GetSP(AttackNode)
    targetting = GetTargetting(AttackNode)
    FlagList = GetFlags(AttackNode)
    
    
    CurrentAtk = Attack(atkName, displayName, mp, sp, targetting, FlagList)
    componentNode = AttackNode.find("Components")
    if (componentNode != None):
        components = componentNode.getchildren()
        for component in components:
            currentComp = ComponentFactory(component, CurrentAtk)
            Indexer = component.tag
            if "index" in component.attrib:
                Indexer = component.attrib["index"]
            CurrentAtk.RegisterComponent(Indexer, currentComp)
    return CurrentAtk

def GetFlags(FlagNode):
    FlagList = StringVector()
    flagNode = FlagNode.find("Flags")
    if (flagNode != None):
        flags = flagNode.getchildren()
        for flag in flags:
            FlagList.append(flag.tag)
    return FlagList

def GetMP(MPNode):
    if "mp" in MPNode.attrib:
        return MPNode.attrib["mp"]
    elif "MP" in MPNode.attrib:
        return MPNode.attrib["MP"]
    return 0

def GetSP(SPNode):
    if "sp" in SPNode.attrib:
        return SPNode.attrib["sp"]
    elif "SP" in SPNode.attrib:
        return SPNode.attrib["SP"]
    return 0

def GetTargetting(TrgtNode):
    if "targetting" in TrgtNode.attrib:
        return TrgtNode.attrib["targetting"]
    return "Any"

def ComponentFactory(ComponentNode, Owner):
    if ComponentNode.tag == "SEChanceComponent":
        semap = {}
        ses = ComponentNode.findall("StatusEffect")
        for se in ses:
            if "name" in se.attrib and "chance" in se.attrib:
                semap[se.attrib["name"]] = se.attrib["chance"]
        currentComponent = SEChanceComponent(Owner, semap)
        return currentComponent
    
    elif ComponentNode.tag == "OutgoingActionModifierComponent":
        return Component()
    elif ComponentNode.tag == "ElementalWeightComponent":
        elemap = {}
        elements = ComponentNode.findall("Element")
        for element in elements:
            if "name" in se.attrib and "weight" in se.attrib:
                elemap[se.attrib["name"]] = se.attrib["weight"]
        currentComponent = ElementWeightComponent(Owner, elemap)
        return currentComponent
    else:
        return Component(Owner)
        

actionTree = xml.parse("..\\..\\..\\resources\\XML Databases\\Actions.xml")
actionRoot = actionTree.getroot()
actionList = actionRoot.findall("Action")



attackList = actionRoot.findall("Attack")

if (attackList != None):
    for attack in attackList:
        atk = AttackFactory(attack)
        ActionModule.ActionLibrary.AddItem(atk)