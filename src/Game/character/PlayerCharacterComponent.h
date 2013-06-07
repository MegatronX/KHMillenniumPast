#pragma once
#include <components/Component.h>
#include <character/LevelingTable.h>
namespace Game
{
	namespace Character
	{
		class PlayerCharacterComponent : public Components::Component
		{
		public:
			PlayerCharacterComponent(Entity* owner) : Component(owner, owner != nullptr ? owner->GetName() + "PlayerCharacterComponent" : "NoOwnerPlayerCharacterComponent", "PlayerCharacterComponent")
			{

			}
			PlayerCharacterComponent(Entity* owner, const std::string& name) : Component(owner, name, "PlayerCharacterComponent")
			{

			}
		protected:
			boost::unordered_map<unsigned int, unsigned int> RequiredExp;

		private:
		};
	}
}