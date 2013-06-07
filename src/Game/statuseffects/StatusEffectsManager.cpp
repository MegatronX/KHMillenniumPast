#include "StatusEffectsManager.h"
#include <Entity.h>
#include <algorithm>
#include <components/ApplyEffectComponent.h>
#include <character/BaseCharacter.h>
namespace Game
{
	namespace StatusEffects
	{
		StatusEffectsLibrary* StatusEffectsManager::SELibrary;
		StatusEffectsManager::StatusEffectsManager(Entity* owner) : Component(owner, "StatusEffectsManager" + owner->GetName(), "StatusEffectsManager"), BaseResistance(0.f)
		{

		}

		void StatusEffectsManager::AddStatusEffect(StatusEffect* se, const int turns)
		{
			AddStatusEffect(se_ptr(se), turns);
		}
		void StatusEffectsManager::AddStatusEffect(se_ptr se, int turns)
		{
			if (se.get() != nullptr)
			{
				if (turns == DEFAULT_TURNS)
				{
					turns = se->GetRecommendedTicks();
				}
				auto it = NameToSE.find(se->GetName());
				if (it != NameToSE.end())
				{
					if (se->IsRefreshable())
					{
						it->second->SetRemainingTicks(turns);
					}
				}
				else
				{
					se->SetRemainingTicks(turns);
					NameToSE[se->GetName()] = se;
					PriorityToSE[se->GetPriority()].push_back(se.get());
					for (auto cc = se->CallConditions.begin(); cc != se->CallConditions.end(); ++cc)
					{
						CallConditionToSE[*cc].push_back(se.get());
					}
					se->SetRemainingTicks(turns);
					auto character = dynamic_cast<Character::BaseCharacter*>(this->GetOwner());
					if (character != nullptr)
					{
						se->SetHolder(character);
						auto applyEff = se->GetComponentAs<Components::ApplyEffectComponent*>(ApplyEffectIndexer);
						if (applyEff != nullptr)
						{
							applyEff->Apply(character);
						}
					}
					DispatchStatusEffectChangeEvent(se->GetName(), false);
				}
				//auto appComp = 
			}
		}
		void StatusEffectsManager::AddStatusEffect(const std::string& effectName, int turns)
		{
			AddStatusEffect(SELibrary->GetStatusEffectClone(effectName), turns);
		}

		bool StatusEffectsManager::RemoveStatusEffect(const std::string& name)
		{
			bool removed = false;
			auto it = NameToSE.find(name);
			if (it != NameToSE.end())
			{
				auto character = dynamic_cast<Character::BaseCharacter*>(this->GetOwner());
				if (character != nullptr)
				{
					auto applyEff = it->second->GetComponentAs<Components::ApplyEffectComponent*>(ApplyEffectIndexer);
					if (applyEff != nullptr)
					{
						applyEff->UnApply(character);
					}
				}
				DispatchStatusEffectChangeEvent(name, true);
			}
			return removed;
		}
		void StatusEffectsManager::RemoveStatusEffects(const int count, bool AtRandom)
		{

		}
		void StatusEffectsManager::RemoveNegativeStatusEffects(const int count, bool AtRandom)
		{

		}
		void StatusEffectsManager::RemovePositiveStatusEffects(const int count, bool AtRandom)
		{

		}



		se_ptr StatusEffectsManager::GetStatusEffect(const std::string& name) const
		{
			return se_ptr();
		}
		std::vector<StatusEffect*> EmptySE;
		std::vector<StatusEffect*>& StatusEffectsManager::GetStatusEffectsWithCallCondition(const CallCondition cc, bool sort)
		{
			auto it = CallConditionToSE.find(cc);
			if (it != CallConditionToSE.end())
			{
				return (it->second);
			}
			else
			{
				return EmptySE;
			}
		}
		
		std::vector<StatusEffect*>& StatusEffectsManager::GetStatusEffectsWithPriority(const int priority)
		{
			auto it = PriorityToSE.find(priority);
			if (it != PriorityToSE.end())
			{
				return (it->second);
			}
			else
			{
				return EmptySE;
			}
		}

