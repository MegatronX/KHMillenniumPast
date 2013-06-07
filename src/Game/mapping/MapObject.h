#pragma once
#include <Entity.h>
#include <SFML/Graphics.hpp>
namespace Game
{
	namespace Mapping
	{
		class GameMap;
		class MapObjectVisualizer;
		class MapObject : public Entity
		{
		public:
			MapObject(const std::string& objectName = "MapObject", int x = 0, int y = 0, int layer = 0);

			MapObject(const std::string& objectName = "MapObject", const sf::Vector3i& pos = sf::Vector3i(0, 0, 0));

			MapObject::RawClonePtr RawClone() const override;

			int GetX() const;
			int GetY() const;
			int GetLayer() const;

			/*bool IsValid() const;
			void SetValid(bool valid = true);*/

			//virtual MapObjectVisualizer* GenerateVisualizer();

			sf::Vector3i MapTilePosition;
			sf::Vector3f MapPosition;
			virtual ~MapObject();
		};
	}
}