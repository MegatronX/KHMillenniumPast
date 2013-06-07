#include "GameMapViewScreen.h"
#include <components/InputComponent.h>
#include <Mapping\MapCharacterMovementHandler.h>
#include <Mapping\MapSpawns.h>
#include <Graphics\Screens\BattleScreen.h>
#include <GameInstance.h>
namespace Game
{
	using namespace Mapping;
	namespace Graphics
	{
		namespace Screens
		{
			GameMapViewScreen::GameMapViewScreen(Engine* engine) : Screen("Game Map Layer", engine, -1)
			{

			}
			GameMapViewScreen::GameMapViewScreen(Engine* engine, const std::string &mapFile, const sf::Vector2f &startPos, const int startingLayer, sf::RenderTarget* window, const std::string &name, const std::string& mapCharName, const int layerID)
				: Screen(name, engine, layerID == -1 ? (engine != nullptr ? engine->GetUID() : -1) : layerID), LastInputUpdate(0), GameWindow(window), WindowSize(window != nullptr ? sf::Vector2f(window->getSize().x, window->getSize().y) : sf::Vector2f(800, 600)),
				FarBottomRightOffset(0.f, 0.f), FarBottomRightPoint(0.f, 0.f), FarTopLeftOffset(0.f, 0.f), FarTopLeftPoint(0.f, 0.f), LastCharDir(None)
			{
				game_map = boost::shared_ptr<Game::Mapping::GameMap>(new Game::Mapping::GameMap(engine->GetContentManager().GetMapDirectory() + mapFile, name, engine));//Game::Mapping::GameMap::LoadMapFromXML(mapFile, name);
				//map = TileMap::LoadMapFromXML(mapFile, name);
				//this->PrimaryWindow = window;
				CharacterView = sf::View(window->getView());
				HalfWindowSize = WindowSize * 0.5f;
				MapChar.CharSpr.SetTexture(engine->GetContentManager().RequestTexture("ArianBase", Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::Guardian, engine->GetTime()));

				auto size = window->getSize();
				auto sprsize = sf::Vector2f(static_cast<float>(MapChar.CharSpr.GetBaseSprite().getTextureRect().width), static_cast<float>(MapChar.CharSpr.GetBaseSprite().getTextureRect().height));

				auto cen = FindTileBasedCenter(sf::Vector2f(size.x, size.y));

				MapChar.ViewOffset.x = -game_map->GetTileWidth();
				MapChar.ViewOffset.y = -sprsize.y + game_map->GetTileHeight();
				MapChar.CharSpr.SetPosition(cen + MapChar.ViewOffset - sf::Vector2f(16, -16));

				FarTopLeftOffset.x = game_map->GetTileWidth() / 2;
				FarTopLeftOffset.y = game_map->GetTileHeight() / 2;//game_map->GetTileHeight() * 2;
				FarBottomRightOffset.x = game_map->GetTileWidth() / 2;
				FarBottomRightOffset.y = game_map->GetTileWidth() / 2;//-game_map->GetTileWidth();

				FarTopLeftPoint.x = GameWindow->getSize().x * 0.5f;
				FarTopLeftPoint.x = FarTopLeftPoint.x - static_cast<float>(static_cast<int>(FarTopLeftPoint.x) % game_map->GetTileWidth()) + FarTopLeftOffset.x;
				FarTopLeftPoint.y = GameWindow->getSize().y * 0.5f;
				FarTopLeftPoint.y = FarTopLeftPoint.y - static_cast<float>(static_cast<int>(FarTopLeftPoint.y) % game_map->GetTileHeight()) + FarTopLeftOffset.y;

				FarBottomRightPoint.x = game_map->GetWidth() - GameWindow->getSize().x * 0.5f;
				FarBottomRightPoint.x = FarBottomRightPoint.x - static_cast<float>(static_cast<int>(FarBottomRightPoint.x) % game_map->GetTileWidth()) + FarBottomRightOffset.x;
				FarBottomRightPoint.y = game_map->GetHeight() - GameWindow->getSize().y * 0.5f;
				FarBottomRightPoint.y = FarBottomRightPoint.y - static_cast<float>(static_cast<int>(FarBottomRightPoint.y) % game_map->GetTileHeight()) + FarBottomRightOffset.y;
				/*MapChar.FollowInX = true;
				MapChar.FollowInY = true;
				MapChar.EdgeGuard = true;

				MapChar.ViewOffset.x = -32;
				MapChar.ViewOffset.y = -sprsize.y + 32;
				MapChar.CharSpr.SetPosition(cen + MapChar.ViewOffset);

				MapChar.FarLeftLimit = GameWindow->getSize().x * 0.5f;// + static_cast<float>(game_map->GetTileWidth());
				MapChar.FarRightLimit = game_map->GetWidth() - GameWindow->getSize().x * 0.5f;// - static_cast<float>(game_map->GetTileWidth());
				MapChar.FarLeftLimit = MapChar.FarLeftLimit - static_cast<float>(static_cast<int>(MapChar.FarLeftLimit) % game_map->GetTileWidth());

				MapChar.FarUpLimit = GameWindow->getSize().y * 0.5f;// + static_cast<float>(game_map->GetTileHeight());
				MapChar.FarDownLimit = game_map->GetHeight() - GameWindow->getSize().y * 0.5f;// + static_cast<float>(game_map->GetTileHeight());

				MapChar.FarUpLimit = MapChar.FarUpLimit - static_cast<float>(static_cast<int>(MapChar.FarUpLimit) % game_map->GetTileHeight());

				MapChar.HalfWindowSize = HalfWindowSize;
				MapChar.WindowSize = WindowSize;*/

				CharacterView.setCenter(startPos);// + MapChar.ViewOffset);
				MapChar.DeterminedSpritePos = MapChar.CharSpr.GetPosition();
				//CharacterView.setCenter(cen);
				MapChar.MapPosition = startPos;
				MapChar.MapTilePosition = sf::Vector2f(startPos.x / game_map->GetTileWidth(), startPos.y / game_map->GetTileHeight());
				MapChar.DrawLayer = startingLayer;
				MapChar.AttachedGameMap = game_map.get();
				MapChar.AddFinishedEvent("MovementContinue", boost::bind(&GameMapViewScreen::ContinuedDirectionHandler, this, _1));
				MapChar.AddFinishedEvent("MapHandlerEvent", boost::bind(&GameMapViewScreen::HandleMapCharacterMovementEvent, this, _1));
				MapChar.AddFinishedEvent("SpawnEvent", boost::bind(&GameMapViewScreen::CheckForSpawn, this, _1));
				game_map->SetMapCharacter(&MapChar);
				MapChar.CharacterName = mapCharName;
				if (mapCharName.size() > 0)
				{
					std::string animFile(mapCharName + " Walk");
					auto cr = engine->GetContentManager().RequestTexture(animFile, Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::Guardian, engine->GetTime());

					MapChar.CharSpr = ::Graphics::AnimatedSprite(cr,false);


					bool validData = false;
					auto & sprData = engine->GetContentManager().RequestSpriteImportData(animFile, Cache::GameStyle::Main, validData);
					if(validData)
					{
						::Graphics::SpriteImportData::ApplySpriteDataToSprite(sprData, MapChar.CharSpr);
						MapChar.CharSpr.GetAnimator().playAnimation("WalkLeft", true);
					}
					sf::Uint32 time = engine->GetTime();
					MapChar.CharSpr.GetAnimator().setLastUpdate(time);
					MapChar.CharSpr.GetAnimator().setFPS("WalkLeft", 5.f);
					MapChar.CharacterName = mapCharName;
					//::Graphics::AnimatedSprite aspr(cr, false);
				}

				//game_map->PlayMusic();

				//game_map->AddLayerTransition(38, 18, -5, MapChar.DrawLayer);
				//game_map->AddLayerTransition(37, 18, MapChar.DrawLayer, -5);
				//MapChar.DrawLayer = 4;
			}

