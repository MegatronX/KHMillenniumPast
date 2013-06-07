from ComponentModule import *
from EntityModule import *
from ActionModule import *
import xml.etree.cElementTree as xml

print "WTF PYTHON"



print "attackList discovered"
actionTree = xml.parse("..\\..\\resources\\XML Databases\\Actions.xml")
actionRoot = actionTree.getroot()
actionList = actionRoot.findall("Action")

attackList = actionRoot.findall("Attack")

if (attackList != None):
    for attack in attackList:
        print "Attack Found"
        atk = AttackFactory(attack)

