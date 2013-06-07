#pragma once

#include <components/Component.h>
namespace Game
{
	namespace Mapping
	{
		struct MapCharacter;
		class GameMap;
		class MapCharacterMovementHandlerComponent : public Components::Component
		{
		public:
			MapCharacterMovementHandlerComponent(Entity* owner);

			virtual void HandleCharacterMovement(GameMap& map, MapCharacter& mchar);

			virtual MapCharacterMovementHandlerComponent::RawClonePtr RawClone() const override;
		};
	}
}