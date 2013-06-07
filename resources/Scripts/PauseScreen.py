from RocketModule import *
from GraphicsModule import *
from ScreenModule import *
from EngineModule import *
from GameScreensModule import *
from CharacterModule import *
from EntityModule import *

class PauseScreen(BasicRMLScreen):
    def __init__(self, LoadSounds = True):
        BasicRMLScreen.__init__(self, "PauseScreen", "PauseScreen.rml", Engine, Engine.GetUID())
        self.PauseOptionNameMap = ["Status", "Equipment", "Items", "Limit Breaks", "Command Styles", "Inventory", "Party", "Save"]
        self.OptionIndex = 0;
        self.OptionSelect = False
        self.CharacterCount = 0
        self.CharacterIndex = 0
        if (LoadSounds):
            Engine.GetSoundSystem().AddSound("SelectionCancel", "SelectionCancel", False, True, True, ".wav")
            Engine.GetSoundSystem().AddSound("SelectionChange", "SelectionChange", False, True, True, ".wav")
            Engine.GetSoundSystem().AddSound("SelectionConfirm", "SelectionConfirm", False, True, True, ".wav")
            Engine.GetSoundSystem().AddSound("SelectionFailed", "SelectionFailed", False, True, True, ".wav")
            Engine.GetSoundSystem().AddSound("SelectionInvalid", "SelectionInvalid", False, True, True, ".wav")
        self.SetAcceptingInputs(True)

        self.MakeOptionsMenu()
        self.MakeCharacterPanel()
        #self.HandleOptionSwap(0, Engine.GetTime())
        self.Transitioning = True
        Time = 150
        Offset = 20
        doc = self.GetDocument()
        newOption = doc.GetElementById(RocketString("Option0")) 
        StartTime = Engine.GetTime()    
        newMove = PositionTransform(None, Vector2f(Offset, 0), StartTime, StartTime + Time)
        newMoveTransformer = ElementTransformer(newOption)
        newMoveTransformer.AddTransformation(newMove)
        self.AddNewTransform("NewOptionMove", newMoveTransformer)
        newMove.ReInitialize(StartTime, StartTime + Time, newMoveTransformer)
        newOption.SetClassNames(RocketString("SelectedOption"))
        newMove.AddFinishedEvent(self.ReadyOption)
        self.MakeDummyItemInventory()
        #party = ActiveGame.GetPlayerParty().GetPartyMembers();
        
    def MakeDummyItemInventory(self):
        inv = ActiveGame.GetPlayerParty().GetInventory()
        inv.AddItem("Fire Shard", 3)
        inv.AddItem("Onyx Shard", 2)
        inv.AddItem("Thunder Gem", 3)
        inv.AddItem("Bright Stone", 3)
        inv.AddItem("Gel Caps", 3)
        inv.AddItem("Mithril Ore", 3)
        inv.AddItem("Orichalcum Ore", 3)
        inv.AddItem("Iron Ore", 3)
        print "Inv Added"

    def MakeCharacterPanel(self):
        cPanel = self.GetDocument().GetElementById(RocketString("ContentPanel"))
        if cPanel != None:
            party = ActiveGame.GetPlayerParty().GetPartyMembersInOrder()
            CharStrs = []
            CharStrs.append("<div id=\"CharacterPanel\" class=\"CharacterPanel\">")
            for member in party:
                CharStrs.append(self.CreateCharacterPreviewRML(member))
                self.CharacterCount += 1
            CharStrs.append("</div>")
            cPanel.SetInnerRML(RocketString("\n".join(CharStrs)))

    def MakeOptionsMenu(self):
         doc = self.GetDocument()
         optionsPanel = doc.GetElementById(RocketString("OptionsPanel"))
         RMLStrs = []
         optionNum = 0
         RMLStrs.append("<div id=\"MainOptionsPanel\">")
         for option in self.PauseOptionNameMap:
             RMLStrs.append("<div id=\"Option%s\" class=\"Option\"><div id=\"OptionText%s\" class=\"OptionText\">%s</div></div>" % (str(optionNum), str(optionNum), option))
             optionNum += 1
         RMLStrs.append("</div>")
         #rmltest = "\n".join(RMLStrs)
         optionsPanel.SetInnerRML(RocketString("\n".join(RMLStrs)))
         #print doc.GetInnerRML().CString()
         #print rmltest
    def CreateCharacterPreviewRML(self, character):
        RMLStrs = []
        if character != None:
            sm = character.GetStatsManager()
            name = character.GetName()
            hp = sm.GetCurrentHP()
            mp = sm.GetCurrentMP()
            sp = sm.GetCurrentSP()
            hpbase = sm.GetBaseStat(Stat.HP)
            mpbase = sm.GetBaseStat(Stat.MP)
            spbase = sm.GetBaseStat(Stat.SP)
            #style="left: 800px;"
            hpwidth = int((float(hp) / float(hpbase)) * 125)
            mpwidth = int((float(mp) / float(mpbase)) * 125)
            spwidth = int((float(sp) / float(spbase)) * 125)
            return "<div id=\"%sPanel\" class=\"SingleCharacterPanel\"><div id=\"%sPotrait\" class=\"CharacterPotrait\"><img src=\"pausemenutest/%sProfile.png\" class=\"CharacterPotraitImage\"/></div><div id=\"%sNamePanel\" class=\"NamePanel\">%s</div><div id=\"%sLevelPanel\" class=\"LevelPanel\"><div id=\"%sLevelHeader\" class=\"LevelHeader\">Level</div><div id=\"%sLevelValue\" class=\"LevelValue\">%s</div></div><div id=\"%sStatPanel\" class=\"StatPanel\"><div id=\"%sHPPanel\" class=\"HPPanel\"><div id=\"%sHPText\" class=\"HPText\">HP</div><div id=\"%sHPValue\" class=\"HPValue\">%s/ %s</div><img id=\"%sHPBar\" class=\"HPBar\" style=\"width: %spx;\" src=\"pausemenutest/HP.png\" /></div><div id=\"%sMPPanel\" class=\"MPPanel\"><div id=\"%sMPText\" class=\"MPText\">MP</div><div id=\"%sMPValue\" class=\"MPValue\">%s/ %s</div><img id=\"%sMPBar\" class=\"HPBar\" style=\"width: %spx;\"src=\"pausemenutest/MP.png\" /></div><div id=\"%sSPPanel\" class=\"SPPanel\"><div id=\"%sSPText\" class=\"SPText\">SP</div><div id=\"%sSPValue\" class=\"SPValue\">%s/ %s</div><img id=\"%sSPBar\" class=\"HPBar\" style=\"width: %spx;\"src=\"pausemenutest/SP.png\" /></div></div></div>" % (name, name, name, name, name, name, name, name, str(character.GetLevel()), name, name, name, name, str(hp), str(hpbase), name, str(hpwidth), name, name, name, str(mp), str(mpbase), name,str(mpwidth), name, name, name, str(sp), str(spbase), name,str(spwidth))
            RMLStrs.append("<div id=\"%sPanel\" class=\"SingleCharacterPanel\">" % (name))
            RMLStrs.append("<div id=\"%sPotrait\" class=\"CharacterPotrait\"><img src=\"pausemenutest/%sProfile.png\" class=\"CharacterPotraitImage\"/></div>" % (name, name));
            RMLStrs.append("<div id=\"%sNamePanel\" class=\"NamePanel\">%s</div>" % (name, name))
            RMLStrs.append("<div id=\"%sLevelPanel\" class=\"LevelPanel\"><div id=\"%sLevelHeader\" class=\"LevelHeader\">Level</div><div id=\"%sLevelValue\" class=\"LevelValue\">%s</div></div>" % (name, name, name, str(character.GetLevel())))
            RMLStrs.append("<div id=\"%sStatPanel\" class=\"StatPanel\">" % (name))
            RMLStrs.append("<div id=\"%sHPPanel\" class=\"HPPanel\"><div id=\"%sHPText\" class=\"HPText\">HP</div><div id=\"%sHPValue\" class=\"HPValue\">%s/ %s</div><img id=\"%sHPBar\" class=\"HPBar\" style=\"width: %spx;\" src=\"pausemenutest/HP.png\" /></div>" % (name, name, name, str(hp), str(hpbase), name, str(hpwidth)))
            RMLStrs.append("<div id=\"%sMPPanel\" class=\"MPPanel\"><div id=\"%sMPText\" class=\"MPText\">MP</div><div id=\"%sMPValue\" class=\"MPValue\">%s/ %s</div><img id=\"%sMPBar\" class=\"HPBar\" style=\"width: %spx;\"src=\"pausemenutest/MP.png\" /></div>" %(name, name, name, str(mp), str(mpbase), name,str(mpwidth)))
            RMLStrs.append("<div id=\"%sSPPanel\" class=\"SPPanel\"><div id=\"%sSPText\" class=\"SPText\">SP</div><div id=\"%sSPValue\" class=\"SPValue\">%s/ %s</div><img id=\"%sSPBar\" class=\"HPBar\" style=\"width: %spx;\"src=\"pausemenutest/SP.png\" /></div>"  %(name, name, name, str(sp), str(spbase), name,str(spwidth)))
            RMLStrs.append("</div></div>") #Close Stat Panel #Close CHaracter Panel
            #print "\n".join(RMLStrs)
        return "\n".join(RMLStrs)

    def CreateCharacterPreviewRMLBasic(self, character):
        RMLStrs = []
        if character != None:
            sm = character.GetStatsManager()
            name = character.GetName()
            hp = sm.GetCurrentHP()
            mp = sm.GetCurrentMP()
            sp = sm.GetCurrentSP()
            hpbase = sm.GetBaseStat(Stat.HP)
            mpbase = sm.GetBaseStat(Stat.MP)
            spbase = sm.GetBaseStat(Stat.SP)
            #style="left: 800px;"
            hpwidth = int((float(hp) / float(hpbase)) * 125)
            mpwidth = int((float(mp) / float(mpbase)) * 125)
            spwidth = int((float(sp) / float(spbase)) * 125)
            RMLStrs.append("<div id=\"" + name + "Panel\" class=\"SingleCharacterPanel\">");
            RMLStrs.append("<div id=\"" + name + "Potrait\" class=\"CharacterPotrait\">" + "<img src=\"pausemenutest/" + name + "Profile.png\" class=\"CharacterPotraitImage\"/>" + "</div>");
            RMLStrs.append("<div id=\"" + name + "NamePanel\" class=\"NamePanel\">" + name + "</div>")
            RMLStrs.append("<div id=\"" + name + "LevelPanel\" class=\"LevelPanel\"><div id=\"" + name + "LevelHeader\" class=\"LevelHeader\">Level</div><div id=\"" + name + "LevelValue\" class=\"LevelValue\">" + str(character.GetLevel()) + "</div></div>")
            RMLStrs.append("<div id=\"" + name + "StatPanel\" class=\"StatPanel\">")
            RMLStrs.append("<div id=\"" + name + "HPPanel\" class=\"HPPanel\"><div id=\"" + name + "HPText\" class=\"HPText\">HP</div><div id=\"" + name + "HPValue\" class=\"HPValue\">" + str(hp) + "/ " + str(hpbase) + "</div><img id=\"" + name + "HPBar\" class=\"HPBar\" style=\"width: " + str(hpwidth) + "px;\" src=\"pausemenutest/HP.png\" /></div>")
            RMLStrs.append("<div id=\"" + name + "MPPanel\" class=\"MPPanel\"><div id=\"" + name + "MPText\" class=\"MPText\">MP</div><div id=\"" + name + "MPValue\" class=\"MPValue\">" + str(mp) + "/ " + str(mpbase) + "</div><img id=\"" + name + "MPBar\" class=\"HPBar\" style=\"width: " + str(mpwidth) + "px;\"src=\"pausemenutest/MP.png\" /></div>")
            RMLStrs.append("<div id=\"" + name + "SPPanel\" class=\"SPPanel\"><div id=\"" + name + "SPText\" class=\"SPText\">SP</div><div id=\"" + name + "SPValue\" class=\"SPValue\">" + str(sp) + "/ " + str(spbase) + "</div><img id=\"" + name + "SPBar\" class=\"HPBar\" style=\"width: " + str(spwidth) + "px;\"src=\"pausemenutest/SP.png\" /></div>")
            RMLStrs.append("</div></div>") #Close Stat Panel #Close CHaracter Panel
            #print "\n".join(RMLStrs)
        return "\n".join(RMLStrs)

    def HandleOptionSwap(self, NewIndex, StartTime):
        Time = 150
        Offset = 20
        doc = self.GetDocument()
        
        if (self.OptionIndex != NewIndex):
            newOption = doc.GetElementById(RocketString("Option" + str(NewIndex)))
            #newPos = newOption.GetAbsoluteOffset()     
            newMove = PositionTransform(None, Vector2f(Offset - newOption.GetOffsetLeft(), 0), StartTime, StartTime + Time)
            #print "Current New Offset = " + str(newOption.GetOffsetLeft())
            newMoveTransformer = ElementTransformer(newOption)
            newMoveTransformer.AddTransformation(newMove)
            self.AddNewTransform("NewOptionMove", newMoveTransformer)
            newMove.ReInitialize(StartTime, StartTime + Time, newMoveTransformer)
            newOption.SetClassNames(RocketString("SelectedOption"))

            oldOption = doc.GetElementById(RocketString("Option" + str(self.OptionIndex)))
            oldMove = PositionTransform(None, Vector2f(-oldOption.GetOffsetLeft(), 0), StartTime, StartTime + Time)
            oldMoveTransformer = ElementTransformer(oldOption)
            oldMoveTransformer.AddTransformation(oldMove)
            self.AddNewTransform("OldOptionMove", oldMoveTransformer)
            oldMove.ReInitialize(StartTime, StartTime + Time, oldMoveTransformer)
            #print "Current Old Offset = " + str(oldOption.GetOffsetLeft())
            self.Transitioning = True
            oldMove.AddFinishedEvent(self.ReadyOption)
            oldOption.SetClassNames(RocketString("Option"))

        self.OptionIndex = NewIndex

    def ReadyOption(self, time, transformation):
        self.Transitioning = False

    def ReadyCharacterSelect(self, time, transformation):
        SelectedCharacter = ActiveGame.GetPlayerParty().GetPartyMembersInOrder()[self.CharacterIndex]
        print SelectedCharacter.GetName()
        self.Transition = False

    def HandleKeyPressed(self, time, inputModule, action):
        if (self.IsAcceptingInputs()):
            if (not self.Transitioning):
                if (self.OptionSelect):
                    return self.HandleKeyPressedCharacterBrowse(time, inputModule, action)
                else:
                    return self.HandleKeyPressedOptionMenu(time, inputModule, action)
            return True
        return False
    def HandleKeyPressedCharacterBrowse(self, time, inputModule, action):
        if (action.PInput == PlayerInput.P1Input):
            if (action.IAction == InputAction.Cancel):
                self.OptionSelect = False
                highlighter = self.GetDocument().GetElementById(RocketString("CharacterHighlighter"))
                self.GetDocument().RemoveChild(highlighter)
                Engine.GetSoundSystem().PlaySound("SelectionCancel", 8, False)
                self.CharacterIndex = 0
            elif (action.IAction == InputAction.Confirm):
                transtime = 250
                
                #Move Options to the side
                Offset = Vector2f(-220, 0)
                optionMenu = self.GetDocument().GetElementById(RocketString("OptionsPanel"))
                oMove = PositionTransform(None, Offset, time, time + transtime)
                oTransform = ElementTransformer(optionMenu)
                oTransform.AddTransformation(oMove)
                self.AddNewTransform("OptionsMove", oTransform)
                oMove.ReInitialize(time, time + transtime, oTransform)
                self.Transitioning = True
                oMove.AddFinishedEvent(self.ReadySubScreen)

                Offset = Vector2f(720, 0)
                charMenu = self.GetDocument().GetElementById(RocketString("CharacterPanel"))
                cMove = PositionTransform(None, Offset, time, time + transtime)
                cTransform = ElementTransformer(charMenu)
                cTransform.AddTransformation(cMove)
                self.AddNewTransform("OptionsMove", cTransform)
                cMove.ReInitialize(time, time + transtime, cTransform)

                Engine.GetSoundSystem().PlaySound("SelectionConfirm", 8, False)

            elif (action.IAction == InputAction.Left):
                self.CharacterIndex -= 1
                Offset = Vector2f(-145, 0)
                if (self.CharacterIndex < 0):
                    self.CharacterIndex = self.CharacterCount - 1
                    Offset.x = 145 * (self.CharacterCount - 1)
                highlighter = self.GetDocument().GetElementById(RocketString("CharacterHighlighter"))
                hMove = PositionTransform(None, Offset, time, time + 150)
                hTransformer = ElementTransformer(highlighter)
                hTransformer.AddTransformation(hMove)
                self.AddNewTransform("HighlighterMove", hTransformer)
                hMove.ReInitialize(time, time + 150, hTransformer)
                self.Transitioning = True
                hMove.AddFinishedEvent(self.ReadyOption)
                Engine.GetSoundSystem().PlaySound("SelectionChange", 8, False)
            elif (action.IAction == InputAction.Right):
                self.CharacterIndex += 1
                Offset = Vector2f(145, 0)
                if (self.CharacterIndex > self.CharacterCount - 1):
                    self.CharacterIndex = 0
                    Offset.x = -145 * (self.CharacterCount - 1)
                highlighter = self.GetDocument().GetElementById(RocketString("CharacterHighlighter"))
                hMove = PositionTransform(None, Offset, time, time + 150)
                hTransformer = ElementTransformer(highlighter)
                hTransformer.AddTransformation(hMove)
                self.AddNewTransform("HighlighterMove", hTransformer)
                hMove.ReInitialize(time, time + 150, hTransformer)
                hMove.AddFinishedEvent(self.ReadyOption)
                self.Transitioning = True
                Engine.GetSoundSystem().PlaySound("SelectionChange", 8, False)
        return True
    def HandleKeyPressedStatusPanel(self, time, inputModule, action):
        if (action.PInput == PlayerInput.P1Input):
            return False
    def PushSubScreen(self):
        screenName = self.PauseOptionNameMap[self.OptionIndex]
        return

    def HandleKeyPressedOptionMenu(self, time, inputModule, action):
        if (action.PInput == PlayerInput.P1Input):
            if (action.IAction == InputAction.Down):
                if (self.OptionIndex >= (len(self.PauseOptionNameMap) - 1)):
                    self.HandleOptionSwap(0, time)
                else:
                    self.HandleOptionSwap(self.OptionIndex + 1, time)
                Engine.GetSoundSystem().PlaySound("SelectionChange", 8, False)
                return True
                Engine.GetSoundSystem().PlaySound("SelectionInvalid", 8, False)
            elif (action.IAction == InputAction.Up):
                if (self.OptionIndex == 0):
                    self.HandleOptionSwap(len(self.PauseOptionNameMap) - 1, time)
                else:
                    self.HandleOptionSwap(self.OptionIndex - 1, time)
                Engine.GetSoundSystem().PlaySound("SelectionChange", 8, False)
                return True
            elif (action.IAction == InputAction.Left):
                Engine.GetSoundSystem().PlaySound("SelectionChange", 8, False)
                return True
            elif (action.IAction == InputAction.Right):
                Engine.GetSoundSystem().PlaySound("SelectionChange", 8, False)
                return True
            elif (action.IAction == InputAction.Cancel or action.IAction == InputAction.Start):
                Engine.GetSoundSystem().PlaySound("SelectionCancel", 8, False)
                self.SetAcceptingInputs(False)
                Engine.GetScreenManager().RemoveStack("PauseScreen")
            elif (action.IAction == InputAction.Confirm):
                Engine.GetSoundSystem().PlaySound("SelectionConfirm", 8, False)
                print "Confirm Selection"
                self.OptionSelect = True
                self.PushOption(time)
                
                #eletarget->GetTarget()->SetProperty(Rocket::Core::String("left"), Rocket::Core::String(newVal.c_str()));
                #HighlightDiv.SetProperty(RocketString("left"), RocketString("100px"))
                #Engine.GetScreenManager().RemoveStack("PauseScreen")
        return True

    def PushOption(self, time):
        IndexName = self.PauseOptionNameMap[self.OptionIndex]
        if IndexName == "Items":
            print "Putting Items"
            transtime = 250
            
            #Move Options to the side
            Offset = Vector2f(-220, 0)
            optionMenu = self.GetDocument().GetElementById(RocketString("OptionsPanel"))
            oMove = PositionTransform(None, Offset, time, time + transtime)
            oTransform = ElementTransformer(optionMenu)
            oTransform.AddTransformation(oMove)
            self.AddNewTransform("OptionsMove", oTransform)
            oMove.ReInitialize(time, time + transtime, oTransform)
            self.Transitioning = True
            
            print "Moving Ops Menu"
            Offset2 = Vector2f(720, 0)
            charMenu = self.GetDocument().GetElementById(RocketString("CharacterPanel"))
            cMove = PositionTransform(None, Offset, time, time + transtime)
            cTransform = ElementTransformer(charMenu)
            cTransform.AddTransformation(cMove)
            self.AddNewTransform("CPanelMove", cTransform)
            cMove.ReInitialize(time, time + transtime, cTransform)
            cMove.AddFinishedEvent(self.ReadySubScreen)
            Engine.GetSoundSystem().PlaySound("SelectionConfirm", 8, False)

           
        elif IndexName == "Status" or IndexName == "Equipment" or IndexName == "Limit Breaks" or IndexName == "Command Styles":
            HighlightDiv = self.GetDocument().CreateElementUnmanaged(RocketString("div"))
            HighlightDiv.SetId(RocketString("CharacterHighlighter"))
            HighlightDiv.SetClass(RocketString("CharacterHighlight"), True)
            self.GetDocument().AppendChild(HighlightDiv)
            return
        #"Status", "Equipment", "Items", "Limit Breaks", "Command Styles", "Inventory", "Party", "Save"
        elif IndexName == "Party":
            self.OptionSelect = False
            return
        elif IndexName == "Save":
            self.OptionSelect = False
            return

    def HandleKeyReleased(self, time, inputModule, action):
        if (self.IsAcceptingInputs()):
            return True
        return False

    #Item Menu
    def HandleKeyPressedItemOptions(self, time, inputModule, action):
        return True

    def ReadySubScreen(self, time, transformation):
        IndexName = self.PauseOptionNameMap[self.OptionIndex]
        if IndexName == "Items":
            print "At Items in SubScreen prep"
            cPanel = self.GetDocument().GetElementById(RocketString("ContentPanel"))
            inv = ActiveGame.GetPlayerParty().GetInventory().GetItems()
            ItemsRML = []
            ItemsRML.append("<div id=\"ItemsPanel\" class=\"ItemsPanel\">")
            print str(len(inv))
            print type(inv)
            inv["Thunder Core"] = 10
            print str(len(inv))
            for key in inv.iterkeys():
                print key
                #ItemsRML.append(self.CreateItemRML(name, inv[key]))
            print str(len(ItemsRML))
            ItemsRML.append("</div>")
            cPanel.SetInnerRML(RocketString("\n".join(ItemsRML)))
            print ("\n".join(ItemsRML))
    def CreateItemRML(self, name, count):
        print "Adding Item " + name
        return "<div id=\"%sBox\" class=\"ItemBox\"><div id=\"%sName\" class=\"ItemName\">%s</div><div id=\"%sItemCount\" class=\"ItemCount\">%s</div></div>" % (name, name, name, name, count)
    def Reload(self):
        return False    

def MakePauseScreen():
    return PauseScreen()
 
#MakeScreen()