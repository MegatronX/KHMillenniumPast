#pragma once
#ifndef _DAMAGECALCULATORCOMPONENT_H_
#define _DAMAGECALCULATORCOMPONENT_H_

#include <components/Component.h>
#include <battle/mechanics/Mechanics.h>
#include <actions/Attack.h>

class Entity;
namespace Game
{
	namespace Character
	{
		class BaseCharacter;
	}
	namespace Battle
	{

		class DamageCalculatorComponent : public Components::Component
		{
		public:
			DamageCalculatorComponent(Entity* owner) : Components::Component(owner, owner->GetName() + "DamageCalculatorComponent", "DamageCalculatorComponent")
			{

			}
			virtual int CalculateDamage(Actions::Action& action, Character::BaseCharacter& target, Mechanics& mechanics)
			{
				//return mechanics.CalculateDamage(action, target);
				return 100;
			}

		};
	}
}

#endif