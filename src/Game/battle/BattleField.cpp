#include "BattleField.h"
#include <battle/mechanics/BaseMechanics.h>
#include <battle/mechanics/ATBTurnGenerator.h>
#include <battle/mechanics/QueueTurnGenerator.h>
#include <boost/algorithm/string.hpp>

namespace Game
{
	namespace Battle
	{
		const static std::string BattleComponentIndex("BattleCharacterComponent");
		boost::shared_ptr<Mechanics> BattleField::FallbackMechanics(new Mechanics(nullptr));
		boost::shared_ptr<SpawnPool> BattleField::SpawningPool(new SpawnPool(nullptr));
		/*BattleField::BattleField(Character::bparty_ptr playerParty, Character::bparty_ptr enemyParty) : Entity("Battlefield", EntityTypes::Battlefield), PlayerParty(playerParty), BattleMechanics(new BaseMechanics(this))
		{
			if (enemyParty.get() != nullptr)
			{
				EnemyParties[enemyParty->GetName()] = enemyParty;
			}
			
		}*/

		BattleField::BattleField() : Entity("Battlefield", EntityTypes::Battlefield), ActiveBattleCharacter(nullptr), ActiveCharacter(nullptr)
		{

		}

		BattleField::BattleField(Character::bparty_ptr playerParty, Character::bparty_ptr enemyParty, const std::string& MechanicsType, const std::string& TurnGenType) : Entity("Battlefield", EntityTypes::Battlefield), PlayerParty(playerParty), ActiveBattleCharacter(nullptr), ActiveCharacter(nullptr)
		{
			if (enemyParty.get() == nullptr)
			{

			}

			EnemyParties[enemyParty->GetName()] = enemyParty;
				

			if (MechanicsType == "BaseMechanics")
			{
				BattleMechanics = boost::shared_ptr<Mechanics>(new BaseMechanics(this));
			}
			else
			{
				BattleMechanics = FallbackMechanics;
			}

			auto lgen = boost::algorithm::to_lower_copy(TurnGenType);
			if (lgen == "atbturngenerator" || lgen == "atb")
			{
				TurnGen = boost::shared_ptr<TurnGenerator>(new ATBTurnGenerator(this));
			}
			else
			{
				TurnGen = boost::shared_ptr<TurnGenerator>(new QueueTurnGenerator(this));
			}

		}

		BattleField::BattleField(Character::bparty_ptr playerParty, const std::vector<Character::bparty_ptr>& enemyParties, const std::string& MechanicsType, const std::string& TurnGenType) : Entity("Battlefield", EntityTypes::Battlefield), PlayerParty(playerParty), ActiveBattleCharacter(nullptr), ActiveCharacter(nullptr)
		{
			for (auto party = enemyParties.begin(); party != enemyParties.end(); ++party)
			{
				if ((*party).get() != nullptr)
				{
					EnemyParties[(*party)->GetName()] = *party;
				}
			}

			if (MechanicsType == "BaseMechanics")
			{
				BattleMechanics = boost::shared_ptr<Mechanics>(new BaseMechanics(this));
			}
			else
			{
				BattleMechanics = FallbackMechanics;
			}

			auto lgen = boost::algorithm::to_lower_copy(TurnGenType);
			if (lgen == "atbturngenerator" || lgen == "atb")
			{
				TurnGen = boost::shared_ptr<TurnGenerator>(new ATBTurnGenerator(this));
			}
			else
			{
				TurnGen = boost::shared_ptr<TurnGenerator>(new QueueTurnGenerator(this));
			}
			TurnGen->AddQueueModifiedEventHandler(boost::bind(&BattleField::HandleQueueModified, this, _1, _2));
		}

		BattleField::BattleField(Character::bparty_ptr playerParty, const boost::unordered_map<std::string, Character::bparty_ptr>& enemyParties, const std::string& MechanicsType, const std::string& TurnGenType) : Entity("Battlefield", EntityTypes::Battlefield), PlayerParty(playerParty), EnemyParties(enemyParties), ActiveBattleCharacter(nullptr), ActiveCharacter(nullptr)
		{
			if (MechanicsType == "BaseMechanics")
			{
				BattleMechanics = boost::shared_ptr<Mechanics>(new BaseMechanics(this));
			}
			else
			{
				BattleMechanics = FallbackMechanics;
			}
			auto lgen = boost::algorithm::to_lower_copy(TurnGenType);
			if (lgen == "atbturngenerator" || lgen == "atb")
			{
				TurnGen = boost::shared_ptr<TurnGenerator>(new ATBTurnGenerator(this));
			}
			else
			{
				TurnGen = boost::shared_ptr<TurnGenerator>(new QueueTurnGenerator(this));
			}
		}

