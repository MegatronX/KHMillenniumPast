#pragma once
#ifndef _CHARACTERSTAT_H_
#define _CHARACTERSTAT_H_
#include <boost/unordered_map.hpp>
#include <string>
#include <array>
namespace Game
{
	namespace Character
	{
		const int StatCount = 14;
		enum Stat
		{
			HP = 0,
			MP = 1,
			SP = 2,
			Strength = 3,
			Vitality = 4,
			Defense = 4,
			Magic = 5,
			Spirit = 6,
			MgDefense = 6,
			Skill = 7,
			Speed = 8,
			Agility = 8,
			Evasion = 9,
			MgEvasion = 10,
			Accuracy = 11,
			MgAccuracy = 12,
			Luck = 13,
			//None = 14 //Using this as an indexer will cause a segfault
		};

		const int VolateStatCount = 3;
		/*enum VolatileStats
		{
			HP = 0,
			MP = 1,
			SP = 2
		};*/
		extern const std::array<Stat, VolateStatCount> VolatileStats;
		extern const boost::unordered_map<Stat, std::string> StatNameLookup;
		extern const boost::unordered_map<std::string, Stat> NameStatLookup;
	}
}

#endif