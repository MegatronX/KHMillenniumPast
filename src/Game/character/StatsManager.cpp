#include "StatsManager.h"

namespace Game
{
	namespace Character
	{
		const int StatLimitL1 = 9999;
		const int StatLimitL2 = 99999;
		StatsManager::StatsManager(Entity* owner) : Component(owner, owner->GetName() + "StatsManager", "StatsManager"), 
			BaseStats(owner, 0), PermanentStatBoosts(owner, 0), PermanentStatMultipliers(owner, 0.f), AbilityStatAdders(owner, 0), AbilityStatMultipliers(owner, 0.f), SEStatAdders(owner, 0), SEStatMultipliers(owner, 0.f),
			CombinedStats(owner, 0), BattleStatAdders(owner, 0), BattleStatMultipliers(owner, 0.f), BattleStats(owner, 0), EquipmentStatAdders(owner, 0), EquipmentStatMultipliers(owner, 0.f), CurrentHP(0), CurrentMP(0), CurrentSP(0)
		{
			SyncAllBattleStats(true);
			CurrentHP = BattleStats[Stat::HP];
			CurrentMP = BattleStats[Stat::MP];
			CurrentSP = BattleStats[Stat::SP];
		}
		StatsManager::StatsManager(Entity* owner, int baseStats[Character::StatCount]) : Component(owner, owner->GetName() + "StatsManager", "StatsManager"), 
			BaseStats(owner, baseStats), PermanentStatBoosts(owner, 0), PermanentStatMultipliers(owner, 0.f), AbilityStatAdders(owner, 0), AbilityStatMultipliers(owner, 0.f), SEStatAdders(owner, 0), SEStatMultipliers(owner, 0.f),
			CombinedStats(owner, 0), BattleStatAdders(owner, 0), BattleStatMultipliers(owner, 0.f), BattleStats(owner, 0), EquipmentStatAdders(owner, 0), EquipmentStatMultipliers(owner, 0.f), CurrentHP(0), CurrentMP(0), CurrentSP(0)
		{
			SyncAllBattleStats(true);
			CurrentHP = BattleStats[Stat::HP];
			CurrentMP = BattleStats[Stat::MP];
			CurrentSP = BattleStats[Stat::SP];
		}
		StatsManager::StatsManager(Entity* owner, std::vector<int>& stats) : Component(owner, owner->GetName() + "StatsManager", "StatsManager"), 
			BaseStats(owner, 0), PermanentStatBoosts(owner, 0), PermanentStatMultipliers(owner, 0.f), AbilityStatAdders(owner, 0), AbilityStatMultipliers(owner, 1.f), SEStatAdders(owner, 0), SEStatMultipliers(owner, 0.f),
			CombinedStats(owner, 0), BattleStatAdders(owner, 0), BattleStatMultipliers(owner, 0.f), BattleStats(owner, 0), EquipmentStatAdders(owner, 0), EquipmentStatMultipliers(owner, 0.f), CurrentHP(0), CurrentMP(0), CurrentSP(0)
		{
			for (int i = 0; i < stats.size() && i < StatCount; ++i)
			{
				BaseStats[i] = stats[i];
			}
			SyncAllBattleStats(true);
			CurrentHP = BattleStats[Stat::HP];
			CurrentMP = BattleStats[Stat::MP];
			CurrentSP = BattleStats[Stat::SP];
		}
		StatsManager::StatsManager(Entity* owner, std::map<Stat, int>& stats) : Component(owner, owner->GetName() + "StatsManager", "StatsManager"), 
			BaseStats(owner, 0), PermanentStatBoosts(owner, 0), PermanentStatMultipliers(owner, 0.f), AbilityStatAdders(owner, 0), AbilityStatMultipliers(owner, 1.f), SEStatAdders(owner, 0), SEStatMultipliers(owner, 0.f),
			CombinedStats(owner, 0), BattleStatAdders(owner, 0), BattleStatMultipliers(owner, 0.f), BattleStats(owner, 0), EquipmentStatAdders(owner, 0), EquipmentStatMultipliers(owner, 0.f), CurrentHP(0), CurrentMP(0), CurrentSP(0)
		{
			for (auto st = stats.begin(); st != stats.end(); ++st)
			{
				BaseStats[st->first] = st->second;
			}
			SyncAllBattleStats(true);
			CurrentHP = BattleStats[Stat::HP];
			CurrentMP = BattleStats[Stat::MP];
			CurrentSP = BattleStats[Stat::SP];
		}
		StatsManager::StatsManager(Entity* owner, boost::unordered_map<Stat, int>& stats) : Component(owner, owner->GetName() + "StatsManager", "StatsManager"), 
			BaseStats(owner, 0), PermanentStatBoosts(owner, 0), PermanentStatMultipliers(owner, 0.f), AbilityStatAdders(owner, 0), AbilityStatMultipliers(owner, 1.f), SEStatAdders(owner, 0), SEStatMultipliers(owner, 0.f),
			CombinedStats(owner, 0), BattleStatAdders(owner, 0), BattleStatMultipliers(owner, 0.f), BattleStats(owner, 0), EquipmentStatAdders(owner, 0), EquipmentStatMultipliers(owner, 0.f), CurrentHP(0), CurrentMP(0), CurrentSP(0)
		{
			for (auto st = stats.begin(); st != stats.end(); ++st)
			{
				BaseStats[st->first] = st->second;
			}
			SyncAllBattleStats(true);
			CurrentHP = BattleStats[Stat::HP];
			CurrentMP = BattleStats[Stat::MP];
			CurrentSP = BattleStats[Stat::SP];
		}
		int StatsManager::GetBaseStat(const Stat stat, bool ignoreLimits) const
		{
			return BaseStats.GetStat(stat);
		}
		int StatsManager::GetPermanentStatBoost(const Stat stat) const
		{
			return PermanentStatBoosts.GetStat(stat);
		}
		float StatsManager::GetPermanentStatMultiplier(const Stat stat) const
		{
			return PermanentStatMultipliers.GetStat(stat);
		}

