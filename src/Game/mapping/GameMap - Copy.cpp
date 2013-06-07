#include "GameMap.h"
#include <io\xml\pugixml.hpp>
#include <boost\algorithm\string.hpp>
#include <boost\regex.hpp>
#include <Mapping\MapCharacterMovementHandler.h>
#include <Mapping\MapCharacter.h>
#include <Mapping\MapChest.h>
#include <Mapping\MapSpawns.h>
#include <io\xml\pugixml.hpp>
#include <boost\algorithm\string.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <boost\algorithm\string_regex.hpp>
#include <Utilities/base64.h>

using namespace Graphics;
using namespace Mapping;

namespace Game
{
	namespace Mapping
	{
		GameMap::GameMap() : UsePythonMove(false), UsePythonScriptClass(false), EncounterRate(0.05f), rng(time(0)), RandomFloatGen(rng, boost::uniform_real<float>(0, 1)), Entity(), ActiveExit(nullptr)
		{

		}
		GameMap::GameMap(const std::string &name, int tilesWide, int tilesHigh, int tilewidth, int tileheight) : TileMap(name, tilesWide, tilesHigh, tilewidth, tileheight), UsePythonMove(false), UsePythonScriptClass(false), EncounterRate(0.05f), rng(time(0)), RandomFloatGen(rng, boost::uniform_real<float>(0, 1)), Entity(name, TileMapEntity), ActiveExit(nullptr)
		{

		}
		GameMap::GameMap(const std::string &file, const std::string &name, Engine* engine) : TileMap(file, name, engine), UsePythonMove(false), UsePythonScriptClass(false), EncounterRate(0.8f), rng(time(0)), RandomFloatGen(rng, boost::uniform_real<float>(0, 1)), Entity(name, TileMapEntity), ActiveExit(nullptr)
		{
			using namespace pugi;
			xml_document mapDoc;

			auto spawner = boost::shared_ptr<MapSpawner>(new MapSpawner(this, false));
			RegisterComponent(MapSpawnComponentIndex, spawner);

			xml_parse_result result = mapDoc.load_file(file.c_str());
			if (!result)
				std::cerr << "Map Failed To Load. Error: " << result.description();
			else
			{
				for(xml_node map = mapDoc.child("map"); map; map = mapDoc.next_sibling("map"))
				{
					for(xml_node objlayer = map.child("objectgroup"); objlayer; objlayer = objlayer.next_sibling("objectgroup"))
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
						name = objlayer.attribute("name").value();
						lwidth = objlayer.attribute("width").as_int();
						lheight = objlayer.attribute("height").as_int();
						xml_node layerProperties = objlayer.child("properties");
						std::string lowerName = name;
						boost::algorithm::to_lower(lowerName);
						int ChestCount = 0;
						int exitCount = 0;
						int transitionCount = 0;
						if (lowerName == "chests" || lowerName == "chest")
						{
							for (xml_node obj = objlayer.child("object"); obj; obj = obj.next_sibling("object"))
							{
								std::string objType = obj.attribute("type").value();
								boost::algorithm::to_lower(objType);
								if (objType == "chest")
								{
									int tilex = 0;
									int tiley = 0;
									int layer = 0;
									bool locked = false;
									std::string chestName = "Chest" + boost::lexical_cast<std::string>(ChestCount);
									std::string chestStyle = "Default";
									tilex = obj.attribute("x").as_int() / tileWidth;
									tiley = obj.attribute("y").as_int() / tileHeight;
									for (xml_node objPrs = obj.child("properties"); objPrs; objPrs = objPrs.next_sibling("properties"))
									{
										for (xml_node objPr = objPrs.child("property"); objPr; objPr = objPr.next_sibling("property"))
										{
											std::string prName = objPr.attribute("name").value();
											boost::algorithm::to_lower(prName);
											if (prName == "contents")
											{

											}
											else if (prName == "layer")
											{
												layer = objPr.attribute("value").as_int();
											}
											else if (prName == "name" || prName == "chestname")
											{
												chestName = objPr.attribute("value").value();
											}
											else if (prName == "style")
											{
												chestStyle = objPr.attribute("style").value();
											}
										}
									}
									//auto newChest = boost::shared_ptr<MapObject>(new MapChest(chestName, tilex, tiley, layer));
									//MapObjects[chestName] = newChest;
									//auto chestVis = boost::shared_ptr<MapObjectVisualizer>(newChest->GenerateVisualizer());//new MapObjectVisualizer(newChest.get()));
									//newChest->RegisterComponent("ChestVisualizer", chestVis);
									//newChest->RegisterComponent()
									//MapObjects[layer][tilex][tiley][chestName] = newChest;
									//MapObjectVisualizers[layer].push_back(chestVis);//[tilex][tiley][chestName] = chestVis;
									++ChestCount;
								}
							}
						}
						else if (lowerName == "npc" || lowerName == "npcs")
						{
							for (xml_node obj = objlayer.child("object"); obj; obj = obj.next_sibling("object"))
							{
								std::string objType = obj.attribute("type").value();
								boost::algorithm::to_lower(objType);
								{
									if (objType == "chest")
									{
										int startX = 0;
										int startY = 0;
										int startLayer = 0;
									}

								}
							}
						}
						else if (lowerName == "layer transitions" || lowerName == "layertransitions")
						{
							for (xml_node obj = objlayer.child("object"); obj; obj = obj.next_sibling("object"))
							{
								bool validTransition = false;
								boost::unordered_map<int, int> transitionMapping;
								std::string objType = obj.attribute("type").value();
								boost::algorithm::to_lower(objType);
								{
									if (objType == "layer transition")
									{
										int tilex = obj.attribute("x").as_int() / tileWidth;
										int tiley = obj.attribute("y").as_int() / tileHeight;
										int width = obj.attribute("width").as_int() / tileWidth;
										int height = obj.attribute("height").as_int() / tileHeight;
										int layer = 0;

										int activelayer = 0;
										int targetlayer = 0;

										for (xml_node objPrs = obj.child("properties"); objPrs; objPrs = objPrs.next_sibling("properties"))
										{
											for (xml_node objPr = objPrs.child("property"); objPr; objPr = objPr.next_sibling("property"))
											{
												std::string prName = objPr.attribute("name").value();
												boost::algorithm::to_lower(prName);
												if (prName == "transitions")
												{

													std::vector<std::string> frags;
													std::string transVal(objPr.attribute("value").value()); 
													boost::split(frags, transVal, boost::is_any_of(","));
													for (auto tSet = frags.begin(); tSet != frags.end(); ++tSet)
													{
														std::vector<std::string> tFrags;
														boost::split(tFrags, *tSet, boost::is_any_of(">"));
														if (tFrags.size() >= 2)
														{
															validTransition = true;
															boost::trim(tFrags[0]);
															boost::to_lower(tFrags[0]);
															boost::trim(tFrags[1]);
															boost::to_lower(tFrags[1]);
															transitionMapping[boost::lexical_cast<int>(tFrags[0])] = boost::lexical_cast<int>(tFrags[1]);
															/*for (unsigned int i = 0; i < tFrags.size(); ++i)
															{
															boost::trim(tFrags[i]);
															boost::to_lower(tFrags[i]);
															if (i == 0)
															activelayer = boost::lexical_cast<int>(tFrags[i]);
															if (i == 1)
															targetlayer = boost::lexical_cast<int>(tFrags[i]);
															}*/
														}
													}


												}
											}
										}
										if (validTransition)
										{
											std::string transLayerName = "LayerTransition" + boost::lexical_cast<std::string>(transitionCount);
											auto transLayerObject = boost::shared_ptr<MapObject>(new MapObject(transLayerName, tilex, tiley, layer));

											boost::shared_ptr<LayerTransitionComponent> transcomp;
											if (width > 1 || height > 1)
											{
												sf::IntRect exitArea(0, 0, width, height);
												transcomp = boost::shared_ptr<LayerTransitionComponent>(new AreaLayerTransitionComponent(transLayerObject.get(), exitArea, transLayerName));
												transLayerObject->RegisterComponent(MapEventIndex, transcomp);
											}
											else
											{
												transcomp = boost::shared_ptr<LayerTransitionComponent>(new LayerTransitionComponent(transLayerObject.get(), transLayerName));
												transLayerObject->RegisterComponent(MapEventIndex, transcomp);
											}
											for (auto transMap = transitionMapping.begin(); transMap != transitionMapping.end(); ++ transMap)
											{
												transcomp->AddLayerTransition(transMap->first, transMap->second);
											}
											AddObject(transLayerName, transLayerObject);
											++transitionCount;
										}
									}
								}
							}
						}
						else if (lowerName == "exits")
						{
							for (xml_node obj = objlayer.child("object"); obj; obj = obj.next_sibling("object"))
							{
								std::string objType = obj.attribute("type").value();
								boost::algorithm::to_lower(objType);
								{
									if (objType == "exit")
									{
										int tilex = obj.attribute("x").as_int() / tileWidth;
										int tiley = obj.attribute("y").as_int() / tileHeight;
										int width = obj.attribute("width").as_int() / tileWidth;
										int height = obj.attribute("height").as_int() / tileHeight;
										int layer = 0;
										int targetx = 0;
										int targety = 0; 
										int targetlayer = 0;
										std::string targetMapName;
										std::string targetMapFile;

										for (xml_node objPrs = obj.child("properties"); objPrs; objPrs = objPrs.next_sibling("properties"))
										{
											for (xml_node objPr = objPrs.child("property"); objPr; objPr = objPr.next_sibling("property"))
											{
												std::string prName = objPr.attribute("name").value();
												boost::algorithm::to_lower(prName);
												if (prName == "active layer")
												{
													layer = objPr.attribute("value").as_int();
												}
												else if (prName == "target map")
												{
													targetMapFile =  objPr.attribute("value").value();
												}
												else if (prName == "target position")
												{
													std::vector<std::string> frags;
													std::string posVal(objPr.attribute("value").value()); 
													boost::split(frags, posVal, boost::is_any_of(":;,"));
													for (unsigned int i = 0; i < frags.size(); ++i)
													{
														boost::trim(frags[i]);
														boost::to_lower(frags[i]);
														switch(i)
														{
														case 0:
															targetx = (frags[i] == "carry" ? -1 : boost::lexical_cast<int>(frags[i]));
															break;
														case 1:
															targety = (frags[i] == "carry" ? -1 : boost::lexical_cast<int>(frags[i]));
															break;
														case 2:
															targetlayer = (frags[i] == "carry" ? -1 : boost::lexical_cast<int>(frags[i]));
															break;
														}
													}
												}
											}
										}

										if (targetMapName.empty() && !targetMapFile.empty())
										{
											targetMapName = targetMapFile;
										}
										else if (!targetMapName.empty() && targetMapFile.empty())
										{
											targetMapFile = targetMapName;
										}
										std::string exitName = "Exit" + boost::lexical_cast<std::string>(exitCount);
										auto exitObject = boost::shared_ptr<MapObject>(new MapObject(exitName, tilex, tiley, layer));
										if (width > 1 || height > 1)
										{
											sf::IntRect exitArea(0, 0, width, height);
											auto aexitcomp = boost::shared_ptr<MapEventComponent>(new AreaMapExitComponent(exitObject.get(), exitArea, targetMapName, targetMapFile, targetx, targety, targetlayer));
											exitObject->RegisterComponent(MapEventIndex, aexitcomp);
											//Area Exit
										}
										else
										{
											auto exitcomp = boost::shared_ptr<MapEventComponent>(new MapExitComponent(exitObject.get(), targetMapName, targetMapFile, targetx, targety, targetlayer));
											exitObject->RegisterComponent(MapEventIndex, exitcomp);
											//Single Tile Exit
										}
										AddObject(exitName, exitObject);
										++exitCount;
									}
								}
							}
						}
					}
				}
				std::string scriptFile = MapProperties["Script"];
				if (scriptFile != "")
				{
					engine->GetPythonScripter().AddScriptObject<GameMap>(std::string("CurrentMap"), *this, engine->GetPythonScripter().GetMappingModule());
					engine->GetPythonScripter().RunFile(scriptFile);
				}
				std::string MusicFile = MapProperties["Music"];
				if (MusicFile != "")
				{
					std::vector<std::string> fragments;
					boost::split(fragments, MusicFile, boost::is_any_of(","));
					switch(fragments.size())
					{
					case 1:
						engine->GetSoundSystem().AddSound(fragments[0], fragments[0], true);
						addedSounds.push_back(fragments[0]);
						break;
					case 2:
						engine->GetSoundSystem().AddSound(fragments[0], fragments[1], true);
						addedSounds.push_back(fragments[1]);
						break;
					case 3:
						engine->GetSoundSystem().AddSound(fragments[0], fragments[1], true, true, false, fragments[2].c_str());
						addedSounds.push_back(fragments[1]);
						break;
					}
				} 

				auto background = MapProperties.find("Background");
				if (background != MapProperties.end())
				{
					auto BackgroundString = background->second;
					std::vector<std::string> fragments;
					boost::split(fragments, BackgroundString, boost::is_any_of(","));
					switch(fragments.size())
					{
					case 1:
						Backgrounds.push_back(Graphics::AnimatedSprite(engine->GetContentManager().RequestTexture(fragments[0], Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::Background, engine->GetTime())));
						break;
					}
				}
			}
			for (auto mfile = addedSounds.begin(); mfile != addedSounds.end(); ++mfile)
			{
				engine->GetSoundSystem().Play(*mfile, 0);
			}
		}

