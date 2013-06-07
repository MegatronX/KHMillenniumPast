#pragma once
#ifndef _EQUIPCOMPONENT_H_
#define _EQUIPCOMPONENT_H_

#include <components/Component.h>
#include <Entity.h>
#include <character/BaseCharacter.h>
namespace Game
{
	namespace Items
	{
		const static std::string EquipComponentIndex = "EquipComponentIndex";
		class EquipComponent : public Components::Component
		{
		public:
			EquipComponent(Entity* owner) : Component(owner, owner != nullptr ? owner->GetName() + "EquipComponent" : "NoOwnerEquipComponent", "EquipComponent")
			{
			}

			virtual bool Equip(Character::BaseCharacter& character)
			{
				return false;
			}
			virtual bool UnEquip(Character::BaseCharacter& character)
			{
				return false;
			}
			EquipComponent::RawClonePtr RawClone() const override
			{
				return EquipComponent::RawClonePtr(new EquipComponent(*this));
			}
		protected:
		private:

		};
	}
}

#endif