		int StatsManager::GetAbilityStatAdder(const Stat stat) const
		{
			return AbilityStatAdders.GetStat(stat);
		}
		float StatsManager::GetAbilityStatMultiplier(const Stat stat) const
		{
			return AbilityStatMultipliers.GetStat(stat);
		}

		void StatsManager::IncrementAbilityStatAdder(const Stat stat, const int inc, bool sync, bool dispatch)
		{
			AbilityStatAdders[stat] += inc;
			if (sync)
			{
				SyncStat(stat);
			}
		}
		void StatsManager::IncrementAbilityStatMultiplier(const Stat stat, const float inc, bool sync, bool dispatch)
		{
			AbilityStatMultipliers[stat] += inc;
			if (sync)
			{
				SyncStat(stat);
			}
		}

		int StatsManager::GetStatusEffectStatAdder(const Stat stat) const
		{
			return SEStatAdders.GetStat(stat);
		}
		float StatsManager::GetStatusEffectStatMultiplier(const Stat stat) const
		{
			return SEStatMultipliers.GetStat(stat);
		}

		void StatsManager::IncrementStatusEffectStatAdder(const Stat stat, const int inc, bool sync, bool dispatch)
		{
			SEStatAdders[stat] += inc;
			if (sync)
			{
				SyncBattleStat(stat, true, dispatch);
			}
		}
		void StatsManager::IncrementStatusEffectStatMultiplier(const Stat stat, const float inc, bool sync, bool dispatch)
		{
			SEStatMultipliers[stat] += inc;
			if (sync)
			{
				SyncBattleStat(stat, true, dispatch);
			}
		}

		int StatsManager::GetEquipmentStatAdder(const Stat stat) const
		{
			return EquipmentStatAdders.GetStat(stat);
		}
		float StatsManager::GetEquipmentStatMultiplier(const Stat stat) const
		{
			return EquipmentStatMultipliers.GetStat(stat);
		}

		void StatsManager::IncrementEquipmentStatAdder(const Stat stat, const int inc, bool sync, bool dispatch)
		{
			EquipmentStatAdders[stat] += inc;
			if (sync)
			{
				SyncBattleStat(stat, true, dispatch);
			}
		}
		void StatsManager::IncrementEquipmentStatMultiplier(const Stat stat, const float inc, bool sync, bool dispatch)
		{
			EquipmentStatMultipliers[stat] += inc;
			if (sync)
			{
				SyncBattleStat(stat, true, dispatch);
			}
		}

