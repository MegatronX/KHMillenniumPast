#pragma once
#ifndef _ITEMDB_H_
#define _ITEMDB_H_
#include <string>
#include <items/Item.h>
#include <boost/shared_ptr.hpp>
namespace Game
{
	namespace Items
	{
		class ItemDatabase
		{
		public:
			//ItemDatabase();
			void AddItem(boost::shared_ptr<Item> item);
			boost::shared_ptr<Item> GetItem(const std::string& name);
		private:
			boost::unordered_map<std::string, boost::shared_ptr<Item>> NameToItemMap;
			boost::unordered_map<int, boost::shared_ptr<Item>> IDToItemMap;
			friend class Inventory;
		};
	}
}

#endif