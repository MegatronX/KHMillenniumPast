#include "Item.h"

namespace Game
{
	namespace Items
	{
		Items::ItemDatabase* Item::ItemDB = nullptr;
		Item::Item()
		{

		}
		Item::Item(const std::string& itemName) : Entity(itemName, EntityTypes::ItemEntity)
		{

		}
		/*Item::Item(const Item& ref) : Entity(ref)
		{
			//if (ref.ItemHealingComponent != nullptr)
			//	ItemHealingComponent = static_cast<Components::HealingComponent*>(ref.ItemHealingComponent->Clone());
			
		}*/

		Item::Item(const std::string& itemName, const std::string& description, const unsigned int itemValue) : Entity(itemName, EntityTypes::ItemEntity), Description(description), BaseMunnyValue(itemValue)
		{

		}

		Item::RawClonePtr Item::RawClone() const
		{
			return new Item(*this);
		}
		/*Item::ClonePtr Item::Clone() const
		{
			return Item::ClonePtr(new Item(*this));
		}*/
		Item::~Item()
		{
			/*for (auto it = ComponentCollection.begin(); it != ComponentCollection.end(); ++it)
			{
				delete it->second;
			}*/
			//delete ItemHealingComponent;
		}
		int Item::GetValue() const
		{
			return BaseMunnyValue;
		}
		const std::string& Item::GetDescription() const
		{
			return Description;
		}
		/*Item& Item::operator=(const Item& ref)
		{
			if (this != &ref)
			{
				//Allocate
				ComponentCollection.clear();
				ComponentCollection.rehash(ref.ComponentCollection.size());
				for (auto it = ref.ComponentCollection.begin(); it != ref.ComponentCollection.end(); ++it)
				{
					ComponentCollection[it->first] = it->second->SmartClone();
				}
			}
			return *this;
			
		}*/
	}
}