		int StatsManager::GetAdditionalStatAdder(const std::string& name, const Stat stat) const
		{
			auto it = AdditionalStatsAdders.find(name);
			if (it != AdditionalStatsAdders.end())
			{
				return (*it).second.GetStat(stat);
			}
			return 0;
		}
		float StatsManager::GetAdditionalStatMultiplier(const std::string& name, const Stat stat) const
		{
			auto it = AdditionalStatsMultipliers.find(name);
			if (it != AdditionalStatsMultipliers.end())
			{
				return (*it).second.GetStat(stat);
			}
			return 0;
		}

		void StatsManager::IncrementAdditionalStatAdder(const std::string& name, const Stat stat, const int inc, bool sync, bool dispatch)
		{
			AdditionalStatsAdders[name].IncrementStat(stat, inc);
			if (sync)
			{
				SyncStat(stat, dispatch);
			}
		}
		void StatsManager::IncrementAdditionalStatMultiplier(const std::string& name, const Stat stat, const float inc, bool sync, bool dispatch)
		{
			AdditionalStatsMultipliers[name].IncrementStat(stat, inc);
			if (sync)
			{
				SyncStat(stat, dispatch);
			}
		}

		int StatsManager::GetCombinedStat(const Stat stat, bool ignoreLimits) const
		{
			return BattleStats.GetStat(GetMappedStat(stat));
		}

		int StatsManager::GetBattleStat(const Stat stat, bool ignoreLimits) const
		{
			int retstat = BattleStats.GetStat(stat);

			if (!ignoreLimits)
			{
				
			}

			return retstat;//BattleStats.GetStat(stat);
		}

		void StatsManager::SyncStat(const Stat stat, bool dispatch)
		{
			Stat effstat = GetMappedStat(stat);
			int base = BaseStats[effstat] + PermanentStatBoosts[effstat] + AbilityStatAdders[effstat] + EquipmentStatAdders[effstat];
			if (AdditionalStatsAdders.size() > 0)
			{
				for (auto it = AdditionalStatsAdders.begin(); it != AdditionalStatsAdders.end(); ++it)
				{
					base += (*it).second[effstat];
				}
			}
			float Mult = 1.f + PermanentStatMultipliers[effstat] + AbilityStatMultipliers[effstat] + EquipmentStatMultipliers[effstat];
			if (AdditionalStatsMultipliers.size() > 0)
			{
				for (auto it = AdditionalStatsMultipliers.begin(); it != AdditionalStatsMultipliers.end(); ++it)
				{
					Mult += (*it).second[effstat];
				}
			}
			Mult = std::max<float>(0.f, Mult);
			int newVal = static_cast<int>(static_cast<float>(base) * Mult);
			int oldVal = CombinedStats[effstat];
			CombinedStats[effstat] = static_cast<int>(static_cast<float>(base) * Mult);
			if (dispatch && oldVal != newVal)
			{
				DispatchStatChangeEvents(effstat, oldVal, newVal);
			}
			//CombinedStats[stat] = value;
		}
		void StatsManager::SyncStat(const int stat, bool dispatch)
		{
			SyncStat(static_cast<Stat>(stat), dispatch);
		}
		void StatsManager::SyncBattleStat(const Stat stat, bool SyncBase, bool dispatch)
		{
			auto effstat = GetMappedStat(stat);
			if (SyncBase)
				SyncStat(stat, false);
			int oldVal = BattleStats[effstat];
			int newVal = static_cast<int>((static_cast<float>(CombinedStats[effstat] + SEStatAdders[effstat] + BattleStatAdders[effstat]) * 
				std::max<float>(0.f, (1.f + SEStatMultipliers[effstat] + BattleStatMultipliers[effstat]))));
			BattleStats[effstat] = newVal;
			if (dispatch && oldVal != newVal)
			{
				DispatchStatChangeEvents(effstat, oldVal, newVal);
			}
			//InBattleStats[stat] = CombinedStats[stat];
		}
		void StatsManager::SyncBattleStat(const int index, bool SyncBase, bool dispatch)
		{
			SyncBattleStat(static_cast<Character::Stat>(index), SyncBase);
		}
		void StatsManager::SyncAllStats(bool dispatch)
		{
			for (int i = 0; i < Character::StatCount; ++i)
			{
				SyncStat(i, dispatch);
			}
		}
		void StatsManager::SyncAllBattleStats(bool SyncBase, bool dispatch)
		{
			for (int i = 0; i < Character::StatCount; ++i)
			{
				SyncBattleStat(i, SyncBase, dispatch);
			}
		}
		
