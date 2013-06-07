#include "TurnGenerator.h"
#include <boost/algorithm/string.hpp>
#include <algorithm>
namespace Game
{
	namespace Battle
	{
		TurnGenerator::TurnGenerator(Entity* owner, const std::string& ctype) : GeneratorMode(Real), Component(owner, owner != nullptr ? owner->GetName() + "TurnGenerator" : "NoOwnerTurnGenerator", ctype) 
		{
			SetGeneratorMode(BattleMode::Real);
		}
		TurnGenerator::TurnGenerator(const TurnGenerator& tg) : GeneratorMode(tg.GeneratorMode), UpdateList(tg.UpdateList), TimerOverflowConnections(tg.TimerOverflowConnections), ownerMechanics(tg.ownerMechanics), Component(tg)
		{

		}
		void TurnGenerator::Update(const sf::Uint32 time, const float TimeScale)
		{

		}
		TurnGenerator::RawClonePtr TurnGenerator::RawClone() const
		{
			return new TurnGenerator(*this);
		}
		void TurnGenerator::TrackCharacter(BattleCharacterComponent* character)
		{
			if (character != nullptr)
			{
				auto bchar = dynamic_cast<Character::BaseCharacter*>(character->GetOwner());
				if (bchar != nullptr)
				{
					auto con = TimerOverflowConnections.find(bchar->GetName());
					if (con != TimerOverflowConnections.end())
					{
						con->second.disconnect();
					}
					UpdateList[bchar->GetName()] = character;
					character->SetCharacterMode(GeneratorMode);
					TimerOverflowConnections[bchar->GetName()] = character->AddTimerOverflowEventHandler(boost::bind(&TurnGenerator::HandleTimerOverflow, this, _1, _2));
				}
			}
		}

		bool TurnGenerator::StopTrackingCharacter(const std::string& name)
		{
			auto it = UpdateList.find(name);
			if (it != UpdateList.end())
			{
				auto con = TimerOverflowConnections.find(name);
				con->second.disconnect();
				TimerOverflowConnections.erase(con);
				UpdateList.erase(it);
				return true;
			}
			return false;
		}
		bool TurnGenerator::StopTrackingCharacter(BattleCharacterComponent* character)
		{
			if (character != nullptr)
			{
				return StopTrackingCharacter(character->GetName());
			}
			return false;
		}

		BattleCharacterComponent* TurnGenerator::GetCharacter(const std::string& name)
		{
			auto it = UpdateList.find(name);
			if (it != UpdateList.end())
			{
				return it->second;
			}
			return nullptr;
		}

		BattleCharacterComponent* TurnGenerator::GetReadyCharater(bool popOffReadyList)
		{
			if (ReadyLists[BattleMode::Real].size() > 0)
			{

			}
			return nullptr;
		}
		void TurnGenerator::PopReadyCharacter()
		{

		}
		void TurnGenerator::GenerateNextCharacter(const unsigned int GenCounter)
		{
			/*while(TurnQueues[GeneratorMode].size() < GenCounter)
			for (int i = 0; i < GenCounter; ++i)
			{
				for (auto character = UpdateList.begin(); character != UpdateList.end(); ++character)
				{
					TickCharacter(character->second);
				}
			}*/
		}

		void TurnGenerator::FillQueue(const unsigned int QueueSizeFill)
		{
			
		}

		void TurnGenerator::ClearQueue(const BattleMode mode)
		{
			TurnQueues[GeneratorMode].clear();
		}

		void TurnGenerator::TickCharacter(BattleCharacterComponent* character)
		{
			if (character != nullptr && character->stats != nullptr)
			{
				character->IncrementTimer(character->stats->GetBattleStat(Character::Stat::Speed));
			}
		}

		const boost::unordered_map<std::string, BattleCharacterComponent*>& TurnGenerator::GetUpdateList() const
		{
			return UpdateList;
		}

		void TurnGenerator::SetGeneratorMode(const BattleMode mode)
		{
			if (mode != GeneratorMode)
			{
				for (auto it = UpdateList.begin(); it != UpdateList.end(); ++it)
				{
					it->second->SetCharacterMode(mode);
				}
				GeneratorMode = mode;
			}
			
		}

		BattleMode TurnGenerator::GetGeneratorMode() const
		{
			return GeneratorMode;
		}

		void TurnGenerator::PushRealToSim()
		{
			for (auto it = UpdateList.begin(); it != UpdateList.end(); ++it)
			{
				it->second->SyncFromRealToSim();
				//it->second->SetCharacterMode(mode);
			}
		}

		void TurnGenerator::PushSimToReal()
		{

		}

		void TurnGenerator::HandleTimerOverflow(BattleCharacterComponent* ch, BattleMode mode)
		{
			std::cout << "Handling Overflow for " << ch->GetOwner()->GetName() << " | Timer Val: " << ch->GetTimerValue(mode) << " | Timer Overflow: " << ch->GetTimerRatio(mode) << "\n";
			ReadyLists[mode].push_back(ch);
			ch->TickCounts[mode] -= MaxTimer;
			if (ch->stats != nullptr)
			{
				if (ch->TickCounts[mode] >= MaxTimer && ch->stats->GetBattleStat(Character::Stat::Speed) > 0)
				{
					ch->OverflowRatio[mode] = static_cast<float>(ch->TickCounts[mode]) / static_cast<float>(ch->stats->GetBattleStat(Character::Stat::Speed));
				}
				else
				{
					ch->OverflowRatio[mode] = 0;
				}

			}
		}
		boost::signals2::connection TurnGenerator::AddCharacterReadyEventHandler(const CharactersReadySignal::slot_type& event)
		{
			return ReadyCharSignal.connect(event);
		}

		boost::signals2::connection TurnGenerator::AddQueueModifiedEventHandler(const QueueChangedSignal::slot_type& event)
		{
			return QueueModifiedSignal.connect(event);
		}

		TurnQueue& TurnGenerator::GetTurnQueue(const BattleMode mode)
		{
			return TurnQueues[mode];
		}

		void TurnGenerator::DispatchQueueModifiedEvents()
		{
			QueueModifiedSignal(*this, GeneratorMode);
		}
		void TurnGenerator::StartCharacterTurn(Character::BaseCharacter& character)
		{

		}

		void TurnGenerator::EndCharacterTurn(Character::BaseCharacter& character)
		{
			if (TurnQueues[GeneratorMode].size() > 0)
			{
				
			}
		}
		/*boost::shared_ptr<TurnGenerator> TurnGenerator::MakeGenerator(const std::string& type)
		{
			boost::algorithm::to_lower(type);
			//static boost::unordered_set<std::string>
			if (type == "atbturngenerator" || type == "atb")
			{
				//return boost::shared_ptr<TurnGenerator>(new ATBTurnGenerator())
			}
			else
			{

			}
		}*/

		TurnGenerator::~TurnGenerator()
		{
			for (auto it = TimerOverflowConnections.begin(); it != TimerOverflowConnections.end(); ++it)
			{
				it->second.disconnect();
			}
		}
	}
}