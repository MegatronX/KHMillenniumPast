#include "MapCharacter.h"
#include "GameMap.h"
namespace Game
{
	namespace Mapping
	{
		MapCharacter::MapCharacter() : TargetPosition(0, 0), TranslationVector(0, 0), MapPosition(0, 0), MapTilePosition(0, 0), ScreenPosition(0, 0), ViewOffset(0, 0), Speed(0, 0),
			InTransit(false), DrawLayer(0), TargetTime(0), LastUpdate(0)
		{

		}
		MapCharacter::MapCharacter(GameMap* gmap) : TargetPosition(0, 0), TranslationVector(0, 0), MapPosition(0, 0), MapTilePosition(0, 0), ScreenPosition(0, 0), ViewOffset(0, 0), Speed(0, 0),
			InTransit(false), DrawLayer(0), TargetTime(0), LastUpdate(0), AttachedGameMap(gmap)
		{

		}
		void MapCharacter::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(CharSpr, states);
		}

		void MapCharacter::Draw(sf::RenderTarget &window, sf::RenderStates states)
		{
			//Need to add shader support
			CharSpr.Draw(window, states);
		}
		void MapCharacter::Draw(sf::RenderTarget &window)
		{
			CharSpr.Draw(window);
		}
		void MapCharacter::Update(const sf::Uint32 time, const float TimeScale)
		{
			if (InTransit)
			{
				sf::Uint32 elapsed = (LastUpdate > time) ? 0 : (time - LastUpdate);
				if (time < TargetTime)
				{
					MapPosition = MapPosition + TranslationVector * static_cast<float>(elapsed);
				}
				else
				{
					InTransit = false;
					MapPosition = TargetPosition;
					RecalcTilePosition(AttachedGameMap);
					TranslationVector = sf::Vector2f(0, 0);
					DispatchFinishedEvents();
				}
			}
			LastUpdate = time;
			CharSpr.Update(time, TimeScale);
		}

		void MapCharacter::RecalcTilePosition(GameMap* map)
		{
			if (map != nullptr)
			{
				RecalcTilePosition(map->GetTileWidth(), map->GetTileHeight());
			}
			else
			{
				RecalcTilePosition();
			}
		}

		void MapCharacter::RecalcTilePosition(const int tileWidth, const int tileHeight)
		{
			MapTilePosition.x = (tileWidth != 0 ? static_cast<int>(MapPosition.x / static_cast<float>(tileWidth)) : 1);
			MapTilePosition.y = (tileHeight != 0 ? static_cast<int>(MapPosition.y / static_cast<float>(tileHeight)) : 1);
		}

		void MapCharacter::SlideMapPosition(const sf::Vector2f &TargetPos, sf::Uint32 slideTime, sf::Uint32 currentTime)
		{
			TargetPosition = TargetPos;
			LastUpdate = currentTime;

			TargetTime = currentTime + slideTime;

			if (slideTime > 0)
			{
				InTransit = true;
				TranslationVector = (TargetPosition - MapPosition) / static_cast<float>(slideTime);
			}
			else
			{
				MapPosition = TargetPos;
				RecalcTilePosition(AttachedGameMap);
				TranslationVector = sf::Vector2f(0, 0);
			}
		}

		

		void MapCharacter::SlideMapPosition(const sf::Vector2f &TargetPos, const sf::Vector2i &tilePos, sf::Uint32 slideTime, sf::Uint32 currentTime)
		{
			TargetPosition = TargetPos;
			LastUpdate = currentTime;

			TargetTime = currentTime + slideTime;

			if (slideTime > 0)
			{
				InTransit = true;
				TranslationVector = (TargetPosition - MapPosition) / (float)slideTime;
			}
			else
			{
				MapPosition = TargetPos;
				RecalcTilePosition(AttachedGameMap);
				TranslationVector = sf::Vector2f(0, 0);
			}
		}

		bool MapCharacter::AddFinishedEvent(const std::string& index, const MovementFinished& handler)
		{
			MoveFinishEvents[index] = handler;
			return true;
		}
		bool MapCharacter::RemoveFinishedEvent(const std::string& index)
		{
			bool removed = false;
			auto fd = MoveFinishEvents.find(index);
			if (fd != MoveFinishEvents.end())
			{
				MoveFinishEvents.erase(fd);
				removed = true;
			}
			return removed;
		}
		/*
		void MapCharacter::CalcLimits()
		{
			if (MapPosition.x > FarRightLimit)
			{
				IsFarRight = true;
			}
			else if (MapPosition.x < FarLeftLimit)
			{
				IsFarLeft = true;
			}
			else
			{
				IsFarRight = false;
				IsFarLeft = false;
			}

			if (MapPosition.y < FarUpLimit)
			{
				IsFarUp = true;
			}
			else if (MapPosition.y > FarDownLimit)
			{
				IsFarDown = true;
			}
			else
			{
				IsFarDown = false;
				IsFarUp = false;
			}
		}
		void MapCharacter::EnforceLimits()
		{
			sf::Vector2f SpritePos = DeterminedSpritePos;
			if (IsFarLeft)
			{
				SpritePos.x = MapPosition.x + ViewOffset.x;
				if (FirstLeft)
				{

				}
			}
			else if (IsFarRight)
			{
				SpritePos.x = MapPosition.x - FarRightLimit + ViewOffset.x + HalfWindowSize.x;
			}
			else
			{
			}
			if (IsFarUp)
			{
				SpritePos.y = MapPosition.y + ViewOffset.y;
			}
			else if (IsFarDown)
			{
				SpritePos.y = MapPosition.y - FarLeftLimit + ViewOffset.y + HalfWindowSize.y;
			}
			else
			{

			}
			CharSpr.SetPosition(SpritePos);
		}
		void MapCharacter::EdgeGuardCharacter(Mapping::MapCharacter& mpChar, GameMap& map, sf::Vector2f& halfWindowSize)
		{

			if (mpChar.MapPosition.x < (halfWindowSize.x + static_cast<float>(map.GetTileWidth())) || 
				mpChar.MapPosition.x > (map.GetWidth() - halfWindowSize.x - static_cast<float>(map.GetTileWidth())))
			{
				mpChar.FollowInX = false;
			}
			else
			{
				mpChar.FollowInX = true;
			}
			if (mpChar.MapPosition.y < (halfWindowSize.y + static_cast<float>(map.GetTileHeight())) || 
				mpChar.MapPosition.y > (map.GetHeight() - halfWindowSize.y - static_cast<float>(map.GetTileHeight())))
			{
				mpChar.FollowInY = false;
			}
			else
			{
				mpChar.FollowInY = true;
			}
		}
		*/
		void MapCharacter::DispatchFinishedEvents()
		{
			for (auto ev = MoveFinishEvents.begin(); ev != MoveFinishEvents.end(); ++ev)
			{
				ev->second(this);
			}
		}

		MapCharacter::~MapCharacter()
		{

		}
	}
}