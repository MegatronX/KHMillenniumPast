#include "TileMap.h"
#include <Engine.h>
#include <math.h>
#include <io\xml\pugixml.hpp>
#include <boost\algorithm\string.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <boost\algorithm\string_regex.hpp>
#include <Utilities/base64.h>
using namespace boost;

struct AnimTileSetProperties
{
	AnimTileSetProperties() : fps(4.0f), startingIndex(0)
	{
	}
	int startingIndex;
	std::string tileset;
	std::vector<std::string> tilesetImages;
	float fps;
};

namespace Mapping
{

	TileMap::TileMap()
	{

	}

	TileMap::TileMap(const std::string &file, const std::string &name, Engine* engine) : PrimaryEngine(engine)
	{
		using namespace pugi;
		xml_document mapDoc;

		xml_parse_result result = mapDoc.load_file(file.c_str());
		if (!result)
			std::cerr << "Map Failed To Load. Error: " << result.description();
		else
		{
			for(xml_node map = mapDoc.child("map"); map; map = mapDoc.next_sibling("map"))
			{
				int width, height, tilewidth, tileheight;
				width = map.attribute("width").as_int();
				height = map.attribute("height").as_int();
				tilewidth = map.attribute("tilewidth").as_int();
				tileheight = map.attribute("tileheight").as_int();
				this->tileHeight = tileheight;
				this->tileWidth = tilewidth;
				this->width = width * tilewidth;
				this->height = height * tileheight;
				this->tilesInX = width;
				this->tilesInY = height;
				//TileMap tilemap(mapName, width, height, tilewidth, tileheight);
				xml_node properties = map.child("properties");
				boost::unordered_map<std::string, AnimTileSetProperties> AnimTileSets;
				for (xml_node prop = properties.child("property"); prop; prop = prop.next_sibling("property"))
				{
					std::string name = prop.attribute("name").value();
					std::string value = prop.attribute("value").value();

					if (name == std::string("AnimateTileSet"))
					{
						std::vector<std::string> PropertyVals;
						boost::split(PropertyVals, value, boost::is_any_of("|"));
						AnimTileSetProperties animproperties;
						for (auto pval = PropertyVals.begin(); pval != PropertyVals.end(); ++pval)
						{
							boost::trim(*pval);
							std::vector<std::string> valset;
							boost::split(valset, *pval, boost::is_any_of(":"));
							if (valset.size() > 1)
							{

								for (auto val = valset.begin(); val != valset.end(); ++val)
								{
									boost::trim(*val);
								}
								std::string pname = valset[0];
								std::string animval = valset[1];
								if (pname == "fps")
								{
									animproperties.fps = boost::lexical_cast<float>(animval);
								}
								else if (pname == "startingindex")
								{
									animproperties.startingIndex = boost::lexical_cast<int>(animval);
								}
								else
								{
									std::vector<std::string> cycleset;
									boost::split(cycleset, animval, boost::is_any_of(","));
									animproperties.tileset = pname;
									for (auto cset = cycleset.begin(); cset != cycleset.end(); ++cset)
									{
										boost::trim(*cset);
										animproperties.tilesetImages.push_back(*cset);
									}
								}
							}
						}
						AnimTileSets[animproperties.tileset] = animproperties;
					}
					else
					{
						MapProperties[name] = value;
					}
				}

				for(xml_node tileset = map.child("tileset"); tileset; tileset = tileset.next_sibling("tileset"))
				{
					int firstGID, tstilewidth, tstileheight;
					std::string name = tileset.attribute("name").value();
					firstGID = tileset.attribute("firstgid").as_int();
					tstilewidth = tileset.attribute("tilewidth").as_int();
					tstileheight = tileset.attribute("tileheight").as_int();
					xml_node imageFile =  tileset.child("image");
					std::string imageSource = imageFile.attribute("source").value();
					std::vector<std::string> frags;
					boost::split(frags, imageSource, boost::is_any_of("."));
					std::string fileName;
					std::string extension;
					for (auto piece = frags.begin(); piece != frags.end(); ++piece)
					{
						auto next = piece;
						next++;
						if (next == frags.end())
						{
							extension = "." + *piece;
						}
						else
						{
							fileName += *piece;
						}
					}
					tileset_ptr tileset;
					auto it = AnimTileSets.find(name);
					if (it != AnimTileSets.end())
					{
						std::vector<boost::shared_ptr<sf::Texture> > textures;
						for (auto tileimage = it->second.tilesetImages.begin(); tileimage != it->second.tilesetImages.end(); ++tileimage)
						{
							frags.clear();
							boost::split(frags, *tileimage, boost::is_any_of("."));
							std::string animFileName;
							std::string animExtension;
							for (auto piece = frags.begin(); piece != frags.end(); ++piece)
							{
								auto next = piece;
								next++;
								if (next == frags.end())
								{
									animExtension = "." + *piece;
								}
								else
								{
									animFileName += *piece;
								}
							}
							textures.push_back(engine->GetContentManager().RequestTexture(animFileName, Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::TileSet, engine->GetTime(), animExtension.c_str()));
						}
						if (textures.size() > 0)
						{
							tileset = tileset_ptr(new AnimatedTileSet(name, firstGID, tstilewidth, tstileheight, textures, it->second.fps, it->second.startingIndex));
							AddTileSet(tileset);
						}
					}
					else
					{
						auto tileSetImage = engine->GetContentManager().RequestTexture(fileName, Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::TileSet, engine->GetTime(), extension.c_str());
						tileset = tileset_ptr(new TileSet(name, firstGID, tstilewidth, tstileheight, tileSetImage));
						AddTileSet(tileset);
					}
				}
				for(xml_node layer = map.child("layer"); layer; layer = layer.next_sibling("layer"))
				{
					std::string name;
					int lwidth, lheight;
					int drawOrder = 0;
					float opacity = 1;
					bool isCollision = false;
					CompType compression = CompType::NoCompression;
					StringEncoding encoding = StringEncoding::NoEncoding;
					std::vector<LayerProperty> layerPropertySet;
					boost::unordered_set<std::string> enforceOn;
					name = layer.attribute("name").value();
					lwidth = layer.attribute("width").as_int();
					lheight = layer.attribute("height").as_int();
					xml_node layerProperties = layer.child("properties");
					for (xml_node prop = layerProperties.child("property"); prop; prop = prop.next_sibling("property"))
					{
						std::string name, value;
						name = prop.attribute("name").value();
						value = prop.attribute("value").value();
						boost::to_lower(name);
						boost::to_lower(value);
						if ((name == "collision layer") && (value == "true"))
						{
							isCollision = true;
						}
						else if (name == "draw order")
						{
							drawOrder = atoi(value.c_str());
						}
						else if (name == "enforce on" && value.length() > 0)
						{
							std::vector<std::string> frags;
							boost::split(frags, value, boost::is_any_of(":;,"));
							for (unsigned int i = 0; i < frags.size(); ++i)
							{
								std::string target = frags[i];
								boost::trim(target);
								enforceOn.insert(target);
							}
						}
						else
						{
							LayerProperty prop(name, value);
							layerPropertySet.push_back(prop);
						}
					}
					xml_node data = layer.child("data");
					std::string encodingAttr = data.attribute("encoding").value();
					if (encodingAttr == "base64")
						encoding = StringEncoding::Base64;
					std::string compressAttr = data.attribute("compression").value();
					if (compressAttr == "gzip")
						compression = CompType::GZip;
					else if (compressAttr =="zlib")
						compression = CompType::Zlib;
					std::string dataString = data.child_value();
					boost::trim(dataString);
					auto test = Base64_DecodeInFours(dataString);
					if (false)
					{
					}
					else
					{
						if (encoding == StringEncoding::Base64)
							dataString = Base64_StringDecode(dataString);
						if (compression == CompType::GZip)
							dataString = GunzipString(dataString);
						else if (compression == CompType::Zlib)
							dataString = UnZlibString(dataString);
						if (isCollision)
						{
							col_layer_ptr colLayer = col_layer_ptr(new CollisionLayer(name, lwidth, lheight, tilewidth, tileheight, 
								dataString, enforceOn));
							colLayer->SetExtendedProperties(layerPropertySet);
							colLayer->SetDrawOrder(drawOrder);
							AddCollisionLayer(colLayer);
						}
						else
						{
							layer_ptr layerptr = layer_ptr(new Layer(name, lwidth, lheight, tilewidth, tileheight, dataString));
							//Layer layer(name, lwidth, lheight, tilewidth, tileheight, dataString);
							layerptr->SetDrawOrder(drawOrder);
							layerptr->SetExtendedProperties(layerPropertySet);
							AddLayer(layerptr);

						}
					}

				}
			}
			SortLayers();
			int layerIndex = 0;
			int colLayerIndex = 0;
			for(auto layer = layers.begin(); layer != layers.end(); ++layer, ++layerIndex, colLayerIndex = 0)
			{
				for(auto col_layer = collisionLayers.begin(); col_layer != collisionLayers.end(); ++col_layer, ++colLayerIndex)
				{
					if ((*col_layer)->ActiveOnLayer((*layer)->GetName()))
					{
						(*col_layer)->AddAsActiveLayer(layerIndex);
					}
				}
			}
			//BuildExits();
		}
	}

