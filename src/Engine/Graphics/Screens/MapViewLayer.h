#pragma once
#ifndef _MAPVIEWLAYER_H_
#define _MAPVIEWLAYER_H_
#include <string>
#include <Graphics\Screens\Screen.h>
#include <sfml\Graphics.hpp>
#include <sfml\System.hpp>
//#include <graphics/AnimatedSprite.h>
//#include <graphics/MapCharacterSprite.h>
#include <mapping/TileMap.h>
#include <mapping/GameMap.h>
#include <boost/shared_ptr.hpp>
#include <system/input/InputModule.h>
#include <character/Party.h>
#include <Engine.h>

namespace Graphics
{
	namespace Screens
	{
		struct MapCharacter
		{
			sf::Vector2i MapPosition;
			sf::Vector2i TilePosition;

			int DrawPriority;
		};
		class MapViewLayer : public Screens::Screen
		{
		public:
			MapViewLayer(Engine* engine);
			MapViewLayer(Engine* engine, std::string &mapFile, sf::Vector2f &startPos, sf::RenderWindow* window, std::string &name, int layerID = -1);
//			MapViewLayer(Engine* engine, std::string &mapFile, sf::Vector2f &startPos, sf::RenderWindow* window, std::string &name, int layerID, bool draw, Game::Character::Party* party, bool drawcaller = true, bool updatecaller = true);
			//Animated Draw
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
			/*
			virtual void Draw(sf::RenderWindow &window) override;
			virtual void Draw(sf::RenderWindow &window, sf::Shader &shader) override;*/
			virtual void Update(const float time, const float TimeScale = 1.0) override;
			virtual void Update(const sf::Uint32 time, const float timescale = 1.0) override;
			sf::Vector2f FindTileBasedCenter(const sf::Vector2f windowSize = sf::Vector2f(800, 600), const sf::Vector2f offset = sf::Vector2f(0, 0));
			void ChangeMaps(std::string &newMap, std::string &newmapname, MapExit &exit);
			void ChangeMapViaMapExit(MapExit exit);

			//virtual bool HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult);
			//virtual bool HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult);
		protected:
			//boost::shared_ptr<TileMap> map;
			boost::shared_ptr<Game::Mapping::GameMap> game_map;
			sf::View CharacterView;
			//std::vector<Graphics::AnimatedSprite> Backgrounds;
			boost::shared_ptr<sf::RenderWindow> PrimaryWindow;
			sf::RenderWindow* GameWindow;
			//MapCharacterSprite MapCharacter;
			//Game::Character::Party* party;
		private:
			sf::Uint32 LastInputUpdate;
		};
	}
}

#endif