#pragma once

#include <components/Component.h>
#include <actions/Action.h>
#include <character/BaseCharacter.h>
#include <battle/mechanics/Mechanics.h>
namespace Game
{
	namespace Battle
	{
		class DamageCalculationComponent : public Components::Component
		{
		public:
			DamageCalculationComponent(Entity* Owner) : Component(Owner, Owner != nullptr ? Owner->GetName() + "DamageCalculationComponent" : "NoOwnerDamageCalculationComponent", "DamageCalculationComponent")
			{
			}

			virtual int CalculateDamage(Actions::Action& action, Character::BaseCharacter& target, Mechanics& mechanics)
			{
				return 0;
			}

			virtual DamageCalculationComponent::RawClonePtr RawClone() const
			{
				return new DamageCalculationComponent(*this);
			}

			virtual ~DamageCalculationComponent()
			{

			}
		};
	}
}