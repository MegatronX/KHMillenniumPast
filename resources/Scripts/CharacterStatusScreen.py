from RocketModule import *
from GraphicsModule import *
from ScreenModule import *
from EngineModule import *
from GameScreensModule import *
from CharacterModule import *
from EntityModule import *

class CharacterStatusScreen(BasicRMLScreen):
    def __init__(self, Char, CallingScreen = None, LoadSounds = True):
        BasicRMLScreen.__init__(self, "PauseScreen", "PauseScreen.rml", Engine, Engine.GetUID())
        self.Character = Char
        self.Caller = CallingScreen

