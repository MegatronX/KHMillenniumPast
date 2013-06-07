#pragma once
#ifndef _EQUIPMANAGER_H_
#define _EQUIPMANAGER_H_
#include <components\Component.h>
#include <items\Item.h>
#include <items\Inventory.h>
#include <boost\unordered_set.hpp>
namespace Game
{
	namespace Character
	{
		class EquipmentManager : public Components::Component
		{
		public:
			EquipmentManager(Entity* owner, Items::Inventory* pInv);
			EquipmentManager(const EquipmentManager& eqMgr);

			Items::item_ptr EquipItem(const std::string& itemSlot, const std::string& item);
			bool ItemEquippedInSlot(const std::string& slot);
			Items::item_ptr GetItemInSlot(const std::string& slotName, bool &itemValid);

			//Accessory Manipulation
			void AddAccessorySlots(int count = 1);
			//Removes accessory slots. If items were equipped in those slots, returns to owner's inventory. If inventory invalid, items are lost and error message is logged 
			void RemoveAccesorySlots(int count = 1);
			//Removed accessory slots, returning any accessories equipped in the removed slots
			std::vector<Items::item_ptr> RemoveAccessorySlotsWithItemReturn(int count = 1);
			int GetAccessorySlotCount() const;

			Items::Inventory* GetInventory() const;

			virtual EquipmentManager::RawClonePtr RawClone() const override;

			virtual ~EquipmentManager();
		protected:
			void SetInventory(Items::Inventory* inv);

			void SwapHolder(BaseCharacter* newHolder, bool UnapplyOldHolder = true, bool ApplyNewHolder = true);
		private:
			BaseCharacter* EquipmentHolder;
			Items::Inventory* HolderInventory;

			boost::unordered_set<std::string> AllowedEquipmentSlots;

			void EnforceItemEquip(Items::item_ptr item);
			void EnforceItemUnequip(Items::item_ptr item);
			boost::unordered_map<std::string, Items::item_ptr> EquippedItems;
			//These properties tend to be more variable, can be driven by other equipped items
			std::map<int, Items::item_ptr> Accessories;
			std::map<int, Items::item_ptr> KeyStones;
		};
	}
}


#endif