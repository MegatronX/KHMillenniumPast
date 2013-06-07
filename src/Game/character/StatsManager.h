#pragma once
#ifndef _STATSMANAGER_H_
#define _STATSMANAGER_H_
#include <components/Component.h>
#include <components/StatsComponent.h>
#include <Entity.h>

#include <boost/signals2.hpp>
#include <boost/function.hpp>
namespace Game
{
	class GameInstance;
	namespace Character
	{
		class StatsManager;
		const static std::string StatManagerIndex = "StatsManager";
		typedef std::pair<bool, int> StatLimitBreaks;
		typedef boost::signals2::signal<void (const std::string& compName, Components::StatComponent<int>*, Character::Stat stat, int oldVal, int newVal)> StatChangedSignal;
		typedef boost::function<void (StatsManager& mng, const Character::Stat stat, const int oldVal, const int newVal)> StatChangeHandler;
		class StatsManager : public Components::Component
		{
		public:
			StatsManager(Entity* owner);
			StatsManager(Entity* owner, int baseStats[Character::StatCount]);
			StatsManager(Entity* owner, std::vector<int>& stats);
			StatsManager(Entity* owner, std::map<Stat, int>& stats);
			StatsManager(Entity* owner, boost::unordered_map<Stat, int>& stats);

			int GetBaseStat(const Stat stat, bool IgnoreLimits = false) const;
			int GetPermanentStatBoost(const Stat stat) const;
			float GetPermanentStatMultiplier(const Stat stat) const;

			int GetAbilityStatAdder(const Stat stat) const;
			float GetAbilityStatMultiplier(const Stat stat) const;

			void IncrementAbilityStatAdder(const Stat stat, const int inc, bool sync = true, bool dispatch = true);
			void IncrementAbilityStatMultiplier(const Stat stat, const float inc, bool sync = true, bool dispatch = true);

			int GetStatusEffectStatAdder(const Stat stat) const;
			float GetStatusEffectStatMultiplier(const Stat stat) const;

			void IncrementStatusEffectStatAdder(const Stat stat, const int inc, bool sync = true, bool dispatch = true);
			void IncrementStatusEffectStatMultiplier(const Stat stat, const float inc, bool sync = true, bool dispatch = true);

			int GetEquipmentStatAdder(const Stat stat) const;
			float GetEquipmentStatMultiplier(const Stat stat) const;

			void IncrementEquipmentStatAdder(const Stat stat, const int inc, bool sync = true, bool dispatch = true);
			void IncrementEquipmentStatMultiplier(const Stat stat, const float inc, bool sync = true, bool dispatch = true);

			int GetAdditionalStatAdder(const std::string& name, const Stat stat) const;
			float GetAdditionalStatMultiplier(const std::string& name, const Stat stat) const;

			void IncrementAdditionalStatAdder(const std::string& name, const Stat stat, const int inc, bool sync = true, bool dispatch = true);
			void IncrementAdditionalStatMultiplier(const std::string& name, const Stat stat, const float inc, bool sync = true, bool dispatch = true);

			int GetCombinedStat(const Stat stat, bool IgnoreLimits = false) const;

			int GetBattleStat(const Stat stat, bool IgnoreLimits = false) const;

			void IncrementStatBreak(const Stat stat, const int breaks, const int Level = 1, bool dispatch = true);

			void ClearStatAdders(const std::string& name, bool sync = true, bool dispatch = true);
			void ClearStatAdder(const std::string& name, const Stat stat, bool sync = true, bool dispatch = true);
			void ClearStatMultipliers(const std::string& name, bool sync = true, bool dispatch = true);
			void ClearStatMultiplier(const std::string& name, const Stat stat, bool sync = true, bool dispatch = true);
			//Volatile Stat
			int GetCurrentHP() const;
			void SetCurrentHP(const int hp, bool inBattle = false, bool dispatch = true);
			void IncrementCurrentHP(const int inc, bool inBattle = false, bool dispatch = true);

			int GetCurrentMP() const;
			void SetCurrentMP(const int mp, bool inBattle = false, bool dispatch = true);
			void IncrementCurrentMP(const int inc, bool inBattle = false, bool dispatch = false);

			int GetCurrentSP() const;
			void SetCurrentSP(const int sp, bool inBattle = false, bool dispatch = true);
			void IncrementCurrentSP(const int inc, bool inBattle = false, bool dispatch = false);

