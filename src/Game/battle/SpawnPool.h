#pragma once
#ifndef _SPAWNPOOL_H_
#define _SPAWNPOOL_H_
#include <vector>
#include <boost/unordered_map.hpp>
#include <character/Party.h>
#include <battle/BattleParty.h>
#include <components/Component.h>
#include <character/BaseCharacter.h>
namespace Game
{
	namespace Battle
	{
		class BattleField;
		class SpawnConfiguration
		{
		public:
			SpawnConfiguration();
			void AddSpawnableParty(const std::string& index, const std::vector<std::string>& members, float chance, bool absChance = false);
			void SetSpawnChance(const std::string& index, float chance, bool absChance);
			void NormalizeSpawnChances();

			boost::unordered_map<std::string, std::vector<std::string> > PartySpawns;
			boost::unordered_map<std::string, float> PartySpawnChances;
			std::vector<std::string> AlwaysSpawn;
			bool AlwaysSpawnSet;
			float totalChance;
		};

		class SpawnPool : public Components::Component
		{
		public:
			SpawnPool(BattleField* owner);
			SpawnPool(BattleField* owner, const SpawnConfiguration& config);

			void SetSpawnConfiguration(const SpawnConfiguration& config);

			SpawnConfiguration& GetConfiguration();

			Character::bparty_ptr SpawnParty(std::string partyName = "");

			//Character::bparty_ptr SpawnBattleParty(std::string partyName = "");

			Character::bparty_ptr SpawnParty(const std::vector<std::string>& members, std::string partyName = "");

			//Character::bparty_ptr SpawnBattleParty(const std::vector<std::string>& members, std::string partyName = "");

			void ResetIDCounter();
		private:
			SpawnConfiguration SpConfig;
			int SpawnPartyIDCounter;
		};
	}
}

#endif