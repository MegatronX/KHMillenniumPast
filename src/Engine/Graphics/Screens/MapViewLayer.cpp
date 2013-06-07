#include "MapViewLayer.h"
#include <boost/bind.hpp>
#include <graphics/Screens/ScreenManager.h>
const sf::Uint32 InputRate = 200;
namespace Cache
{
	enum GameStyle;
	enum World;
	enum ResourceClass;
}
namespace Graphics
{
	namespace Screens
	{
		MapViewLayer::MapViewLayer(Engine* engine) : Screen("Map Layer", engine, -1)
		{

		}
		MapViewLayer::MapViewLayer(Engine* engine, std::string &mapFile, sf::Vector2f &startPos, sf::RenderWindow* window, std::string &name, int layerID)
			: Screen(name, engine, layerID == -1 ? (engine != nullptr ? engine->GetUID() : -1) : layerID), LastInputUpdate(0), GameWindow(window)
		{
			game_map = boost::shared_ptr<Game::Mapping::GameMap>(new Game::Mapping::GameMap(engine->GetContentManager().GetMapDirectory() + mapFile, name, engine));//Game::Mapping::GameMap::LoadMapFromXML(mapFile, name);
			//map = TileMap::LoadMapFromXML(mapFile, name);
			//this->PrimaryWindow = window;
			CharacterView = sf::View(window->getView());
			//MapCharacter.SetMapPosition(startPos);


			//std::vector<Graphics::RowDescriptionTuple> rowDescriptors;
			//Down up left right

			//Graphics::RowDescriptionTuple newTuple(Graphics::RowClass::Down, 16, std::vector<int>(32, 32), 1, 0);

			//MapCharacter.characterSprite.AddTranslationEvent(std::string("MoveEvent"), &MapViewLayer::CharacterHookEvent);

			CharacterView.setCenter(startPos);
			game_map->PlayMusic();

		}
		/*MapViewLayer::MapViewLayer(Engine* engine, std::string &mapFile, sf::Vector2f &startPos, sf::RenderWindow* window, std::string &name, int layerID, bool draw, Game::Character::Party* _party, bool drawcaller, bool updatecaller)
			: Screen(name, engine, engine->GetUID()), CharacterView(window->GetView()), LastInputUpdate(0), GameWindow(window)
		{
			game_map = boost::shared_ptr<Game::Mapping::GameMap>(new Game::Mapping::GameMap(engine->GetContentManager()->GetMapDirectory() + mapFile, name, engine));//Game::Mapping::GameMap::LoadMapFromXML(mapFile, name);
			//map = TileMap::LoadMapFromXML(mapFile, name);
			//this->PrimaryWindow = window;
			party = _party;
			//CharacterView = sf::View(window->GetView());
			/*MapCharacter.SetMapPosition(startPos);
			MapCharacter.SetMapTilePosition(sf::Vector2f(startPos.x / game_map->GetTileWidth(), startPos.y / game_map->GetTileHeight()));
			MapCharacter.SetFollowInX(true);
			MapCharacter.SetFollowInY(true);

			//MapCharacter.SetMapPosition(startPos);
			std::vector<Graphics::RowDescriptionTuple> rowDescriptors;
			rowDescriptors.push_back(Graphics::RowDescriptionTuple(Graphics::RowClass::Down, 16, std::vector<int>(2, 16), 1, 0));
			rowDescriptors.push_back(Graphics::RowDescriptionTuple(Graphics::RowClass::Up, 16, std::vector<int>(2, 16), 1, 0));
			rowDescriptors.push_back(Graphics::RowDescriptionTuple(Graphics::RowClass::Left, 16, std::vector<int>(2, 16), 1, 0));
			rowDescriptors.push_back(Graphics::RowDescriptionTuple(Graphics::RowClass::Right, 16, std::vector<int>(2, 16), 1, 0));
			//Cache::GameStyle style = Cache::GameStyle::FFV;
			auto bSprite = engine->GetContentManager()->RequestTexture(std::string("BartzOverworld"), Cache::GameStyle::FFV, Cache::World::FF_V, Cache::ResourceClass::OverworldSprite, 600);
			
			bSprite->SetSmooth(true);
			MapCharacter.characterSprite = Graphics::AnimatedSprite(bSprite, rowDescriptors, 6, false, Graphics::AnimType::SingleLoop);
			MapCharacter.characterSprite.SetScale(2, 2);
			MapCharacter.characterSprite.SetPosition(FindTileBasedCenter(sf::Vector2f(window->GetWidth(), window->GetHeight())));

			MapCharacter.AddTranslationElapsedEvent(std::string("ExitsFunction"), [&]()
			{
				for (auto exit = this->game_map->GetExits().begin(); exit != this->game_map->GetExits().end(); ++exit)
				{
					if ((*exit).get<0>() == MapCharacter.GetMapTilePosition().x && (*exit).get<1>() == MapCharacter.GetMapTilePosition().y && exit->get<2>() == MapCharacter.GetLayer())
					{
						ChangeMapViaMapExit(*exit);
						break;
					}
				}
			});
			MapCharacter.AddTranslationElapsedEvent(std::string("MoveEvent"), [&]()
			{
				this->game_map->CallMoveFunction(*party, MapCharacter);
				this->MapCharacter.SetFollowInX(false);
				this->MapCharacter.SetFollowInY(false);
			});*/

