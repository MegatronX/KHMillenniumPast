#include "GameInstance.h"
#include <Engine.h>
#include <statuseffects/StatusEffectsManager.h>
#include <items/Inventory.h>
#include <items/Inventory.h>
#include <items\Item.h>
#include <boost/assign.hpp>
#include <character/CharacterSpawner.h>
//#include <Scripting/ItemModule.h>
//#include <Scripting/GameScripting.h>
//#include <Scripting/ItemModule.h>
using namespace std;
namespace Game
{

	GameInstance* ActiveInstance = nullptr;

	boost::unordered_map<GameDifficulty, std::string> DifficultyNameMap = boost::assign::map_list_of
		(GameDifficulty::Easy, string("Easy"))
		(GameDifficulty::Medium, string("Medium"))
		(GameDifficulty::Hard, string("Hard"))
		(GameDifficulty::Expert, string("Expert"))
		(GameDifficulty::Critical, string("Critical"))
		;

	boost::unordered_map<std::string, GameDifficulty> NameDifficultyMap = boost::assign::map_list_of
		(string("Easy"), GameDifficulty::Easy)
		(string("Beginner"), GameDifficulty::Easy)
		(string("Standard"), GameDifficulty::Easy)
		(string("Medium"), GameDifficulty::Easy)
		;


	void GameInstance::MakeGameInstance()
	{
		PrimaryEngine->GetPythonScripter().AddScriptObject<GameInstance>("ActiveGame", *this, PrimaryEngine->GetPythonScripter().GetModule("GameInstanceModule"));
		Items::Item::ItemDB = &(this->itemDB);

		//Initalize others

		try
		{
			GenerateItems();
			GenerateStatusEffects();
			GenerateActions();
			GenerateEnemies();
			readySig();
			ActiveInstance = this;
		}
		catch (boost::python::error_already_set)
		{
			PyErr_Print();
		}
	}
	GameInstance::GameInstance(Engine& engine, bool ThreadStart) : PrimaryEngine(&engine), MakeThread(&GameInstance::MakeGameInstance, this), SelectedDifficulty("Standard"), PParty(new Character::PlayerParty())
	{
		if (ThreadStart)
		{
			MakeThread.launch();
		}
		else
		{
			MakeGameInstance();
		}
	}
	void GameInstance::ReloadItemLibrary()
	{
		itemDB.EmptyDatabase();
		PrimaryEngine->GetPythonScripter().RunFile(std::string("Items.py"));
	}
	void GameInstance::GenerateItems()
	{
		PrimaryEngine->GetPythonScripter().AddScriptObject<Items::ItemDatabase>("ItemLibrary", itemDB, PrimaryEngine->GetPythonScripter().GetModule("ItemModule"));
		PrimaryEngine->GetPythonScripter().RunFile(std::string("Items.py"));
	}
	void GameInstance::GenerateStatusEffects()
	{
		StatusEffects::StatusEffectsManager::SELibrary = &SELib;
		PrimaryEngine->GetPythonScripter().AddScriptObject<StatusEffects::StatusEffectsLibrary>("StatusEffectsLibrary", SELib, PrimaryEngine->GetPythonScripter().GetModule("StatusEffectsModule"));
		PrimaryEngine->GetPythonScripter().RunFile(std::string("StatusEffects.py"));
	}
	void GameInstance::ReloadStatusEffectsLibrary()
	{

	}

	void GameInstance::GenerateActions()
	{
		PrimaryEngine->GetPythonScripter().AddScriptObject<Actions::ActionsLibrary>("ActionLibrary", ActLib, PrimaryEngine->GetPythonScripter().GetModule("ActionModule"));
		PrimaryEngine->GetPythonScripter().RunFile(std::string("Actions.py"));
	}

	void GameInstance::ReloadActions()
	{

	}

	void GameInstance::GenerateEnemies()
	{
		//using namespace Character;
		Character::CharacterSpawner::SetCharacterDatabase(&CharacterDB);
		PrimaryEngine->GetPythonScripter().AddScriptObject<Character::CharacterDatabase>("EnemyLibrary", CharacterDB, PrimaryEngine->GetPythonScripter().GetModule("CharacterModule"));
		PrimaryEngine->GetPythonScripter().RunFile(std::string("Enemies.py"));
	}

	void GameInstance::ReloadEnemies()
	{
	
	}