	TileMap::TileMap(const std::string &name, int width, int height, int tilewidth, int tileheight)
	{
		this->name = name;
		this->width = width * tilewidth;
		this->height = height * tileheight;
		this->tileWidth = tilewidth;
		this->tileHeight = tileheight;
		this->tilesInX = width;
		this->tilesInY = height;
	}

	std::string &lowercase(std::string &str) {
		std::string::iterator i = str.begin();
		for (; i != str.end(); ++i) {
			*i = tolower(*i);
		}
		return str;
	}

	std::string TileMap::GetName() const
	{
		return this->name;
	}

	int TileMap::GetHeight() const
	{
		return height;
	}

	layer_ptr TileMap::GetLayer(int index) const
	{
		return layers[index];
	}

	int TileMap::GetLayerCount() const
	{
		return layers.size();
	}

	int TileMap::GetTileHeight() const
	{
		return tileHeight;
	}

	int TileMap::GetTilesInX() const
	{
		return tilesInX;
	}

	int TileMap::GetTilesInY() const
	{
		return tilesInY;
	}

	int TileMap::GetTileWidth() const
	{
		return tileWidth;
	}

	int TileMap::GetWidth() const
	{
		return width;
	}

	void TileMap::AddLayer(layer_ptr layer, int insertAt, bool active)
	{
		if (insertAt < 0)
			layers.push_back(layer);
		else
			layers.insert(layers.begin() + insertAt, layer);
	}

