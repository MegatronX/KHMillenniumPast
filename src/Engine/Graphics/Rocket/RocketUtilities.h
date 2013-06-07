#pragma once
#ifndef _ROCKETUTIL_H_
#define _ROCKETUTIL_H_
#include <Rocket/Core.h>
#include <sfml/Graphics.hpp>
namespace Graphics
{
	Rocket::Core::String ColorToRGBARocketString(const sf::Color& color);

	sf::Color StringToColor(const Rocket::Core::String& colorString);

	sf::Color StringToColor(const std::string& colorString);
}

#endif