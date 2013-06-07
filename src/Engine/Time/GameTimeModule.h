#pragma once
#ifndef _GAMETIMEMODULE_H_
#define _GAMETIMEMODULE_H_
#include <Time/ScalableClock.h>
namespace Time
{
	class GameTimeModule
	{
	public:
		GameTimeModule();
		sf::Uint32 GetGameElapsedTime();
		sf::Uint32 GetTrueElapsedTime() const;
	protected:
	private:
		ScalableClock PrimaryClock;
	};
}


#endif