			void GameMapViewScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
			{
				auto tempView = target.getView();
				sf::View PrevView = tempView;
				sf::Vector2f prevCenter = PrevView.getCenter();
				sf::Vector2f newCenter = prevCenter;
				sf::Vector2f spritePos = MapChar.CharSpr.GetPosition();
				if (MapChar.MapPosition.x < FarTopLeftPoint.x)
				{
					spritePos.x = MapChar.MapPosition.x + MapChar.ViewOffset.x * 0.5 - FarTopLeftOffset.x;
					newCenter.x = FarTopLeftPoint.x;
				}
				else if (MapChar.MapPosition.x > FarBottomRightPoint.x)
				{
					spritePos.x = MapChar.DeterminedSpritePos.x + MapChar.MapPosition.x - FarBottomRightPoint.x;// - FarBottomRightOffset.x;
					newCenter.x = FarBottomRightPoint.x;
				}
				else
				{
					spritePos.x = MapChar.DeterminedSpritePos.x;
					newCenter.x = MapChar.MapPosition.x;
				}
				if (MapChar.MapPosition.y < FarTopLeftPoint.y)
				{
					spritePos.y = MapChar.MapPosition.y + MapChar.ViewOffset.y - FarTopLeftOffset.y;
					newCenter.y = FarTopLeftPoint.y;
				}
				else if (MapChar.MapPosition.y > FarBottomRightPoint.y)
				{
					spritePos.y = MapChar.DeterminedSpritePos.y + MapChar.MapPosition.y - FarBottomRightPoint.y;// - FarBottomRightOffset.y;
					newCenter.y = FarBottomRightPoint.y;
				}
				else
				{
					spritePos.y = MapChar.DeterminedSpritePos.y;
					newCenter.y = MapChar.MapPosition.y;
				}
				if (newCenter != prevCenter)
				{
					tempView.setCenter(newCenter);
				}
				//CONST CAST BAD BAD BAD BADDDDDDDDDDDDDDDD
				const_cast<GameMapViewScreen*>(this)->MapChar.CharSpr.SetPosition(spritePos);
				//MapChar.CharSpr.SetPosition(spritePos);
				target.setView(tempView);
				game_map->draw(target, states);
				//game_map->Draw(window, MapChar, PrevView);
				target.setView(PrevView);
			}
			