			//CharacterView.setCenter(startPos);
			//game_map->PlayMusic();
		//}
		void MapViewLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			states.transform *= GetTransformConst();
			sf::View prevView = target.getView();
			bool restoreView = true;
			target.setView(CharacterView);
			if (restoreView)
				target.setView(prevView);
		}
		//Animated Draw
		/*void MapViewLayer::Draw(sf::RenderWindow &window)
		{
			//MapCharacter.characterSprite.SetColor(sf::Color(255, 255, 255, 255));
			sf::View prevView = window.getView();
			bool restoreView = true;
			window.setView(CharacterView);
			//game_map->Draw(window);//, MapCharacter, prevView);
			//map->Draw(window, MapCharacter, prevView);
			if (restoreView)
				window.setView(prevView);
		}
		void MapViewLayer::Draw(sf::RenderWindow &window, sf::Shader &shader)
		{
			sf::View prevView = window.getView();
			bool restoreView = false;
			window.setView(CharacterView);
			//game_map->Draw(window, shader);
			//map->Draw(window, shader, MapCharacter, prevView);
			if (restoreView)
				window.setView(prevView);
		}*/
		void MapViewLayer::Update(const sf::Uint32 time, const float timescale)
		{
			//InputModule* module = &(engine->GetInputModule());
			//HandleInputs(time, *(engine->GetInputModule()));
			/*for (auto it = Backgrounds.begin(); it != Backgrounds.end(); ++it)
			{
				it->Update(time, timescale);
			}*/
			game_map->Update(time, timescale);
			//map->Update(time);
			//MapCharacter.Update(time, timescale);
		}
		void MapViewLayer::Update(const float time, const float timescale)
		{
			Update(static_cast<sf::Uint32>(time * 1000), timescale);
		}
		//Not Finished
		sf::Vector2f MapViewLayer::FindTileBasedCenter(const sf::Vector2f windowSize, const sf::Vector2f offset)
		{
			int xTiles = (int)(windowSize.x / game_map->GetTileWidth());
			int yTiles = (int)(windowSize.y / game_map->GetTileHeight());
			return sf::Vector2f((xTiles * 0.5) * game_map->GetTileWidth() + offset.x, (yTiles * 0.5) * game_map->GetTileHeight() + offset.y);
		}
		void MapViewLayer::ChangeMaps(std::string &newMap, std::string &newmapname, MapExit &exit)
		{
			game_map = boost::shared_ptr<Game::Mapping::GameMap>(new Game::Mapping::GameMap(newMap, newmapname, engine));
			sf::Vector2f startPos(exit.get<5>(), exit.get<6>());
			/*MapCharacter.SetLayer(exit.get<7>());
			MapCharacter.SetMapPosition(startPos);
			MapCharacter.SetMapTilePosition(sf::Vector2f(startPos.x / game_map->GetTileWidth(), startPos.y / game_map->GetTileHeight()));
			MapCharacter.SetFollowInX(true);
			MapCharacter.SetFollowInY(true);
			CharacterView.SetCenter(startPos);*/
		}
		void MapViewLayer::ChangeMapViaMapExit(MapExit exit)
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

		/*bool MapViewLayer::HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult)
		{

		}
		bool MapViewLayer::HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult)
		{

		}*/

	}
}
