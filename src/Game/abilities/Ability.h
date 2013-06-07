#pragma once
#ifndef _ABILITY_H_
#define _ABILITY_H_
#include <statuseffects/StatusEffect.h>
namespace Game
{
	namespace Abilities
	{
		class AbilityManager;
		
		class Ability : public StatusEffects::StatusEffect
		{
		public:
			Ability(Character::BaseCharacter* owner, const std::string& name, int priority);
			virtual RawClonePtr RawClone() const override;
			int GetAPCost() const;

			int GetInstances() const;
			int GetLevel() const;

			virtual ~Ability();
		private:
			int APCost;
			int Instances;
			int RequiredXP;
			int Level;
			friend class AbilityManager;
			//static boost::unordered_map<std::string, boost::unordered_map<std::string, int> > APCostOverrides;
			//static boost::unordered_map<std::string, boost::unordered_map<std::string, int> > RequiredXPOverrides;
		};

		typedef boost::shared_ptr<Ability> abil_ptr;
	}
}

#endif