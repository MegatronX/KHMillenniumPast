from ItemModule import *
from ComponentModule import *
from EntityModule import *
from GameInstanceModule import *
from CharacterModule import *
from ActionModule import *
from BattleModule import *
import math
import xml.etree.cElementTree as xml

#.def("GetAtLevel", pure_virtual(&CharacterEntry::GetAtLevel))

	#		HP = 0,
	#		MP = 1,
	#		SP = 2,
	#		Strength = 3,
	#		Vitality = 4,
	#		Defense = 4,
	#		Magic = 5,
	#		Spirit = 6,
	#		MgDefense = 6,
	#		Skill = 7,
	#		Speed = 8,
	#		Agility = 8,
	#		Evasion = 9,
	#		MgEvasion = 10,
	#		Accuracy = 11,
	#		MgAccuracy = 12,
	#		Luck = 13,
#.def("ValidForLevel", pure_virtual(&CharacterEntry::ValidForLevel))
StatMappings = {
               "HP" : Stat.HP,
               "MP" : Stat.MP,
               "SP" : Stat.SP,
               "Strength" : Stat.Strength,
               "Vitality" : Stat.Vitality,
               "Defense" : Stat.Defense,
               "Magic" : Stat.Magic,
               "Spirit" : Stat.Spirit,
               "MgDefense" : Stat.MgDefense,
               "Skill" : Stat.Skill,
               "Speed" : Stat.Speed,
               "Agility" : Stat.Agility,
               "Evasion" : Stat.Evasion,
               "MgEvasion" : Stat.MgEvasion,
               "Accuracy" : Stat.Accuracy,
               "MgAccuracy" : Stat.MgAccuracy,
               "Luck" : Stat.Luck,
               }
class EntryBasedLevelGeneration(CharacterEntry):
    def __init__(self):
        self.Entries = dict()
        CharacterEntry.__init__(self)
    def AddLevelEntry(self, level, entry):
        print "Adding level " + str(level) + " " + entry.GetName()
        self.Entries[level] = entry

    def GetAtLevel(self, level):
        if level in self.Entries:
            return self.Entries[level]
        print "Could not find match for level " + str(level)
        ch = BaseCharacter()
        ch.SetValid(False)
        return ch
    def ValidForLevel(self, level):
        return level in self.Entries

class FailsafeEntryBasedLevelGeneration(CharacterEntry):
    def __init__(self):
        self.Entries = dict()
        CharacterEntry.__init__(self)
    def AddLevelEntry(self, level, entry):
        self.Entries[level] = entry

    def GetAtLevel(self, level):
        if level in self.Entries:
            return self.Entries[level]
        if len(self.Entries) > 0:
            closestMatch = None
            closestLevel = 0
            for elevel, entry in self.Entries:
                if closestMatch == None:
                    closestMatch = entry
                    closestLevel = elevel
                else:
                    if math.fabs(elevel - level) < math.fabs(closestLevel - level):
                        closestMatch = entry
                        closestLevel = elevel
            print "Could not find exact match for level " + str(level) + ". Falling back to level " + str(closestLevel)
            return closestMatch
        else:
            print "Could not find match for level " + str(level)
            ch = BaseCharacter()
            ch.SetValid(False)

    def ValidForLevel(self, level):
        return level in self.Entries

class FormulaBasedLevelGeneration(CharacterEntry):
    def __init__(self, statformulas = None, abilities = None):
        self.AbilityGenerator = dict()
        CharacterEntry.__init__(self)
        for stat, formula in statforumlas.iteritems():
            self.StatGenerators[stat] = formula

        return#self.Ab
    def AddAbility(self, ability, levellimit):
        if not levellimit in self.AbilityGenerator:
            self.AbilityGenerator[levellimit] = list()
        self.AbilityGenerator[levellimit].append(ability)

    def SetFormula(self, stat, function):
        self.StatGenerators[stat] = function

    def GetAtLevel(self, level):
        valid = False
        if level in self.Entries:
            valid = True
            return self.Entries[level]
        print "Could not find match for level " + str(level)
        ch = BaseCharacter()
        ch.SetValid(False)
        return ch

    def ValidForLevel(self, level):
        return True

def EnemyFactory(EnemyNode):
    EnemyName = "Invalid"
    DisplayName = ""
    Description = None
    if "name" in EnemyNode.attrib:
        EnemyName = EnemyNode.attrib["name"]
    if "displayname" in EnemyNode.attrib:
        DisplayName = EnemyNode.attrib["displayname"]
    else:
        DisplayName = EnemyName
    print "Adding Character " + EnemyName
    Instances = EnemyNode.findall("EnemyInstance")
    if Instances != None and len(Instances) > 0:
        #Instance Based
        Entries = EntryBasedLevelGeneration()
        for instance in Instances:
            level = 0
            if "level" in instance.attrib:
                level = int(instance.attrib["level"])
            character = InstanceGeneration(instance, EnemyName, DisplayName)
            Entries.AddLevelEntry(level, character)
            
            x = 0
        valid = True
        EnemyLibrary.AddCharacterEntry(EnemyName, Entries)
    return

def InstanceGeneration(instance, name, dname):
    Description = None
    SMap = StatMap()
    
    stats = instance.find("Stats")
    if stats != None:
        for stat, value in stats.attrib.iteritems():
            if stat in StatMappings:
                SMap[StatMappings[stat]] = int(value)
            else:
                print "Stat " + str(stat) + " does not match any known stat"
   
    character = BaseCharacter(name, SMap)
    character.SetProperty("DisplayName", dname)

    desc = instance.find("Description")
    if desc != None and "value" in desc.attrib:
        print desc.attrib["value"]
        character.SetProperty("Description", desc.attrib["value"])
    return character

enemyTree = xml.parse("..\\..\\..\\resources\\XML Databases\\Enemies.xml")
enemyRoot = enemyTree.getroot()
enemyList = enemyRoot.findall("Enemy")
if (enemyList != None):
    for enemy in enemyList:
        EnemyFactory(enemy)



