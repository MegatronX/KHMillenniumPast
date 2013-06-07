#pragma once

#include <Graphics/Screens/Screen.h>
#include <Mapping/GameMap.h>

namespace Game
{
	namespace Graphics
	{
		namespace Screens
		{
			const std::string MapInputComponentIndex = "MapInputHandler";
			enum MapDirection
			{
				North = 0,
				East,
				West,
				South,
				None
			};
			class GameMapViewScreen : public ::Graphics::Screens::Screen
			{
			public:
				GameMapViewScreen(Engine* engine);
				GameMapViewScreen(Engine* engine, const std::string &mapFile, const sf::Vector2f &startPos, const int startingLayer, sf::RenderTarget* window, const std::string &name, const std::string& mapCharName, const int layerID = -1);
				//			MapViewLayer(Engine* engine, std::string &mapFile, sf::Vector2f &startPos, sf::RenderWindow* window, std::string &name, int layerID, bool draw, Game::Character::Party* party, bool drawcaller = true, bool updatecaller = true);
				//Animated Draw
				
				virtual void Draw(sf::RenderTarget &window) override;
				virtual void Draw(sf::RenderTarget &window, sf::RenderStates states) override;
				void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
				virtual void Update(const float time, const float TimeScale = 1.0) override;
				virtual void Update(const sf::Uint32 time, const float timescale = 1.0) override;
				sf::Vector2f FindTileBasedCenter(const sf::Vector2f windowSize = sf::Vector2f(800, 600), const sf::Vector2f offset = sf::Vector2f(0, 0));
				void ChangeMaps(std::string &newMap, std::string &newmapname, Mapping::MapExitComponent &exit);
				void ChangeMapViaMapExit(const Mapping::MapExitComponent& exit);

				virtual bool HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult);
				virtual bool HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult);

				::Game::Mapping::MapCharacter& GetMapCharacter();
			protected:
				
				void ContinuedDirectionHandler(Mapping::MapCharacter* ch);
				void HandleMapCharacterMovementEvent(Mapping::MapCharacter* mpchar);
				void CheckForSpawn(Mapping::MapCharacter* mpchar);
				//boost::shared_ptr<TileMap> map;
				boost::shared_ptr<Game::Mapping::GameMap> game_map;
				sf::View CharacterView;
				sf::View MapView;
				//std::vector<Graphics::AnimatedSprite> Backgrounds;
				::Game::Mapping::MapCharacter MapChar;
				MapDirection LastCharDir;
				boost::shared_ptr<sf::RenderWindow> PrimaryWindow;
				sf::RenderTarget* GameWindow;
				sf::Vector2f WindowSize;
				sf::Vector2f HalfWindowSize;
				//MapCharacterSprite MapCharacter;
				//Game::Character::Party* party;

				//Map Character limiters

				sf::Vector2f FarTopLeftPoint;
				sf::Vector2f FarBottomRightPoint;

				sf::Vector2f FarTopLeftOffset;
				sf::Vector2f FarBottomRightOffset;
			private:
				sf::Uint32 LastInputUpdate;
			};
		}
	}
}