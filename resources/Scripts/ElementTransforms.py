from RocketModule import *

class ScrollTransform(ElementTransformInterface):
    def __init__(self, target, scrollRateX, scrollRateY, currentTime, endTime):
        self.ScrollRateX = scrollRateX
        self.ScrollRateY = scrollRateY
        ElementTransformationInterface(target, currentTime, endTime)
    def FullyReInitialize():
        return
    def Update(self, time):
        return
    
    
