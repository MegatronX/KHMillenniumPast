#pragma once
#ifndef _BASEMECHANICS_H_
#define _BASEMECHANICS_H_
#include "Mechanics.h"
#include <statuseffects/StatusEffectsManager.h>
#include <actions/ActionUserTarget.h>
#include <unordered_set>
namespace Game
{
	namespace Actions
	{
		class Action;
	}
	namespace Battle
	{
		class BaseMechanics : public Mechanics
		{
		public:
			BaseMechanics(BattleField* owner);
			virtual bool ApplyStatusEffect(Character::BaseCharacter& target, const std::string& se, int turns, float seApplyRate = 1.0f) override;
			virtual void ProcessAction(Actions::Action& action);

			virtual std::vector<StatusEffects::StatusEffect*> GetEffectsWithCallCondition(CallCondition cc, std::vector<Actions::ActionUserTarget>& characters, bool IncludeSE = true, bool IncludeAbil = true) override;
			virtual std::vector<StatusEffects::StatusEffect*> GetEffectsWithCallCondition(CallCondition cc, std::vector<Character::BaseCharacter*>& characters, bool IncludeSE = true, bool IncludeAbil = true) override;
			virtual std::vector<StatusEffects::StatusEffect*> GetEffectsWithCallCondition(CallCondition cc, boost::unordered_map<std::string, Actions::ActionUserTarget>& characters, bool IncludeSE = true, bool IncludeAbil = true) override;

			/*virtual bool IsHit(Character::BaseCharacter& target, Actions::Action& action) override;
			virtual bool IsCritical(Character::BaseCharacter& target, Actions::Action& action) override;*/
		};
	}
}


#endif