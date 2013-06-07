#pragma once
#ifndef _ATTACKTARGETS_H_
#define _ATTACKTARGETS_H_
#include <string>
#include <vector>
#include <Components/Component.h>
namespace Game
{
	namespace Character
	{
		class BaseCharacter;
	}
	namespace Actions
	{
		class Attack;
		struct AttackTarget
		{
			std::string characterName;
			Character::BaseCharacter* character;
			boost::shared_ptr<Attack> attack;

		};
		class AttackTargetsComponent : public Components::Component
		{
		public:
			AttackTargetsComponent(Attack* referenceAtk);

			void PushAttackToTargets();
			AttackTarget& GetTarget(const std::string& characterName);
		protected:
			std::vector<AttackTarget> Targets;
			Attack* refAtk;
		};
	}
}

#endif