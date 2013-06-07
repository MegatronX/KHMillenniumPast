#include "Inventory.h"
namespace Game
{
	namespace Items
	{
		//ItemDatabase* InventoryComponent::ItemDB = nullptr;

		InventoryComponent::InventoryComponent(Entity* owner) : Component(owner, owner != nullptr ? owner->GetName() + "InventoryComponent" : "NoOwnerInventoryComponent", "InventoryComponent")
		{

		}
		bool InventoryComponent::AddItem(boost::shared_ptr<Entity>& item, const int count)
		{
			return  item.get() != nullptr ? AddItem(item->GetName(), count) : false;
		}
		bool InventoryComponent::AddItem(Item* item, const int count)
		{
			return item != nullptr ? AddItem(item->GetName(), count) : false;
		}
		bool InventoryComponent::AddItem(Item& item, const int count)
		{
			return AddItem(item.GetName(), count);
		}
		bool InventoryComponent::AddItem(int itemID, const int count)
		{
			return false;
		}
		bool InventoryComponent::AddItem(const std::string& itemname, const int count)
		{
			auto it = ItemCount.find(itemname);
			if (it != ItemCount.end())
				it->second += count;
			ItemCount[itemname] = count;
			return true;
		}

		bool InventoryComponent::AddKeyItem(boost::shared_ptr<Entity>& item, const int count)
		{
			return  item.get() != nullptr ? AddKeyItem(item->GetName(), count) : false;
		}
		bool InventoryComponent::AddKeyItem(Item* item, const int count)
		{
			return item != nullptr ? AddKeyItem(item->GetName(), count) : false;
		}
		bool InventoryComponent::AddKeyItem(Item& item, const int count)
		{
			return AddKeyItem(item.GetName(), count);
		}
		bool InventoryComponent::AddKeyItem(int itemID, const int count)
		{
			return false;
		}
		bool InventoryComponent::AddKeyItem(const std::string& itemname, const int count)
		{
			auto it = KeyItemCount.find(itemname);
			if (it != KeyItemCount.end())
				it->second += count;
			KeyItemCount[itemname] = count;
			return true;
		}
		int InventoryComponent::GetItemCount(const std::string& itemName)
		{
			return 0;
		}
		int InventoryComponent::GetItemCount(const int itemID)
		{
			return 0;
		}

		void InventoryComponent::AddItemAddedEventHandler(const std::string& name, const ItemAddedHandler& handler)
		{

		}
		bool InventoryComponent::RemoveItemAddedEventHandler(const std::string& name)
		{
			return false;
		}
		void InventoryComponent::DispatchItemAddedEvents()
		{

		}

		void InventoryComponent::AddItemRemovedEventHandler(const std::string& name, const ItemAddedHandler& handler)
		{
			ItemAddEvents[name] = handler;
		}
		bool InventoryComponent::RemoveItemRemovedEventHandler(const std::string& name)
		{
			auto it = ItemRemovedEvents.find(name);
			if (it != ItemRemovedEvents.end())
			{
				ItemRemovedEvents.erase(it);
				return true;
			}
			return false;
		}
		void InventoryComponent::DispatchItemRemovedEvents()
		{

		}
		boost::unordered_map<std::string, int>& InventoryComponent::GetItems()
		{
			return ItemCount;
		}

		std::map<std::string, int> InventoryComponent::GetItemsCopy() const
		{
			std::map<std::string, int> cp;
			for (auto it = ItemCount.begin(); it != ItemCount.end(); ++it)
			{
				cp[it->first] = it->second;
			}
			return cp;
		}

		/*void InventoryComponent::SetItemDatabase(ItemDatabase* db)
		{
			ItemDB = db;
		}*/
	}
}