		Character::Stat StatsManager::GetMappedStat(const Character::Stat st) const
		{
			auto stl = StatRemapping.find(st);
			if (stl != StatRemapping.end())
				return stl->second;
			return st;
		}
		bool StatsManager::LimitVolatileStat(const Character::Stat st, bool remap, bool inBattle)
		{
			bool Limited = false;
			Character::Stat effStat = st;
			if (remap)
			{
				effStat = GetMappedStat(st);
			}
			switch (effStat)
			{
			case Stat::HP:
				if (inBattle)
				{
					if (CurrentHP > BattleStats[Stat::HP])
					{
						CurrentHP = BattleStats[Stat::HP];
						Limited = true;
					}
				}
				else
				{
					if (CurrentHP > CombinedStats[Stat::HP])
					{
						CurrentHP = BattleStats[Stat::HP];
						Limited = true;
					}
				}
				break;
			case Stat::MP:
				if (inBattle)
				{
					if (CurrentMP > BattleStats[Stat::MP])
					{
						CurrentMP = BattleStats[Stat::MP];
						Limited = true;
					}
				}
				else
				{
					if (CurrentMP > CombinedStats[Stat::MP])
					{
						CurrentMP = BattleStats[Stat::MP];
						Limited = true;
					}
				}
				break;
			case Stat::SP:
				if (inBattle)
				{
					if (CurrentSP > BattleStats[Stat::SP])
					{
						CurrentSP = BattleStats[Stat::SP];
						Limited = true;
					}
				}
				else
				{
					if (CurrentSP > CombinedStats[Stat::SP])
					{
						CurrentSP = BattleStats[Stat::SP];
						Limited = true;
					}
				}
				break;
			}
			return Limited;
		}
		int StatsManager::GetCurrentHP() const
		{
			auto stat = GetMappedStat(Stat::HP);

			switch (stat)
			{
			case Stat::HP:
				{
					return CurrentHP;
					break;
				}
			case Stat::MP:
				{
					return CurrentMP;
					break;
				}
			case Stat::SP:
				{
					return CurrentSP;
					break;
				}
			}
			return 0;
		}
		void StatsManager::SetCurrentHP(const int hp, bool inBattle, bool dispatch)
		{
			auto stat = GetMappedStat(Stat::HP);

			switch (stat)
			{
			case Stat::HP:
				{
					int old = CurrentHP;
					CurrentHP = hp;
					LimitVolatileStat(stat);
					if (dispatch)
						DispatchStatChangeEvents(Stat::HP, old, CurrentHP);
					break;
				}
			case Stat::MP:
				{
					int old = CurrentMP;
					CurrentMP = hp;
					LimitVolatileStat(stat);
					if (dispatch)
						DispatchStatChangeEvents(Stat::MP, old, CurrentMP);
					break;
				}
			case Stat::SP:
				{
					int old = CurrentSP;
					CurrentSP = hp;
					LimitVolatileStat(stat);
					if (dispatch)
						DispatchStatChangeEvents(Stat::SP, old, CurrentSP);
					break;
				}
			}
		}
		void StatsManager::IncrementCurrentHP(const int inc, bool inBattle, bool dispatch)
		{
			auto stat = GetMappedStat(Stat::HP);

			switch (stat)
			{
			case Stat::HP:
				{
					int old = CurrentHP;
					CurrentHP += inc;
					LimitVolatileStat(stat);
					DispatchStatChangeEvents(Stat::HP, old, CurrentHP);
					break;
				}
			case Stat::MP:
				{
					int old = CurrentMP;
					CurrentMP += inc;
					LimitVolatileStat(stat);
					DispatchStatChangeEvents(Stat::MP, old, CurrentMP);
					break;
				}
			case Stat::SP:
				{
					int old = CurrentSP;
					CurrentSP += inc;
					LimitVolatileStat(stat);
					DispatchStatChangeEvents(Stat::SP, old, CurrentSP);
					break;
				}
			}
		}

