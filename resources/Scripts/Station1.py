from GameMappingModule import *
from MappingModule import *
from ComponentModule import *
from GraphicsModule import *
CopyKey = "copy";

#MovementComponentIndex
#HandleCharacterMovement(GameMap& map, MapCharacter& mchar)
class HandleCharacterMovementTest(MapCharacterMovementHandlerComponent):

    def __init__(self, *args, **kwargs):
        if (CopyKey in kwargs):
            MapCharacterMovementHandlerComponent.__init__(self, kwargs[CopyKey])
        else:
            #Expect Arguments in form:  owner, stat, multiplier
            argc = len(args)
            MapCharacterMovementHandlerComponent.__init__(self, None if argc < 1 else args[0])

    def HandleCharacterMovement(self, map, mchar):
        print "Printing Position"
        print "Map Position: X: " + str(mchar.MapPosition.x) + " | " + str(mchar.MapPosition.y)
    def Clone(self):
        return HandleCharacterMovementTest(self = copy)

CurrentMap.RegisterComponent(MovementComponentIndex, HandleCharacterMovementTest(CurrentMap), True)

print "Appended movement component"