	void GameInstance::MakeNewGame(const std::string& difficulty)
	{
		SelectedDifficulty = difficulty;
		PrimaryEngine->GetScreenManager().ClearStacks();
		//PParty.RegisterComponent("Inventory Component", boost::shared_ptr<Items::InventoryComponent>(new Items::InventoryComponent(&PParty)), true);
		PrimaryEngine->GetPythonScripter().RunFile("MakeNewGame.py");

	}
	void GameInstance::PartySave(boost::shared_ptr<Character::PartyInterface<Character::BaseCharacter>> party, pugi::xml_node& PartyNode)
	{

	}
	void GameInstance::PartyLoad(boost::shared_ptr<Character::PartyInterface<Character::BaseCharacter>> party, pugi::xml_node& PartyNode)
	{
		using namespace pugi;
		using namespace Character;
		if (party.get() != nullptr)
		{
			for (auto character = PartyNode.child("PartyMember"); character; character = character.next_sibling("PartyMember"))
			{
				auto name = character.attribute("name").value();
				unsigned int level = character.attribute("level").as_uint();
				auto charPtr = boost::make_shared<BaseCharacter>(name);
				charPtr->SetLevel(level);
				StatsManager& mng = charPtr->GetStatsManager();
				auto StatSets = character.child("Stats");
				int currentHP = 0;
				int currentMP = 0;
				int currentSP = 0;
				if (StatSets)
				{
					for (auto SSet = StatSets.first_child(); SSet; SSet = SSet.next_sibling())
					{
						auto StatSetName = std::string(SSet.name());
						if (StatSetName == std::string("Base"))
						{
							for (auto targetStat = SSet.first_child(); targetStat; targetStat = targetStat.next_sibling())
							{
								auto statit = NameStatLookup.find(targetStat.name());
								if (statit != NameStatLookup.end())
								{
									mng.SetBaseStat(statit->second, targetStat.attribute("value").as_int());//.BaseStats.SetStat(statit->second, targetStat.attribute("value").as_int());
								}
							}
						}
						else if (StatSetName == std::string("PermanentAdders"))
						{
							for (auto targetStat = SSet.first_child(); targetStat; targetStat = targetStat.next_sibling())
							{
								auto statit = NameStatLookup.find(targetStat.name());
								if (statit != NameStatLookup.end())
								{
									mng.SetPermanentStatBoost(statit->second, targetStat.attribute("value").as_int());//.PermanentStatBoosts.SetStat(statit->second, targetStat.attribute("value").as_int());
									//mng.BaseStats.SetStat(statit->second, targetStat.attribute("value").as_int());
								}
							}
						}
						else if (StatSetName == std::string("PermanentMultipliers"))
						{
							for (auto targetStat = SSet.first_child(); targetStat; targetStat = targetStat.next_sibling())
							{
								auto statit = NameStatLookup.find(targetStat.name());
								if (statit != NameStatLookup.end())
								{
									mng.SetPermanentStatMultiplier(statit->second, targetStat.attribute("value").as_float());
									//mng.SetPermanentStatBoost(statit->second, targetStat.attribute("value").as_int());//.PermanentStatBoosts.SetStat(statit->second, targetStat.attribute("value").as_int());
									//mng.BaseStats.SetStat(statit->second, targetStat.attribute("value").as_int());
								}
							}
						}
						else if (StatSetName == std::string("Current"))
						{
							for (auto targetStat = SSet.first_child(); targetStat; targetStat = targetStat.next_sibling())
							{
								auto statit = NameStatLookup.find(targetStat.name());
								if (statit != NameStatLookup.end())
								{
									if (statit->second == Stat::HP)
									{
										currentHP = targetStat.attribute("value").as_int();
									}
									else if (statit->second == Stat::MP)
									{
										currentMP = targetStat.attribute("value").as_int();
									}
									else if (statit->second == Stat::SP)
									{
										currentSP = targetStat.attribute("value").as_int();
									}
								}
							}
						}
						else
						{
							std::string statSetName(StatSetName);
							std::string type(SSet.attribute("type").value());
							if (type == "Mult" || type == "Multiplier" || type == "Multipliers")
							{
								Components::StatComponent<float> mults;
								for (auto targetStat = SSet.first_child(); targetStat; targetStat = targetStat.next_sibling())
								{
									auto statit = NameStatLookup.find(targetStat.name());
									if (statit != NameStatLookup.end())
									{
										mults.IncrementStat(statit->second, targetStat.attribute("value").as_float() - mults.GetStat(statit->second));
										//mng.SetBaseStat(statit->second, targetStat.attribute("value").as_int());//.BaseStats.SetStat(statit->second, targetStat.attribute("value").as_int());
									}
								}
								mng.AddAdditionalStatMultiplier(statSetName, mults);
							}
							else
							{
								Components::StatComponent<int> adds;
								for (auto targetStat = SSet.first_child(); targetStat; targetStat = targetStat.next_sibling())
								{
									auto statit = NameStatLookup.find(targetStat.name());
									if (statit != NameStatLookup.end())
									{
										adds.IncrementStat(statit->second, targetStat.attribute("value").as_int() - adds.GetStat(statit->second));
										//mng.SetBaseStat(statit->second, targetStat.attribute("value").as_int());//.BaseStats.SetStat(statit->second, targetStat.attribute("value").as_int());
									}
								}
								mng.AddAdditionalStatAdder(statSetName, adds);
							}
						}
					}
				}
				//Equipment Load Out here
				//Ability Load Out here

				//SE Load Out here

				//

				mng.SyncAllStats(false);
				mng.SetCurrentHP(currentHP);
				mng.SetCurrentMP(currentMP);
				mng.SetCurrentSP(currentSP);
				
				//LoadProperties(*charPtr, )
				auto PropertySet = character.child("Properties");
				LoadProperties(*charPtr, PropertySet);
				party->AddMember(charPtr, charPtr->GetName(), true);
				//charPtr
			}
			//End Party Nodes
		}
	}
	void GameInstance::InventorySave(Items::InventoryComponent& inv, pugi::xml_node& InventoryNode)
	{

	}
	void GameInstance::InventoryLoad(Items::InventoryComponent& inv, pugi::xml_node& InventoryNode)
	{
		for (auto item = InventoryNode.child("Item"); item; item = item.next_sibling("Item"))
		{
			auto itemName = item.attribute("name").value();
			auto itemCount = item.attribute("count").as_uint();
			inv.AddItem(itemName, itemCount);
		}
		for (auto item = InventoryNode.child("KeyItem"); item; item = item.next_sibling("KeyItem"))
		{
			auto itemName = item.attribute("name").value();
			auto itemCount = item.attribute("count").as_uint();
			inv.AddKeyItem(itemName, itemCount);
		}
	}
	void GameInstance::LoadSave(const std::string& savefile, const std::string& savename)
	{
		using namespace pugi;
		xml_parse_result result = XMLSaveFile.load_file(savefile.c_str());
		if (!result)
			std::cerr << "Save File Failed To Load. Error: " << result.description();
		else
		{
			std::string saveQuery = "/Saves/Save[@name=\'" + savename + "\']";

			auto QueriedSaveNode = XMLSaveFile.root().select_single_node(saveQuery.c_str());
			auto SaveNode = QueriedSaveNode.node();
			//Pull out time
			auto TimeNode = SaveNode.child("PlayTime");
			unsigned int timeHours = TimeNode.attribute("hours").as_uint();
			unsigned int timeMinutes = TimeNode.attribute("minutes").as_uint();
			unsigned int timeSeconds = TimeNode.attribute("seconds").as_uint();
			SavedGameTime = sf::seconds(static_cast<float>(timeSeconds) + static_cast<float>(timeMinutes) * 60.f + static_cast<float>(timeHours) * 3600.f);
			GameTime.restart();
			//Pull out munny
			auto MunnyNode = SaveNode.child("Munny");
			unsigned int munny = MunnyNode.attribute("value").as_uint();
			
			//Pull out location
			auto AreaNode = SaveNode.child("Area");
			//xml_node prop = properties.child("property"); prop; prop = prop.next_sibling("property")
			//Process Inventory
			auto InvNode = SaveNode.child("Inventory");
			if (InvNode)
			{
				InventoryLoad(PParty->GetInventory(), InvNode);
			}
			

			//Character Import
			auto CharacterNode = SaveNode.child("MainParty");
			PartyLoad(PParty, CharacterNode);
			
			//auto saveNode = XMLSaveFile.root().select_single_node();
			//for (xml_node Saves = XMLSaveFile.child("Saves"); )
		}
	}
	void GameInstance::SaveGame(const std::string& savefile, const std::string& savename)
	{
		using namespace pugi;
		xml_parse_result result = XMLSaveFile.load_file(savefile.c_str());
		if (!result)
			std::cerr << "Save File Failed To Load. Error: " << result.description();
		else
		{
		}
	}

