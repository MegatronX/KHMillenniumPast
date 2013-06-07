#include "ItemComponent.h"

namespace Game
{
	using namespace Items;
	namespace Components
	{
		ItemComponent::ItemComponent(Item* item, const std::string& name, const int compType) : HoldingItem(item), Component(item, name, compType)
		{

		}
		Items::Item* ItemComponent::GetHoldingItem() const
		{
			return HoldingItem;
		}
		void ItemComponent::SetHoldingItem(Items::Item* item)
		{
			HoldingItem = item;
		}
	}
}