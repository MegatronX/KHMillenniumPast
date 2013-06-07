#include "LevelingTable.h"

namespace Game
{
	namespace Character
	{
		LevelingTable::LevelingTable()
		{
			RequiredExp.rehash(110);
			for (unsigned int i = 0; i < 101; ++i)
			{
				RequiredExp[i] = i * i * i * 100 + 100 * i * i + 100 * i + 100;
			}
		}
		unsigned int LevelingTable::GetRequiredExp(const unsigned int level)
		{
			return RequiredExp[level];
		}
	}
}