#pragma once
#ifndef _MAPEXIT_H_
#define _MAPEXIT_H_
#include <Mapping/MapEvent.h>
namespace Game
{
	namespace Mapping
	{
		const std::string ExitComponentIndex = "ExCmp";
		class MapExitComponent : public MapEventComponent
		{
		public:
			MapExitComponent(MapObject* owner, std::string& targetMapName, std::string& targetMapFile, int newMapx, int newMapy, int newMaplayer, bool active = true, bool clearAssets = true, bool clearMusic = true);

			sf::Vector3i& GetTargetMapPositon();
			void SetTargetMapPosition(const sf::Vector3i& newTargPos);
			sf::Vector3<bool>& GetCarryOver();

			const std::string& GetTargetMapName() const;
			void SetTargetMapName(const std::string& newMapName);

			const std::string& GetTargetMapFile() const;

			void SetTargetMapFile(const std::string& newMapFile);

			virtual void ProcessEvent(GameMap& map, MapCharacter& playerChar) override;

			bool GetClearAssets() const;
			void SetClearAssets(const bool clear);

			bool GetClearMusic() const;
			void SetClearMusic(const bool clear);

			MapExitComponent::RawClonePtr RawClone() const override;
		private:
			sf::Vector3i NewMapPosition;
			sf::Vector3<bool> CarryOver;
			std::string TargetMapName;
			std::string TargetMapFile;
			bool ClearMusic;
			bool ClearAssets;
		};

		class AreaMapExitComponent : public MapExitComponent
		{
		public:
			AreaMapExitComponent(MapObject* owner, const sf::IntRect& eventArea, std::string& targetMapName, std::string& targetMapFile, int newMapx, int newMapy, int newMaplayer, bool active = true);

			bool InEventRange(const MapCharacter& character) override;

			AreaMapExitComponent::RawClonePtr RawClone() const override;
		protected:
			sf::IntRect Area;
		private:
		};

		class MapExitBad// : public MapEvent
		{
		public:
			MapExitBad(const sf::IntRect& eventArea, const bool active, std::string& targetMapName, std::string& targetMapFile, int newMapx = 0, int newMapy = 0, int newMaplayer = 0) 
				//: MapEvent(x, y, layer, active), TargetMapName(TargetMapName), TargetMapFile(targetMapFile), NewMapPosition(newMapx, newMapy, newMaplayer)
			{

			}

			/*virtual void EventActivated(GameMap* map, MapCharacter* character) override
			{

			}*/



			const std::string& GetTargetMapName() const
			{
				return TargetMapName;
			}

			const std::string& GetTargetMapFile() const
			{
				return TargetMapFile;
			}

			const sf::Vector3i& GetNewMapPosition() const
			{
				return NewMapPosition;
			}

			int GetNewMapX() const
			{
				return NewMapPosition.x;
			}
			int GetNewMapY() const
			{
				return NewMapPosition.y;
			}
			int GetNewMapLayer() const
			{
				return NewMapPosition.z;
			}
		protected:
			sf::IntRect Area;
			sf::Vector3i NewMapPosition;
			std::string TargetMapName;
			std::string TargetMapFile;
		};
	}
}


#endif