#pragma once
#ifndef _MAPCHARACTER_H_
#define _MAPCHARACTER_H_
#include <boost/unordered_map.hpp>
#include <sfml/Graphics.hpp>
#include <Graphics/Sprites/AnimatedSprite.h>

namespace Game
{
	namespace Mapping
	{
		struct MapCharacter;
		class GameMap;
		typedef boost::function<void(MapCharacter*)> MovementFinished;

		const std::string MovementComponentIndex = "MovementComponent";

		struct MapCharacter : public ::Graphics::AnimatedDraw
		{
			MapCharacter();

			MapCharacter(GameMap* gmap);

			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
			
			virtual void Draw(sf::RenderTarget& window, sf::RenderStates states) override;
			virtual void Draw(sf::RenderTarget& window) override;
			virtual void Update(const sf::Uint32 time, const float TimeScale = 1.0) override;

			void SlideMapPosition(const sf::Vector2f &TargetPos, sf::Uint32 slideTime, sf::Uint32 currentTime);

			void SlideMapPosition(const sf::Vector2f &TargetPos, const sf::Vector2i &tilePos, sf::Uint32 slideTime, sf::Uint32 currentTime);

			bool AddFinishedEvent(const std::string& index, const MovementFinished& handler);
			bool RemoveFinishedEvent(const std::string& index);
			void DispatchFinishedEvents();

			void RecalcTilePosition(GameMap* map);
			void RecalcTilePosition(const int tileWidth = 32, const int tileHeight = 32);

			::Graphics::AnimatedSprite CharSpr;
			std::string CharacterName;
			sf::Vector2f TargetPosition;
			sf::Vector2f TranslationVector;
			sf::Vector2f MapPosition;
			sf::Vector2f MapTilePosition;
			sf::Vector2f ScreenPosition;
			sf::Vector2f Speed;
			sf::Vector2f ViewOffset;
			sf::Vector2f DeterminedSpritePos;

			bool InTransit;
			int DrawLayer;
			sf::Vector2f centerOff;
			sf::Uint32 TargetTime;
			sf::Uint32 LastUpdate;

			GameMap* AttachedGameMap;
			boost::unordered_map<std::string, MovementFinished> MoveFinishEvents;

			virtual ~MapCharacter();
		};
		
	}
}

#endif