from RocketModule import *
from GraphicsModule import *
from ScreenModule import *
from EngineModule import *
from GameScreensModule import *
from CharacterModule import *
from EntityModule import *

def BattleTransitionScreen(BasicRMLScreen):
    def __init__(self):
        BasicRMLScreen.__init__(self, "BattleTransitionScreen", "BattleTransitionScreen.rml", Engine, Engine.GetUID())


    def PushBattleScreen(self):
        return

    def PopScreen(self):
        return

