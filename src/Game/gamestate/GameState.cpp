#include "GameState.h"

namespace Game
{

	const std::string& GameState::GetDifficulty() const
	{
		return GameDifficulty;
	}
	void GameState::SetDifficulty(const std::string& difficulty)
	{
		GameDifficulty = difficulty;
	}

	bool GameState::HasFlag(const std::string& flag) const
	{
		auto fi = GameFlags.find(flag);
		return (fi != GameFlags.end() && fi->second);
	}
	bool GameState::HasFlag(const std::string& flag, bool& found)
	{
		auto fi = GameFlags.find(flag);
		found = (fi != GameFlags.end());
		return found && fi->second;
	}
	void GameState::SetFlag(const std::string& flag)
	{
		GameFlags[flag] = true;
	}
	void GameState::SetFlag(const std::string& flag, const bool set)
	{
		GameFlags[flag] = set;
	}

	PlayerParty& GameState::GetPlayerParty() const
	{
		return PParty;
	}
}