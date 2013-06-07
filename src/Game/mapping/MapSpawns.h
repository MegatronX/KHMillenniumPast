#pragma once
#ifndef _MAPSPAWNS_H_
#define _MAPSPAWNS_H_

#include <character/CharacterSpawner.h>
#include <Utilities/Range.h>
#include <Mapping/GameMap.h>
namespace Game
{
	namespace Mapping
	{
		
		struct SpawnData
		{
			SpawnData() : RareSpawn(false)
			{

			}
			SpawnData(const boost::unordered_map<Character::EntryID, int>& members, const std::vector<Character::EntryID>& order = std::vector<Character::EntryID>(), bool rareSpawn = false)
				: PartyMembers(members), PartyMembersInOrder(order), RareSpawn(rareSpawn)
			{

			}
			boost::unordered_map<Character::EntryID, int> PartyMembers; //name, level, count
			std::vector<Character::EntryID> PartyMembersInOrder;
			bool RareSpawn;//If rare spawn, some abilities increase chance of encounter
		};

		const std::string MapSpawnComponentIndex = "MapSpawnComponentIndex";

		class MapSpawner : public Character::CharacterSpawner
		{
		public:
			MapSpawner(Entity* owner, bool determinesSpawn = false) : RunningTotal(0.f), Character::CharacterSpawner(owner), DeterminesSpawn(determinesSpawn)
			{

			}

			/*virtual Character::PartyInterface<Character::BaseCharacter> CreateParty(const std::string& PartyName, const boost::unordered_map<Character::EntryID, int>& Spawns, bool PerformBattlePrep = true, const std::vector<Character::EntryID>& SpawnOrder = std::vector<Character::EntryID>()) override
			{
				using namespace Character;
				return CharacterSpawner::CreateParty(PartyName, Spawns, PerformBattlePrep, SpawnOrder);
				PartyInterface<Character::BaseCharacter> spawnParty(PartyName);
				if (CharacterDB != nullptr)
				{
					
					for (auto spawn = Spawns.begin(); spawn != Spawns.end(); ++spawn)
					{
					}

				}
				return spawnParty;
			}*/

			void AddSpawn(const float chance, const boost::unordered_map<Character::EntryID, int>& spawnset, std::vector<std::string>& spawnOrder, bool rareSpawn = false, bool absoluteChance = false)
			{
				SpawnData data;
				data.RareSpawn = rareSpawn;
				data.PartyMembers = spawnset;
				if (absoluteChance)
				{
					float effChance = RunningTotal;
				}
				else
				{
					MapSpawnSet[Range<float>(RunningTotal, RunningTotal + chance)] = data;
					RunningTotal += chance;
				}
			}

			bool DetermineIfSpawn(GameMap& map)
			{
				return true;
			}

			void Normalize() 
			{

			}

			float GetRunningTotal() const
			{
				return RunningTotal;
			}

			bool GetDeterminesSpawn() const
			{
				return DeterminesSpawn;
			}

			void SetDeterminesSpawn(const bool val)
			{
				DeterminesSpawn = val;
			}

		private:

			bool DeterminesSpawn;
			std::map<Range<float>, SpawnData> MapSpawnSet;
			float RunningTotal;
		};
	}
}


#endif