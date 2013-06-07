#pragma once

#ifndef _UPDATER_H_
#define _UPDATER_H_
#include <SFML/Config.hpp>
namespace Graphics
{
	class Updater
	{
	public:
		virtual void Update(const sf::Uint32 time, const float TimeScale = 1.0) 
		{

		}
		virtual void Update(const float time, const float TimeScale = 1.0)
		{
			Update(static_cast<sf::Uint32>(time * 0.001), TimeScale);
		}
		virtual ~Updater()
		{

		}
	};
}

#endif