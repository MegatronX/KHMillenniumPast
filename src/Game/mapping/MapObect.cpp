#include "MapObject.h"
#include <Mapping/MapObjectVisualizer.h>

namespace Game
{
	namespace Mapping
	{
		MapObject::MapObject(const std::string& objectName, int x, int y, int layer) : MapTilePosition(x, y, layer), Entity(objectName, EntityTypes::TileMapEntity)
		{

		}

		MapObject::MapObject(const std::string& objectName, const sf::Vector3i& pos) : MapTilePosition(pos), Entity(objectName, EntityTypes::TileMapEntity)
		{

		}

		MapObject::RawClonePtr MapObject::RawClone() const
		{
			return MapObject::RawClonePtr(new MapObject(*this));
		}

		int MapObject::GetX() const
		{
			return MapPosition.x;
		}
		int MapObject::GetY() const
		{
			return MapPosition.y;
		}
		int MapObject::GetLayer() const
		{
			return MapPosition.z;
		}

		MapObject::~MapObject()
		{

		}
		/*bool MapObject::IsValid() const
		{
			return Interactable;
		}
		void MapObject::SetValid(bool valid)
		{
			Interactable = valid;
		}*/
		/*MapObjectVisualizer* MapObject::GenerateVisualizer()
		{
			return new MapObjectVisualizer(this);
		}*/
	}
}