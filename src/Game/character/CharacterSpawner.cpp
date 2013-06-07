#include "CharacterSpawner.h"

namespace boost
{
	std::size_t hash_value(const Game::Character::EntryID& entry)
	{
		boost::hash<std::string> sthash;
		boost::hash<int> inthash;
		return sthash(entry.Name) + inthash(entry.Level);
		//boost::hash<std::string> hasher;
		//const std::string & str = b.get();
		//return hasher(str);
	}
}

namespace Game
{
	namespace Character
	{
		CharacterDatabase* CharacterSpawner::CharacterDB = nullptr;
	}
}