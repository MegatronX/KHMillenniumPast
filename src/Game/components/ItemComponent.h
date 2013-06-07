#pragma once
#ifndef _ITEMCOMPONENT_H_
#define _ITEMCOMPONENT_H_

#include <items/Item.h>
#include <components/Component.h>
namespace Game
{
	namespace Components 
	{
		class ItemComponent : public Component
		{
		public:
			ItemComponent(Items::Item* item, const std::string& name, const int compType);
			Items::Item* GetHoldingItem() const;
		protected:
			virtual void SetHoldingItem(Items::Item* item);
		private:
			Items::Item* HoldingItem;
		};
	}
}
#endif