		void GameMap::SetMapCharacter(MapCharacter* character)
		{
			Character = character;
		}

		/*GameMap::GameMap(std::string &file, std::string &name) : TileMap(file, name)
		{

		}*/

		/*void GameMap::SetMoveFunction(MovementFunction &function)
		{

		}*/
		/*void GameMap::SetPythonMoveFunction(boost::python::object function)
		{
		pythonMoveFunction = function;
		UsePythonMove = true;
		UsePythonScriptClass = false;
		}
		void GameMap::SetMapPythonScriptClass(boost::python::object scriptClass)
		{
		MapScriptClass = scriptClass;
		UsePythonScriptClass = true;
		UsePythonMove = false;
		}
		void GameMap::CallMoveFunction(Character::Party &party, MapCharacterSprite &character)
		{
		try
		{
		bool DoEnemyEncounterTest = true;
		if (UsePythonMove)
		pythonMoveFunction(party, character);
		else if (UsePythonScriptClass)
		DoEnemyEncounterTest = MapScriptClass.attr("MoveFunction")(boost::ref(party), boost::ref(character));
		if (DoEnemyEncounterTest)
		{
		float RN = RandomFloatGen();
		if (EncounterRate > RN)
		{

		}
		}
		}
		catch (boost::python::error_already_set)
		{
		PyErr_Print();
		}

		}*/
		void GameMap::PlayMusic()
		{
			for(auto mapSounds = addedSounds.begin(); mapSounds != addedSounds.end(); ++mapSounds)
			{
				PrimaryEngine->GetSoundSystem().Play(*mapSounds, 2);
			}
		}
		void GameMap::PauseMusic()
		{
			for(auto mapSounds = addedSounds.begin(); mapSounds != addedSounds.end(); ++mapSounds)
			{
				PrimaryEngine->GetSoundSystem().SetChannelPause(2);
			}
		}