	void TileMap::AddAnimatedLayer(anim_layer_ptr layer, int insertAt, bool active)
	{
		AddLayer(layer, insertAt, active);
		if (insertAt < 0)
			animatedLayers.push_back(layer);
		else
			animatedLayers.insert(animatedLayers.begin() + insertAt, layer);
	}

	void TileMap::AddCollisionLayer(col_layer_ptr layer, int insertAt, bool active)
	{
		if (insertAt < 0)
			collisionLayers.push_back(layer);
		else
			collisionLayers.insert(collisionLayers.begin() + insertAt, layer);
	}

	void TileMap::AddTileSet(tileset_ptr set)
	{
		tileSets.push_back(set);
	}

	bool TileMap::ValidTile(int x, int y)
	{
		return (x < tilesInX && x >= 0 && y < tilesInY && y >= 0);
	}

	bool TileMap::Walkable(int x, int y, int layerId)
	{
		if (!ValidTile(x, y))
			return false;
		int index = 0;
		bool walkable = true;
		for(auto layer = collisionLayers.begin(); layer != collisionLayers.end() && walkable; ++layer, ++index)
		{
			if ((*layer)->IsActive())
			{
				if (layerId == -9000 || (*layer)->ActiveOnLayer(layerId))// || (*layer)->ActiveOnLayer(GetLayer(layerId)->GetName()))
				{
					walkable = !((*layer)->At(x, y) > 0);
				}
			}
		}
		return walkable;
	}

	bool TileMap::Walkable(sf::Vector2<int> &xy, int layer)
	{
		return Walkable(xy.x, xy.y, layer);
	}

