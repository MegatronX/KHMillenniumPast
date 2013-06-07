#include "ItemDatabase.h"

namespace Game
{
	namespace Items
	{
		const Item* ItemDatabase::GetItemByName(const std::string& itemName) const
		{
			auto it = NameToItemMap.find(itemName);
			if (it != NameToItemMap.end())
			{
				return it->second.get();
			}
			return nullptr;
		}
		const Item* ItemDatabase::GetItemByID(const int ID) const
		{
			auto it = IDToItemMap.find(ID);
			if (it != IDToItemMap.end())
			{
				return it->second.get();
			}
			return nullptr;
		}

		boost::shared_ptr<Item> ItemDatabase::GetItemCopyByName(const std::string& itemName) const
		{
			auto it = NameToItemMap.find(itemName);
			if (it != NameToItemMap.end())
			{
				return boost::dynamic_pointer_cast<Item>(it->second->Clone());// boost::shared_ptr<Item>(static_cast<Item*>(it->second->RawClone()));
			}
			return boost::shared_ptr<Item>();
		}
		boost::shared_ptr<Item> ItemDatabase::GetItemCopyByID(const int ID) const
		{
			auto it = IDToItemMap.find(ID);
			if (it != IDToItemMap.end())
			{
				return boost::dynamic_pointer_cast<Item>(it->second->Clone());
			}
			return boost::shared_ptr<Item>();
		}
		void ItemDatabase::AddItem(boost::shared_ptr<Item> item)
		{
			if (item.get() != nullptr)
			{
				IDToItemMap[item->GetID()] = item;
				NameToItemMap[item->GetName()] = item;
				/*auto healComp = item->GetComponent("Healing Component");
				if (healComp != nullptr)
				{
					test.push_back(healComp);
					int x = 10;
				}*/
			}
		}
		unsigned int ItemDatabase::GetItemCount() const
		{
			return NameToItemMap.size();
		}
		void ItemDatabase::EmptyDatabase()
		{
			IDToItemMap.clear();
			NameToItemMap.clear();
		}

		//static std::vector<Components::Component*> test;
		void ItemDatabase_::AddItem(boost::shared_ptr<Entity> item)
		{
			if (item.get() != nullptr)
			{
				IDToItemMap[item->GetID()] = item;
				NameToItemMap[item->GetName()] = item;
				/*auto healComp = item->GetComponent("Healing Component");
				if (healComp != nullptr)
				{
					test.push_back(healComp);
					int x = 10;
				}*/
			}
		}
		boost::shared_ptr<Entity> ItemDatabase_::GetItem(const std::string& name)
		{
			auto it = NameToItemMap.find(name);
			if (it != NameToItemMap.end())
			{
				/*auto healComp = it->second->GetComponent("Healing Component");
				if (healComp != nullptr)
				{
					int x = 10;
				}*/
				return it->second;
				
			}
			return boost::shared_ptr<Entity>(new Entity("Default Item", EntityTypes::ItemEntity));
		}
	}
}