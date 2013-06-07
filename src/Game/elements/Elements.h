#pragma once
#ifndef _ELEMENTS_H_
#define _ELEMENTS_H_
#include <boost/unordered_map.hpp>
static const int ELEMENTCOUNT = 10;
static const double ElementDefenseFloor = -1;
static const double ElementDamageCeiling = 4;
namespace Game
{
	class Entity;
	namespace Elements
	{

		enum Element
		{
			Air = 1,
			Dark = 2,
			Earth = 4,
			Elementless = 8,
			Fire = 16,
			Ice = 32,
			Light = 64,
			SpaceTime = 128,
			Thunder = 256,
			Water = 512,
		};
		extern boost::unordered_map<Element, std::string> ElementNameMap;
		extern boost::unordered_map<std::string, Element> NameElementMap;
	}
}
#endif