		void BattleField::Update(const sf::Uint32 time, const float timeScale)
		{
			auto genMode = TurnGen->GetGeneratorMode();
			TurnGen->SetGeneratorMode(BattleMode::Real);
			TurnGen->Update(time, timeScale);
			TurnGen->SetGeneratorMode(genMode);
			//*(gen.GetTurnQueue(mode).begin())
			if (ActiveBattleCharacter == nullptr && TurnGen->GetTurnQueue(BattleMode::Real).size() > 0)
			{
				ActiveBattleCharacter = *(TurnGen->GetTurnQueue(BattleMode::Real).begin());
				ActiveCharacter = dynamic_cast<Character::BaseCharacter*>(ActiveBattleCharacter->GetOwner());
				StartCharacterTurn();
				
			}
		}

		void BattleField::InitBattle()
		{
			
		}

		void BattleField::BattlePhase()
		{
			
			
		}

		void BattleField::PreBattlePhase()
		{
			PlayerBattleParty = battleparty_ptr(new BattleParty("PlayerBattleParty"));
			if (PlayerParty.get() != nullptr)
			{
				for (auto member = PlayerParty->GetPartyMembers().begin(); member != PlayerParty->GetPartyMembers().end(); ++member)
				{
					if (member->second.get() != nullptr)
					{
						boost::shared_ptr<BattleCharacterComponent> bcharcomp(new BattleCharacterComponent(member->second.get(), PlayerBattleParty.get(), PlayerParty.get()));
						member->second->RegisterComponent(BattleComponentIndex, bcharcomp);
						member->second->SetParty(PlayerParty.get());
						PlayerBattleParty->AddMember(bcharcomp, member->second->GetName());
						BattleMechanics->ReadyCharacter(*(member->second), *bcharcomp, *this);
					}
				}
			}
			for (auto eparty = EnemyParties.begin(); eparty != EnemyParties.end(); ++eparty)
			{
				auto ebparty = battleparty_ptr(new BattleParty(eparty->second->GetName() + "BattleParty"));
				for (auto enemy = eparty->second->GetPartyMembers().begin(); enemy != eparty->second->GetPartyMembers().end(); ++enemy)
				{
					boost::shared_ptr<BattleCharacterComponent> bcharcomp(new BattleCharacterComponent(enemy->second.get(), ebparty.get(), eparty->second.get()));
					enemy->second->RegisterComponent(BattleComponentIndex, bcharcomp);
					enemy->second->SetParty(eparty->second.get());
					//PlayerBattleParty->AddMember(bcharcomp, member->second->GetName());
					ebparty->AddMember(bcharcomp, enemy->second->GetName());
					BattleMechanics->ReadyCharacter(*(enemy->second), *bcharcomp, *this);
				}
				EnemyBattleParties[ebparty->GetName()] = ebparty;
			}
			BattleMechanics->Init();

			if (PlayerBattleParty.get() != nullptr && TurnGen.get() != nullptr)
			{
				for(auto it = PlayerBattleParty->GetPartyMembers().begin(); it != PlayerBattleParty->GetPartyMembers().end(); ++it)
				{
					TurnGen->TrackCharacter(it->second.get());
				}
				for (auto it = EnemyBattleParties.begin(); it != EnemyBattleParties.end(); ++it)
				{
					for (auto eparty = it->second->GetPartyMembers().begin(); eparty != it->second->GetPartyMembers().end(); ++eparty)
					{
						TurnGen->TrackCharacter(eparty->second.get());
					}
				}
			}

			auto prevMode = TurnGen->GetGeneratorMode();
			TurnGen->SetGeneratorMode(BattleMode::Sim);
			TurnGen->FillQueue(25);
			TurnGen->SetGeneratorMode(prevMode);

		}

		void BattleField::PostBattlePhase()
		{

		}

		Components::Component* BattleField::GetComponent(const std::string& index)
		{
			if (index == "Mechanics")
				return BattleMechanics.get();
			else
				return Entity::GetComponent(index);
		}

		void BattleField::AddEnemyParty( Character::bparty_ptr basePart, battleparty_ptr btlParty, const std::string& index, bool prepCharacters)
		{
			EnemyParties[index] = basePart;
			EnemyBattleParties[index] = btlParty;

			if (prepCharacters)
			{
				for (auto it = basePart->GetPartyMembers().begin(); it != basePart->GetPartyMembers().end(); ++it)
				{
					auto btlcp = it->second->GetComponentAs<BattleCharacterComponent*>(BattleCharacterComponentIndex);
					if (btlcp != nullptr)
					{
						BattleMechanics->ReadyCharacter(*(it->second), *btlcp, *this);
					}
				}
			}
			
		}


		void BattleField::AddEnemyParty( Character::bparty_ptr basePart, const std::string& index, bool prepCharacters)
		{
			/*EnemyParties[index] = basePart;
			EnemyBattleParties[index] = btlParty;*/

			battleparty_ptr bparty(new BattleParty(index));
			for (auto member = basePart->GetPartyMembers().begin(); member != basePart->GetPartyMembers().end(); ++member)
			{
				auto bcomp = (member->second)->GetComponentSmartPtrAs<BattleCharacterComponent>(BattleCharacterComponentIndex);
				if (bcomp != nullptr)
				{
					bparty->AddMember(bcomp, member->second->GetName());
				}
				else
				{
					boost::shared_ptr<BattleCharacterComponent> btlcomp(new BattleCharacterComponent(member->second.get(), bparty.get(), basePart.get()));
					member->second->RegisterComponent(BattleCharacterComponentIndex, btlcomp);
					member->second->SetParty(basePart.get());
					bparty->AddMember(btlcomp, member->second->GetName());
				}
			}
			AddEnemyParty(basePart, bparty, index, prepCharacters);
		}