			void GameMapViewScreen::Draw(sf::RenderTarget &window)
			{
				if (!Drawing)
					return;
				MapView = window.getView();
				sf::View PrevView = MapView;
				sf::Vector2f prevCenter = window.getView().getCenter();
				sf::Vector2f newCenter = prevCenter;
				sf::Vector2f spritePos = MapChar.CharSpr.GetPosition();
				if (MapChar.MapPosition.x < FarTopLeftPoint.x)
				{
					spritePos.x = MapChar.MapPosition.x + MapChar.ViewOffset.x * 0.5 - FarTopLeftOffset.x;
					newCenter.x = FarTopLeftPoint.x;
				}
				else if (MapChar.MapPosition.x > FarBottomRightPoint.x)
				{
					spritePos.x = MapChar.DeterminedSpritePos.x + MapChar.MapPosition.x - FarBottomRightPoint.x;// - FarBottomRightOffset.x;
					newCenter.x = FarBottomRightPoint.x;
				}
				else
				{
					spritePos.x = MapChar.DeterminedSpritePos.x;
					newCenter.x = MapChar.MapPosition.x;
				}
				if (MapChar.MapPosition.y < FarTopLeftPoint.y)
				{
					spritePos.y = MapChar.MapPosition.y + MapChar.ViewOffset.y - FarTopLeftOffset.y;
					newCenter.y = FarTopLeftPoint.y;
				}
				else if (MapChar.MapPosition.y > FarBottomRightPoint.y)
				{
					spritePos.y = MapChar.DeterminedSpritePos.y + MapChar.MapPosition.y - FarBottomRightPoint.y;// - FarBottomRightOffset.y;
					newCenter.y = FarBottomRightPoint.y;
				}
				else
				{
					spritePos.y = MapChar.DeterminedSpritePos.y;
					newCenter.y = MapChar.MapPosition.y;
				}
				if (newCenter != prevCenter)
				{
					MapView.setCenter(newCenter);
				}
				MapChar.CharSpr.SetPosition(spritePos);
				window.setView(MapView);
				game_map->Draw(window, MapChar, PrevView);
				window.setView(PrevView);
			}
			
