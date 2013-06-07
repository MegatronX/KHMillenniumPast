#pragma once
#ifndef _BATTLERAI_H_
#define _BATTLERAI_H_

#include <Entity.h>
//#include <BattleCharacterComponent.h>
#include <Battle/mechanics/Mechanics.h>

namespace Game
{
	namespace Actions
	{
		class Action;
	}
	namespace Battle
	{
		class BattleCharacterComponent;
		class BattleField;

		class AIComData
		{
		public:
		};
		const std::string BattleAIComponentIndex = "BattleAIComponent";
		class BattlerAI : public Components::Component
		{
		public:
			BattlerAI(Character::BaseCharacter* controlledCharacter, BattleCharacterComponent* ControlledBatCharacter);

			virtual void Init(Mechanics& mec, BattleField& field);

			virtual boost::shared_ptr<Actions::Action> DetermineNextAction();

			virtual void ActionFeedback(boost::shared_ptr<Actions::Action> finalAction);

			virtual void ReceiveAIComData(AIComData& data);

			virtual ~BattlerAI();
		private:
			BattleCharacterComponent* BatChar;
			Character::BaseCharacter* BaseChar;
			Mechanics* mech;
		};
	}
}

#endif