		void BattleField::SetPlayerParty(Character::bparty_ptr bp)
		{
			PlayerParty = bp;
		}

		void BattleField::SetPlayerParty(battleparty_ptr btlp)
		{
			PlayerBattleParty = btlp;
		}

		void BattleField::SetPlayerParty(Character::bparty_ptr bp, battleparty_ptr btlp)
		{
			PlayerParty = bp;
			PlayerBattleParty = btlp;
		}

		Character::bparty_ptr BattleField::GetPlayerParty() const
		{
			return PlayerParty;
		}

		battleparty_ptr BattleField::GetBattlePlayerParty() const
		{
			return PlayerBattleParty;
		}

		Character::bparty_ptr BattleField::GetEnemyParty(const std::string& index) const
		{
			auto it = EnemyParties.find(index);
			if (it != EnemyParties.end())
			{
				return it->second;
			}
			return Character::bparty_ptr();
		}

		battleparty_ptr BattleField::GetBattleEnemyParty(const std::string& index) const
		{
			auto it = EnemyBattleParties.find(index);
			if (it != EnemyBattleParties.end())
			{
				return it->second;
			}
			return battleparty_ptr();
		}

		Mechanics& BattleField::GetMechanics()
		{
			return *BattleMechanics.get();
		}

		TurnGenerator* BattleField::GetTurnGenerator()
		{
			return TurnGen.get();
		}

		SpawnPool* BattleField::GetSpawnPool()
		{
			return SpawningPool.get();
		}

		void BattleField::HandleQueueModified(TurnGenerator& gen, BattleMode mode)
		{
			if (mode == BattleMode::Real)
			{
				//ActiveBattleCharacter = *(gen.GetTurnQueue(mode).begin());
				//ActiveCharacter = dynamic_cast<Character::BaseCharacter*>(ActiveBattleCharacter->GetOwner());
			}
		}

		void BattleField::StartCharacterTurn(Character::BaseCharacter& character)
		{
			//BattleMechanics->StartCharacterTurn(*ActiveCharacter, *ActiveBattleCharacter);
			//BattleMechanics->StartCharacterTurn(character);
		}

		void BattleField::StartCharacterTurn()
		{
			BattleMechanics->StartCharacterTurn(*ActiveCharacter, *ActiveBattleCharacter);
			//BattleMechanics->StartCharacterTurn(character);
		}

		void BattleField::EndCharacterTurn(Character::BaseCharacter& character)
		{
			//BattleMechanics->EndCharacterTurn(character);
		}

		void BattleField::EndCharacterTurn()
		{
			if (ActiveBattleCharacter != nullptr && ActiveCharacter != nullptr)
			{
				BattleMechanics->EndCharacterTurn(*ActiveCharacter, *ActiveBattleCharacter);

				for (auto it = TurnGen->GetTurnQueue(BattleMode::Real).begin(); it != TurnGen->GetTurnQueue(BattleMode::Real).end(); ++it)
				{
					if (*ActiveBattleCharacter == *(*it))
					{
						TurnGen->GetTurnQueue(BattleMode::Real).erase(it);
						ActiveBattleCharacter = nullptr;
						ActiveCharacter = nullptr;
						break;
					}
				}
				auto mode = TurnGen->GetGeneratorMode();
				TurnGen->SetGeneratorMode(BattleMode::Sim);
				TurnGen->PushRealToSim();
				for (auto it = TurnGen->GetTurnQueue(BattleMode::Real).begin(); it != TurnGen->GetTurnQueue(BattleMode::Real).end(); ++it)
				{
					(*it)->IncrementTimer(MaxTimer);
				}
				TurnGen->ClearQueue(BattleMode::Sim);
				TurnGen->FillQueue(25);
				TurnGen->SetGeneratorMode(mode);
			}
			
			if (ActiveBattleCharacter == nullptr && TurnGen->GetTurnQueue(BattleMode::Real).size() > 0)
			{
				ActiveBattleCharacter = *(TurnGen->GetTurnQueue(BattleMode::Real).begin());
				ActiveCharacter = dynamic_cast<Character::BaseCharacter*>(ActiveBattleCharacter->GetOwner());
				BattleMechanics->StartCharacterTurn(*ActiveCharacter, *ActiveBattleCharacter);
			}
		}
		/*bfield_ptr MakeDefaultBattleField()
		{
			auto field = boost::make_shared<BattleField>();
			return field;
		}
		boost::shared_ptr<BattleField> MakeDefaultBattleField(Character::bparty_ptr playerParty, Character::bparty_ptr enemyParty)
		{
			auto field = boost::make_shared<BattleField>(playerParty, enemyParty);
			return field;
		}*/
	}
}