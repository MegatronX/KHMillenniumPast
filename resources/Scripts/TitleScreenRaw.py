from RocketModule import *
from GraphicsModule import *
from ScreenModule import *
from EngineModule import *
from GameScreensModule import *
print "Got titlescreen 1"
doc = TitleScreen.GetDocument()
print "Got titlescreen doc"
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
#discfadeout = FaderTransform(None, 255, 0, ETime + CTime + 1600, ETime + CTime + 1600 + 1600)
#discfade.AddPostTransform(lfadeout, 1200)
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
#heartFadeOut = FaderTransform(None, 255, 0, ETime + CTime + 1600, ETime + CTime + 1600 + 1600)
#heartFadeIn.AddPostTransform(ceiraFadeOut, 1600)
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

#set time to Ceira's fadeout finalization
CTime += 3000 + 2300

