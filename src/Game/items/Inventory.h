#pragma once
#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <boost/unordered_map.hpp>
#include <boost/function.hpp>

#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>

#include <items/ItemDatabase.h>
#include <items/Item.h>
namespace Game
{
	namespace Items
	{
		typedef boost::signals2::signal<void (const Item*, int, int)> ItemAddedSignal;
		typedef boost::signals2::signal<void (const Item*, int, int)> ItemRemovedSignal;

		typedef boost::function<void (const Item*, int, int)> ItemAddedHandler;
		typedef boost::function<void (const Item*, int, int)> ItemRemovedHandler;

		const std::string InventoryComponentIndex = "InventoryComponent";

		class InventoryComponent : public Components::Component
		{
		public:
			InventoryComponent(Entity* owner);

			bool AddItem(boost::shared_ptr<Entity>& item, const int count = 1);
			bool AddItem(Item* item, const int count = 1);
			bool AddItem(Item& item, const int count = 1);
			bool AddItem(int itemID, const int count = 1);
			bool AddItem(const std::string& itemname, const int count = 1);

			bool AddKeyItem(boost::shared_ptr<Entity>& item, const int count = 1);
			bool AddKeyItem(Item* item, const int count = 1);
			bool AddKeyItem(Item& item, const int count = 1);
			bool AddKeyItem(int itemID, const int count = 1);
			bool AddKeyItem(const std::string& itemname, const int count = 1);

			int GetItemCount(const std::string& itemName);
			int GetItemCount(const int itemID);

			void AddItemAddedEventHandler(const std::string& name, const ItemAddedHandler& handler);
			bool RemoveItemAddedEventHandler(const std::string& name);
			void DispatchItemAddedEvents();

			void AddItemRemovedEventHandler(const std::string& name, const ItemAddedHandler& handler);
			bool RemoveItemRemovedEventHandler(const std::string& name);
			void DispatchItemRemovedEvents();

			boost::unordered_map<std::string, int>& GetItems();

			std::map<std::string, int> GetItemsCopy() const;
			//static void SetItemDatabase(ItemDatabase* db);
		private:
			boost::unordered_map<std::string, ItemAddedHandler> ItemAddEvents;
			boost::unordered_map<std::string, ItemRemovedHandler> ItemRemovedEvents;
			boost::unordered_map<std::string, int> ItemCount;
			boost::unordered_map<std::string, int> KeyItemCount;
			boost::unordered_set<std::string> KeyItemList;
			//ItemAddedSignal ItemAddedEvents;
			//ItemRemovedSignal ItemRemovedEvents;
			//static ItemDatabase* ItemDB;
		};
	}
}

#endif