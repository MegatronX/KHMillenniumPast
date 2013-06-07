#include "RocketUtilities.h"
#include <boost/lexical_cast.hpp>
namespace Graphics
{
	Rocket::Core::String ColorToRGBARocketString(const sf::Color& color)
	{
		return Rocket::Core::String(("rgba(" + boost::lexical_cast<std::string>((unsigned int)color.r) + ", " + 
			boost::lexical_cast<std::string>((unsigned int)color.g) + ", " +
			boost::lexical_cast<std::string>((unsigned int)color.b) + ", " +
			boost::lexical_cast<std::string>((unsigned int)color.a) + ")").c_str());
	}

	sf::Color StringToColor(const Rocket::Core::String& colorString)
	{
		return sf::Color::White;
	}

	sf::Color StringToColor(const std::string& colorString)
	{
		return sf::Color::White;
	}

}