	void GameInstance::LoadProperties(Entity& entity, pugi::xml_node& PropertiesNode)
	{
		if (PropertiesNode)
		{
			for (auto property = PropertiesNode.child("Property"); property; property = property.next_sibling("Property"))
			{
				std::string name(property.attribute("name").value());
				std::string value(property.attribute("value").value());
				entity.SetProperty(name, value);
			}
		}
	}

	Character::PlayerParty& GameInstance::GetPlayerParty()
	{
		return (*PParty);
	}

	boost::shared_ptr<Character::PlayerParty> GameInstance::GetPlayerPartyPtr() const
	{
		return PParty;
	}

	/*GameState& GameInstance::GetPlayerGameState()
	{
	return PlayerState;
	}*/
	Items::ItemDatabase& GameInstance::GetItemLibrary()
	{
		return itemDB;
	}
	StatusEffects::StatusEffectsLibrary& GameInstance::GetSELibrary()
	{
		return SELib;
	}
	Actions::ActionsLibrary& GameInstance::GetActionLibrary()
	{
		return ActLib;
	}
	Character::CharacterDatabase& GameInstance::GetCharacterLibrary()
	{
		return CharacterDB;
	}
	boost::signals2::connection GameInstance::AddGameReadySignal(const GameReadySignal::slot_type& event)
	{
		return readySig.connect(event);
	}
}