#pragma once
#ifndef _ITEM_H_
#define _ITEM_H_
#include <Entity.h>
#include <components/UseComponent.h>
#include <boost/unordered_map.hpp>
#include <Utilities/Cloneable.h>
namespace Game
{
	namespace Items
	{
		class Item : public Cloneable<Item>, public Entity
		{
		public:
			Item();
			Item(const Item& ref);
			Item(const std::string& itemName);
			Components::Component* GetComponent(const std::string index);
			
			void RegisterComponent(const std::string& indexName, Components::Component* component);

			//Components::UseComponent* HealingUseComponent;
			//Components::UseComponent* ThrowUseComponent;

			virtual ClonePtr Clone() const override;

			virtual ~Item();

			Item& operator=(const Item& base);
		protected:
			//Components::HealingComponent* ItemHealingComponent;
		private:
			boost::unordered_map<std::string, Components::Component*> ComponentCollection;
		};
	}
}

#endif