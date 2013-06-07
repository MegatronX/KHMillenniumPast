#pragma once

#include <Entity.h>
#include <components/Component.h>
#include <actions/Action.h>
#include <character/BaseCharacter.h>
#include <battle/mechanics/Mechanics.h>

namespace Game
{
	namespace Battle
	{
		class CriticalHitComponent : public Components::Component
		{
		public:
			CriticalHitComponent(Entity* entity) : Component(entity, entity != nullptr ? entity->GetName() + "CriticalComponent" : "NoOwnerCriticalComponent", "CriticalComponent")
			{

			}

			virtual bool IsCritical(Character::BaseCharacter& target, Actions::Action& action, Mechanics& mechanics)
			{
				return mechanics.ApplyCriticalFormula(target, action);
			}

			CriticalHitComponent::RawClonePtr RawClone() const override
			{
				return new CriticalHitComponent(*this);
			}
		};
	}
}