			void GameMapViewScreen::Draw(sf::RenderTarget &window, sf::RenderStates states)
			{
				if (!Drawing)
					return;
				MapView = window.getView();
				sf::View PrevView = MapView;
				sf::Vector2f prevCenter = window.getView().getCenter();
				sf::Vector2f newCenter = prevCenter;
				sf::Vector2f spritePos = MapChar.CharSpr.GetPosition();
				if (MapChar.MapPosition.x < FarTopLeftPoint.x)
				{
					spritePos.x = MapChar.MapPosition.x + MapChar.ViewOffset.x * 0.5 - FarTopLeftOffset.x;
					newCenter.x = FarTopLeftPoint.x;
				}
				else if (MapChar.MapPosition.x > FarBottomRightPoint.x)
				{
					spritePos.x = MapChar.DeterminedSpritePos.x + MapChar.MapPosition.x - FarBottomRightPoint.x;// - FarBottomRightOffset.x;
					newCenter.x = FarBottomRightPoint.x;
				}
				else
				{
					spritePos.x = MapChar.DeterminedSpritePos.x;
					newCenter.x = MapChar.MapPosition.x;
				}
				if (MapChar.MapPosition.y < FarTopLeftPoint.y)
				{
					spritePos.y = MapChar.MapPosition.y + MapChar.ViewOffset.y - FarTopLeftOffset.y;
					newCenter.y = FarTopLeftPoint.y;
				}
				else if (MapChar.MapPosition.y > FarBottomRightPoint.y)
				{
					spritePos.y = MapChar.DeterminedSpritePos.y + MapChar.MapPosition.y - FarBottomRightPoint.y;// - FarBottomRightOffset.y;
					newCenter.y = FarBottomRightPoint.y;
				}
				else
				{
					spritePos.y = MapChar.DeterminedSpritePos.y;
					newCenter.y = MapChar.MapPosition.y;
				}
				if (newCenter != prevCenter)
				{
					MapView.setCenter(newCenter);
				}
				MapChar.CharSpr.SetPosition(spritePos);
				window.setView(MapView);
				game_map->Draw(window, states, MapChar, PrevView);
				window.setView(PrevView);
			}

			/*void GameMapViewScreen::Draw(sf::RenderWindow &window)
			{
			MapView = window.getView();
			sf::View PrevView = MapView;
			sf::Vector2f prevCenter = window.getView().getCenter();
			sf::Vector2f newCenter = prevCenter;
			sf::Vector2f spritePos = MapChar.CharSpr.GetPosition();
			if (MapChar.IsFarLeft)
			{
			spritePos.x = MapChar.MapPosition.x + MapChar.ViewOffset.x;
			newCenter.x = MapChar.FarLeftLimit;
			}
			else if (MapChar.IsFarRight)
			{
			spritePos.x = MapChar.DeterminedSpritePos.x + MapChar.MapPosition.x - MapChar.FarRightLimit;
			newCenter.x = MapChar.FarRightLimit;
			}
			else
			{
			spritePos.x = MapChar.DeterminedSpritePos.x;
			newCenter.x = MapChar.MapPosition.x;
			}
			if (MapChar.IsFarUp)
			{
			//MapChar.CharSpr.SetPosition(MapChar.CharSpr.GetPosition().x, MapChar.MapPosition.y + MapChar.ViewOffset.y);
			spritePos.y = MapChar.MapPosition.y + MapChar.ViewOffset.y;
			newCenter.y = MapChar.FarUpLimit;
			}
			else if (MapChar.IsFarDown)
			{
			spritePos.y = MapChar.DeterminedSpritePos.y + MapChar.MapPosition.y - MapChar.FarDownLimit;
			newCenter.y = MapChar.FarDownLimit;
			}
			else
			{
			spritePos.y = MapChar.DeterminedSpritePos.y;
			//MapChar.CharSpr.SetPosition(MapChar.CharSpr.GetPosition().x, MapChar.DeterminedSpritePos.y);
			newCenter.y = MapChar.MapPosition.y;
			}
			if (newCenter != prevCenter)
			{
			MapView.setCenter(newCenter);
			}
			MapChar.CharSpr.SetPosition(spritePos);
			MapView.setRotation(30.f);
			window.setView(MapView);
			game_map->Draw(window, MapChar, PrevView);
			window.setView(PrevView);
			}*/

