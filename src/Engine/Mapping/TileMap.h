#pragma once
#ifndef _TILEDMAP_H_
#define _TILEDMAP_H_

#include <string>
#include <vector>
#include <list>
#include <mapping\Layer.h>
#include <mapping\AnimatedLayer.h>
#include <mapping\TileSet.h>
#include <mapping\AnimatedTileSet.h>
#include <Graphics/DrawInterface.h>
//#include <mapping\MapObject.h>
#include <boost\shared_ptr.hpp>
#include <boost\tuple\tuple.hpp>
#include <boost/unordered_map.hpp>
#include <sfml\Graphics.hpp>
#include <sfml\System.hpp>
#include <Compression\CompressionUtils.h>
#include <System/Input/InputInterface.h>
//#include <graphics/AnimatedSprite.h>
//#include <graphics/MapCharacterSprite.h>

//#include <Graphics\MapCharacterSprite.h>
namespace Cache
{
	enum GameStyle;
	enum World;
	enum ResourceClass;
}
enum CompType
{
	GZip,
	Zlib,
	NoCompression
};
class Engine;

/* MapExit Tuple Definition
1. Exit X-Coordinate
2. Exit Y-Coordinate
3. Exit LayerID Number
4. Target MapFile name
5. Target Map Name
6. New Map Starting X-Coordinate
7. New Map Starting Y-Coordinate
8. New Map Starting LayerID
9. Flags whether the exit parsed correctly
*/
typedef boost::tuple<int, int, int, std::string, std::string, int, int, int, bool> MapExit;

namespace Graphics
{
	namespace Screens
	{
		class MapViewLayer;
	};
}
namespace Mapping
{
	/* MapExit Tuple Definition
	1. Exit X-Coordinate
	2. Exit Y-Coordinate
	3. Exit LayerID Number
	4. Target MapFile name
	5. Target Map Name
	6. New Map Starting X-Coordinate
	7. New Map Starting Y-Coordinate
	8. New Map Starting LayerID
	9. Flags whether the exit parsed correctly
	*/
	/*typedef boost::tuple<int, int, int, std::string, std::string, int, int, int, bool> MapExitOld;

	struct MapExit_
	{
		MapExit_(int x, int y, int layer, std::string& mfile, std::string& mname, int nx, int ny, int nl, bool parsed) :
			x(x), y(y), layer(layer), mapfile(mfile), mapname(mname), newx(nx), newy(ny), newlayer(nl), parsed(parsed)
		{

		}
		int x;
		int y;
		int layer;
		std::string mapfile;
		std::string mapname;
		int newx;
		int newy;
		int newlayer;
		bool parsed;
	};*/

	enum StringEncoding
	{
		Base64,
		NoEncoding
	};
	class TileMap : public ::Input::InputInterface, public ::Graphics::DrawInterface
	{
	public:
		TileMap();
		TileMap(const std::string &name, int tilesWide, int tilesHigh, int tilewidth, int tileheight);
		TileMap(const std::string &file, const std::string &name, Engine* engine);
		std::string GetName() const;
		int GetWidth() const;
		int GetHeight() const;
		int GetTilesInX() const;
		int GetTilesInY() const;
		int GetTileWidth() const;
		int GetTileHeight() const;
		int GetLayerCount() const;
		layer_ptr GetLayer(int index) const;

		void AddLayer(layer_ptr layer, int insertAt = -1, bool active = true);
		void AddAnimatedLayer(anim_layer_ptr layer, int insertAt = -1, bool active = true);
		void AddCollisionLayer(col_layer_ptr layer, int insertAt = -1, bool active = true);

		void AddTileSet(tileset_ptr set);
		void AddAnimatedTileSet(anim_tile_ptr set);

		bool Walkable(int x, int y, int layer = -9000);
		bool Walkable(sf::Vector2<int> &xy, int layer = -9000);
		bool ValidTile(int x, int y);
		//void AddMapObject(mapobj_ptr &mapObj);
		//Visualizer
		/*
		virtual void Draw(sf::RenderWindow &window);
		
		virtual void Draw(sf::RenderWindow &window, sf::Shader &shader);
		*/
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual void Update(const sf::Uint32 time, const float timescale = 1.0, bool elapsed = true);
		virtual void Update(const float time, const float TimeScale, bool elapsed = true);

		static TileMap* LoadMapFromXMLFile(const std::string &file, std::string &mapName);
		static boost::shared_ptr<TileMap> LoadMapFromXML(std::string &file, std::string &mapName);
		void SortLayers();
		void SortCollisionLayers();
		sf::Vector2f SnapToTiles(const sf::Vector2<float> &coordinates) const;
		sf::Vector2f SnapToTiles(const sf::Vector2<int> &coordinates) const;

		const std::string& GetMapProperty(const std::string& index) const;
		bool AddMapProperty(const std::string& index, const std::string& val, const bool overwriteExisting = true);
		//bool IsAnExit(int x, int y, int layer);

		friend class Graphics::Screens::MapViewLayer;
		virtual ~TileMap();
	protected:
		bool LoadMap(const std::string &file, const std::string &name, bool clear = true);
		//std::list<mapobj_ptr> MapObjects;
		
		std::map <std::string, std::string> MapProperties;
		
		//std::vector<MapExit>& GetExits();
		//std::vector<MapExit> MapExits;
		Engine* PrimaryEngine;

		sf::Uint32 targetTime;
		sf::Uint32 lastUpdate;
		int offsetX, offsetY, width, height, tilesInX, tilesInY, tileWidth, tileHeight;
		std::string name;

		std::vector<layer_ptr> layers;
		std::vector<anim_layer_ptr> animatedLayers; //layers to update. Need to be in animated layers as well
		std::vector<col_layer_ptr> collisionLayers;
		std::vector<tileset_ptr> tileSets;
		std::vector<anim_tile_ptr> animatedTileSets; //Animated layers are in both layer and animatedLayers. Animated layers is only inspected on update
	private:
		
	};

	typedef boost::shared_ptr<TileMap> map_ptr;


}





#endif
