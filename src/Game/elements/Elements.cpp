#include "Elements.h"
#include <boost/assign.hpp>
using namespace std;
namespace Game
{
	namespace Elements
	{
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

		boost::unordered_map<std::string, Element> NameElementMap = boost::assign::map_list_of
			(string("Air"), Element::Air)
			(string("Dark"), Element::Dark)
			(string("Earth"), Element::Earth)
			(string("Elementless"), Element::Elementless)
			(string("Fire"), Element::Fire)
			(string("Ice"), Element::Ice)
			(string("Light"), Element::Light)
			(string("SpaceTime"), Element::SpaceTime)
			(string("Thunder"), Element::Thunder)
			(string("Water"), Element::Water)
			;
	}
}
