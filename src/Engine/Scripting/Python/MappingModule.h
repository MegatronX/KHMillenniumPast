#pragma once

#include "ScriptHelpers.h"
#include <Mapping/TileMap.h>

using namespace Mapping;
using namespace boost::python;
namespace Scripting
{
	BOOST_PYTHON_MODULE(MappingModule)
	{
		class_<TileMap>("TileMap", init<>())
			//.def("GetExits", &TileMap::GetExits, return_value_policy<reference_existing_object>())
			.def("GetHeight", &TileMap::GetHeight)
			.def("GetLayer", &TileMap::GetLayer)
			.def("GetLayerCount", &TileMap::GetLayerCount)
			.def("GetName", &TileMap::GetName)
			.def("GetTileHeight", &TileMap::GetTileHeight)
			.def("GetTilesInX", &TileMap::GetTilesInX)
			.def("GetTilesInY", &TileMap::GetTilesInY)
			.def("GetTileWidth", &TileMap::GetTileWidth)
			.def("GetWidth", &TileMap::GetWidth)
			//.def("SnapToTiles", &TileMap::SnapToTiles)
			//.def("SnapToTiles", &TileMap::SnapToTiles)
			.def("SortCollisionLayers", &TileMap::SortCollisionLayers)
			.def("SortLayers", &TileMap::SortLayers)
			.def("ValidTile", &TileMap::ValidTile)
			.def("Walkable", (bool (TileMap::*)(int, int, int))&TileMap::Walkable, boost::python::arg("layer") = -9000)
			.def("Walkable", (bool (TileMap::*)(sf::Vector2<int>&, int))&TileMap::Walkable, boost::python::arg("layer") = -9000)
			//.def("", &TileMap:)
			;
		//bool Walkable(int x, int y, int layer = -9000);
		//bool Walkable(sf::Vector2<int> &xy, int layer = -9000);
	}
}