	void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		bool characterDrawn = false;
		if (layers.size() > 0)
		{
			sf::Vector2f top = SnapToTiles(target.mapPixelToCoords(sf::Vector2i(0, 0)));
			auto size = target.getSize();
			sf::Vector2f bottom = SnapToTiles(target.mapPixelToCoords(sf::Vector2i(size.x, size.y)));
			int x_start = std::min((int)top.x - 1, tilesInX - 1);
			x_start = std::max(x_start, 0);
			int x_end = std::min((int)bottom.x + 1, tilesInX - 1);
			x_end = std::max(x_end, 0);

			int y_start = std::min((int)top.y - 1, tilesInY - 1);
			y_start = std::max(y_start, 0);
			int y_end = std::min((int)bottom.y + 1, tilesInY - 1);
			y_end = std::max(y_end, 0);

			//sf::Drawable tile;
			sf::Sprite* tile;
			sf::Vector2f position;
			int limit = tilesInY * tilesInX - 1;
			int layerCount = 0;
			for (auto layer = layers.begin(); layer != layers.end(); ++layer, ++layerCount)
			{
				//if((*current)
				for (int j = y_start; j < y_end; ++j)
				{
					for (int k = x_start; k < x_end; ++k)
					{
						int index = j * (*layer)->GetWidth() + k;
						position.x = static_cast<float>(k * tileWidth);
						position.y = static_cast<float>(j * tileHeight);
						if (index > limit)
							continue;
						int tileID = (*layer)->At(index);
						if (tileID <= 0)
							continue;
						for(auto tileset = tileSets.begin(); tileset != tileSets.end(); ++tileset)
						{
							if ((*tileset)->GetFirstGID() <= tileID && (*tileset)->GetEndGID() >= tileID)
							{
								tile = &((*tileset)->GetTile(tileID - (*tileset)->GetFirstGID()));
								tile->setPosition(position);
								target.draw((*tile));
								break;
							}
							//sf::Drawable tile = (*tileset).
						}
						//for (int l = 0; l 
					}
				}
			}
		}
	}

	/*void TileMap::Draw(sf::RenderWindow &window)
	{
		bool characterDrawn = false;
		if (layers.size() > 0)
		{
			sf::Vector2f top = SnapToTiles(window.mapPixelToCoords(sf::Vector2i(0, 0)));
			auto size = window.getSize();
			sf::Vector2f bottom = SnapToTiles(window.mapPixelToCoords(sf::Vector2i(size.x, size.y)));
			int x_start = std::min((int)top.x - 1, tilesInX - 1);
			x_start = std::max(x_start, 0);
			int x_end = std::min((int)bottom.x + 1, tilesInX - 1);
			x_end = std::max(x_end, 0);

			int y_start = std::min((int)top.y - 1, tilesInY - 1);
			y_start = std::max(y_start, 0);
			int y_end = std::min((int)bottom.y + 1, tilesInY - 1);
			y_end = std::max(y_end, 0);

			//sf::Drawable tile;
			sf::Sprite* tile;
			sf::Vector2f position;
			int limit = tilesInY * tilesInX - 1;
			int layerCount = 0;
			for (auto layer = layers.begin(); layer != layers.end(); ++layer, ++layerCount)
			{
				//if((*current)
				for (int j = y_start; j < y_end; ++j)
				{
					for (int k = x_start; k < x_end; ++k)
					{
						int index = j * (*layer)->GetWidth() + k;
						position.x = static_cast<float>(k * tileWidth);
						position.y = static_cast<float>(j * tileHeight);
						if (index > limit)
							continue;
						int tileID = (*layer)->At(index);
						if (tileID <= 0)
							continue;
						for(auto tileset = tileSets.begin(); tileset != tileSets.end(); ++tileset)
						{
							if ((*tileset)->GetFirstGID() <= tileID && (*tileset)->GetEndGID() >= tileID)
							{
								tile = &((*tileset)->GetTile(tileID - (*tileset)->GetFirstGID()));
								tile->setPosition(position);
								window.draw((*tile));
								break;
							}
							//sf::Drawable tile = (*tileset).
						}
						//for (int l = 0; l 
					}
				}
			}
		}
	}
	
	void TileMap::Draw(sf::RenderWindow &window, sf::Shader &shader)
	{
		Draw(window);
	}*/
	
	void TileMap::Update(const sf::Uint32 time, float timescale, bool elapsed)
	{
		for (auto it = layers.begin(); it != layers.end(); ++it)
		{
			if ((*it)->GetIsAnimated())
			{
				auto animlayer = dynamic_cast<AnimatedLayer*>(it->get());
				if (animlayer != nullptr)
				{
					animlayer->Update(time, timescale);
				}
			}
		}
		for (auto tileset = tileSets.begin(); tileset != tileSets.end(); ++tileset)
		{
			if ((*tileset)->IsAnimated())
			{
				auto & dyncast = boost::dynamic_pointer_cast<AnimatedTileSet>(*tileset);
				if (dyncast.get() != nullptr)
				{
					dyncast->Update(time, timescale);
				}
			}
		}
	}

	void TileMap::Update(const float time, const float timescale, const bool elapsed)
	{

	}

	void TileMap::SortLayers()
	{
		std::sort(layers.begin(), layers.end(), [](const layer_ptr& layer1, const layer_ptr& layer2)
		{
			return layer1->GetDrawOrder() < layer2->GetDrawOrder();
		});
	}

	void TileMap::SortCollisionLayers()
	{
		/*std::sort(layers.begin(), layers.end(), [](const col_layer_ptr& layer1, const col_layer_ptr& layer2)
		{
		return layer1->
		});*/
	}

	TileMap::~TileMap(void)
	{
		/*for (int i = 0; i < layers.size(); ++i)
		{

		}*/
	}

	//Protected

	bool TileMap::LoadMap(const std::string &file, const std::string &name, bool clear)
	{
		using namespace pugi;
		xml_document mapDoc;

		xml_parse_result result = mapDoc.load_file(file.c_str());
		if (!result)
		{
			std::cerr << "Map Failed To Load. Error: " << result.description();
			return false;
		}
		else
		{
			this->name = name;
			if (clear)
			{
				MapProperties.clear();
				layers.clear();
				animatedLayers.clear();
				collisionLayers.clear();
				tileSets.clear();
				animatedTileSets.clear();
			}
			for(xml_node map = mapDoc.child("map"); map; map = mapDoc.next_sibling("map"))
			{
				int width, height, tilewidth, tileheight;
				width = map.attribute("width").as_int();
				height = map.attribute("height").as_int();
				tilewidth = map.attribute("tilewidth").as_int();
				tileheight = map.attribute("tileheight").as_int();
				this->tileHeight = tileheight;
				this->tileWidth = tilewidth;
				this->width = width * tilewidth;
				this->height = height * tileheight;
				this->tilesInX = width;
				this->tilesInY = height;
				//TileMap tilemap(mapName, width, height, tilewidth, tileheight);
				xml_node properties = map.child("properties");
				boost::unordered_map<std::string, AnimTileSetProperties> AnimTileSets;
				for (xml_node prop = properties.child("property"); prop; prop = prop.next_sibling("property"))
				{
					std::string name = prop.attribute("name").value();
					std::string value = prop.attribute("value").value();

					if (name == std::string("AnimateTileSet"))
					{
						std::vector<std::string> PropertyVals;
						boost::split(PropertyVals, value, boost::is_any_of("|"));
						AnimTileSetProperties animproperties;
						for (auto pval = PropertyVals.begin(); pval != PropertyVals.end(); ++pval)
						{
							boost::trim(*pval);
							std::vector<std::string> valset;
							boost::split(valset, *pval, boost::is_any_of(":"));
							if (valset.size() > 1)
							{

								for (auto val = valset.begin(); val != valset.end(); ++val)
								{
									boost::trim(*val);
								}
								std::string pname = valset[0];
								std::string animval = valset[1];
								if (pname == "fps")
								{
									animproperties.fps = boost::lexical_cast<float>(animval);
								}
								else if (pname == "startingindex")
								{
									animproperties.startingIndex = boost::lexical_cast<int>(animval);
								}
								else
								{
									std::vector<std::string> cycleset;
									boost::split(cycleset, animval, boost::is_any_of(","));
									animproperties.tileset = pname;
									for (auto cset = cycleset.begin(); cset != cycleset.end(); ++cset)
									{
										boost::trim(*cset);
										animproperties.tilesetImages.push_back(*cset);
									}
								}
							}
						}
						AnimTileSets[animproperties.tileset] = animproperties;
					}
					else
					{
						MapProperties[name] = value;
					}
				}

				for(xml_node tileset = map.child("tileset"); tileset; tileset = tileset.next_sibling("tileset"))
				{
					int firstGID, tstilewidth, tstileheight;
					std::string name = tileset.attribute("name").value();
					firstGID = tileset.attribute("firstgid").as_int();
					tstilewidth = tileset.attribute("tilewidth").as_int();
					tstileheight = tileset.attribute("tileheight").as_int();
					xml_node imageFile =  tileset.child("image");
					std::string imageSource = imageFile.attribute("source").value();
					std::vector<std::string> frags;
					boost::split(frags, imageSource, boost::is_any_of("."));
					std::string fileName;
					std::string extension;
					for (auto piece = frags.begin(); piece != frags.end(); ++piece)
					{
						auto next = piece;
						next++;
						if (next == frags.end())
						{
							extension = "." + *piece;
						}
						else
						{
							fileName += *piece;
						}
					}
					tileset_ptr tileset;
					auto it = AnimTileSets.find(name);
					if (it != AnimTileSets.end())
					{
						std::vector<boost::shared_ptr<sf::Texture> > textures;
						for (auto tileimage = it->second.tilesetImages.begin(); tileimage != it->second.tilesetImages.end(); ++tileimage)
						{
							frags.clear();
							boost::split(frags, *tileimage, boost::is_any_of("."));
							std::string animFileName;
							std::string animExtension;
							for (auto piece = frags.begin(); piece != frags.end(); ++piece)
							{
								auto next = piece;
								next++;
								if (next == frags.end())
								{
									animExtension = "." + *piece;
								}
								else
								{
									animFileName += *piece;
								}
							}
							textures.push_back(PrimaryEngine->GetContentManager().RequestTexture(animFileName, Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::TileSet, PrimaryEngine->GetTime(), animExtension.c_str()));
						}
						if (textures.size() > 0)
						{
							tileset = tileset_ptr(new AnimatedTileSet(name, firstGID, tstilewidth, tstileheight, textures, it->second.fps, it->second.startingIndex));
							AddTileSet(tileset);
						}
					}
					else
					{
						auto tileSetImage = PrimaryEngine->GetContentManager().RequestTexture(fileName, Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::TileSet, PrimaryEngine->GetTime(), extension.c_str());
						tileset = tileset_ptr(new TileSet(name, firstGID, tstilewidth, tstileheight, tileSetImage));
						AddTileSet(tileset);
					}
				}
				for(xml_node layer = map.child("layer"); layer; layer = layer.next_sibling("layer"))
				{
					std::string name;
					int lwidth, lheight;
					int drawOrder = 0;
					float opacity = 1;
					bool isCollision = false;
					CompType compression = CompType::NoCompression;
					StringEncoding encoding = StringEncoding::NoEncoding;
					std::vector<LayerProperty> layerPropertySet;
					boost::unordered_set<std::string> enforceOn;
					name = layer.attribute("name").value();
					lwidth = layer.attribute("width").as_int();
					lheight = layer.attribute("height").as_int();
					xml_node layerProperties = layer.child("properties");
					for (xml_node prop = layerProperties.child("property"); prop; prop = prop.next_sibling("property"))
					{
						std::string name, value;
						name = prop.attribute("name").value();
						value = prop.attribute("value").value();
						boost::to_lower(name);
						boost::to_lower(value);
						if ((name == "collision layer") && (value == "true"))
						{
							isCollision = true;
						}
						else if (name == "draw order")
						{
							drawOrder = atoi(value.c_str());
						}
						else if (name == "enforce on" && value.length() > 0)
						{
							std::vector<std::string> frags;
							boost::split(frags, value, boost::is_any_of(":;,"));
							for (unsigned int i = 0; i < frags.size(); ++i)
							{
								std::string target = frags[i];
								boost::trim(target);
								enforceOn.insert(target);
							}
						}
						else
						{
							LayerProperty prop(name, value);
							layerPropertySet.push_back(prop);
						}
					}
					xml_node data = layer.child("data");
					std::string encodingAttr = data.attribute("encoding").value();
					if (encodingAttr == "base64")
						encoding = StringEncoding::Base64;
					std::string compressAttr = data.attribute("compression").value();
					if (compressAttr == "gzip")
						compression = CompType::GZip;
					else if (compressAttr =="zlib")
						compression = CompType::Zlib;
					std::string dataString = data.child_value();
					boost::trim(dataString);
					auto test = Base64_DecodeInFours(dataString);
					if (false)
					{
					}
					else
					{
						if (encoding == StringEncoding::Base64)
							dataString = Base64_StringDecode(dataString);
						if (compression == CompType::GZip)
							dataString = GunzipString(dataString);
						else if (compression == CompType::Zlib)
							dataString = UnZlibString(dataString);
						if (isCollision)
						{
							col_layer_ptr colLayer = col_layer_ptr(new CollisionLayer(name, lwidth, lheight, tilewidth, tileheight, 
								dataString, enforceOn));
							colLayer->SetExtendedProperties(layerPropertySet);
							colLayer->SetDrawOrder(drawOrder);
							AddCollisionLayer(colLayer);
						}
						else
						{
							layer_ptr layerptr = layer_ptr(new Layer(name, lwidth, lheight, tilewidth, tileheight, dataString));
							//Layer layer(name, lwidth, lheight, tilewidth, tileheight, dataString);
							layerptr->SetDrawOrder(drawOrder);
							layerptr->SetExtendedProperties(layerPropertySet);
							AddLayer(layerptr);

						}
					}

				}
			}
			SortLayers();
			int layerIndex = 0;
			int colLayerIndex = 0;
			for(auto layer = layers.begin(); layer != layers.end(); ++layer, ++layerIndex, colLayerIndex = 0)
			{
				for(auto col_layer = collisionLayers.begin(); col_layer != collisionLayers.end(); ++col_layer, ++colLayerIndex)
				{
					if ((*col_layer)->ActiveOnLayer((*layer)->GetName()))
					{
						(*col_layer)->AddAsActiveLayer(layerIndex);
					}
				}
			}
			//BuildExits();
		}
		return true;
	}

	sf::Vector2f TileMap::SnapToTiles(const sf::Vector2<int> &coordinates) const
	{
		sf::Vector2<float> vec;
		vec.x = static_cast<float>(coordinates.x / tileWidth);
		vec.y = static_cast<float>(coordinates.x / tileHeight);
		return vec;
	}

	sf::Vector2f TileMap::SnapToTiles(const sf::Vector2<float> &coordinates) const
	{
		sf::Vector2<float> vec;
		vec.x = coordinates.x / tileWidth;
		vec.y = coordinates.y / tileHeight;
		return vec;
	}

	const std::string& TileMap::GetMapProperty(const std::string& index) const
	{
		auto it = MapProperties.find(index);
		if (it != MapProperties.end())
		{
			return it->second;
		}
		return "Invalid";
	}
	bool TileMap::AddMapProperty(const std::string& index, const std::string& val, const bool overwriteExisting)
	{
		bool exists = MapProperties.find(index) != MapProperties.end();
		if (overwriteExisting || !exists)
		{
			MapProperties[index] = val;
		}
		return exists;
	}

	const boost::xpressive::sregex re_escape_text = boost::xpressive::sregex::compile("([\\^\\.\\$\\|\\(\\)\\[\\]\\*\\+\\?\\/\\\\])");

	/*std::string regex_escape(std::string text){
	text = boost::xpressive::regex_replace( text, re_escape_text, std::string("\\$1") );
	return text;
	}*/


	

	/*std::vector<MapExit>& TileMap::GetExits()
	{
		return MapExits;
	}*/

	//static functions

	map_ptr TileMap::LoadMapFromXML(std::string &file, std::string &mapName)
	{
		using namespace pugi;
		xml_document mapDoc;
		xml_parse_result result = mapDoc.load_file(file.c_str());
		if (!result)
			std::cout << "Map Failed To Load. Error: " << result.description();
		for(xml_node map = mapDoc.child("map"); map; map = mapDoc.next_sibling("map"))
		{
			int width, height, tilewidth, tileheight;
			width = map.attribute("width").as_int();
			height = map.attribute("height").as_int();
			tilewidth = map.attribute("tilewidth").as_int();
			tileheight = map.attribute("tileheight").as_int();
			map_ptr tilemap = map_ptr(new TileMap(mapName, width, height, tilewidth, tileheight));
			//TileMap tilemap(mapName, width, height, tilewidth, tileheight);
			xml_node properties = map.child("properties");
			for (xml_node prop = properties.child("property"); prop; prop = prop.next_sibling("property"))
			{

			}

			for(xml_node tileset = map.child("tileset"); tileset; tileset = tileset.next_sibling("tileset"))
			{
				int firstGID, tstilewidth, tstileheight;
				std::string name = tileset.attribute("name").value();
				firstGID = tileset.attribute("firstgid").as_int();
				tstilewidth = tileset.attribute("tilewidth").as_int();
				tstileheight = tileset.attribute("tileheight").as_int();
				xml_node imageFile =  tileset.child("image");
				std::string imageSource = imageFile.attribute("source").value();
				sf::Texture tileSetImage;
				if (tileSetImage.loadFromFile(imageSource))
				{
					tileset_ptr tileset = tileset_ptr(new TileSet(name, firstGID, tstilewidth, tstileheight, tileSetImage));
					tilemap->AddTileSet(tileset);
				}
				else
				{
					std::cerr << "Failed to load Image for tileset: " << name << std::endl;
				}
			}
			for(xml_node layer = map.child("layer"); layer; layer = layer.next_sibling("layer"))
			{
				std::string name;
				int lwidth, lheight;
				int drawOrder = 0;
				float opacity = 1;
				bool isCollision = false;
				CompType compression = CompType::NoCompression;
				StringEncoding encoding = StringEncoding::NoEncoding;
				std::vector<LayerProperty> layerPropertySet;
				boost::unordered_set<std::string> enforceOn;
				name = layer.attribute("name").value();
				lwidth = layer.attribute("width").as_int();
				lheight = layer.attribute("height").as_int();
				xml_node layerProperties = layer.child("properties");
				for (xml_node prop = layerProperties.child("property"); prop; prop = prop.next_sibling("property"))
				{
					std::string name, value;
					name = prop.attribute("name").value();
					value = prop.attribute("value").value();
					boost::to_lower(name);
					boost::to_lower(value);
					if ((name == "collision layer") && (value == "true"))
					{
						isCollision = true;
					}
					else if (name == "draw order")
					{
						drawOrder = atoi(value.c_str());
					}
					else if (name == "enforce on" && value.length() > 0)
					{
						std::vector<std::string> frags;
						boost::split(frags, value, boost::is_any_of(":;,"));
						for (unsigned int i = 0; i < frags.size(); ++i)
						{
							std::string target = frags[i];
							boost::trim(target);
							enforceOn.insert(target);
						}
					}
					else
					{
						LayerProperty prop(name, value);
						layerPropertySet.push_back(prop);
					}
				}
				xml_node data = layer.child("data");
				std::string encodingAttr = data.attribute("encoding").value();
				if (encodingAttr == "base64")
					encoding = StringEncoding::Base64;
				std::string compressAttr = data.attribute("compression").value();
				if (compressAttr == "gzip")
					compression = CompType::GZip;
				std::string dataString = data.child_value();
				boost::trim(dataString);
				if (encoding == StringEncoding::Base64)
					dataString = base64_decode(dataString);
				if (compression == CompType::GZip)
					dataString = GunzipString(dataString);
				if (isCollision)
				{
					col_layer_ptr colLayer = col_layer_ptr(new CollisionLayer(name, lwidth, lheight, tilewidth, tileheight, 
						dataString,enforceOn));
					colLayer->SetExtendedProperties(layerPropertySet);
					colLayer->SetDrawOrder(drawOrder);
					tilemap->AddCollisionLayer(colLayer);
				}
				else
				{
					layer_ptr layer = layer_ptr(new Layer(name, lwidth, lheight, tilewidth, tileheight, dataString));
					//Layer layer(name, lwidth, lheight, tilewidth, tileheight, dataString);
					layer->SetDrawOrder(drawOrder);
					layer->SetExtendedProperties(layerPropertySet);
					tilemap->AddLayer(layer);

				}
			}
			return tilemap;
		}
		return map_ptr();
	}

}