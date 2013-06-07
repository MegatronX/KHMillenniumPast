#include "Item.h"

namespace Game
{
	namespace Items
	{
		Item::Item()
		{

		}
		Item::Item(const Item& ref) : Entity(ref.GetName(), ref.GetType())
		{
			//if (ref.ItemHealingComponent != nullptr)
			//	ItemHealingComponent = static_cast<Components::HealingComponent*>(ref.ItemHealingComponent->Clone());
			ComponentCollection.rehash(ref.ComponentCollection.size());
			for (auto it = ref.ComponentCollection.begin(); it != ref.ComponentCollection.end(); ++it)
			{
				ComponentCollection[it->first] = it->second->Clone();
			}
		}
		Item::Item(const std::string& itemName) : Entity(itemName, EntityTypes::ItemEntity)
		{

		}
		Components::Component* Item::GetComponent(const std::string index)
		{
			//need to fillin
			/*if (index == "HealingComponent")
				return HealingUseComponent;
			else if (index == "ThrowComponent")
				return ThrowUseComponent;*/
			auto it = ComponentCollection.find(index);
			if (it != ComponentCollection.end())
				return it->second;
			return nullptr;
		}
		void Item::RegisterComponent(const std::string& indexName, Components::Component* component)
		{
			auto it = ComponentCollection.find(indexName);
			if (it != ComponentCollection.end())
				delete it->second;
			ComponentCollection[indexName] = component;//->Clone();
		}
		Item::ClonePtr Item::Clone() const
		{
			return new Item(*this);
		}
		Item::~Item()
		{
			for (auto it = ComponentCollection.begin(); it != ComponentCollection.end(); ++it)
			{
				delete it->second;
			}
			//delete ItemHealingComponent;
		}
		Item& Item::operator=(const Item& ref)
		{
			if (this != &ref)
			{
				/*delete ItemHealingComponent;
				
				if (ref.ItemHealingComponent != nullptr)
					ItemHealingComponent = static_cast<Components::HealingComponent*>(ref.ItemHealingComponent->Clone());
				*/
				//Allocate
				for (auto it = ComponentCollection.begin(); it != ComponentCollection.end(); ++it)
				{
					delete it->second;
				}
				ComponentCollection.rehash(ref.ComponentCollection.size());
				for (auto it = ref.ComponentCollection.begin(); it != ref.ComponentCollection.end(); ++it)
				{
					ComponentCollection[it->first] = it->second->Clone();
				}
			}
			return *this;
			
		}
	}
}