		int StatsManager::GetCurrentMP() const
		{
			auto stat = GetMappedStat(Stat::MP);

			switch (stat)
			{
			case Stat::HP:
				{
					return CurrentHP;
					break;
				}
			case Stat::MP:
				{
					return CurrentMP;
					break;
				}
			case Stat::SP:
				{
					return CurrentSP;
					break;
				}
			}
			return 0;
		}
		void StatsManager::SetCurrentMP(const int mp, bool inBattle, bool dispatch)
		{
			auto stat = GetMappedStat(Stat::MP);

			switch (stat)
			{
			case Stat::HP:
				{
					int old = CurrentHP;
					CurrentHP = mp;
					LimitVolatileStat(stat);
					if (dispatch)
					DispatchStatChangeEvents(Stat::HP, old, CurrentHP);
					break;
				}
			case Stat::MP:
				{
					int old = CurrentMP;
					CurrentMP = mp;
					LimitVolatileStat(stat);
					if (dispatch)
						DispatchStatChangeEvents(Stat::MP, old, CurrentMP);
					break;
				}
			case Stat::SP:
				{
					int old = CurrentSP;
					CurrentMP = mp;
					LimitVolatileStat(stat);
					if (dispatch)
						DispatchStatChangeEvents(Stat::SP, old, CurrentSP);
					break;
				}
			}
		}
		void StatsManager::IncrementCurrentMP(const int inc, bool inBattle, bool dispatch)
		{
			auto stat = GetMappedStat(Stat::MP);

			switch (stat)
			{
			case Stat::HP:
				{
					int old = CurrentHP;
					CurrentHP += inc;
					LimitVolatileStat(stat);
					if (dispatch)
						DispatchStatChangeEvents(Stat::HP, old, CurrentHP);
					break;
				}
			case Stat::MP:
				{
					int old = CurrentMP;
					CurrentMP += inc;
					LimitVolatileStat(stat);
					if (dispatch)
						DispatchStatChangeEvents(Stat::MP, old, CurrentMP);
					break;
				}
			case Stat::SP:
				{
					int old = CurrentSP;
					CurrentSP += inc;
					LimitVolatileStat(stat);
					if (dispatch)
						DispatchStatChangeEvents(Stat::SP, old, CurrentSP);
					break;
				}
			}
		}

		int StatsManager::GetCurrentSP() const
		{
			auto stat = GetMappedStat(Stat::SP);

			switch (stat)
			{
			case Stat::HP:
				{
					return CurrentHP;
					break;
				}
			case Stat::MP:
				{
					return CurrentMP;
					break;
				}
			case Stat::SP:
				{
					return CurrentSP;
					break;
				}
			}
			return 0;
		}
		void StatsManager::SetCurrentSP(const int sp, bool inBattle, bool dispatch)
		{
			auto stat = GetMappedStat(Stat::SP);

			switch (stat)
			{
			case Stat::HP:
				{
					int old = CurrentHP;
					CurrentHP = sp;
					LimitVolatileStat(stat, true, inBattle);
					if (dispatch)
						DispatchStatChangeEvents(Stat::HP, old, CurrentHP);
					break;
				}
			case Stat::MP:
				{
					int old = CurrentMP;
					CurrentMP = sp;
					LimitVolatileStat(stat, true, inBattle);
					if (dispatch)
						DispatchStatChangeEvents(Stat::MP, old, CurrentMP);
					break;
				}
			case Stat::SP:
				{
					int old = CurrentSP;
					CurrentSP = sp;
					LimitVolatileStat(stat);
					if (dispatch)
						DispatchStatChangeEvents(Stat::SP, old, CurrentSP);
					break;
				}
			}
		}
		void StatsManager::IncrementCurrentSP(const int inc, bool inBattle, bool dispatch)
		{
			auto stat = GetMappedStat(Stat::SP);
			switch (stat)
			{
			case Stat::HP:
				{
					int prevHP = CurrentHP;
					CurrentHP += inc;
					LimitVolatileStat(stat);
					if (dispatch)
						DispatchStatChangeEvents(Stat::HP, prevHP, CurrentHP);
					break;
				}
			case Stat::MP:
				{
					int prevMP = CurrentMP;
					CurrentMP += inc;
					LimitVolatileStat(stat);
					if (dispatch)
						DispatchStatChangeEvents(Stat::MP, prevMP, CurrentMP);
					break;
				}
			case Stat::SP:
				{
					int prevSP = CurrentSP;
					CurrentSP += inc;
					LimitVolatileStat(stat);
					if (dispatch)
						DispatchStatChangeEvents(Stat::SP, prevSP, CurrentSP);
					break;
				}
			}
		}

