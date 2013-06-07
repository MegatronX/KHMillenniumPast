#include "GameTimeModule.h"

namespace Time
{
	GameTimeModule::GameTimeModule() : PrimaryClock()
	{

	}
	sf::Uint32 GameTimeModule::GetGameElapsedTime()
	{
		return PrimaryClock.GetElapsedGameTime();
	}
	sf::Uint32 GameTimeModule::GetTrueElapsedTime() const
	{
		return PrimaryClock.GetElapsedRealTime();
	}
}