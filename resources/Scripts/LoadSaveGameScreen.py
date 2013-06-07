from RocketModule import *
from GraphicsModule import *
from ScreenModule import *
from EngineModule import *
from GameScreensModule import *
#from TitleScreen import *
import os
import xml.etree.cElementTree as xml

class SaveGameHeader():
    def __init__(self, index):
        self.Index = index
        self.AreaMajor = "Invalid"
        self.AreaMinor = "Invalid"
        self.Area = "Invalid - Invalid"
        self.PHours = 0
        self.PMinutes = 0
        self.PSeconds = 0
        self.PlayTime = "0:0:0"
        self.Munny = 0
        self.Level = ""
        self.PartyMembers = []
        self.Leader = ""
        self.LeaderLevel = ""
        self.SaveFile = ""
    def MakePlayTime(self, seperator = ":", truncate = True):
        self.PlayTime = ("" if (self.PHours < 1 and truncate) else str(self.PHours)) + seperator + ("" if (self.PMinutes < 1 and truncate) else str(self.PMinutes)) + seperator + ("" if (self.PSeconds < 1 and truncate) else str(self.PSeconds))
        return self.PlayTime
    
    def MakeArea(self, seperator = "-", spaces = True):
        self.Area = self.AreaMajor + (" " if spaces else "") + seperator + (" " if spaces else "") + self.AreaMinor
        return self.Area
     
def MakeSaveHeaderFromXML(xmlnode, index):
    Header = SaveGameHeader(index)
    ptime = xmlnode.find("PlayTime")
    if (ptime != None):
        if "hours" in ptime.attrib:
            Header.PHours = int(ptime.attrib["hours"])
        if "minutes" in ptime.attrib:
            Header.PMinutes = int(ptime.attrib["minutes"])
        if "seconds" in ptime.attrib:
            Header.PSeconds = int(ptime.attrib["seconds"])
        Header.MakePlayTime()
    munny = xmlnode.find("Munny")
    if (munny != None):
        Header.Munny = int(munny.attrib["value"])
    area = xmlnode.find("Area")
    if (area != None):
        if "major" in area.attrib:
            Header.AreaMajor = area.attrib["major"]
        if "minor" in area.attrib:
            Header.AreaMinor = area.attrib["minor"]
        Header.MakeArea()
        
    party = xmlnode.find("MainParty")
    if (party != None):
        members = party.findall("PartyMember")
        first = True
        for member in members:
            if "name" in member.attrib:
                mname = member.attrib["name"]
                mlv = int(member.attrib["level"]) if "level" in member.attrib else 0
                if (first):
                    Header.Leader = mname
                    Header.LeaderLevel = mlv
            
            first = False
    return Header

def MakeSaveHeaderFromXMLSave(xmlfile, index):
    save = xml.parse(xmlfile)
    root = save.getroot()
    sg = root.find("Saves")
    saves = sg.findall("Save")
    SaveHeaders = []
    for sv in saves:
        ls = MakeSaveHeaderFromXML(sv, index)
        ls.SaveFile = xmlfile
        SaveHeaders.append(ls)
        index += 1
    return SaveHeaders         

