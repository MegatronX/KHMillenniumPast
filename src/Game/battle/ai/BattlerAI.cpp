#include "BattlerAI.h"
#include <battle/BattleCharacterComponent.h>

namespace Game
{
	namespace Battle
	{
		BattlerAI::BattlerAI(Character::BaseCharacter* controlledCharacter, BattleCharacterComponent* ControlledBatCharacter) : BatChar(ControlledBatCharacter), BaseChar(controlledCharacter)
		{

		}

		void BattlerAI::Init(Mechanics& mec, BattleField& field)
		{

		}

		boost::shared_ptr<Actions::Action> BattlerAI::DetermineNextAction()
		{
			return boost::shared_ptr<Actions::Action>();
		}

		void BattlerAI::ActionFeedback(boost::shared_ptr<Actions::Action> finalAction)
		{

		}

		void BattlerAI::ReceiveAIComData(AIComData& data)
		{

		}

		BattlerAI::~BattlerAI()
		{

		}
	}
}