		float GameMap::GetEncounterRate() const
		{
			return EncounterRate;
		}
		void GameMap::SetEncounterRate(const float rate)
		{
			EncounterRate = rate;
		}

		void GameMap::Draw(sf::RenderTarget &window, MapCharacter &mapChar, sf::View &characterView) 
		{
			for (auto background = Backgrounds.begin(); background != Backgrounds.end(); ++background)
			{
				background->Draw(window);
				//background->Draw(window);
			}
			bool characterDrawn = false;


			bool ObjectsToDraw = MapObjectVisualizers.size() > 0;
			int DrawnObjectsUpTo = 0;
			if (ObjectsToDraw)
			{
				for (auto objs = MapObjectVisualizers.begin(); objs != MapObjectVisualizers.end() && objs->first < 0; ++objs)
				{
					for (auto obj = objs->second.begin(); obj != objs->second.end(); ++obj)
					{
						(*obj)->Draw(window);//, sf::Transform());
						//(*obj)->Draw(window);
					}
				}
			}


			if (layers.size() > 0)
			{
				auto lastDrawnIt = MapObjectVisualizers.begin();
				sf::Vector2f top = SnapToTiles(window.mapPixelToCoords(sf::Vector2i(0, 0)));
				auto size = window.getSize();
				sf::Vector2f bottom = SnapToTiles(window.mapPixelToCoords(sf::Vector2i(size.x, size.y)));
				int x_start = std::min((int)top.x - 1, tilesInX - 1);
				x_start = std::max(x_start, 0);
				int x_end = std::min((int)bottom.x + 1, tilesInX + 1);
				x_end = std::max(x_end, 0);

				int y_start = std::min((int)top.y - 1, tilesInY - 1);
				y_start = std::max(y_start, 0);
				int y_end = std::min((int)bottom.y + 1, tilesInY + 1);
				y_end = std::max(y_end, 0);

				//sf::Drawable tile;
				sf::Sprite* tile;
				sf::Vector2f position;
				int limit = tilesInY * tilesInX - 1;
				//charSprite.Draw(window);
				int layerCount = 0;
				for (auto layer = layers.begin(); layer != layers.end(); ++layer, ++layerCount)
				{
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
							}
						}
					}
					if(mapChar.DrawLayer <= layerCount && !characterDrawn)
					{
						sf::View tempView(window.getView());
						window.setView(characterView);
						mapChar.Draw(window);
						//charSprite.Draw(window);
						window.setView(tempView);
						characterDrawn = true;
					}
					if (ObjectsToDraw)
					{
						int LayerOrder = (*layer)->GetDrawOrder();
						auto objs = MapObjectVisualizers.find(LayerOrder);
						if (objs != MapObjectVisualizers.end())
						{
							++objs;
							for (;lastDrawnIt != objs && lastDrawnIt != MapObjectVisualizers.end(); ++lastDrawnIt)
							{
								for (auto obj = lastDrawnIt->second.begin(); obj != lastDrawnIt->second.end(); ++obj)
								{
									(*obj)->Draw(window);
								}
							}
							//while (lastDrawnIt != objs && last)
							DrawnObjectsUpTo = LayerOrder;
						}

					}
				}
			}
			if (ObjectsToDraw)
			{
				for (auto objs = MapObjectVisualizers.upper_bound(DrawnObjectsUpTo); objs != MapObjectVisualizers.end(); ++objs)
				{
					if (!characterDrawn && objs->first > mapChar.DrawLayer)
					{
						sf::View tempView(window.getView());
						window.setView(characterView);
						mapChar.Draw(window);
						//charSprite.Draw(window);
						window.setView(tempView);
						characterDrawn = true;
					}
					for (auto obj = objs->second.begin(); obj != objs->second.end(); ++obj)
					{
						(*obj)->Draw(window);
					}

				}
			}
			if (!characterDrawn)
			{
				sf::View tempView(window.getView());
				window.setView(characterView);
				mapChar.Draw(window);
				//charSprite.Draw(window);
				window.setView(tempView);
				characterDrawn = true;
			}
		}

		void GameMap::Draw(sf::RenderTarget &window, sf::RenderStates states, MapCharacter &mapChar, sf::View &characterView)
		{
			for (auto background = Backgrounds.begin(); background != Backgrounds.end(); ++background)
			{
				background->draw(window, states);
				//background->Draw(window, shader);
			}
			bool characterDrawn = false;
			if (layers.size() > 0)
			{
				sf::Vector2f top = SnapToTiles(window.mapPixelToCoords(sf::Vector2i(0, 0)));
				auto size = window.getSize();
				sf::Vector2f bottom = SnapToTiles(window.mapPixelToCoords(sf::Vector2i(size.x, size.y)));
				int x_start = std::min((int)top.x - 1, tilesInX - 1);
				x_start = std::max(x_start, 0);
				int x_end = std::min((int)bottom.x + 1, tilesInX + 1);
				x_end = std::max(x_end, 0);

				int y_start = std::min((int)top.y - 1, tilesInY - 1);
				y_start = std::max(y_start, 0);
				int y_end = std::min((int)bottom.y + 1, tilesInY + 1);
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
					if(mapChar.DrawLayer <= layerCount && !characterDrawn)
					{
						sf::View tempView(window.getView());
						window.setView(characterView);
						mapChar.draw(window, states);
						//mapChar.Draw(window, shader);
						window.setView(tempView);
						characterDrawn = true;
					}
				}
			}
		}
		/*
		void GameMap::Draw(sf::RenderTarget &window, MapCharacter &mapChar, sf::View &characterView)
		{
			for (auto background = Backgrounds.begin(); background != Backgrounds.end(); ++background)
			{
				background->Draw(window);
			}
			bool characterDrawn = false;


			bool ObjectsToDraw = MapObjectVisualizers.size() > 0;
			int DrawnObjectsUpTo = 0;
			if (ObjectsToDraw)
			{
				for (auto objs = MapObjectVisualizers.begin(); objs != MapObjectVisualizers.end() && objs->first < 0; ++objs)
				{
					for (auto obj = objs->second.begin(); obj != objs->second.end(); ++obj)
					{
						(*obj)->Draw(window);
					}
				}
			}


			if (layers.size() > 0)
			{
				auto lastDrawnIt = MapObjectVisualizers.begin();
				sf::Vector2f top = SnapToTiles(window.mapPixelToCoords(sf::Vector2i(0, 0)));
				auto size = window.getSize();
				sf::Vector2f bottom = SnapToTiles(window.mapPixelToCoords(sf::Vector2i(size.x, size.y)));
				int x_start = std::min((int)top.x - 1, tilesInX - 1);
				x_start = std::max(x_start, 0);
				int x_end = std::min((int)bottom.x + 1, tilesInX + 1);
				x_end = std::max(x_end, 0);

				int y_start = std::min((int)top.y - 1, tilesInY - 1);
				y_start = std::max(y_start, 0);
				int y_end = std::min((int)bottom.y + 1, tilesInY + 1);
				y_end = std::max(y_end, 0);

				//sf::Drawable tile;
				sf::Sprite* tile;
				sf::Vector2f position;
				int limit = tilesInY * tilesInX - 1;
				//charSprite.Draw(window);
				int layerCount = 0;
				for (auto layer = layers.begin(); layer != layers.end(); ++layer, ++layerCount)
				{
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
							}
						}
					}
					if(mapChar.DrawLayer <= layerCount && !characterDrawn)
					{
						sf::View tempView(window.getView());
						window.setView(characterView);
						mapChar.Draw(window);
						//charSprite.Draw(window);
						window.setView(tempView);
						characterDrawn = true;
					}
					if (ObjectsToDraw)
					{
						int LayerOrder = (*layer)->GetDrawOrder();
						auto objs = MapObjectVisualizers.find(LayerOrder);
						if (objs != MapObjectVisualizers.end())
						{
							++objs;
							for (;lastDrawnIt != objs && lastDrawnIt != MapObjectVisualizers.end(); ++lastDrawnIt)
							{
								for (auto obj = lastDrawnIt->second.begin(); obj != lastDrawnIt->second.end(); ++obj)
								{
									(*obj)->Draw(window);
								}
							}
							//while (lastDrawnIt != objs && last)
							DrawnObjectsUpTo = LayerOrder;
						}

					}
				}
			}
			if (ObjectsToDraw)
			{
				for (auto objs = MapObjectVisualizers.upper_bound(DrawnObjectsUpTo); objs != MapObjectVisualizers.end(); ++objs)
				{
					if (!characterDrawn && objs->first > mapChar.DrawLayer)
					{
						sf::View tempView(window.getView());
						window.setView(characterView);
						mapChar.Draw(window);
						//charSprite.Draw(window);
						window.setView(tempView);
						characterDrawn = true;
					}
					for (auto obj = objs->second.begin(); obj != objs->second.end(); ++obj)
					{
						(*obj)->Draw(window);
					}

				}
			}
			if (!characterDrawn)
			{
				sf::View tempView(window.getView());
				window.setView(characterView);
				mapChar.Draw(window);
				//charSprite.Draw(window);
				window.setView(tempView);
				characterDrawn = true;
			}
		}

		void GameMap::Draw(sf::RenderTarget &window, sf::RenderStates states, MapCharacter &mapChar, sf::View &characterView)
		{
			for (auto background = Backgrounds.begin(); background != Backgrounds.end(); ++background)
			{
				background->Draw(window, states);
			}
			bool characterDrawn = false;
			if (layers.size() > 0)
			{
				sf::Vector2f top = SnapToTiles(window.mapPixelToCoords(sf::Vector2i(0, 0)));
				auto size = window.getSize();
				sf::Vector2f bottom = SnapToTiles(window.mapPixelToCoords(sf::Vector2i(size.x, size.y)));
				int x_start = std::min((int)top.x - 1, tilesInX - 1);
				x_start = std::max(x_start, 0);
				int x_end = std::min((int)bottom.x + 1, tilesInX + 1);
				x_end = std::max(x_end, 0);

				int y_start = std::min((int)top.y - 1, tilesInY - 1);
				y_start = std::max(y_start, 0);
				int y_end = std::min((int)bottom.y + 1, tilesInY + 1);
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
					if(mapChar.DrawLayer <= layerCount && !characterDrawn)
					{
						sf::View tempView(window.getView());
						window.setView(characterView);
						mapChar.Draw(window, states);
						window.setView(tempView);
						characterDrawn = true;
					}
				}
			}
		}
		*/
		//static function
		gmap_ptr GameMap::LoadMapFromXML(std::string &file, std::string &mapName)
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
				gmap_ptr tilemap = gmap_ptr(new GameMap(mapName, width, height, tilewidth, tileheight));
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
						::Mapping::tileset_ptr tileset = ::Mapping::tileset_ptr(new ::Mapping::TileSet(name, firstGID, tstilewidth, tstileheight, tileSetImage));
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
			return gmap_ptr();
		}

		bool GameMap::IsAnEvent(int x, int y, int layer)
		{
			/*	auto finderx = EventLookup.find(x);
			if (finderx != EventLookup.end())
			{
			auto findery = finderx->second.find(y);
			if (findery != finderx->second.end())
			{
			auto finderl = findery->second.find(layer);
			return (finderl != findery->second.end());
			}
			}*/

			return false;
		}

		/*MapEvent& GameMap::GetEvent(int x, int y, int layer)
		{
		auto finderx = EventLookup.find(x);
		if (finderx != EventLookup.end())
		{
		auto findery = finderx->second.find(y);
		if (findery != finderx->second.end())
		{
		auto finderl = findery->second.find(layer);
		if (finderl != findery->second.end())
		{
		//return finderl->second[0];
		}
		}
		}
		return InvalidEvent;
		}*/

		/*void GameMap::AddEvent(int x, int y, int layer)
		{

		}*/

		void GameMap::ProcessEvents(MapCharacter& character)
		{
			std::vector<boost::unordered_map<std::string, MapEventComponent*>::iterator> removals;
			for (auto event = Events.begin(); event != Events.end(); ++event)
			{
				if (event->second != nullptr)
				{
					if (event->second->IsActive() && event->second->InEventRange(character))
					{
						event->second->ProcessEvent(*this, character);
					}
				}
				else
				{
					removals.push_back(event);
				}
			}
			for (auto rmv = removals.begin(); rmv != removals.end(); ++rmv)
			{
				Events.erase(*rmv);
			}
			if (ExitActive())
			{
				SwapMapViaExit(*ActiveExit);
				SetExit(nullptr);
			}
		}

		/*bool GameMap::IsLayerTransition(int x, int y, int layer)
		{
		auto xfinder = LayerTransitions.find(x);
		if (xfinder != LayerTransitions.end())
		{
		auto yfinder = xfinder->second.find(y);
		if (yfinder != xfinder->second.end())
		{
		auto lfinder = yfinder->second.find(layer);
		return (lfinder != yfinder->second.end());
		}
		}
		return false;
		}*/

		/*bool GameMap::ProcessLayerChange(int x, int y, int layer, int &newLayer)
		{
		}*/

		void GameMap::AddLayerTransition(int x, int y, int layer, int changeLayer)
		{
			//LayerTransitions[x][y][layer] = changeLayer;
		}

		/*bool GameMap::ProcessMapExits(int x, int y, int layer, std::string& newMapName, std::string& newMapFile)
		{
		bool exitFound = false;

		auto Exitx = ExitLookup.find(x);
		if (Exitx != ExitLookup.end())
		{
		auto Exity = Exitx->second.find(y);
		if (Exity != Exitx->second.end())
		{
		auto Exitlayer = Exity->second.find(layer);
		if (Exitlayer != Exity->second.end())
		{
		exitFound = true;

		}
		}
		}

		return exitFound;
		}*/

		void GameMap::AddMapExit(int x, int y, int layer, const std::string& newMapName, const std::string& newMapFile, bool Active, int newx, int newy, int newlayer)
		{

		}

		void GameMap::AddMapExit(const MapExit& MExit)
		{

		}

		void GameMap::AddObject(const std::string index, boost::shared_ptr<MapObject> obj)
		{
			if (obj.get() != nullptr)
			{
				auto ev = obj->GetComponentAs<MapEventComponent*>(MapEventIndex);
				auto iev = obj->GetComponentAs<InputTriggeredMapEvent*>(InputMapEventIndex);
				if (ev != nullptr)
				{
					Events[obj->GetName()] = ev;
				}
				if (iev != nullptr)
				{
					InputEvents[obj->GetName()] = iev;
				}
				obj->MapPosition.x = obj->MapTilePosition.x * this->tileWidth;
				obj->MapPosition.y = obj->MapTilePosition.y * this->tileHeight;
				MapObjects[obj->GetName()] = obj;
			}
		}

		void GameMap::AddEventToObject(const std::string& objIndex, boost::shared_ptr<MapEventComponent> evComp)
		{
			if (evComp.get() != nullptr)
			{
				auto obj = MapObjects.find(objIndex);
				if (obj != MapObjects.end())
				{
					auto iev = boost::dynamic_pointer_cast<InputTriggeredMapEvent>(evComp);
					if (iev.get() != nullptr)
					{
						obj->second->RegisterComponent(InputMapEventIndex, iev);
						InputEvents[objIndex] = iev.get();
					}
					else
					{
						obj->second->RegisterComponent(MapEventIndex, evComp);
						Events[objIndex] = evComp.get();
					}
				}

			}
		}

		const std::vector<std::string>& GameMap::GetAddedSounds() const
		{
			return addedSounds;
		}

		bool GameMap::HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult)
		{
			for (auto it = InputEvents.begin(); it != InputEvents.end(); ++it)
			{
				if(it->second->InputTriggering(time, inputModule) && Character != nullptr && it->second->InEventRange(*Character))
				{
					it->second->ProcessEvent(*this, *Character);
					return true;
				}
			}
			return false;
		}
		bool GameMap::HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult)
		{
			return false;
		}

		void GameMap::SwapMapViaExit(MapExitComponent& exit)
		{
			std::cout << "Processing MapExit\n";
			
			auto & targetMapFile = exit.GetTargetMapFile();
			auto & targetMapName = exit.GetTargetMapName();
			auto Carries = exit.GetCarryOver();
			auto TargetPos = exit.GetTargetMapPositon();
			if (LoadGameMap(targetMapFile, targetMapName, exit.GetClearAssets()))
			{
				//Note that exit becomes null at this point
				//std::cout << "Character ptr " << Character << "\n";
				if (Character != nullptr)
				{
					int oldx = Character->MapTilePosition.x;
					Character->MapTilePosition.x = (Carries.x ? Character->MapTilePosition.x : TargetPos.x);
					//std::cout << "X Transfer| Carry: " << Carries.x << ", Prev X Tile: " << oldx << ", New X Tile: " << Character->MapTilePosition.x << ", Target Map Pos: " << TargetPos.x << "\n";
					Character->MapPosition.x = static_cast<float>(Character->MapTilePosition.x * static_cast<float>(tileWidth));

					Character->MapTilePosition.y = (Carries.y ? Character->MapTilePosition.y : TargetPos.y);
					Character->MapPosition.y = static_cast<float>(Character->MapTilePosition.y * static_cast<float>(tileHeight));

					Character->DrawLayer = (Carries.z ? Character->DrawLayer: TargetPos.z);
				}
			}

			
			
		}
		void GameMap::SetExit(MapExitComponent* exit)
		{
			ActiveExit = exit;
		}
		bool GameMap::ExitActive() const
		{
			return ActiveExit != nullptr;
		}
		MapExitComponent* GameMap::GetActiveExit() const
		{
			return ActiveExit;
		}

		void GameMap::BuildExits()
		{
			using namespace boost;
			//const static std::string ValidateExits("(\{((\d+),\s*){3}(\s*(.*?),\s*){2}(\s*(\d+),{0, 1}\s*(\d+)\},*\s*)*");
			//const static std::string ExtractExits("");
			std::string exitString = MapProperties["Exits"];
			if (exitString != "")
			{	
				const static boost::regex re("(\\{(\\d+,\\s*){3}((.*?),\\s*){2}(\\d+,\\s*){2}(\\d+)\\}(,\\s*){0,1})");
				try
				{
					boost::sregex_token_iterator token(exitString.begin(), exitString.end(), re, 0);
					boost::sregex_token_iterator end;
					for(; token != end; ++token)
					{
						std::string foundmatch(token->first, token->second);
						boost::erase_all(foundmatch, "{");
						boost::erase_all(foundmatch, "}");
						boost::trim(foundmatch);
						std::vector<std::string> fragments;
						boost::split(fragments, foundmatch, boost::is_any_of(","));
						for (auto fragment = fragments.begin(); fragment != fragments.end(); ++fragment)
						{
							boost::trim(*fragment);
						}
						//MapExits.push_back(MapExit(lexical_cast<int>(fragments[0]), lexical_cast<int>(fragments[1]),lexical_cast<int>(fragments[2]), fragments[3], fragments[4], lexical_cast<int>(fragments[5]), lexical_cast<int>(fragments[6]), lexical_cast<int>(fragments[7]), true));
					}
				}
				catch (boost::regex_error& error)
				{
					std::cerr << error.what() << std::endl;
				}
			}
		}

		bool GameMap::LoadGameMap(const std::string& filename, const std::string& name, bool clear)
		{
			
			std::string mappedFileName(PrimaryEngine->GetContentManager().GetMapDirectory() + filename);
			if (!TileMap::LoadMap(mappedFileName, name, clear))
				return false;
			
			using namespace pugi;
			xml_document mapDoc;

			xml_parse_result result = mapDoc.load_file(mappedFileName.c_str());
			if (!result)
			{
				std::cerr << "Map Failed To Load. Error: " << result.description();
				return false;
			}
			else
			{
				if (clear)
				{
					Events.clear();
					InputEvents.clear();
					MapObjects.clear();
					MapObjectVisualizers.clear();
					Backgrounds.clear();
					addedSounds.clear();
				}
				for(xml_node map = mapDoc.child("map"); map; map = mapDoc.next_sibling("map"))
				{
					for(xml_node objlayer = map.child("objectgroup"); objlayer; objlayer = objlayer.next_sibling("objectgroup"))
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
						name = objlayer.attribute("name").value();
						lwidth = objlayer.attribute("width").as_int();
						lheight = objlayer.attribute("height").as_int();
						xml_node layerProperties = objlayer.child("properties");
						std::string lowerName = name;
						boost::algorithm::to_lower(lowerName);
						int ChestCount = 0;
						int exitCount = 0;
						int transitionCount = 0;
						if (lowerName == "chests" || lowerName == "chest")
						{
							for (xml_node obj = objlayer.child("object"); obj; obj = obj.next_sibling("object"))
							{
								std::string objType = obj.attribute("type").value();
								boost::algorithm::to_lower(objType);
								if (objType == "chest")
								{
									int tilex = 0;
									int tiley = 0;
									int layer = 0;
									bool locked = false;
									std::string chestName = "Chest" + boost::lexical_cast<std::string>(ChestCount);
									std::string chestStyle = "Default";
									tilex = obj.attribute("x").as_int() / tileWidth;
									tiley = obj.attribute("y").as_int() / tileHeight;
									for (xml_node objPrs = obj.child("properties"); objPrs; objPrs = objPrs.next_sibling("properties"))
									{
										for (xml_node objPr = objPrs.child("property"); objPr; objPr = objPr.next_sibling("property"))
										{
											std::string prName = objPr.attribute("name").value();
											boost::algorithm::to_lower(prName);
											if (prName == "contents")
											{

											}
											else if (prName == "layer")
											{
												layer = objPr.attribute("value").as_int();
											}
											else if (prName == "name" || prName == "chestname")
											{
												chestName = objPr.attribute("value").value();
											}
											else if (prName == "style")
											{
												chestStyle = objPr.attribute("style").value();
											}
										}
									}
									//auto newChest = boost::shared_ptr<MapObject>(new MapChest(chestName, tilex, tiley, layer));
									//MapObjects[chestName] = newChest;
									//auto chestVis = boost::shared_ptr<MapObjectVisualizer>(newChest->GenerateVisualizer());//new MapObjectVisualizer(newChest.get()));
									//newChest->RegisterComponent("ChestVisualizer", chestVis);
									//newChest->RegisterComponent()
									//MapObjects[layer][tilex][tiley][chestName] = newChest;
									//MapObjectVisualizers[layer].push_back(chestVis);//[tilex][tiley][chestName] = chestVis;
									++ChestCount;
								}
							}
						}
						else if (lowerName == "npc" || lowerName == "npcs")
						{
							for (xml_node obj = objlayer.child("object"); obj; obj = obj.next_sibling("object"))
							{
								std::string objType = obj.attribute("type").value();
								boost::algorithm::to_lower(objType);
								{
									if (objType == "chest")
									{
										int startX = 0;
										int startY = 0;
										int startLayer = 0;
									}

								}
							}
						}
						else if (lowerName == "layer transitions" || lowerName == "layertransitions")
						{
							for (xml_node obj = objlayer.child("object"); obj; obj = obj.next_sibling("object"))
							{
								bool validTransition = false;
								boost::unordered_map<int, int> transitionMapping;
								std::string objType = obj.attribute("type").value();
								boost::algorithm::to_lower(objType);
								{
									if (objType == "layer transition")
									{
										int tilex = obj.attribute("x").as_int() / tileWidth;
										int tiley = obj.attribute("y").as_int() / tileHeight;
										int width = obj.attribute("width").as_int() / tileWidth;
										int height = obj.attribute("height").as_int() / tileHeight;
										int layer = 0;

										int activelayer = 0;
										int targetlayer = 0;

										for (xml_node objPrs = obj.child("properties"); objPrs; objPrs = objPrs.next_sibling("properties"))
										{
											for (xml_node objPr = objPrs.child("property"); objPr; objPr = objPr.next_sibling("property"))
											{
												std::string prName = objPr.attribute("name").value();
												boost::algorithm::to_lower(prName);
												if (prName == "transitions")
												{

													std::vector<std::string> frags;
													std::string transVal(objPr.attribute("value").value()); 
													boost::split(frags, transVal, boost::is_any_of(","));
													for (auto tSet = frags.begin(); tSet != frags.end(); ++tSet)
													{
														std::vector<std::string> tFrags;
														boost::split(tFrags, *tSet, boost::is_any_of(">"));
														if (tFrags.size() >= 2)
														{
															validTransition = true;
															boost::trim(tFrags[0]);
															boost::to_lower(tFrags[0]);
															boost::trim(tFrags[1]);
															boost::to_lower(tFrags[1]);
															transitionMapping[boost::lexical_cast<int>(tFrags[0])] = boost::lexical_cast<int>(tFrags[1]);
															/*for (unsigned int i = 0; i < tFrags.size(); ++i)
															{
															boost::trim(tFrags[i]);
															boost::to_lower(tFrags[i]);
															if (i == 0)
															activelayer = boost::lexical_cast<int>(tFrags[i]);
															if (i == 1)
															targetlayer = boost::lexical_cast<int>(tFrags[i]);
															}*/
														}
													}


												}
											}
										}
										if (validTransition)
										{
											std::string transLayerName = "LayerTransition" + boost::lexical_cast<std::string>(transitionCount);
											auto transLayerObject = boost::shared_ptr<MapObject>(new MapObject(transLayerName, tilex, tiley, layer));

											boost::shared_ptr<LayerTransitionComponent> transcomp;
											if (width > 1 || height > 1)
											{
												sf::IntRect exitArea(0, 0, width, height);
												transcomp = boost::shared_ptr<LayerTransitionComponent>(new AreaLayerTransitionComponent(transLayerObject.get(), exitArea, transLayerName));
												transLayerObject->RegisterComponent(MapEventIndex, transcomp);
											}
											else
											{
												transcomp = boost::shared_ptr<LayerTransitionComponent>(new LayerTransitionComponent(transLayerObject.get(), transLayerName));
												transLayerObject->RegisterComponent(MapEventIndex, transcomp);
											}
											for (auto transMap = transitionMapping.begin(); transMap != transitionMapping.end(); ++ transMap)
											{
												transcomp->AddLayerTransition(transMap->first, transMap->second);
											}
											AddObject(transLayerName, transLayerObject);
											++transitionCount;
										}
									}
								}
							}
						}
						else if (lowerName == "exits")
						{
							for (xml_node obj = objlayer.child("object"); obj; obj = obj.next_sibling("object"))
							{
								std::string objType = obj.attribute("type").value();
								boost::algorithm::to_lower(objType);
								{
									if (objType == "exit")
									{
										int tilex = obj.attribute("x").as_int() / tileWidth;
										int tiley = obj.attribute("y").as_int() / tileHeight;
										int width = obj.attribute("width").as_int() / tileWidth;
										int height = obj.attribute("height").as_int() / tileHeight;
										int layer = 0;
										int targetx = 0;
										int targety = 0; 
										int targetlayer = 0;
										std::string targetMapName;
										std::string targetMapFile;

										for (xml_node objPrs = obj.child("properties"); objPrs; objPrs = objPrs.next_sibling("properties"))
										{
											for (xml_node objPr = objPrs.child("property"); objPr; objPr = objPr.next_sibling("property"))
											{
												std::string prName = objPr.attribute("name").value();
												boost::algorithm::to_lower(prName);
												if (prName == "active layer")
												{
													layer = objPr.attribute("value").as_int();
												}
												else if (prName == "target map")
												{
													targetMapFile =  objPr.attribute("value").value();
												}
												else if (prName == "target position")
												{
													std::vector<std::string> frags;
													std::string posVal(objPr.attribute("value").value()); 
													boost::split(frags, posVal, boost::is_any_of(":;,"));
													for (unsigned int i = 0; i < frags.size(); ++i)
													{
														boost::trim(frags[i]);
														boost::to_lower(frags[i]);
														switch(i)
														{
														case 0:
															targetx = (frags[i] == "carry" ? -1 : boost::lexical_cast<int>(frags[i]));
															break;
														case 1:
															targety = (frags[i] == "carry" ? -1 : boost::lexical_cast<int>(frags[i]));
															break;
														case 2:
															targetlayer = (frags[i] == "carry" ? -1 : boost::lexical_cast<int>(frags[i]));
															break;
														}
													}
												}
											}
										}

										if (targetMapName.empty() && !targetMapFile.empty())
										{
											targetMapName = targetMapFile;
										}
										else if (!targetMapName.empty() && targetMapFile.empty())
										{
											targetMapFile = targetMapName;
										}
										std::string exitName = "Exit" + boost::lexical_cast<std::string>(exitCount);
										auto exitObject = boost::shared_ptr<MapObject>(new MapObject(exitName, tilex, tiley, layer));
										if (width > 1 || height > 1)
										{
											sf::IntRect exitArea(0, 0, width, height);
											auto aexitcomp = boost::shared_ptr<MapEventComponent>(new AreaMapExitComponent(exitObject.get(), exitArea, targetMapName, targetMapFile, targetx, targety, targetlayer));
											exitObject->RegisterComponent(MapEventIndex, aexitcomp);
											//Area Exit
										}
										else
										{
											auto exitcomp = boost::shared_ptr<MapEventComponent>(new MapExitComponent(exitObject.get(), targetMapName, targetMapFile, targetx, targety, targetlayer));
											exitObject->RegisterComponent(MapEventIndex, exitcomp);
											//Single Tile Exit
										}
										AddObject(exitName, exitObject);
										++exitCount;
									}
								}
							}
						}
					}
				}
				std::string scriptFile = MapProperties["Script"];
				if (scriptFile != "")
				{
					PrimaryEngine->GetPythonScripter().AddScriptObject<GameMap>(std::string("CurrentMap"), *this, PrimaryEngine->GetPythonScripter().GetMappingModule());
					PrimaryEngine->GetPythonScripter().RunFile(scriptFile);
				}
				std::string MusicFile = MapProperties["Music"];
				if (MusicFile != "")
				{
					std::vector<std::string> fragments;
					boost::split(fragments, MusicFile, boost::is_any_of(","));
					switch(fragments.size())
					{
					case 1:
						PrimaryEngine->GetSoundSystem().AddSound(fragments[0], fragments[0], true);
						addedSounds.push_back(fragments[0]);
						break;
					case 2:
						PrimaryEngine->GetSoundSystem().AddSound(fragments[0], fragments[1], true);
						addedSounds.push_back(fragments[1]);
						break;
					case 3:
						PrimaryEngine->GetSoundSystem().AddSound(fragments[0], fragments[1], true, true, false, fragments[2].c_str());
						addedSounds.push_back(fragments[1]);
						break;
					}
				} 

				auto background = MapProperties.find("Background");
				if (background != MapProperties.end())
				{
					auto BackgroundString = background->second;
					std::vector<std::string> fragments;
					boost::split(fragments, BackgroundString, boost::is_any_of(","));
					switch(fragments.size())
					{
					case 1:
						Backgrounds.push_back(Graphics::AnimatedSprite(PrimaryEngine->GetContentManager().RequestTexture(fragments[0], Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::Background, PrimaryEngine->GetTime())));
						break;
					}
				}
			}
			return true;
		}

		void GameMap::BuildMap(const std::string& filename)
		{

		}

		GameMap::RawClonePtr GameMap::RawClone() const
		{
			return new GameMap(*this);
		}

		GameMap::~GameMap()
		{

		}
	}
}