		void StatsManager::RemapStat(const Character::Stat src, const Character::Stat dest, bool dispatch)
		{
			StatRemapping[src] = dest;
		}
		void StatsManager::ClearRemapping(const Character::Stat st, bool dispatch)
		{
			auto stat = StatRemapping.find(st);
			if (stat != StatRemapping.end())
			{
				StatRemapping.erase(stat);
			}
		}
		bool StatsManager::IsRemapped(const Character::Stat st) const
		{
			return StatRemapping.find(st) != StatRemapping.end();
		}
		void StatsManager::ClearRemappings()
		{
			StatRemapping.clear();
		}

		bool StatsManager::AddStatChangeHandler(const std::string& index, const StatChangeHandler& handler)
		{
			StatChangeSignals[index] = handler;
			return true;
		}
		bool StatsManager::RemoveStatChangeHandler(const std::string& index)
		{
			auto it = StatChangeSignals.find(index);
			if (it != StatChangeSignals.end())
			{
				StatChangeSignals.erase(it);
				return true;
			}
			return false;
		}
		void StatsManager::DispatchStatChangeEvents(const Stat stat, const int old, const int newVal)
		{
			for (auto evt = StatChangeSignals.begin(); evt != StatChangeSignals.end(); ++evt)
			{
				evt->second(*this, stat, old, newVal);
			}
		}


		/*bool StatsManager::LimitVolatileStat(const Character::Stat st, bool remap, bool inBattle)
		{
			return false;
		}*/
		void StatsManager::SetBaseStat(const Stat stat, const int val, bool sync)
		{
			BaseStats.SetStat(stat, val);
			if (sync)
			{
				SyncStat(stat);
			}
		}
		void StatsManager::SetPermanentStatBoost(const Stat stat, const int val, bool sync)
		{
			PermanentStatBoosts.SetStat(stat, val);
			if (sync)
			{
				SyncStat(stat);
			}
		}
		void StatsManager::SetPermanentStatMultiplier(const Stat stat, const float val, bool sync)
		{
			PermanentStatMultipliers.SetStat(stat, val);
			if (sync)
			{
				SyncStat(stat);
			}
		}

		void StatsManager::IncrementBaseStat(const Stat stat, const int increment, bool sync)
		{
			BaseStats.SetStat(stat, BaseStats.GetStat(stat) + increment);
			if (sync)
			{
				SyncStat(stat);
			}
		}
		void StatsManager::IncrementPermanentStatBoost(const Stat stat, const int inc, bool sync)
		{
			PermanentStatBoosts.SetStat(stat, PermanentStatBoosts.GetStat(stat) + inc);
			if (sync)
			{
				SyncStat(stat);
			}
		}
		void StatsManager::IncrementPermanentStatMultiplier(const Stat stat, const float inc, bool sync)
		{
			PermanentStatMultipliers.SetStat(stat, PermanentStatMultipliers.GetStat(stat) + inc);
			if (sync)
			{
				SyncStat(stat);
			}
		}
		void StatsManager::AddAdditionalStatAdder(const std::string& adderIndex, Components::StatComponent<int>& comp)
		{
			AdditionalStatsAdders[adderIndex] = comp;
		}
		void StatsManager::AddAdditionalStatMultiplier(const std::string& multIndex, Components::StatComponent<float>& comp)
		{
			AdditionalStatsMultipliers[multIndex] = comp;
		}
		bool StatsManager::RemoveStatAdder(const std::string& index)
		{
			bool rmv = false;
			auto it = AdditionalStatsAdders.find(index);
			if (it != AdditionalStatsAdders.end())
			{
				AdditionalStatsAdders.erase(it);
				rmv = true;
			}
			return rmv;
		}
		bool StatsManager::RemoveStatMultiplier(const std::string& index)
		{
			bool rmv = false;
			auto it = AdditionalStatsMultipliers.find(index);
			if (it != AdditionalStatsMultipliers.end())
			{
				AdditionalStatsMultipliers.erase(it);
				rmv = true;
			}
			return rmv;
		}
	}
}