			/*void GameMapViewScreen::Draw(sf::RenderWindow &window)
			{
			sf::View prevView = window.getView();
			bool restoreView = false;
			if (MapChar.FollowInX || MapChar.FollowInY)
			{
			restoreView = true;
			auto NewCen = prevView.getCenter(); 
			if (MapChar.FollowInX)
			{
			NewCen.x = MapChar.MapPosition.x;
			}
			if (MapChar.FollowInY)
			{
			NewCen.y = MapChar.MapPosition.y;
			}
			CharacterView.setCenter(NewCen);// + MapChar.ViewOffset);
			//window.setView(CharacterView);

			}
			game_map->Draw(window, MapChar, CharacterView);//, MapCharacter, prevView);
			//map->Draw(window, MapCharacter, prevView);
			if (restoreView)
			window.setView(prevView);
			}*/
/*
			void GameMapViewScreen::Draw(sf::RenderWindow &window, sf::Shader &shader)
			{

				sf::View prevView = window.getView();
				bool restoreView = false;

				game_map->Draw(window, shader, MapChar, prevView);//, MapCharacter, prevView);
				//map->Draw(window, MapCharacter, prevView);
				if (restoreView)
					window.setView(prevView);
			}*/
			void GameMapViewScreen::Update(const sf::Uint32 time, const float timescale)
			{
				game_map->Update(time, timescale);
				MapChar.Update(time, timescale);

			}
			void GameMapViewScreen::Update(const float time, const float timescale)
			{
				Update(static_cast<sf::Uint32>(time * 1000), timescale);
			}
			//Not Finished
			sf::Vector2f GameMapViewScreen::FindTileBasedCenter(const sf::Vector2f windowSize, const sf::Vector2f offset)
			{
				int xTiles = (int)(windowSize.x / game_map->GetTileWidth());
				int yTiles = (int)(windowSize.y / game_map->GetTileHeight());
				return sf::Vector2f((xTiles * 0.5) * game_map->GetTileWidth() + offset.x, (yTiles * 0.5) * game_map->GetTileHeight() + offset.y);
			}
			void GameMapViewScreen::ChangeMaps(std::string &newMap, std::string &newmapname, MapExitComponent &exit)//std::string &newMap, std::string &newmapname, MapExit &exit)
			{
				game_map = boost::shared_ptr<Game::Mapping::GameMap>(new Game::Mapping::GameMap(newMap, newmapname, engine));
				//sf::Vector2f startPos(exit.get<5>(), exit.get<6>());
				/*MapCharacter.SetLayer(exit.get<7>());
				MapCharacter.SetMapPosition(startPos);
				MapCharacter.SetMapTilePosition(sf::Vector2f(startPos.x / game_map->GetTileWidth(), startPos.y / game_map->GetTileHeight()));
				MapCharacter.SetFollowInX(true);
				MapCharacter.SetFollowInY(true);
				CharacterView.SetCenter(startPos);*/
			}
			void GameMapViewScreen::ChangeMapViaMapExit(const MapExitComponent& exit)
			{
				/*game_map->ReleaseResources();
				game_map = boost::shared_ptr<Game::Mapping::GameMap>(new Game::Mapping::GameMap(engine->GetContentManager()->GetMapDirectory() + exit.get<3>(), exit.get<4>(), engine));
				sf::Vector2f startPos(exit.get<5>() * game_map->GetTileWidth(), exit.get<6>() * game_map->GetTileHeight());
				MapCharacter.SetLayer(exit.get<7>());
				MapCharacter.SetMapPosition(startPos);
				MapCharacter.SetMapTilePosition(sf::Vector2f(startPos.x / game_map->GetTileWidth(), startPos.y / game_map->GetTileHeight()));
				MapCharacter.SetFollowInX(true);
				MapCharacter.SetFollowInY(true);
				game_map->PlayMusic();*/
			}
			static sf::Uint32 TransTime = 100;
			bool GameMapViewScreen::HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult)
			{

				sf::Uint32 EffTime = TransTime;
				bool Handled = false;
				game_map->HandleKeyPressed(time, inputModule, actionResult);
				auto input = game_map->GetComponentAs<Components::InputComponent*>(MapInputComponentIndex);
				if (input != nullptr)
				{
					Handled = input->HandleKeyPressed(time, inputModule, actionResult);
				}
				if (!Handled && !MapChar.InTransit && actionResult.PInput == ::Input::P1Input)
				{
					switch(actionResult.IAction)
					{
					case ::Input::InputAction::Start:
						{
							//if (!engine->GetScreenManager().DoesStackExist("PauseScreen"))
							{
								engine->GetSoundSystem().Play("SelectionConfirm", 6, false);
								engine->GetPythonScripter().RunFile("PauseScreen.py");
								//std::cout << "Making Pause Screen\n";
								auto pscreen = engine->GetPythonScripter().RunFunction<::Graphics::Screens::screen_ptr>("MakePauseScreen");
								engine->GetScreenManager().AddScreen(pscreen, this->GetDrawPriority() + 1);
								Handled = true;
								break;
							}
						}
					case ::Input::InputAction::Up:
						{
							sf::Vector2f targetPosition = sf::Vector2f(MapChar.MapPosition.x, boost::math::round(MapChar.MapPosition.y - game_map->GetTileHeight()));
							sf::Vector2i tilePosition = sf::Vector2i(static_cast<int>(targetPosition.x / game_map->GetTileWidth()), static_cast<int>(targetPosition.y / game_map->GetTileHeight()));
							if (game_map->Walkable(tilePosition, MapChar.DrawLayer))
							{
								MapChar.SlideMapPosition(targetPosition, EffTime, time);
							}
							else
							{
								MapChar.SlideMapPosition(MapChar.MapPosition, EffTime, time);
							}
							if (LastCharDir != North)
							{
								LastCharDir = North;
								MapChar.CharSpr.GetAnimator().playAnimation("WalkUp", true);
							}
						}
						//MapChar.FollowInY = true;
						Handled = true;
						break;
					case ::Input::InputAction::Down:
						{
							sf::Vector2f targetPosition = sf::Vector2f(MapChar.MapPosition.x, boost::math::round(MapChar.MapPosition.y + game_map->GetTileHeight()));
							sf::Vector2i tilePosition = sf::Vector2i(static_cast<int>(targetPosition.x / game_map->GetTileWidth()), static_cast<int>(targetPosition.y / game_map->GetTileHeight()));
							if (game_map->Walkable(tilePosition, MapChar.DrawLayer))
							{
								MapChar.SlideMapPosition(targetPosition, EffTime, time);
							}
							else
							{
								MapChar.SlideMapPosition(MapChar.MapPosition, EffTime, time);
							}
							if (LastCharDir != South)
							{
								LastCharDir = South;
								MapChar.CharSpr.GetAnimator().playAnimation("WalkDown", true);
							}
						}
						//MapChar.FollowInY = true;
						Handled = true;
						break;
					case ::Input::InputAction::Left:
						{
							sf::Vector2f targetPosition = sf::Vector2f(boost::math::round(MapChar.MapPosition.x - game_map->GetTileWidth()), MapChar.MapPosition.y);
							sf::Vector2i tilePosition = sf::Vector2i(static_cast<int>(targetPosition.x / game_map->GetTileWidth()), static_cast<int>(targetPosition.y / game_map->GetTileHeight()));
							if (game_map->Walkable(tilePosition, MapChar.DrawLayer))
							{
								MapChar.SlideMapPosition(targetPosition, EffTime, time);
							}
							else
							{
								MapChar.SlideMapPosition(MapChar.MapPosition, EffTime, time);
							}
							if (LastCharDir != West)
							{
								LastCharDir = West;
								MapChar.CharSpr.GetAnimator().playAnimation("WalkLeft", true);
							}
						}
						//MapChar.FollowInX = true;
						Handled = true;
						break;
					case ::Input::InputAction::Right:
						{
							sf::Vector2f targetPosition = sf::Vector2f(boost::math::round(MapChar.MapPosition.x + game_map->GetTileWidth()), MapChar.MapPosition.y);
							sf::Vector2i tilePosition = sf::Vector2i(static_cast<int>(targetPosition.x / game_map->GetTileWidth()), static_cast<int>(targetPosition.y / game_map->GetTileHeight()));
							if (game_map->Walkable(tilePosition, MapChar.DrawLayer))
							{
								MapChar.SlideMapPosition(targetPosition, EffTime, time);
							}
							else
							{
								MapChar.SlideMapPosition(MapChar.MapPosition, EffTime, time);
							}
							if (LastCharDir != East)
							{
								LastCharDir = East;
								MapChar.CharSpr.GetAnimator().playAnimation("WalkRight", true);
							}
						}
						//MapChar.FollowInX = true;
						Handled = true;
						break;
					}
				}
				return Handled;
			}
			bool GameMapViewScreen::HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult)
			{
				bool Handled = false;
				game_map->HandleKeyReleased(time, inputModule, actionResult);
				auto input = game_map->GetComponentAs<Components::InputComponent*>(MapInputComponentIndex);
				if (input != nullptr)
				{
					Handled = input->HandleKeyReleased(time, inputModule, actionResult);
				}
				return Handled;
			}

