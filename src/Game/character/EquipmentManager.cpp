#include "EquipmentManager.h"
#include <Items/EquipComponent.h>

namespace Game
{
	using namespace Items;
	namespace Character
	{
		EquipmentManager::EquipmentManager(Entity* owner, Items::Inventory* pInv) : Component(owner, owner != nullptr ? owner->GetName() + "EquipmentManager" : "NoOwnerEquipmentManager", "EquipmentManager")
		{

		}
		EquipmentManager::EquipmentManager(const EquipmentManager& eqMgr) : Component(eqMgr), EquipmentHolder(eqMgr.EquipmentHolder), HolderInventory(eqMgr.HolderInventory)
		{
			for (auto eqIt = eqMgr.EquippedItems.begin(); eqIt != eqMgr.EquippedItems.end(); ++eqIt)
			{
				EquippedItems[eqIt->first] = (eqIt->second.get() != nullptr ? boost::dynamic_pointer_cast<Item>(eqIt->second->Clone()) : item_ptr());
			}
			for (auto acc = eqMgr.Accessories.begin(); acc != eqMgr.Accessories.end(); ++acc)
			{
				Accessories[acc->first] = (acc->second.get() != nullptr ? boost::dynamic_pointer_cast<Item>(acc->second->Clone()) : item_ptr());
			}
			for (auto kst = eqMgr.KeyStones.begin(); kst!= eqMgr.KeyStones.end(); ++kst)
			{
				KeyStones[kst->first] = (kst->second.get() != nullptr ? boost::dynamic_pointer_cast<Item>(kst->second->Clone()) : item_ptr());
			}
		}
		Items::item_ptr EquipmentManager::EquipItem(const std::string& itemSlot, const std::string& item)
		{
			item_ptr itPtr;
			auto it = EquippedItems.find(itemSlot);
			if (it != EquippedItems.end())
			{
				itPtr = it->second;
				EnforceItemUnequip(itPtr);

				auto newitem = Item::ItemDB->GetItemCopyByName(item);
				if (newitem.get() != nullptr)
				{
					it->second = newitem;
					EnforceItemEquip(it->second);
				}
			}
			return itPtr;
		}
		bool EquipmentManager::ItemEquippedInSlot(const std::string& slot)
		{
			return (EquippedItems.find(slot) != EquippedItems.end());
		}
		Items::item_ptr EquipmentManager::GetItemInSlot(const std::string& slotName, bool &itemValid)
		{
			itemValid = false;
			auto it = EquippedItems.find(slotName);
			if (it != EquippedItems.end())
			{
				itemValid = true;
				return it->second;
			}
			return item_ptr();
		}
		//Accessory Manipulation
		void EquipmentManager::AddAccessorySlots(int count)
		{
			for (int i = 0; i < count; ++i)
			{
				Accessories[Accessories.size()] = item_ptr();
			}
		}
		//Removes accessory slots. If items were equipped in those slots, returns to owner's inventory. If inventory invalid, items are lost and error message is logged 
		void EquipmentManager::RemoveAccesorySlots(int count)
		{
			for (int i = count - 1; i >= 0 && Accessories.size(); --i)
			{
				auto it = Accessories.find(i);
				if (it->second.get() != nullptr)
				{
					EnforceItemUnequip(it->second);
				}
				Accessories.erase(it);
			}
		}
		//Removed accessory slots, returning any accessories equipped in the removed slots
		std::vector<item_ptr> EquipmentManager::RemoveAccessorySlotsWithItemReturn(int count)
		{
			std::vector<item_ptr> removedItems;
			for (int i = count - 1; i >= 0 && Accessories.size(); --i)
			{
				auto it = Accessories.find(i);
				if (it->second.get() != nullptr)
				{
					EnforceItemUnequip(it->second);
					removedItems.push_back(it->second);
				}
				Accessories.erase(it);
			}
			return removedItems;
		}

		int EquipmentManager::GetAccessorySlotCount() const
		{
			return Accessories.size();
		}
		void EquipmentManager::SwapHolder(BaseCharacter* newHolder, bool UnapplyOldHolder, bool ApplyNewHolder)
		{
			if (UnapplyOldHolder)
			{
				for (auto it = EquippedItems.begin(); it != EquippedItems.end(); ++it)
				{
					EnforceItemUnequip((it->second));
				}
				//auto &sm = EquipmentHolder->GetStatsManager();
				
			}
		}
		void EquipmentManager::EnforceItemEquip(item_ptr item)
		{
			if (item.get() != nullptr)
			{
				auto ecomp = item->GetComponentAs<EquipComponent*>(EquipComponentIndex);
				if (ecomp != nullptr)
				{
					ecomp->Equip(*EquipmentHolder);
				}
				else
				{

				}
			}
		}
		void EquipmentManager::EnforceItemUnequip(item_ptr item)
		{
			if (item.get() != nullptr)
			{
				auto ecomp = item->GetComponentAs<EquipComponent*>(EquipComponentIndex);
				if (ecomp != nullptr)
				{
					ecomp->UnEquip(*EquipmentHolder);
				}
				else
				{
				}
			}
		}

		Items::Inventory* EquipmentManager::GetInventory() const
		{
			return HolderInventory;
		}

		void EquipmentManager::SetInventory(Items::Inventory* inv)
		{
			HolderInventory = inv;
		}

		EquipmentManager::RawClonePtr EquipmentManager::RawClone() const
		{
			return EquipmentManager::RawClonePtr(new EquipmentManager(*this));
		}
		EquipmentManager::~EquipmentManager()
		{
		}
	}
}