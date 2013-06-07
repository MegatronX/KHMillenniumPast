#pragma once

#include <components/Component.h>
#include <items/Inventory.h>
namespace Game
{
	namespace Character
	{
		class PlayerPartyComponent : public Components::Component
		{
		public:
			PlayerPartyComponent() : Munny(0), MunnyCap(99999999)
			{

			}
			PlayerPartyComponent(Entity* owner) : Component(owner, owner != null ? owner + "PlayerPartyComponent" : "NoOwnerPlayerPartyComponent", "PlayerPartyComponent"), Munny(0), MunnyCap(99999999)
			{

			}
			PlayerPartyComponent(Entity* owner, const std::string& name) : Component(owner, name, "PlayerPartyComponent"), Munny(0), MunnyCap(99999999)
			{

			}
		protected:
			unsigned int Munny;
			unsigned int MunnyCap;
			
		private:
		};
	}
}