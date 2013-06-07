#include "MapChest.h"
#include <Mapping/MapObjectVisualizer.h>
#include <boost/assign.hpp>
namespace Game
{
	namespace Mapping
	{
		/*
		boost::unordered_map<Element, std::string> ElementNameMap = boost::assign::map_list_of
		(Element::Air, string("Air"))
		(Element::Dark, string("Dark"))
		(Element::Earth, string("Earth"))
		(Element::Elementless, string("Elementless"))
		(Element::Fire, string("Fire"))
		(Element::Ice, string("Ice"))
		(Element::Light, string("Light"))
		(Element::SpaceTime, string("SpaceTime"))
		(Element::Thunder, string("Thunder"))
		(Element::Water, string("Water"))
		;
		*/

		boost::unordered_map<std::string, std::string> MapChestComponent::StyleSpriteMapping = boost::assign::map_list_of
			(std::string("Default"), std::string("Air"))

			;

		MapChestComponent::MapChestComponent(MapObject* owner, const std::string& name, bool active) : MapEventComponent(owner, name, active)
		{

		}

		/*MapChest::MapChest(const std::string& name, sf::Vector3i Position, const std::string style) : MapObject(name, Position), ChestStyle(style)
		{
		}

		MapChest::MapChest(const std::string& name, const int x, const int y, const int layer, const std::string style) : MapObject(name, x, y, layer), ChestStyle(style)
		{

		}*/

		MapChestComponent::RawClonePtr MapChestComponent::RawClone() const
		{
			return MapChestComponent::RawClonePtr(new MapChestComponent(*this));
		}

		/*MapObjectVisualizer* MapChest::GenerateVisualizer()
		{
			auto chestVis = new MapObjectVisualizer(this);
			auto styler = StyleSpriteMapping.find(ChestStyle);
			if(styler == StyleSpriteMapping.end())
			{
				styler = StyleSpriteMapping.find("default");
			}
			if (styler != StyleSpriteMapping.end())
			{

			}
			//chestVis->

			return chestVis;
		}*/
	}
}