		std::vector<StatusEffect*> StatusEffectsManager::GetStatusEffectsWithComponent(const std::string& compName, bool SortByPriority) const
		{
			std::vector<StatusEffect*> matches;
			for (auto it = NameToSE.begin(); it != NameToSE.end(); ++it)
			{
			}
			if (SortByPriority && matches.size() > 1)
			{
				SortStatusEffectsByPriority(matches);
			}
			return matches;
		}
		std::vector<StatusEffect*> StatusEffectsManager::GetPositiveStatusEffects(bool SortByPriority) const
		{
			std::vector<StatusEffect*> matches;
			for (auto it = NameToSE.begin(); it != NameToSE.end(); ++it)
			{
				if (it->second->IsPositive())
				{
					matches.push_back(it->second.get());
				}
			}
			if (SortByPriority && matches.size() > 1)
			{
				SortStatusEffectsByPriority(matches);
			}
			return matches;
		}
		std::vector<StatusEffect*> StatusEffectsManager::GetNegativeStatusEffects(bool SortByPriority) const
		{
			std::vector<StatusEffect*> matches;
			for (auto it = NameToSE.begin(); it != NameToSE.end(); ++it)
			{
				if (!(it->second->IsPositive()))
				{
					matches.push_back(it->second.get());
				}
			}
			if (SortByPriority && matches.size() > 1)
			{
				SortStatusEffectsByPriority(matches);
			}
			return matches;
		}
		void StatusEffectsManager::HandleCharacterTicked(int ticks)
		{

		}
		void StatusEffectsManager::HandleTimeElapsed(const int time)
		{

		}

		float StatusEffectsManager::GetStatusResistance(const std::string& name) const
		{
			auto it = SEResistances.find(name);
			if (it != SEResistances.end())
				return it->second + BaseResistance;
			return 0.f;
		}
		float StatusEffectsManager::GetStatusResistance(const StatusEffect* effect) const
		{
			if (effect != nullptr)
				return GetStatusResistance(effect->GetName());
			return 0.f;
		}
		float StatusEffectsManager::GetStatusResistance(se_ptr effect) const
		{
			if (effect.get() != nullptr)
				return GetStatusResistance(effect->GetName());
			return 0.f;
		}

		void StatusEffectsManager::IncrementStatusResistance(const std::string& name, const float inc)
		{
			auto it = SEResistances.find(name);
			if (it != SEResistances.end())
			{
				it->second += inc;
			}
			else
			{
				SEResistances[name] = inc;
			}
		}
		void StatusEffectsManager::IncrementStatusResistance(const StatusEffect* effect, const float inc)
		{
			if (effect != nullptr)
				IncrementStatusResistance(effect->GetName(), inc);
		}
		void StatusEffectsManager::IncrementStatusResistance(se_ptr effect, const float inc)
		{
			if (effect.get() != nullptr)
				IncrementStatusResistance(effect->GetName(), inc);
		}

		float StatusEffectsManager::GetBaseResistance() const
		{
			return BaseResistance;
		}
		void StatusEffectsManager::SetBaseResistance(const float res)
		{
			BaseResistance = res;
		}

		void StatusEffectsManager::IncrementBaseResistance(const float res)
		{
			BaseResistance += res;
		}

		void StatusEffectsManager::AddStatusEffectChangedHandler(const std::string& index, const StatusEffectChangedEvent& handler)
		{
			StatusEffectChangedEvents[index] = handler;
		}
		bool StatusEffectsManager::RemoveStatusEffectChangedHandler(const std::string& name)
		{
			auto it = StatusEffectChangedEvents.find(name);
			if (it != StatusEffectChangedEvents.end())
			{
				StatusEffectChangedEvents.erase(it);
				return true;
			}
			return false;
		}
		void StatusEffectsManager::DispatchStatusEffectChangeEvent(const std::string& name, bool removed)
		{
			for (auto ev = StatusEffectChangedEvents.begin(); ev != StatusEffectChangedEvents.end(); ++ev)
			{
				ev->second(this, name, removed);
			}
		}

		StatusEffectsManager::RawClonePtr StatusEffectsManager::RawClone() const
		{
			return new StatusEffectsManager(*this);
		}

		void StatusEffectsManager::SortStatusEffectsByPriority(std::vector<StatusEffect*>& effects)
		{
			std::sort(effects.begin(), effects.end(), [](const StatusEffect* se1, const StatusEffect* se2){ return se1->GetPriority() < se2->GetPriority();});
		}

		void StatusEffectsManager::SortStatusEffectsByPriority(std::vector<se_ptr>& effects)
		{
			std::sort(effects.begin(), effects.end(), [](const se_ptr se1, const se_ptr se2){ return se1->GetPriority() < se2->GetPriority();});
		}
	}
}