			::Game::Mapping::MapCharacter& GameMapViewScreen::GetMapCharacter()
			{
				return MapChar;
			}

			void GameMapViewScreen::ContinuedDirectionHandler(Mapping::MapCharacter* ch)
			{
				if (engine != nullptr && !MapChar.InTransit)
				{
					sf::Uint32 EffTime = TransTime;
					auto time = engine->GetTime();
					auto &input = engine->GetInput();
					bool actpress = input.IsActionPushed(Input::PlayerInput::P1Input, Input::InputAction::Up);
					bool actpress2 = input.IsActionPushed(Input::PlayerInput::P1Input, Input::InputAction::Right);
					bool Moved = false;
					if (input.IsActionPushed(Input::PlayerInput::P1Input, Input::InputAction::Up))
					{
						sf::Vector2f targetPosition = sf::Vector2f(MapChar.MapPosition.x, boost::math::round(MapChar.MapPosition.y - game_map->GetTileHeight()));
						sf::Vector2i tilePosition = sf::Vector2i(static_cast<int>(targetPosition.x / game_map->GetTileWidth()), static_cast<int>(targetPosition.y / game_map->GetTileHeight()));
						if (game_map->Walkable(tilePosition, MapChar.DrawLayer))
						{
							sf::Vector2i adder = sf::Vector2i(0, -1);
							MapChar.SlideMapPosition(targetPosition, EffTime, time);
						}
						else
						{
							MapChar.SlideMapPosition(MapChar.MapPosition, EffTime, time);
						}
						Moved = true;
						if (LastCharDir != North)
						{
							LastCharDir = North;
							MapChar.CharSpr.GetAnimator().playAnimation("WalkUp", true);
						}
						//MapChar.FollowInY = true;
					}
					if (input.IsActionPushed(Input::PlayerInput::P1Input, Input::InputAction::Down))
					{
						sf::Vector2f targetPosition = sf::Vector2f(MapChar.MapPosition.x, boost::math::round(MapChar.MapPosition.y + game_map->GetTileHeight()));
						sf::Vector2i tilePosition = sf::Vector2i(static_cast<int>(targetPosition.x / game_map->GetTileWidth()), static_cast<int>(targetPosition.y / game_map->GetTileHeight()));
						if (game_map->Walkable(tilePosition, MapChar.DrawLayer))
						{
							sf::Vector2i adder = sf::Vector2i(0, 1);
							MapChar.SlideMapPosition(targetPosition, EffTime, time);
						}
						else
						{
							MapChar.SlideMapPosition(MapChar.MapPosition, EffTime, time);
						}
						Moved = true;
						if (LastCharDir != South)
						{
							LastCharDir = South;
							MapChar.CharSpr.GetAnimator().playAnimation("WalkDown", true);
						}
						//MapChar.FollowInY = true;
					}
					if (input.IsActionPushed(Input::PlayerInput::P1Input, Input::InputAction::Left))
					{
						sf::Vector2f targetPosition = sf::Vector2f(boost::math::round(MapChar.MapPosition.x - game_map->GetTileWidth()), MapChar.MapPosition.y);
						sf::Vector2i tilePosition = sf::Vector2i(static_cast<int>(targetPosition.x / game_map->GetTileWidth()), static_cast<int>(targetPosition.y / game_map->GetTileHeight()));
						if (game_map->Walkable(tilePosition, MapChar.DrawLayer))
						{
							sf::Vector2i adder = sf::Vector2i(-1, 0);
							MapChar.SlideMapPosition(targetPosition, EffTime, time);
						}
						else
						{
							MapChar.SlideMapPosition(MapChar.MapPosition, EffTime, time);
						}
						Moved = true;
						if (LastCharDir != West)
						{
							LastCharDir = West;
							MapChar.CharSpr.GetAnimator().playAnimation("WalkLeft", true);
						}

						//MapChar.FollowInX = true;
					}
					if (input.IsActionPushed(Input::PlayerInput::P1Input, Input::InputAction::Right))
					{
						sf::Vector2f targetPosition = sf::Vector2f(boost::math::round(MapChar.MapPosition.x + game_map->GetTileWidth()), MapChar.MapPosition.y);
						sf::Vector2i tilePosition = sf::Vector2i(static_cast<int>(targetPosition.x / game_map->GetTileWidth()), static_cast<int>(targetPosition.y / game_map->GetTileHeight()));
						if (game_map->Walkable(tilePosition, MapChar.DrawLayer))
						{
							sf::Vector2i adder = sf::Vector2i(1, 0);
							MapChar.SlideMapPosition(targetPosition, EffTime, time);
						}
						else
						{
							MapChar.SlideMapPosition(MapChar.MapPosition, EffTime, time);
						}
						Moved = true;
						if (LastCharDir != East)
						{
							LastCharDir = East;
							MapChar.CharSpr.GetAnimator().playAnimation("WalkLeft", true);
						}
						//MapChar.FollowInX = true;
					}

					if (!Moved)
					{
						//
						LastCharDir = None;
					}
				}
			}