class GameSaveScreen(BasicRMLScreen):
    def __init__(self, Caller, Name = "GameSaveScreen", SaveEnabled = True, LoadEnabled = False, LoadSounds = False):
        self.Caller = Caller
        self.Name = Name
        self.SaveEn = SaveEnabled
        self.LoadEn = LoadEnabled
        if LoadSounds:
            Engine.GetSoundSystem().AddSound("SelectionCancel", "SelectionCancel", False, True, True, ".wav")
            Engine.GetSoundSystem().AddSound("SelectionChange", "SelectionChange", False, True, True, ".wav")
            Engine.GetSoundSystem().AddSound("SelectionConfirm", "SelectionConfirm", False, True, True, ".wav")
            Engine.GetSoundSystem().AddSound("SelectionFailed", "SelectionFailed", False, True, True, ".wav")
            Engine.GetSoundSystem().AddSound("SelectionInvalid", "SelectionInvalid", False, True, True, ".wav")
        #BasicRMLScreen.__init__(self, "TitleScreen", "Titlescreen.rml", Engine, Engine.GetUID())
        BasicRMLScreen.__init__(self, Name, "GameSaveScreen.rml", Engine, Engine.GetUID())
        self.DisplaySaveGames()
        
    def DisplaySaveGames(self):
        SaveDir = Engine.GetApplicationConfiguration().GetApplicationSetting("SaveDirectory")
        if (len (SaveDir) > 0):
            RMLStrs = []
            Saves = []
            index = 0
            RMLStrs.append("<div id=\"savepanel\" class=\"savepanel\">")
            for root, dirs, files in os.walk(SaveDir):
                for f in files:
                    path = os.path.join(root, f)
                    svs = MakeSaveHeaderFromXMLSave(path, index)

                    index += len(svs)
                    Saves += svs
        
            if (len(Saves) > 0):
                print "Found " + str(len(Saves)) + " saves."
                for save in Saves:
                    RMLStrs.append("<div id=\"save" + str(save.Index) + "\" class=\"save\">")
                    RMLStrs.append("<div id=\"Id" + str(save.Index) + "\" class=\"saveid\"><div id=\"IdText" + str(save.Index) + "\" class=\"aveidtext\">"+ str(save.Index + 1) + "</div></div>")
                    RMLStrs.append("<div id=\"Level" + str(save.Index) + "\" class=\"savelevel\">Level " + str(save.LeaderLevel) + "</div>")
                    RMLStrs.append("<div id=\"Munny" + str(save.Index) + "\" class=\"savemoney\">Munny: " + str(save.Munny) + "</div>")
                    #          <div id="Level0" class="savelevel">Level 62</div>
                    #<div id="Munny0" class="savemoney">Munny: 103622</div>

                    RMLStrs.append("<div id=\"Time" + str(save.Index) + "\" class=\"savetime\">Time: " + save.PlayTime + "</div>")
                    RMLStrs.append("<div id=\"Area" + str(save.Index) + "\" class=\"savearea\">" + save.Area + "</div>")
                    RMLStrs.append("<img id=\"Char" + str(save.Index) + "\" class=\"character\" src=\"testimages/RandomChars/" + save.Leader + ".png\"/>")
                    #          <img id="Char4" class="character" src="testimages/RandomChars/4.png"/>
                    RMLStrs.append("</div>")
            else:
                print "Save Count was 0"
            RMLStrs.append("</div>")
            RMLstr = "\n".join(RMLStrs)
            body = self.GetDocument().GetElementById(RocketString("MainPanel"))
            body.SetInnerRML(RocketString(RMLstr))

            print RMLstr;
        else:
            #Need to add a message saying no save files found
            print "No Saves Found!"
            return
        
        
    def HandleKeyPressed(self, time, inputModule, action):
        print "In Load Save Game Input Handler"
        if (self.IsAcceptingInputs()):
            if (action.IAction == InputAction.Cancel):
                Engine.GetScreenManager().RemoveStack(self.Name)
                Engine.GetSoundSystem().PlaySound("SelectionCancel", 8, False)
                self.SetAcceptingInputs(False)
                self.Caller.SetAcceptingInputs(True)
                action.IAction = InputAction.InvalidAction
                action.Cancelled = True
                if (self.Caller.__class__.__name__ == "TitleScreen"):
                    self.Caller.Mode = "MainOptions"
                else:
                    print "Caller could not pass as TitleScreen. "+ self.Caller.__class__.__name__ 
        return False
    
    def HandleKeReleased(self, time, inputModule, action):
        return False
        

def MakeSaveHeader(index, filepath):
    SG = SaveGameHeader
    SG.Index = index
    SG.Path = filepath

def MakeGameSaveScreen(Caller, Name, SaveEn = True, LoadEn = False, LoadSounds = False):
    print "Making Stack"
    GS = GameSaveScreen(Caller, Name, SaveEn, LoadEn, LoadSounds)
    FR = BasicRMLScreen(Name + "Front", "StandardFront.html", Engine, Engine.GetUID())
    BR = BasicRMLScreen(Name + "Back", "StandardBack.html", Engine, Engine.GetUID())
    #GB = StandardBack(Caller, Name, "Red", "Transparent", 5, 100, 100)
   # GF = StandardFront(Caller, "Red", )
    SS = ScreenStack("LoadGameSaveStack", Engine.GetUID())
    SS.AddScreen(GS, 1)
    SS.AddScreen(FR, 3)
    SS.AddScreen(BR, 0)
    #SS.AddScreen(GB, 0)
    return SS
    