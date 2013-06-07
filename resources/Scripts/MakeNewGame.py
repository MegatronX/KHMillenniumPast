
from ItemModule import *
from ComponentModule import *
from EntityModule import *
from GameInstanceModule import *
from CharacterModule import *
from ActionModule import *
from BattleModule import *
import xml.etree.cElementTree as xml
from array import array

party = GameInstanceModule.ActiveGame.GetPlayerParty()

characterTree = xml.parse("..\\..\\..\\resources\\XML Databases\\Characters.xml")
characterRoot = itemTree.getroot()
characterList = itemsRoot.findall("Character")

for character in characterList:
    if (character.attrib["name"] != None and character.attrib["name"] == "Arian"):
        Arian = MakeCharacter(character)
        party.AddCharacter(Arian)

def MakeCharacter(chNode):
    initialState = chNode.find("InitialState")
    stats = StatList()
    if (initialState != None):
        stNode = initialState.find("Stats")
        stats = MakeStatList(stNode)
    ch = BaseCharacter(character.attrib["name"], stat)
    return ch

statName = ("HP", "MP", "SP", "Str", "Vit", "Mg", "Spr", "Skl", "Spd", "Acc", "Ev", "MgEv", "Luck")
#Str="25" Vit="22" Mg="25" Spr="22" Skl="25" Spd="28" Acc="100" Ev="5" MgEv="5" Luck="45"/>
def MakeStatList(stNode):
    stats = StatList()
    for stat in statName:
        if stNode.attrib[stat] != None:
            stats.append(int(stNode.attrib[stat]))
        else:
            stats.append(0)