			void GameMapViewScreen::HandleMapCharacterMovementEvent(Mapping::MapCharacter* mpchar)
			{
				//game_map->ProcessLayerChange(static_cast<int>(mpchar->MapTilePosition.x), static_cast<int>(mpchar->MapTilePosition.y), mpchar->DrawLayer, mpchar->DrawLayer);
				//game_map->ProcessEvents(static_cast<int>(mpchar->MapTilePosition.x), static_cast<int>(mpchar->MapTilePosition.y), mpchar->DrawLayer);
				game_map->ProcessEvents(*mpchar);
				auto mv = game_map->GetComponentAs<MapCharacterMovementHandlerComponent*>(MovementComponentIndex);
				if (mv != nullptr)
				{
					mv->HandleCharacterMovement(*game_map, *mpchar);
				}
			}

			void GameMapViewScreen::CheckForSpawn(Mapping::MapCharacter* mpchar)
			{
				auto spawner = game_map->GetComponentAs<MapSpawner*>(MapSpawnComponentIndex);
				if (spawner != nullptr)
				{
					if ((spawner->GetDeterminesSpawn() && spawner->DetermineIfSpawn(*game_map)) || (game_map->GetEncounterRate() > engine->GetRandomDouble(0.f, 1.f)))
					{
						std::cout << "Hit Spawn, spawning...\n";
						for (auto sound = game_map->GetAddedSounds().cbegin(); sound != game_map->GetAddedSounds().cend(); ++sound)
						{
							engine->GetSoundSystem().SetChannelPause(0);
						}
						auto party = spawner->DummySpawn();
						auto& bg = game_map->GetMapProperty("Battle Background");
						auto bscreen = boost::shared_ptr<BattleScreen>(new BattleScreen(engine, ActiveInstance->GetPlayerPartyPtr(), party, bg));
						engine->GetScreenManager().AddScreen(bscreen, this->GetDrawPriority() + 1);
						this->SetDrawing(false);
					}
				}
			}
		}
	}
}