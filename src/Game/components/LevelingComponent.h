#pragma once

#include <character/BaseCharacter.h>

namespace Game
{
	namespace Character
	{
		typedef boost::function<int(int, BaseCharacter&)> LevelingFunction;

		class LevelingComponent : public Components::Component
		{
		public:

			int GetStatAtLevel(const Stat stat, const int Level)
			{
				StatLevelers[stat](Level, *Owner);
			}
		protected:
			BaseCharacter* Owner;
		private:
			LevelingFunction StatLevelers[Character::StatCount];
			LevelingFunction APLeveler;
		};

	}
}