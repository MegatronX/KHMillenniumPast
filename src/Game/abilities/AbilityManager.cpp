#include "AbilityManager.h"
#include <Entity.h>
namespace Game
{
	namespace Abilities
	{
//		boost::unordered_map<std::string, boost::unordered_map<std::string, int> > Ability::APCostOverrides; // = boost::unordered_map<std::string, boost::unordered_map<std::string, int> >();
	//	boost::unordered_map<std::string, boost::unordered_map<std::string, int> > Ability::RequiredXPOverrides;

		AbilityLibrary* AbilityManager::abilLib;


		boost::unordered_map<std::string, boost::unordered_map<std::string, int> > AbilityManager::APCostOverrides;
		boost::unordered_map<std::string, boost::unordered_map<std::string, int> > AbilityManager::RequiredXPOverrides;
		boost::unordered_map<std::string, boost::unordered_map<std::string, boost::unordered_map<int, int> > > AbilityManager::AbilityLvExpOverrides;

		std::vector<Ability*> EmptyAbilSet;
		AbilityManager::AbilityManager()
		{

		}
		AbilityManager::AbilityManager(Entity* owner) : Component(owner, "AbilityManger" + owner->GetName(), "AbilityManager")
		{

		}

		std::vector<Ability*>& AbilityManager::GetAbilitiesWithCallCondition(const CallCondition cc, bool sortByPriority) const
		{
			return EmptyAbilSet;
		}
		std::vector<Ability*>& AbilityManager::GetAbilitiesWithPriority(const int priority) const
		{
			return EmptyAbilSet;
		}

		std::vector<Ability*> AbilityManager::GetAbilitiesWithComponent(const std::string& compName, bool SortByPriority) const
		{
			return EmptyAbilSet;
		}
		std::vector<Ability*> AbilityManager::GetPositiveStatusEffects(bool SortByPriority) const
		{
			return EmptyAbilSet;
		}
		std::vector<Ability*> AbilityManager::GetNegativeStatusEffects(bool SortByPriority) const
		{
			return EmptyAbilSet;
		}
		
		bool AbilityManager::AddAbility(const std::string& AbilityName, int instances)
		{
			if (abilLib != nullptr)
			{
				auto abil = abilLib->GetAbility(AbilityName);
				if (abil != nullptr)
				{
					return AddAbility(boost::dynamic_pointer_cast<Ability>(abil->Clone()), instances);
				}
	#ifdef DEBUG
				else
				{
					std::cerr << "Ability " << AbilityName << " could not be found in database." << std::end;
				}
	#endif
			}
	#ifdef DEBUG
			else
			{
				std::cerr << "Ability Library is not set!" << std::endl;
			}
			return false;
	#endif
		}
		bool AbilityManager::AddAbility(const Ability* ability, int instances)
		{
			if (ability != nullptr)
			{
				return AddAbility(boost::dynamic_pointer_cast<Ability>(ability->Clone()), instances);
			}
			return false;
		}
		bool AbilityManager::AddAbility(abil_ptr ability, int instances)
		{
			bool Added = false;
			
			
			return Added;
		}
			
		bool AbilityManager::RemoveAbility(const std::string, int instances)
		{
			bool removed = false;

			return removed;
		}
		
		void AbilityManager::SetAbilityLibrary(AbilityLibrary* lib)
		{
			abilLib = lib;
		}
		void AbilityManager::SetAPCostOverride(const std::string& character, const std::string& ability, const int apOverride)
		{
			APCostOverrides[character][ability] = apOverride;
		}
		void AbilityManager::SetLevelOverride(const std::string& character, const std::string& ability, const int level, const int lvOverride)
		{
			AbilityLvExpOverrides[character][ability][level] = lvOverride;
		}
		void AbilityManager::SetRequiredExpOverrides(const std::string& character, const std::string& ability, const int Exp)
		{
			RequiredXPOverrides[character][ability] = Exp;
		}
		void AbilityManager::DistributeXP(const int XP)
		{
			if (AllowXP)
			{
				for (auto abil = UnlearnedAbilities.begin(); abil != UnlearnedAbilities.end(); ++abil)
				{
					if (abil->second.LearningInstances > 0 && abil->second.LearnRate > 0.001f)
					{
						int EffExp = static_cast<int>(abil->second.LearnRate * static_cast<float>(XP));
						if (EffExp > 0)
						{
							
						}
					}
				}
			}
		}

		AbilityManager::~AbilityManager()
		{

		}
	}
}