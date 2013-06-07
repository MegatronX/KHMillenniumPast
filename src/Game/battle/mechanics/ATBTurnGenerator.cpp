#include "ATBTurnGenerator.h"
#include <algorithm>
namespace Game
{
	namespace Battle
	{
		ATBTurnGenerator::ATBTurnGenerator(Entity* owner, const sf::Uint32 UpdateRate, float TicksPerSecond, const std::string& CType) : Launched(false), UpdateMult(TicksPerSecond / static_cast<float>(UpdateRate)), TurnGenerator(owner, CType), UpdateRate(sf::milliseconds(UpdateRate)), UpdaterThread(&ATBTurnGenerator::GeneratorFunction, this), Update(false), GenCount(0)
		{
			
		}
		ATBTurnGenerator::ATBTurnGenerator(const ATBTurnGenerator& gen) : Launched(false), TurnGenerator(gen), UpdateRate(gen.UpdateRate), Update(gen.Update), GenCount(gen.Update), UpdaterThread(&ATBTurnGenerator::GeneratorFunction, this), UpdateMult(gen.UpdateMult)
		{
			
		}
		ATBTurnGenerator::RawClonePtr ATBTurnGenerator::RawClone() const
		{
			return new ATBTurnGenerator(*this);
		}
		void ATBTurnGenerator::TrackCharacter(BattleCharacterComponent* character)
		{
			mtx.lock();
			TurnGenerator::TrackCharacter(character);
			mtx.unlock();
		}
		bool ATBTurnGenerator::StopTrackingCharacter(const std::string& name)
		{
			mtx.lock();
			bool result = TurnGenerator::StopTrackingCharacter(name);
			mtx.unlock();
			return result;
		}
		bool ATBTurnGenerator::StopTrackingCharacter(BattleCharacterComponent* character)
		{
			mtx.lock();
			bool result = TurnGenerator::StopTrackingCharacter(character);
			mtx.unlock();
			return result;
		}

		BattleCharacterComponent* ATBTurnGenerator::GetCharacter(const std::string& name)
		{
			mtx.lock();
			auto res = TurnGenerator::GetCharacter(name);
			mtx.unlock();
			return res;
		}

		void ATBTurnGenerator::GenerateNextCharacter(int GenCounter)
		{
			mtx.lock();
			if (!Launched)
			{
				UpdaterThread.launch();
				Launched = true;
			}
			GenCount = GenCounter;
			Update = true;
			mtx.unlock();
		}
		void ATBTurnGenerator::TickCharacter(BattleCharacterComponent* character)
		{
			if (character != nullptr && character->GetStatManager() != nullptr)
			{
				character->IncrementTimer(character->GetStatManager()->GetBattleStat(Character::Stat::Speed) * UpdateMult);
			}
		}
		void ATBTurnGenerator::Pause()
		{
			mtx.lock();
			Update = false;
			mtx.unlock();
		}

		void ATBTurnGenerator::UnPause()
		{
			mtx.lock();
			Update = false;
			mtx.unlock();
		}

		/*void ATBTurnGenerator::TickCharacter(BattleCharacterComponent* character)
		{
			
		}*/

		void ATBTurnGenerator::GeneratorFunction()
		{
			int Generated = 0;
			for(;;)
			{
				if (Update)
				{
					mtx.lock();
					for(auto it = UpdateList.begin(); it != UpdateList.end(); ++it)
					{
						TickCharacter(it->second);
					}
					if (ReadyLists[GeneratorMode].size() > 0)
					{
						if (ReadyLists[GeneratorMode].size() > 1)
							std::sort(ReadyLists[GeneratorMode].begin(), ReadyLists[GeneratorMode].end(), [](const BattleCharacterComponent* a, const BattleCharacterComponent* b) -> bool { return a->GetTimerRatio() > b->GetTimerRatio(); });
						
						ReadyCharSignal(ReadyLists[GeneratorMode], GeneratorMode);
						Generated += ReadyLists[GeneratorMode].size();
						TurnQueues[GeneratorMode].insert(TurnQueues[GeneratorMode].end(), ReadyLists[GeneratorMode].begin(), ReadyLists[GeneratorMode].end());
						ReadyLists[GeneratorMode].clear();
						if (Generated >= GenCount)
						{
							Generated = 0;
							Update = false;
						}
						QueueModifiedSignal(*this, GeneratorMode);
					}
					mtx.unlock();
				}
				sf::sleep(UpdateRate);
			}
		}

		ATBTurnGenerator::~ATBTurnGenerator()
		{
			UpdaterThread.terminate();
		//	TickThread.terminate();
		}
	}
}