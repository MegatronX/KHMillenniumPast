#pragma once
#include <battle/mechanics/TurnGenerator.h>

namespace Game
{
	namespace Battle
	{
		class QueueTurnGenerator : public TurnGenerator
		{
		public:
			QueueTurnGenerator(Entity* owner, const std::string& CType = "QueueTurnGenerator");
			virtual void Update(const sf::Uint32 time, const float TimeScale = 1.f) override;
			virtual RawClonePtr RawClone() const override;

			virtual void GenerateNextCharacter(int GenCounter = 1);

			virtual void FillQueue(const unsigned int QueueSizeFill = 10) override;

		protected:
			virtual void HandleTimerOverflow(BattleCharacterComponent*, BattleMode);
		private:
			int GenCount;
		};
	}
}