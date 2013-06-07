from RocketModule import *
from GraphicsModule import *
from ScreenModule import *
from EngineModule import *
from GameScreensModule import *
from GameInstanceModule import *

DifficultyText = {"Beginner": RocketString("An easier mode intended for new players"), "Standard": RocketString("The recommended mode for most players"), "Expert":RocketString("A difficult and challenging mode intended for experienced players")}
ElementBackMap = {"Beginner": RocketString("EasyDifficultyBack"), "Standard": RocketString("NormalDifficultyBack"), "Expert": RocketString("HardDifficultyBack")}
IndexMap = {0: "Beginner", 1: "Standard", 2: "Expert"}
DifficultyElement = RocketString("gamedifficultytext")


class NewGameOptionsScreen(BasicRMLScreen):
    def __init__(self, Caller, Name = "NewGameOptionsScreen", LoadSounds = False):
        self.Caller = Caller
        self.Name = Name
        self.SelectedDifficultyIndex = 1
        if LoadSounds:
            Engine.GetSoundSystem().AddSound("SelectionCancel", "SelectionCancel", False, True, True, ".wav")
            Engine.GetSoundSystem().AddSound("SelectionChange", "SelectionChange", False, True, True, ".wav")
            Engine.GetSoundSystem().AddSound("SelectionConfirm", "SelectionConfirm", False, True, True, ".wav")
            Engine.GetSoundSystem().AddSound("SelectionFailed", "SelectionFailed", False, True, True, ".wav")
            Engine.GetSoundSystem().AddSound("SelectionInvalid", "SelectionInvalid", False, True, True, ".wav")
        #BasicRMLScreen.__init__(self, "TitleScreen", "Titlescreen.rml", Engine, Engine.GetUID())
        BasicRMLScreen.__init__(self, Name, "NewGameOptions.html", Engine, Engine.GetUID())
        self.GetDocument().GetElementById(DifficultyElement).SetInnerRML(DifficultyText[IndexMap[self.SelectedDifficultyIndex]])
        self.SwapOptions(-1, self.SelectedDifficultyIndex)
    def HandleKeyPressed(self, time, inputModule, action):
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
            elif(action.IAction == InputAction.Down):
                Engine.GetSoundSystem().PlaySound("SelectionChange", 8, False)
                oldIndex = self.SelectedDifficultyIndex
                self.SelectedDifficultyIndex = (self.SelectedDifficultyIndex + 1) % 3
                self.SwapOptions(oldIndex, self.SelectedDifficultyIndex)
            elif(action.IAction == InputAction.Up):
                Engine.GetSoundSystem().PlaySound("SelectionChange", 8, False)
                oldIndex = self.SelectedDifficultyIndex
                self.SelectedDifficultyIndex -= 1
                if (self.SelectedDifficultyIndex < 0):
                    self.SelectedDifficultyIndex = 2
                self.SwapOptions(oldIndex, self.SelectedDifficultyIndex)
            elif(action.IAction == InputAction.Confirm):
                ActiveGame.MakeNewGame(IndexMap[self.SelectedDifficultyIndex])
                #Start up Game
        return False

    def SwapOptions(self, OldIndex, NewIndex):
        doc = self.GetDocument()
        if (OldIndex > -1):
            oldele = doc.GetElementById(RocketString("BackgroundImage" + str(OldIndex)))
            if (oldele != None):
                oldele.SetInnerRML(RocketString("<img id=\"" + str(OldIndex) + "DifficultyBack\" class=\"nsdifficultyback\" src=\"testimages/NewGameOptionBack.png\"/>"))
            else:
                print "Could not find element " + "BackgroundImage" + str(OldIndex)
        if (NewIndex > -1):
            cursor = self.GetDocument().GetElementById(RocketString("MainCursor"))
            cursor.SetClass(RocketString("cursor" + IndexMap[NewIndex]), True)
            print "Setting class to cursor" + IndexMap[NewIndex]
            newele = doc.GetElementById(RocketString("BackgroundImage" + str(NewIndex)))
            if (newele != None):
                newele.SetInnerRML(RocketString("<img id=\"" + str(OldIndex) + "DifficultyBack\" class=\"nsdifficultyback\" src=\"testimages/NewGameOptionBackSelected.png\"/>"))
            else:
                print "Could not find element " + "BackgroundImage" + str(NewIndex)
        self.GetDocument().GetElementById(DifficultyElement).SetInnerRML(DifficultyText[IndexMap[NewIndex]])
        
        return
    
    def HandleKeyReleased(self, time, inputModule, action):
        return False



def MakeNewGameOptionsScreen(Caller, Name, LoadSounds = False):
    print "Making Options Stack"
    NG = NewGameOptionsScreen(Caller, Name, LoadSounds)
    #FR = BasicRMLScreen(Name + "Front", "StandardFront.html", Engine, Engine.GetUID())
    #BR = BasicRMLScreen(Name + "Back", "StandardBack.html", Engine, Engine.GetUID())
    #GB = StandardBack(Caller, Name, "Red", "Transparent", 5, 100, 100)
   # GF = StandardFront(Caller, "Red", )
    SS = ScreenStack(Name, Engine.GetUID())
    SS.AddScreen(NG, 1)
    #SS.AddScreen(FR, 3)
    #SS.AddScreen(BR, 0)
    #SS.AddScreen(GB, 0)
    return SS