from RocketModule import *
from GraphicsModule import *
from ScreenModule import *
from EngineModule import *
from GameScreensModule import *
from LoadSaveGameScreen import *
from NewGameOptionsScreen import *
class TitleScreen(BasicRMLScreen):
    def __init__(self, LoadSounds = True):
        BasicRMLScreen.__init__(self, "TitleScreen", "Titlescreen.rml", Engine, Engine.GetUID())
        Engine.GetSoundSystem().AddSound("Dearly Beloved", "Dearly Beloved")
        Engine.GetSoundSystem().PlaySound("Dearly Beloved")
        self.MakeAnimationSequence()
        #Engine.GetSoundSystem().AddSound("Dearly Beloved", "Dearly Beloved")
        if (LoadSounds):
            Engine.GetSoundSystem().AddSound("SelectionCancel", "SelectionCancel", True, True, True, ".wav")
            Engine.GetSoundSystem().AddSound("SelectionChange", "SelectionChange", True, True, True, ".wav")
            Engine.GetSoundSystem().AddSound("SelectionConfirm", "SelectionConfirm", True, True, True, ".wav")
            Engine.GetSoundSystem().AddSound("SelectionFailed", "SelectionFailed", True, True, True, ".wav")
            Engine.GetSoundSystem().AddSound("SelectionInvalid", "SelectionInvalid", True, True, True, ".wav")
        self.OptionIndex = 0
        self.GameOptionNameMap = [RocketString("NewGameOption"), RocketString("LoadGameOption"), RocketString("OptionsGameBox")]
        self.NewGameOptions = [RocketString("Beginner"), RocketString("Standard"), RocketString("Expert")];
        self.NewGameDescriptions = [RocketString("An easy mode intended for new players"), RocketString("A mode intended for most users."), RocketString("A difficult mode intended for experience players")];
        self.Mode = "Intro"
        self.Ready = False
        self.AllowJump = True
        self.SetAcceptingInputs(True)

    def MakeAnimationSequence(self):
        doc = self.GetDocument()
        TitleScreen = self
        CTime = 0
        lfade = FaderTransform(None, 0, 255, Engine.GetTime(), Engine.GetTime() + 2200)
        lfadeout = FaderTransform(None, 255, 0, Engine.GetTime(), Engine.GetTime() + 1200)
        lfade.AddPostTransform(lfadeout, 1200)
        eleTransformer = ElementTransformer(doc.GetElementById(RocketString("Logo")))
        eleTransformer.AddTransformation(lfade)
        TitleScreen.AddNewTransform("LogoFade", eleTransformer)
        lfade.ReInitialize(Engine.GetTime(), Engine.GetTime() + 2200, eleTransformer)

        CTime += 3400
        ETime = Engine.GetTime()
        print str(ETime)
        inspFadeIn = FaderTransform(None, 0, 255, ETime + CTime, ETime + CTime + 1200)
        #inspFadeOut = FaderTransform(None, 255, 0, 
        inspTrans = ElementTransformer(doc.GetElementById(RocketString("InspiredBy")))
        inspTrans.AddTransformation(inspFadeIn)
        inspFadeIn.ReInitialize(ETime + CTime, ETime + CTime + 1200, inspTrans)
        TitleScreen.AddNewTransform("InspFade", inspTrans)
        CTime += 1200

        disneyFadeIn = FaderTransform(None, 0, 255, ETime + CTime, ETime + CTime + 1600)
        disneyFadeOut = FaderTransform(None, 255, 0, ETime + CTime + 1600, ETime + CTime + 1600 + 1600)
        disneyFadeIn.AddPostTransform(disneyFadeOut, 1600)
        disTransformer = ElementTransformer(doc.GetElementById(RocketString("DisneyLogo")))
        disTransformer.AddTransformation(disneyFadeIn)
        disneyFadeIn.ReInitialize(ETime + CTime, ETime + CTime + 1600, disTransformer)
        TitleScreen.AddNewTransform("DisFade", disTransformer)

        squareFadeIn = FaderTransform(None, 0, 255, ETime + CTime, ETime + CTime + 1600)
        squareFadeOut = FaderTransform(None, 255, 0, ETime + CTime + 1600, ETime + CTime + 1600 + 1600)
        squareFadeIn.AddPostTransform(squareFadeOut, 1600)
        squareTransformer = ElementTransformer(doc.GetElementById(RocketString("SELogo")))
        squareTransformer.AddTransformation(squareFadeIn)
        squareFadeIn.ReInitialize(ETime + CTime, ETime + CTime + 1600, squareTransformer)
        TitleScreen.AddNewTransform("SquareFade", squareTransformer)
        CTime += 1600

        inspFadeOut = FaderTransform(None, 255, 0, ETime + CTime, ETime + CTime + 1600)
        inspTrans = ElementTransformer(doc.GetElementById(RocketString("InspiredBy")))
        inspTrans.AddTransformation(inspFadeOut)

        inspFadeOut.ReInitialize(ETime + CTime, ETime + CTime + 1600, inspTrans)
        TitleScreen.AddNewTransform("InspFadeOut", inspTrans)
        CTime += 1600
        #inspFadeIn.ReInitialize(ETIme + CTime, ETime + CTime + 1200, eleT2)

        discfade = FaderTransform(None, 0, 255, ETime + CTime, ETime + CTime + 2800)
        discTransformer = ElementTransformer(doc.GetElementById(RocketString("Disclaimer")))
        discTransformer.AddTransformation(discfade)
        TitleScreen.AddNewTransform("DiscFade", discTransformer)
        discfade.ReInitialize(ETime + CTime, ETime + CTime + 2800, discTransformer)
        CTime += 2800 + 2200

        discFadeOut = FaderTransform(None, 255, 0, ETime + CTime, ETime + CTime + 1200)
        discTransformer = ElementTransformer(doc.GetElementById(RocketString("Disclaimer")))
        discTransformer.AddTransformation(discFadeOut)
        TitleScreen.AddNewTransform("DiscFadeOut", discTransformer)
        discFadeOut.ReInitialize(ETime + CTime, ETime + CTime + 1200, discTransformer)

        CTime += 1200 + 300

        aoniMove = PositionTransform(None, Vector2f(805 , 100), ETime + CTime, ETime + CTime + 3400)
        aoniTransformer = ElementTransformer(doc.GetElementById(RocketString("Aoni")))
        aoniTransformer.AddTransformation(aoniMove)
        TitleScreen.AddNewTransform("AoniMove", aoniTransformer)
        aoniMove.ReInitialize(ETime + CTime, ETime + CTime + 3500, aoniTransformer)

        ArianMove = PositionTransform(None, Vector2f(-800 , 100), ETime + CTime, ETime + CTime + 3400)
        arianTransformer = ElementTransformer(doc.GetElementById(RocketString("Arian")))
        arianTransformer.AddTransformation(ArianMove)
        TitleScreen.AddNewTransform("ArianMove", arianTransformer)
        ArianMove.ReInitialize(ETime + CTime, ETime + CTime + 3500, arianTransformer)

        #CTime += 4000

        heartFadeIn = FaderTransform(None, 0, 200, ETime + CTime + 1450, ETime + CTime + 1450 + 2300)
        heartTransformer = ElementTransformer(doc.GetElementById(RocketString("Heart")))
        heartTransformer.AddTransformation(heartFadeIn)
        heartFadeIn.ReInitialize(ETime + CTime + 1450, ETime + CTime + 1450 + 2300, heartTransformer)
        TitleScreen.AddNewTransform("HeartFade", heartTransformer)
        CTime += 4000

        #Wait for 1600 ms
        CTime += 1600

        aoniFadeIn = FaderTransform(None, 140, 255, ETime + CTime, ETime + CTime + 3000)
        aoniFadeOut = FaderTransform(None, 255, 0, ETime + CTime + 3000, ETime + CTime + 3000 + 2300)
        aoniFadeIn.AddPostTransform(aoniFadeOut, 2300)
        aoniFadeTransformer = ElementTransformer(doc.GetElementById(RocketString("Aoni")))
        aoniFadeTransformer.AddTransformation(aoniFadeIn)
        aoniFadeIn.ReInitialize(ETime + CTime, ETime + CTime + 3000, aoniFadeTransformer)
        TitleScreen.AddNewTransform("AoniFader", aoniFadeTransformer)

        arianFadeIn = FaderTransform(None, 140, 255, ETime + CTime, ETime + CTime + 3000)
        arianFadeOut = FaderTransform(None, 255, 0, ETime + CTime + 3000, ETime + CTime + 3000 + 2300)
        arianFadeIn.AddPostTransform(arianFadeOut, 2300)
        arianFadeTransformer = ElementTransformer(doc.GetElementById(RocketString("Arian")))
        arianFadeTransformer.AddTransformation(arianFadeIn)
        arianFadeIn.ReInitialize(ETime + CTime, ETime + CTime + 3000, arianFadeTransformer)
        TitleScreen.AddNewTransform("ArianFader", arianFadeTransformer)

        ceiraFadeIn = FaderTransform(None, 0, 255, ETime + CTime, ETime + CTime + 3000)
        ceiraFadeOut = FaderTransform(None, 255, 0, ETime + CTime + 3000, ETime + CTime + 3000 + 2300)
        ceiraFadeIn.AddPostTransform(ceiraFadeOut, 2300)
        ceiraFadeTransformer = ElementTransformer(doc.GetElementById(RocketString("Ceira")))
        ceiraFadeTransformer.AddTransformation(ceiraFadeIn)
        ceiraFadeIn.ReInitialize(ETime + CTime, ETime + CTime + 3000, ceiraFadeTransformer)
        TitleScreen.AddNewTransform("CeiraFader", ceiraFadeTransformer)

        heartFadeOut = FaderTransform(None, 200, 0, ETime + CTime + 2300, ETime + CTime + 3000 + 2300)
        #heartFadeOut = FaderTransform(None, 255, 0, ETime + CTime + 1600, ETime + CTime + 1600 + 1600)
        #heartFadeIn.AddPostTransform(ceiraFadeOut, 1600)
        heartTransformer2 = ElementTransformer(doc.GetElementById(RocketString("Heart")))
        heartTransformer2.AddTransformation(heartFadeOut)
        heartFadeOut.ReInitialize(ETime + CTime + 2300, ETime + CTime + 3000 + 2300, heartTransformer2)
        TitleScreen.AddNewTransform("HeartFadeOut", heartTransformer2)
        heartFadeOut.AddFinishedEvent(self.TurnJumpOff)

        #set time to Ceira's fadeout finalization
        CTime += 3000 + 2300

        #AandCMove = PositionTransform(None, Vector2f(-800 , 0), ETime + CTime, ETime + CTime + 1200)
        AandCMove = FaderTransform(None, 0, 220, ETime + CTime, ETime + CTime + 2200)
        AandCTransformer = ElementTransformer(doc.GetElementById(RocketString("AandC")))
        AandCTransformer.AddTransformation(AandCMove)
        TitleScreen.AddNewTransform("AandCMove", AandCTransformer)
        AandCMove.ReInitialize(ETime + CTime + 0, ETime + CTime + 1200, AandCTransformer)


        lBack = FaderTransform(None, 0, 255, ETime + CTime, ETime + CTime + 2900)
        lBackTransformer = ElementTransformer(doc.GetElementById(RocketString("LogoBack")))
        lBackTransformer.AddTransformation(lBack)
        TitleScreen.AddNewTransform("LBack", lBackTransformer)
        lBack.ReInitialize(ETime + CTime + 0, ETime + CTime + 1200, lBackTransformer)


        lFront = FaderTransform(None, 0, 255, ETime + CTime, ETime + CTime + 2900)
        lFrontTransformer = ElementTransformer(doc.GetElementById(RocketString("LogoFront")))
        lFrontTransformer.AddTransformation(lFront)
        TitleScreen.AddNewTransform("LFront", lFrontTransformer)
        lFront.ReInitialize(ETime + CTime + 0, ETime + CTime + 1200, lFrontTransformer)

        CTime += 250 + 800

        NewGameOptionMove = PositionTransform(None, Vector2f(-700, 0), ETime + CTime, ETime + CTime + 1270);
        NewGameOptTransformer = ElementTransformer(doc.GetElementById(RocketString("NewGameOption")))
        NewGameOptTransformer.AddTransformation(NewGameOptionMove)
        NewGameOptionMove.ReInitialize(ETime + CTime, ETime + CTime + 1270, NewGameOptTransformer)
        TitleScreen.AddNewTransform("NewGameOptMove", NewGameOptTransformer)

        LoadGameOptionMove = PositionTransform(None, Vector2f(-650, 0), ETime + CTime + 1000, ETime + CTime + 1000 + 1270);
        LoadGameOptTransformer = ElementTransformer(doc.GetElementById(RocketString("LoadGameOption")))
        LoadGameOptTransformer.AddTransformation(LoadGameOptionMove)
        LoadGameOptionMove.ReInitialize(ETime + CTime + 1000, ETime + CTime + 1000 + 1270, NewGameOptTransformer)
        TitleScreen.AddNewTransform("LoadGameOptMove", LoadGameOptTransformer)

        NewGameOptionMove = PositionTransform(None, Vector2f(-700, 0), ETime + CTime + 2000, ETime + CTime + 2000 + 1270);
        NewGameOptTransformer = ElementTransformer(doc.GetElementById(RocketString("OptionsGameBox")))
        NewGameOptTransformer.AddTransformation(NewGameOptionMove)
        NewGameOptionMove.ReInitialize(ETime + CTime + 2000, ETime + CTime + 2000 + 1270, NewGameOptTransformer)
        TitleScreen.AddNewTransform("OptionsBoxMove", NewGameOptTransformer)
        NewGameOptionMove.AddFinishedEvent(self.ReadyOption)

    def HandleMainOptionsKeyPressed(self, time, inputModule, action):
        if (action.PInput == PlayerInput.P1Input):
            if (action.IAction == InputAction.Down):
                self.OptionIndex = (self.OptionIndex + 1) % len(self.GameOptionNameMap)
                Engine.GetSoundSystem().PlaySound("SelectionChange", 8, False)
                self.SetMainOptionHighlight(0, None)
                return True
            elif (action.IAction == InputAction.Up):
                self.OptionIndex -= 1
                if (self.OptionIndex < 0):
                    self.OptionIndex = len(self.GameOptionNameMap) - 1
                Engine.GetSoundSystem().PlaySound("SelectionChange", 8, False)
                self.SetMainOptionHighlight(0, None)
                return True
            elif (action.IAction == InputAction.Confirm or action.IAction == InputAction.Start):
                print "Hit action confirm"
                print "Index: " + str(self.OptionIndex)
                if (self.OptionIndex == 0):
                    self.Mode = "NewGameOptions"
                    self.SetAcceptingInputs(False)
                    print "Disabled Inputs, switching to New Game Options"
                    LS = MakeNewGameOptionsScreen(self, "NewGameOptions", False)
                    Engine.GetScreenManager().AddScreenStack("NewGameOptions", LS, 10)
                    Engine.GetSoundSystem().PlaySound("SelectionConfirm", 8, False)
                    print "Pushed GS onto stack"
                    '''
                    optFade = FaderTransform(None, 0, 255, Engine.GetTime(), Engine.GetTime() + 800)
                    optFade.AddFinishedEvent(self.EnableInputs)
                    optTransformer = ElementTransformer(self.GetDocument().GetElementById(RocketString("NewGameMenu")))
                    optTransformer.AddTransformation(optFade)
                    self.AddNewTransform("GameOptionsFadeIn", optTransformer)'''
                    
                    return True
                elif (self.OptionIndex == 1):
                    print "Hit Load Game Save Screen"
                    self.Mode = "LoadGameOpened"
                    self.SetAcceptingInputs(False)
                    print "Disabled Inputs, Pushing GS onto stack"
                    LS = MakeGameSaveScreen(self, "GameSaveScreen", False, True)
                    Engine.GetScreenManager().AddScreenStack("GameSaveScreen", LS, 10)
                    Engine.GetSoundSystem().PlaySound("SelectionConfirm", 8, False)
                    print "Pushed GS onto stack"
                    #Push Load Game Screen onto screen stack
                elif (self.OptionIndex == 2):
                    #self.Mode = "LoadGameOpened"
                    #self.SetAcceptingInputs(False)
                    Engine.GetSoundSystem().PlaySound("SelectionInvalid", 8, False)
            elif (action.IAction == InputAction.Cancel):
                
                Engine.GetSoundSystem().PlaySound("SelectionInvalid", 8, False)
        return False
    def HandleMainOptionsKeyReleased(self, time, inputModule, action):
        return
    
    def EnableInputs(self, test, transformation):
        self.SetAcceptingInputs(True)

    def TurnJumpOff(self, test, transformation):
        self.AllowJump = False
    
    def JumpToStart(self):
        if (self.AllowJump):
            self.AllowJump = False
            ClearList = ["Logo", "InspiredBy", "DisneyLogo", "SELogo", "InspiredBy", "Disclaimer", "Aoni", "Arian", "Heart", "Ceira"]
            self.ClearTransforms()
            doc = self.GetDocument()
            TitleScreen = self
            for clear in ClearList:
                doc.GetElementById(RocketString(clear)).SetClass(RocketString("Hide"), True)
            ETime = Engine.GetTime()
            CTime = 0
            AandCMove = FaderTransform(None, 0, 220, ETime + CTime, ETime + CTime + 2200)
            AandCTransformer = ElementTransformer(doc.GetElementById(RocketString("AandC")))
            AandCTransformer.AddTransformation(AandCMove)
            TitleScreen.AddNewTransform("AandCMove", AandCTransformer)
            AandCMove.ReInitialize(ETime + CTime + 0, ETime + CTime + 1200, AandCTransformer)


            lBack = FaderTransform(None, 0, 255, ETime + CTime, ETime + CTime + 2900)
            lBackTransformer = ElementTransformer(doc.GetElementById(RocketString("LogoBack")))
            lBackTransformer.AddTransformation(lBack)
            TitleScreen.AddNewTransform("LBack", lBackTransformer)
            lBack.ReInitialize(ETime + CTime + 0, ETime + CTime + 1200, lBackTransformer)


            lFront = FaderTransform(None, 0, 255, ETime + CTime, ETime + CTime + 2900)
            lFrontTransformer = ElementTransformer(doc.GetElementById(RocketString("LogoFront")))
            lFrontTransformer.AddTransformation(lFront)
            TitleScreen.AddNewTransform("LFront", lFrontTransformer)
            lFront.ReInitialize(ETime + CTime + 0, ETime + CTime + 1200, lFrontTransformer)

            CTime += 250 + 800

            NewGameOptionMove = PositionTransform(None, Vector2f(-700, 0), ETime + CTime, ETime + CTime + 1270);
            NewGameOptTransformer = ElementTransformer(doc.GetElementById(RocketString("NewGameOption")))
            NewGameOptTransformer.AddTransformation(NewGameOptionMove)
            NewGameOptionMove.ReInitialize(ETime + CTime, ETime + CTime + 1270, NewGameOptTransformer)
            TitleScreen.AddNewTransform("NewGameOptMove", NewGameOptTransformer)

            LoadGameOptionMove = PositionTransform(None, Vector2f(-650, 0), ETime + CTime + 1000, ETime + CTime + 1000 + 1270);
            LoadGameOptTransformer = ElementTransformer(doc.GetElementById(RocketString("LoadGameOption")))
            LoadGameOptTransformer.AddTransformation(LoadGameOptionMove)
            LoadGameOptionMove.ReInitialize(ETime + CTime + 1000, ETime + CTime + 1000 + 1270, NewGameOptTransformer)
            TitleScreen.AddNewTransform("LoadGameOptMove", LoadGameOptTransformer)

            NewGameOptionMove = PositionTransform(None, Vector2f(-700, 0), ETime + CTime + 2000, ETime + CTime + 2000 + 1270);
            NewGameOptTransformer = ElementTransformer(doc.GetElementById(RocketString("OptionsGameBox")))
            NewGameOptTransformer.AddTransformation(NewGameOptionMove)
            NewGameOptionMove.ReInitialize(ETime + CTime + 2000, ETime + CTime + 2000 + 1270, NewGameOptTransformer)
            TitleScreen.AddNewTransform("OptionsBoxMove", NewGameOptTransformer)
            NewGameOptionMove.AddFinishedEvent(self.ReadyOption)

    def HandleNewGameOptionsKeyPressed(self, time, inputModule, action):
        if (action.PInput == PlayerInput.P1Input):
            if (action.IAction == InputAction.Down):
                self.NewGameOption = (self.NewGameOption + 1) % len(self.NewGameOptions);
                Engine.GetSoundSystem().PlaySound("SelectionChange", 8, False)
            elif (action.IAction == InputAction.Cancel):
                self.Mode = "Intro"
                Engine.GetSoundSystem().PlaySound("SelectionCancel", 8, False)
    def HandleNewGameOptionsKeyReleased(self, time, inputMode, action):
        return False
    def HandleKeyPressed(self, time, inputModule, action):
        if (self.IsAcceptingInputs()):
            if (self.Mode == "MainOptions"):
                return self.HandleMainOptionsKeyPressed(time, inputModule, action)
            elif (self.Mode == "NewGameOptions"):
                return self.HandleNewGameOptionsKeyPressed(time, inputModule, aciton)
            elif(self.Mode == "Intro" and action.PInput == PlayerInput.P1Input and action.IAction == InputAction.Start):
                self.JumpToStart()
                print "Jumping to start"
                return True
        print "Key Pressed: " + str(action.IAction) + " | " + str(action.PInput) + " | Mode: " + self.Mode
        return False
    
    def HandleKeyReleased(self, time, inputModule, action):
        if (self.IsAcceptingInputs()):
            if (self.Mode == "MainOptions"):
                return self.HandleMainOptionsKeyReleased(time, inputModule, action)
            elif (self.Mode == "NewGameOptions"):
                return self.HandleNewGameOptionsKeyReleased(time, inputMode, action)
        return False

    def SetMainOptionHighlight(self, time, transformation):
        ele = self.GetDocument().GetElementById(self.GameOptionNameMap[self.OptionIndex])
        top = ele.GetAbsoluteTop()
        left = ele.GetAbsoluteLeft()
        highlight = self.GetDocument().GetElementById(RocketString("MainSelectedOption"))
        highlight.SetOffset(RVector2f(-20, -21), ele, False)

    def ReadyOption(self, time, transformation):
        ele = self.GetDocument().GetElementById(RocketString("MainSelectedOption"))
        ele.SetClass(RocketString("MainSelectedOptionVis"), True)
        self.SetMainOptionHighlight(time, transformation)
        self.Mode = "MainOptions"
        self.Ready = True
        self.SetAcceptingInputs(True)
    
    def Reload(self):
        return False
    
def test(time, transformation):
    print "Callback Test"



def SwapGameOptions(index1, index2, document):
    document.GetElementById(GameOptionNameMap[index1]).SetClass(GameOptionActiveClass, True)
    document.GetElementById(GameOptionNameMap[index2]).SetClass(GameOptionBaseClass, True)


def testx(time, transformation):
    print "Callback Test"
    #engine->GetSoundSystem().AddSound("Dearly Beloved", "Dearly Beloved");
				#engine->GetSoundSystem().PlaySound("Dearly Beloved");

Engine.GetScreenManager().AddScreen(TitleScreen(), 0)
    
