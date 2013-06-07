#pragma once
#ifndef _ITEMDB_H_
#define _ITEMDB_H_
#include <string>
#include <items/Item.h>
#include <boost/shared_ptr.hpp>
namespace Game
{
	class GameInstance;
	namespace Components
	{
		class CharacterEquipmentComponent;
	}
	namespace Items
	{
		class ItemDatabase
		{
		public:
			const Item* GetItemByName(const std::string& itemName) const;
			const Item* GetItemByID(const int ID) const;

			boost::shared_ptr<Item> GetItemCopyByName(const std::string& itemName) const;
			boost::shared_ptr<Item> GetItemCopyByID(const int ID) const;

			void AddItem(boost::shared_ptr<Item> item);
			
			unsigned int GetItemCount() const;
			//void AddItem(boost::shared_ptr<Entity> item);
		private:
			void EmptyDatabase();
			Item* GetBaseItemByName(const std::string& itemName) const;
			Item* GetBaseItemByID(const int ID) const;

			boost::unordered_map<std::string, boost::shared_ptr<Item> > NameToItemMap;
			boost::unordered_map<int, boost::shared_ptr<Item> > IDToItemMap;
			friend class Inventory;
			friend class Components::CharacterEquipmentComponent;
			friend class GameInstance;
		};
		class ItemDatabase_
		{
		public:
			//ItemDatabase();
			void AddItem(boost::shared_ptr<Entity> item);
			
			boost::shared_ptr<Entity> GetItem(const std::string& name);
		private:
			boost::unordered_map<std::string, boost::shared_ptr<Entity>> NameToItemMap;
			boost::unordered_map<int, boost::shared_ptr<Entity>> IDToItemMap;
			friend class Inventory;
		};
	}
}

#endif