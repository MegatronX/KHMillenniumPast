#pragma once
#ifndef _CONSUMABLECOMPONENT_H_
#define _CONSUMABLECOMPONENT_H_

#include <components/Component.h>
#include <Entity.h>
#include <character/BaseCharacter.h>

namespace Game
{
	namespace Battle
	{
		class BattleField;
	}
	namespace Items
	{
		class ConsumableComponent : public Components::Component
		{
		public:
			ConsumableComponent(Entity* owner);
			virtual void Consume(Character::BaseCharacter& character);
			virtual void BattleConsume(Character::BaseCharacter& character, Battle::BattleField& battlefield);
			virtual RawClonePtr RawClone() const override;
		};
	}
}

#endif