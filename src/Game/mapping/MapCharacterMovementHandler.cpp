#include "MapCharacterMovementHandler.h"
#include "GameMap.h"

namespace Game
{
	namespace Mapping
	{
		MapCharacterMovementHandlerComponent::MapCharacterMovementHandlerComponent(Entity* owner) : Components::Component(owner, owner != nullptr ? owner->GetName() + "MapCharMoveHandlerComp" : "NoOwnerMapCharMoveHandlerComp", "MapCharacterMovementHandlerComponent")
		{

		}

		void MapCharacterMovementHandlerComponent::HandleCharacterMovement(GameMap& map, MapCharacter& mchar)
		{

		}

		MapCharacterMovementHandlerComponent::RawClonePtr MapCharacterMovementHandlerComponent::RawClone() const
		{
			return MapCharacterMovementHandlerComponent::RawClonePtr(new MapCharacterMovementHandlerComponent(*this));
		}
	}
}