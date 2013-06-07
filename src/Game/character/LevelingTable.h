#pragma once
#include <character/Stats.h>
#include <boost/unordered_map.hpp>
#include <boost/function.hpp>
namespace Game
{
	namespace Character
	{

		class Leveler
		{
		public:
			//unsigned int
		};
		class LevelingTable
		{
		public:
			LevelingTable();
			unsigned int GetRequiredExp(const unsigned int level);

			void SetLevelExp(const unsigned int level, const unsigned int xp);

			int GetStatAtLevel(const unsigned int level, const Stat stat);
		protected:
		private:

			Leveler StatLevelers[StatCount];

			boost::unordered_map<unsigned int, unsigned int> RequiredExp;
		};
	}
}