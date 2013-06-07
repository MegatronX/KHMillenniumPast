#include "QueueTurnGenerator.h"

namespace Game
{
	namespace Battle
	{
		QueueTurnGenerator::QueueTurnGenerator(Entity* owner, const std::string& CType) : TurnGenerator(owner, CType)
		{

		}
		void QueueTurnGenerator::Update(const sf::Uint32 time, const float TimeScale)
		{
			if (TurnQueues[GeneratorMode].size() < 1)
			{
				FillQueue(1);
			}
		}
		QueueTurnGenerator::RawClonePtr QueueTurnGenerator::RawClone() const
		{
			return new QueueTurnGenerator(*this);
		}

		void QueueTurnGenerator::GenerateNextCharacter(int GenCounter)
		{
			
		}

		void QueueTurnGenerator::FillQueue(const unsigned int QueueSizeFill)
		{
			bool Modified = false;
			while (TurnQueues[GeneratorMode].size() < QueueSizeFill && UpdateList.size() > 0)
			{
				for (auto character = UpdateList.begin(); character != UpdateList.end(); ++character)
				{
					TickCharacter(character->second);
				}
				if (ReadyLists[GeneratorMode].size() > 0)
				{
					for (auto ch = ReadyLists[GeneratorMode].begin(); ch != ReadyLists[GeneratorMode].end();)
					{
						if (!(*ch)->IsEligibleForQueue())
						{
							(*ch)->StartTurn();
							(*ch)->EndTurn();
							ch = ReadyLists[GeneratorMode].erase(ch);
						}
						else
						{
							++ch;
						}
					}
					if (ReadyLists[GeneratorMode].size() > 1)
						std::sort(ReadyLists[GeneratorMode].begin(), ReadyLists[GeneratorMode].end(), [](const BattleCharacterComponent* a, const BattleCharacterComponent* b) -> bool { return a->GetTimerRatio() > b->GetTimerRatio(); });

					ReadyCharSignal(ReadyLists[GeneratorMode], GeneratorMode);
					TurnQueues[GeneratorMode].insert(TurnQueues[GeneratorMode].end(), ReadyLists[GeneratorMode].begin(), ReadyLists[GeneratorMode].end());
					ReadyLists[GeneratorMode].clear();
					Modified = true;
				}
			}
			if (Modified)
			{
				DispatchQueueModifiedEvents();
			}
		}

		void QueueTurnGenerator::HandleTimerOverflow(BattleCharacterComponent* character, BattleMode mode)
		{
			TurnGenerator::HandleTimerOverflow(character, mode);

		}
	}
}