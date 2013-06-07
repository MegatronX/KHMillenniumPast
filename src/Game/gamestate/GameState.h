#pragma once

/*
*  Represents the current state of a player's game. Dumps to/from save files
*  Stores all the data needed to determine the player's progress
*
*
*
*/

#include <string>
#include <boost/unordered_map.hpp>
#include <character/PlayerParty.h>
#include <SFML/Graphics.hpp>
namespace Game
{
	class GameInstance;
	class GameState
	{
	public:
		const std::string& GetDifficulty() const;
		void SetDifficulty(const std::string& difficulty);

		bool HasFlag(const std::string& flag) const;
		bool HasFlag(const std::string& flag, bool& found);
		void SetFlag(const std::string& flag);
		void SetFlag(const std::string& flag, const bool set = true);

		Character::PlayerParty& GetPlayerParty() const;

		sf::Vector2i GetTilePosition() const;
		void SetTilePosition(const sf::Vector2i& pos);

		const std::string& GetMapMajor();
		const std::string& GetMapMinor();

		void SetMapLocation(const std::string& major, const std::string& minor);

		unsigned int GetMunny() const;
		void IncrementMunny(const unsigned int inc);
	protected:
		void SetMunny(const unsigned int inc);
		Character::PlayerParty PParty;
	private:
		int Munny;
		std::string MapMajor;
		std::string MapMinor;
		sf::Vector2i TilePosition;
		std::string GameDifficulty;
		boost::unordered_map<std::string, bool> GameFlags;
		friend class GameInstance;
	};
}