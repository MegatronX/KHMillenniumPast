#pragma once
#ifndef _HITCOMPONENT_H_
#define _HITCOMPONENT_H_

#include <Entity.h>
#include <components/Component.h>
#include <actions/Action.h>
#include <character/BaseCharacter.h>
#include <battle/mechanics/Mechanics.h>

namespace Game
{
	namespace Battle
	{
		class HitComponent :public Components::Component
		{
		public:
			HitComponent(Entity* entity) : Component(entity, entity != nullptr ? entity->GetName() + "HitComponent" : "NoOwnerHitComponent", "HitComponent")
			{

			}

			virtual bool IsHit(Character::BaseCharacter& target, Actions::Action& action, Mechanics& mechanics)
			{
				return mechanics.ApplyHitFormula(target, action);
			}

			HitComponent::RawClonePtr RawClone() const
			{
				return new HitComponent(*this);
			}
		};
	}
}

#endif