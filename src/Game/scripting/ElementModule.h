#pragma once
#ifndef _ELEMENTMODULE_H_
#define _ELEMENTMODULE_H_
#include <elements/Elements.h>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
using namespace boost::python;

namespace Game
{
	namespace Scripting
	{
		BOOST_PYTHON_MODULE(ElementModule)
		{
			enum_<Elements::Element>("Element")
				.value("Air", Elements::Element::Air)
				.value("Dark", Elements::Element::Dark)
				.value("Earth", Elements::Element::Earth)
				.value("Elementless", Elements::Element::Elementless)
				.value("Fire", Elements::Element::Fire)
				.value("Ice", Elements::Element::Ice)
				.value("Light", Elements::Element::Light)
				.value("SpaceTime", Elements::Element::SpaceTime)
				.value("Thunder", Elements::Element::Thunder)
				.value("Water", Elements::Element::Water)
				;
			class_<boost::unordered_map<Elements::Element, float> >("ElementWeightMap")
				.def(map_indexing_suite<boost::unordered_map<Elements::Element, float> >())
				;
		}
	}
}
#endif