			//Sync Stat Functions
			void SyncStat(const Stat stat, bool dispatch = false);
			void SyncStat(const int index, bool dispatch = false);
			void SyncBattleStat(const Stat stat, bool SyncBase = false, bool dispatch = false);
			void SyncBattleStat(const int index, bool SyncBase = false, bool dispatch = false);
			void SyncAllStats(bool dispatch = false);
			void SyncAllBattleStats(bool SyncBase = false, bool dispatch = false);

			void RemapStat(const Character::Stat src, const Character::Stat dest, bool dispatch = false);
			void ClearRemapping(const Character::Stat st, bool dispatch = false);
			bool IsRemapped(const Character::Stat st) const;
			Character::Stat GetMappedStat(const Character::Stat st) const;
			void ClearRemappings();

			bool AddStatChangeHandler(const std::string& index, const StatChangeHandler& handler);
			bool RemoveStatChangeHandler(const std::string& index);
			void DispatchStatChangeEvents(const Stat stat, const int old, const int newVal);
		protected:
			
			bool LimitVolatileStat(const Character::Stat st, bool remap = true, bool inBattle = false);
			void SetBaseStat(const Stat stat, const int increment, bool sync = true);
			void SetPermanentStatBoost(const Stat stat, const int val, bool sync = true);
			void SetPermanentStatMultiplier(const Stat stat, const float val, bool sync = true);

			void IncrementBaseStat(const Stat stat, const int increment, bool sync = true);
			void IncrementPermanentStatBoost(const Stat stat, const int inc, bool sync = true);
			void IncrementPermanentStatMultiplier(const Stat stat, const float inc, bool sync = true);

			void AddAdditionalStatAdder(const std::string& adderIndex, Components::StatComponent<int>& comp);
			void AddAdditionalStatMultiplier(const std::string& multIndex, Components::StatComponent<float>& comp);
			bool RemoveStatAdder(const std::string& index);
			bool RemoveStatMultiplier(const std::string& index);

			std::array<boost::unordered_map<int, int>, StatCount> StatBreakCounts; //StatBreakCounts[stat][level] -> break count
			std::array<boost::unordered_map<int, int>, StatCount> StatLimits; //StatBreakCounts[stat][level] -> break count

			
			friend class ::Game::GameInstance;
			//boost::unordered_map<Character::Stat, boost::unordered_map<int, int> > StatBreakCounts; //StatBreakCounts[stat][level] -> break count
			//boost::unordered_map<Character::Stat, boost::unordered_map<int, int> > StatBreakLimits; //StatBreakLimits[stat][level] -> Stat Limit at level
		private:
			//Volatile Stats
			int CurrentHP;
			int CurrentMP;
			int CurrentSP;
			//Base Stat Set
			Components::StatComponent<int> BaseStats;
			Components::StatComponent<int> PermanentStatBoosts;
			Components::StatComponent<float> PermanentStatMultipliers;
			//Abilities
			Components::StatComponent<int> AbilityStatAdders;
			Components::StatComponent<float> AbilityStatMultipliers;
			//Equipment
			Components::StatComponent<int> EquipmentStatAdders;
			Components::StatComponent<float> EquipmentStatMultipliers;
			//Others
			boost::unordered_map<std::string, Components::StatComponent<int> > AdditionalStatsAdders;
			boost::unordered_map<std::string, Components::StatComponent<float> > AdditionalStatsMultipliers;
			//Combined
			Components::StatComponent<int> CombinedStats;
			//SE
			Components::StatComponent<int> SEStatAdders;
			Components::StatComponent<float> SEStatMultipliers;
			//Battle
			Components::StatComponent<int> BattleStatAdders;
			Components::StatComponent<float> BattleStatMultipliers;
			Components::StatComponent<int> BattleStats;
			/*Components::StatComponent<int, float> BaseStats;
			Components::StatComponent PermanentStatBoosts;
			Components::StatComponent AbilityStatBoosts;
			Components::StatComponent SEStatBoosts;
			Components::StatComponent CombinedStats;
			Components::StatComponent InBattleStats;
			
			Components::StatComponent PreviewStats;

			boost::unordered_map<std::string, Components::StatComponent> AdditionalStatsAdders;*/

			//boost::unordered_map<std::string, 

			//StatChangedSignal StatsChangeSignal;

			boost::unordered_map<std::string, StatChangeHandler> StatChangeSignals;

			StatLimitBreaks StatsBreaksL1[Character::StatCount];
			StatLimitBreaks StatsBreaksL2[Character::StatCount];

			boost::unordered_map<Character::Stat, Character::Stat> StatRemapping;
			
		};

		
	}
}

#endif