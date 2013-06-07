#pragma once
#ifndef _ROCKETSYSTEMINTERFACE_H_
#define _ROCKETSYSTEMINTERFACE_H_

#include <Rocket/Core/SystemInterface.h>
#include <Rocket/Core/Input.h>
#include <SFML/Graphics.hpp>

namespace Graphics
{
	namespace RocketInterface
	{
		class RocketSystemInterface : public Rocket::Core::SystemInterface
		{
		public:
			Rocket::Core::Input::KeyIdentifier TranslateKey(sf::Keyboard::Key key);
			int GetKeyModifiers(sf::Window* window);
			float GetElapsedTime();
			bool LogMessage(Rocket::Core::Log::Type type, const Rocket::Core::String& message);
		private:
			sf::Clock timer;
		};
	}
}

#endif