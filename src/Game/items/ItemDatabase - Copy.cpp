#include "ItemDatabase.h"

namespace Game
{
	namespace Items
	{
		static std::vector<Components::Component*> test;
		void ItemDatabase::AddItem(boost::shared_ptr<Item> item)
		{
			if (item.get() != nullptr)
			{
				IDToItemMap[item->GetID()] = item;
				NameToItemMap[item->GetName()] = item;
				auto healComp = item->GetComponent("Healing Component");
				if (healComp != nullptr)
				{
					test.push_back(healComp);
					int x = 10;
				}
			}
		}
		boost::shared_ptr<Item> ItemDatabase::GetItem(const std::string& name)
		{
			auto it = NameToItemMap.find(name);
			if (it != NameToItemMap.end())
			{
				auto healComp = it->second->GetComponent("Healing Component");
				if (healComp != nullptr)
				{
					int x = 10;
				}
				return it->second;
				
			}
			return boost::shared_ptr<Item>(new Item("Default Item"));
		}
	}
}