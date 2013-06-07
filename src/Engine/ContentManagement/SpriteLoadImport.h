#pragma once
#ifndef _SPRITELOADIMPORT_H_
#define _SPRITELOADIMPORT_H_

#include <string>
#include <boost/unordered_map.hpp>
#include <sfml/Graphics.hpp>
namespace Content
{
	class SpriteLoadImport
	{
	public:
	private:
		boost::unordered_map<int, std::pair<sf::Vector2f, sf::Vector2f> > Frames;
		boost::unordered_map<std::string, std::vector<std::pair<int, float>>> AnimationSequences;//Anim Name, Frame List <frame #, relative duration>
	};
}

#endif