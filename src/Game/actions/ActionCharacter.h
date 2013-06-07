#pragma once

#include <character/BaseCharacter.h>
#include <actions/ActionResult.h>
#include <battle/BattleCharacter.h>
namespace Game
{
	namespace Actions
	{
		class ActionCharacter
		{
		public:
			ActionResult Result;
			Character::BaseCharacter* TargetCharacter;
			Battle::BattleCharacter* TargetBattleCharacter;
			//Action* UsingAction;
		};
	}
}