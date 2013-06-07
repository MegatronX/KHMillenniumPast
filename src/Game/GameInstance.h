#pragma once
#ifndef _GAMEINSTANCE_H_
#define _GAMEINSTANCE_H_
#include <items/ItemDatabase.h>
#include <statuseffects/StatusEffectsLibrary.h>
#include <actions/ActionLibrary.h>
#include <character/CharacterDatabase.h>
#include <boost/signals2.hpp>
#include <boost/noncopyable.hpp>
#include <sfml/System.hpp>
#include <character/PlayerParty.h>
#include <gamestate/GameState.h>
#include <io\xml\pugixml.hpp>
#include <save/Save.h>
class Engine;
namespace Game
{
	enum GameDifficulty
	{
		Easy,
		Medium,
		Hard,
		Expert,
		Critical
	};

	extern boost::unordered_map<GameDifficulty, std::string> DifficultyNameMap;
	extern boost::unordered_map<std::string, GameDifficulty> NameDifficultyMap;

	typedef boost::signals2::signal<void()> GameReadySignal;
	class GameInstance : boost::noncopyable
	{
	public:

		GameInstance(Engine& engine, bool ThreadStart = true);
		Items::ItemDatabase& GetItemLibrary();
		StatusEffects::StatusEffectsLibrary& GetSELibrary();
		Actions::ActionsLibrary& GetActionLibrary();
		Character::CharacterDatabase& GetCharacterLibrary();
		boost::signals2::connection AddGameReadySignal(const GameReadySignal::slot_type& event);

		void MakeNewGame(const std::string& difficulty = "Standard");
		void LoadSave(const std::string& savefile, const std::string& savename);
		void SaveGame(const std::string& savefile, const std::string& savename);

		void PartySave(boost::shared_ptr<Character::PartyInterface<Character::BaseCharacter>> party, pugi::xml_node& PartyNode);
		void PartyLoad(boost::shared_ptr<Character::PartyInterface<Character::BaseCharacter>> party, pugi::xml_node& PartyNode);

		void InventorySave(Items::InventoryComponent& inv, pugi::xml_node& InventoryNode);
		void InventoryLoad(Items::InventoryComponent& inv, pugi::xml_node& InvenotryNode);

		void LoadProperties(Entity& entity, pugi::xml_node& PropertiesNode);

		Character::PlayerParty& GetPlayerParty();
		boost::shared_ptr<Character::PlayerParty> GetPlayerPartyPtr() const;
		//GameState& GetPlayerGameState();
	protected:
		void MakeGameInstance();
		void GenerateItems();
		void ReloadItemLibrary();

		void GenerateStatusEffects();
		void ReloadStatusEffectsLibrary();

		void GenerateActions();
		void ReloadActions();

		void GenerateEnemies();
		void ReloadEnemies();
	private:
		Items::ItemDatabase itemDB;
		StatusEffects::StatusEffectsLibrary SELib;
		Actions::ActionsLibrary ActLib;
		Character::CharacterDatabase CharacterDB;
		boost::shared_ptr<Character::PlayerParty> PParty;
		Engine* PrimaryEngine;
		GameReadySignal readySig;
		sf::Thread MakeThread;
		sf::Time SavedGameTime;
		sf::Clock GameTime;
		//CurrentGameState PlayerState;
		std::string SelectedDifficulty;

		pugi::xml_document XMLSaveFile;
	};

	extern GameInstance* ActiveInstance;// = nullptr;
}

#endif