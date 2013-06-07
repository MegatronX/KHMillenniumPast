#pragma once
#ifndef _STATUSEFFECTSMANAGER_H_
#define _STATUSEFFECTSMANAGER_H_

#include <boost/unordered_map.hpp>
#include "StatusEffect.h"
#include <components/Component.h>
#include "StatusEffectsLibrary.h"

#include <boost/function.hpp>

#define DEFAULT_TURNS 100000

namespace Game
{
	class Entity;
	class GameInstance;
	
	namespace StatusEffects
	{
		const std::string ApplyEffectIndexer = "ApplyEffectComponent";
		class StatusEffectManager;
		typedef boost::function<void (StatusEffectsManager* mng, const std::string& seName, const bool Removed)> StatusEffectChangedEvent;
		class StatusEffectsManager : public Components::Component
		{
		public:
			StatusEffectsManager(Entity* owner);
			
			void AddStatusEffect(StatusEffect* se, const int turns);
			void AddStatusEffect(se_ptr se, int turns);
			void AddStatusEffect(const std::string& effectName, int turns);
			
			bool RemoveStatusEffect(const std::string& name);
			void RemoveStatusEffects(const int count, bool AtRandom = true);
			void RemoveNegativeStatusEffects(const int count, bool AtRandom = true);
			void RemovePositiveStatusEffects(const int count, bool AtRandom = true);

			se_ptr GetStatusEffect(const std::string& name) const;
			std::vector<StatusEffect*>& GetStatusEffectsWithCallCondition(const CallCondition cc, bool sort);
			std::vector<StatusEffect*>& GetStatusEffectsWithPriority(const int priority);
			
			std::vector<StatusEffect*> GetStatusEffectsWithComponent(const std::string& compName, bool SortByPriority = false) const;
			std::vector<StatusEffect*> GetPositiveStatusEffects(bool SortByPriority = false) const;
			std::vector<StatusEffect*> GetNegativeStatusEffects(bool SortByPriority = false) const;
			void HandleCharacterTicked(int ticks);
			void HandleTimeElapsed(const int time);

			float GetStatusResistance(const std::string& name) const;
			float GetStatusResistance(const StatusEffect* effect) const;
			float GetStatusResistance(se_ptr effect) const;

			void IncrementStatusResistance(const std::string& name, const float inc);
			void IncrementStatusResistance(const StatusEffect* effect, const float inc);
			void IncrementStatusResistance(se_ptr effect, const float inc);

			float GetBaseResistance() const;
			void SetBaseResistance(const float res);
			void IncrementBaseResistance(const float res);

			void AddStatusEffectChangedHandler(const std::string& index, const StatusEffectChangedEvent& handler);
			bool RemoveStatusEffectChangedHandler(const std::string& name);
			void DispatchStatusEffectChangeEvent(const std::string& name, bool removed = true);
			
			const boost::unordered_map<std::string, se_ptr>& GetActiveStatusEffects() const
			{
				return NameToSE;
			}
			virtual RawClonePtr RawClone() const override;

			static void SortStatusEffectsByPriority(std::vector<StatusEffect*>& effects);
			static void SortStatusEffectsByPriority(std::vector<se_ptr>& effects);
		private:
			
			boost::unordered_map<std::string, se_ptr> NameToSE;
			boost::unordered_map<CallCondition, std::vector<StatusEffect*> > CallConditionToSE;
			boost::unordered_map<int, std::vector<StatusEffect*> > PriorityToSE;
			boost::unordered_set<std::string> LockedInStatusEffects;
			boost::unordered_map<std::string, float> SEResistances;

			boost::unordered_map<std::string, StatusEffectChangedEvent> StatusEffectChangedEvents;

			static StatusEffectsLibrary* SELibrary;
			float BaseResistance;
			friend class GameInstance;
		};
	}
}

#endif