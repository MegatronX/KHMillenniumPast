#pragma once
#ifndef _CAHRACTERSPAWNER_H_
#define _CAHRACTERSPAWNER_H_ 

#include <components/Component.h>
#include <character/Party.h>
#include <character/BaseCharacter.h>
#include <character/CharacterDatabase.h>
#include <battle/BattleCharacterComponent.h>
#include <boost/lexical_cast.hpp>

namespace Game
{
	namespace Character
	{
		struct EntryID;
	}
}

namespace boost {
	// this would be picked up but is slightly evil
	std::size_t hash_value(const Game::Character::EntryID& entry);
}

namespace Game
{
	namespace Character
	{
		class GameInstance;

		struct EntryID
		{
			EntryID() : Level(0)
			{

			}
			EntryID(const std::string& name, const int lv) : Name(name), Level(lv)
			{

			}
			bool operator==(const EntryID& cmp) const
			{
				return Name == cmp.Name && Level == cmp.Level;
			}
			bool operator!=(const EntryID& cmp) const
			{
				return !(*this == cmp);
			}
			std::string Name;
			int Level;
		};
		class CharacterSpawner : public Components::Component
		{
		public:
			CharacterSpawner(Entity* owner) : Component(owner, owner != nullptr ? owner->GetName() + "CharacterSpawner" : "NoOwnerCharacterSpawner", "CharacterSpawner")
			{


			}

			Character::bparty_ptr DummySpawn()
			{
				boost::unordered_map<EntryID, int> spawns;
				spawns[EntryID("Red Dragon", 56)] = 1;
				//spawns[EntryID("Neo Shadow", 9)] = 1;
				return CreatePartyPtr("Default", spawns, false);
			}

			virtual PartyInterface<BaseCharacter> CreateParty(const std::string& PartyName, const boost::unordered_map<EntryID, int>& Spawns, bool PerformBattlePrep = true, const std::vector<Character::EntryID>& SpawnOrder = std::vector<Character::EntryID>())
			{
				PartyInterface<BaseCharacter> spawnParty(PartyName);

				if (CharacterDB != nullptr)
				{
					boost::unordered_map<std::string, int> NameCounter;
					boost::unordered_map<std::string, boost::shared_ptr<BaseCharacter> > SingleNamed;
					std::vector<boost::shared_ptr<BaseCharacter> > tempList;
					if (SpawnOrder.size() > 0)
					{
						//spawnParty.
					}
					else
					{
						for (auto spawn = Spawns.begin(); spawn != Spawns.end(); ++spawn)
						{
							for (int i = 0; i < spawn->second; ++i)
							{
								auto character = CharacterDB->GetCharacter(spawn->first.Name, spawn->first.Level);
								if (character->GetValid())
								{
									character->SetProperty("Type", character->GetName());
									auto it = NameCounter.find(character->GetName());
									if (it != NameCounter.end())
									{
										if (it->second < 2)
										{
											auto single = SingleNamed.find(spawn->first.Name);
											auto newName = single->second->GetName() + " " + boost::lexical_cast<std::string>(0);
											single->second->SetName(newName);
											single->second->SetProperty("DisplayName", newName);
											SingleNamed.erase(single);
										}
										auto newName = spawn->first.Name + " " + boost::lexical_cast<std::string>(it->second);
										character->SetName(newName);
										character->SetProperty("DisplayName", newName);
										
										it->second += 1;
									}
									else
									{
										SingleNamed[character->GetName()] = character;
										NameCounter[character->GetName()] = 1;
									}
								}
								tempList.push_back(character);
							}
						}
					}
					if (tempList.size() > 0)
					{
						for (auto temp = tempList.begin(); temp != tempList.end(); ++temp)
						{
							spawnParty.AddMember(*temp, (*temp)->GetName());
							if (PerformBattlePrep)
							{
								auto btcomp = boost::shared_ptr<Battle::BattleCharacterComponent>(new Battle::BattleCharacterComponent((*temp).get(), nullptr, &spawnParty));
								(*temp)->RegisterComponent(Battle::BattleCharacterComponentIndex, btcomp);
							}
						}
					}
				}
				else
				{

				}

				return spawnParty;
			}

			virtual Character::bparty_ptr CreatePartyPtr(const std::string& PartyName, const boost::unordered_map<EntryID, int>& Spawns, bool PerformBattlePrep = true, const std::vector<Character::EntryID>& SpawnOrder = std::vector<Character::EntryID>())
			{
				bparty_ptr spawnParty(new BaseParty(PartyName));

				if (CharacterDB != nullptr)
				{
					boost::unordered_map<std::string, int> NameCounter;
					boost::unordered_map<std::string, boost::shared_ptr<BaseCharacter> > SingleNamed;
					std::vector<boost::shared_ptr<BaseCharacter> > tempList;
					if (SpawnOrder.size() > 0)
					{
						//spawnParty.
					}
					else
					{
						for (auto spawn = Spawns.begin(); spawn != Spawns.end(); ++spawn)
						{
							for (int i = 0; i < spawn->second; ++i)
							{
								auto character = CharacterDB->GetCharacter(spawn->first.Name, spawn->first.Level);
								if (character->GetValid())
								{
									character->SetProperty("Type", character->GetName());
									auto it = NameCounter.find(character->GetName());
									if (it != NameCounter.end())
									{
										if (it->second < 2)
										{
											auto single = SingleNamed.find(spawn->first.Name);
											auto newName = single->second->GetName() + " " + boost::lexical_cast<std::string>(0);
											single->second->SetName(newName);
											single->second->SetProperty("DisplayName", newName);
											SingleNamed.erase(single);
										}
										auto newName = spawn->first.Name + " " + boost::lexical_cast<std::string>(it->second);
										character->SetName(newName);
										character->SetProperty("DisplayName", newName);

										it->second += 1;
									}
									else
									{
										SingleNamed[character->GetName()] = character;
										NameCounter[character->GetName()] = 1;
									}
								}
								tempList.push_back(character);
							}
						}
					}
					if (tempList.size() > 0)
					{
						for (auto temp = tempList.begin(); temp != tempList.end(); ++temp)
						{
							spawnParty->AddMember(*temp, (*temp)->GetName());
							if (PerformBattlePrep)
							{
								auto btcomp = boost::shared_ptr<Battle::BattleCharacterComponent>(new Battle::BattleCharacterComponent((*temp).get(), nullptr, spawnParty.get()));
								(*temp)->RegisterComponent(Battle::BattleCharacterComponentIndex, btcomp);
							}
						}
					}
				}
				else
				{

				}

				return spawnParty;
			}

			static void SetCharacterDatabase(CharacterDatabase* db)
			{
				CharacterDB = db;
			}

			static CharacterDatabase* GetCharacterDatabase()
			{
				return CharacterDB;
			}
		protected:
			friend class GameInstance;
			static CharacterDatabase* CharacterDB;
		};
	}
}

#endif