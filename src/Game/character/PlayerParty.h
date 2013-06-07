#pragma once
#include <character/Party.h>
#include <character/BaseCharacter.h>
#include <character/PlayerCharacterComponent.h>
#include <items/Inventory.h>
namespace Game
{
	class GameInstance;
	class GameState;
	namespace Character
	{
		class PlayerParty : public PartyInterface<BaseCharacter>
		{
		public:
			PlayerParty();
			void AddCharacter(const std::string& name, boost::shared_ptr<BaseCharacter> character);

			void RemoveCharacter(const std::string& name);

			PartyInterface<PlayerCharacterComponent> GetPlayerCharacterParty();

			Items::InventoryComponent& GetInventory();

			virtual Components::Component* GetComponent(const std::string& index) override;
		protected:
			PartyInterface<PlayerCharacterComponent> PlayerCharacterComponents;
			static std::string pcompindex;
			Items::InventoryComponent Inventory;
			friend class GameInstance;
			friend class GameState;
		};

		
	}
	
}