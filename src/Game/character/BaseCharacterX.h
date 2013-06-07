#pragma once
#ifndef _CHARACTERCLASS_H_
#define _CHARACTERCLASS_H_
#include <string>
#include <boost/function.hpp>
#include <boost/signal.hpp>
#include <boost/signals.hpp>
#include <boost/bind.hpp>
#include <boost/unordered_map.hpp>
#include <character/Stats.h>
#include <components/StatsComponent.h>
#include <deque>
#include <statuseffects/StatusEffect.h>
namespace Game
{
	const int StatusCount = 2;
	enum CharacterStatus
	{
		Normal,
		Preview
	};
	namespace Character
	{
		typedef std::pair<Components::StatComponent*, boost::signals::connection> ComponentConnection;
		typedef std::pair<bool, ComponentConnection> HeldComponent;
		class BaseCharacter : public Entity, public boost::signals::trackable
		{
		public:
			BaseCharacter();
			BaseCharacter(const std::string& Name, const int ID);
			BaseCharacter(const std::string& Name, const int ID, Components::StatComponent& statComp);
			BaseCharacter(const std::string& Name, const int ID, int InitialStats[StatCount]);
			//BaseCharacter(const std::string& Name, const int ID, StatComponent& statComp);
			//const std::string& GetName() const;
			CharacterStatus GetStatus() const;
			void SetCharacterStatus(CharacterStatus charStatus);
			int GetUID() const;
			int GetLevel() const;
			virtual void SyncCombinedStat(Stat stat);
			void SyncCombinedStats();
			virtual void SyncActualToPreview(Stat stat);
			virtual void SyncActualToPreview();

			bool AddStatComponent(const std::string& name, Components::StatComponent* component, const CharacterStatus status = CharacterStatus::Normal, const bool manage = true, const bool replaceExisting = true);
			bool RemoveStatComponent(const std::string& name, const CharacterStatus status = CharacterStatus::Normal);
			//Stat Accessors
			int GetCombinedStat(Stat stat) const;
			bool operator==(const BaseCharacter& character) const;
			bool operator!=(const BaseCharacter& character) const;

			virtual ~BaseCharacter();

			virtual void HandleNormalStatsModifiedEvent(const std::string& compName, Components::StatComponent*, Stat stat, int oldVal, int newVal);
			virtual void HandlePreviewStatsModifiedEvent(const std::string& compName, Components::StatComponent*, Stat stat, int oldVal, int newVal);
		protected:
			std::deque<boost::shared_ptr<StatusEffects::StatusEffect> > ActiveStatusEffects;
			Components::StatComponent BaseStats[StatusCount];
			Components::StatComponent CombinedStats[StatusCount];
			Components::StatComponent BattleStats[StatusCount];
			int CurrentHP[StatusCount];
			int CurrentMP[StatusCount];
			int CurrentSP[StatusCount];
			//string = component indexer, pair bool = character managed, StatComponent = extra stat component
			//boost::unordered_map<std::string, HeldComponent > AdditionalStatComponents[StatusCount];
		private:
			bool SyncingStats;
			CharacterStatus Status;
			//std::string Name;
			int CharacterID;
			int Level;
		};
	}
}

#endif