#pragma once
#ifndef _ATKDEFSTATCOMPONENT_H_
#define _ATKDEFSTATCOMPONENT_H_

#include <components/Component.h>
#include <actions/Attack.h>
#include <battle/mechanics/Mechanics.h>
namespace Game
{
	namespace Battle
	{
		class AtkDefStatComponent : public Components::Component
		{
		public:
			AtkDefStatComponent(Entity* owner) : Components::Component(owner, owner != nullptr ? owner->GetName() + "AtkDefStatComponent" : "NoOwnerAtkDefStatComponent", "AtkDefStatComponent")
			{

			}

			virtual int GetAttackerStat(Actions::Action& action, Character::BaseCharacter& target, Mechanics& mechanics)
			{
				int retVal = 0;
				if (action.Users.GroupSize() > 1)
				{
					for (auto it = action.Users.GetGroup().begin(); it != action.Users.GetGroup().end(); ++it)
					{
						retVal += ExtractAttackerStat(action, *it->second.AttachedCharacter);
					}
					retVal /= action.Users.GroupSize();
				}
				return retVal;
				
			}

			virtual int ExtractAttackerStat(Actions::Action& action, Character::BaseCharacter& atker)
			{
				auto sm = atker.GetComponentAs<Character::StatsManager*>("StatsManager");
				auto atk = dynamic_cast<Actions::Attack*>(&action);
				if (atk != nullptr)
				{
					return static_cast<int>(atk->GetPhysicalWeight() * static_cast<float>(sm->GetBattleStat(Character::Stat::Strength)) + atk->GetMagicWeight() * static_cast<float>(sm->GetBattleStat(Character::Stat::Magic)));
				}
				return sm->GetBattleStat(Character::Stat::Strength);
			}

			virtual int GetDefenderStat(Actions::Action& action, Character::BaseCharacter& target, Mechanics& mechanics)
			{
				return ExtractDefenderStat(action, target);
			}

			virtual int ExtractDefenderStat(Actions::Action& action, Character::BaseCharacter& defender)
			{
				auto sm = defender.GetComponentAs<Character::StatsManager*>("StatsManager");
				auto atk = dynamic_cast<Actions::Attack*>(&action);
				if (atk != nullptr)
				{
					return static_cast<int>(atk->GetPhysicalWeight() * static_cast<float>(sm->GetBattleStat(Character::Stat::Vitality)) + atk->GetMagicWeight() * static_cast<float>(sm->GetBattleStat(Character::Stat::Spirit)));
				}
				return sm->GetBattleStat(Character::Stat::Vitality);
			}

			AtkDefStatComponent::RawClonePtr RawClone() const override
			{
				return new AtkDefStatComponent(*this);
			}

			virtual ~AtkDefStatComponent()
			{

			}
		private:
		};
	}
}

#endif