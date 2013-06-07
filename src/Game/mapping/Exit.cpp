#include "Exit.h"
#include "MapCharacter.h"
#include "GameMap.h"
namespace Game
{
	namespace Mapping
	{
		MapExitComponent::MapExitComponent(MapObject* owner, std::string& targetMapName, std::string& targetMapFile, int newMapx, int newMapy, int newMaplayer, bool active, bool clearAssets, bool clearMusic)
			: MapEventComponent(owner,"MapExit", active), NewMapPosition(newMapx, newMapy, newMaplayer), TargetMapName(targetMapName), TargetMapFile(targetMapFile), ClearAssets(clearAssets), ClearMusic(clearMusic),
			CarryOver(newMapx == -1 ? true : false, newMapy == -1 ? true : false, newMaplayer == -1 ? true : false)
		{

		}

		sf::Vector3i& MapExitComponent::GetTargetMapPositon()
		{
			return NewMapPosition;
		}
		void MapExitComponent::SetTargetMapPosition(const sf::Vector3i& newTargPos)
		{
			NewMapPosition = newTargPos;
		}
		sf::Vector3<bool>& MapExitComponent::GetCarryOver()
		{
			return CarryOver;
		}

		const std::string& MapExitComponent::GetTargetMapName() const
		{
			return TargetMapName;
		}
		void MapExitComponent::SetTargetMapName(const std::string& newMapName)
		{
			TargetMapName = newMapName;
		}

		const std::string& MapExitComponent::GetTargetMapFile() const
		{
			return TargetMapFile;
		}

		void MapExitComponent::SetTargetMapFile(const std::string& newMapFile)
		{
			TargetMapFile = newMapFile;
		}

		void MapExitComponent::ProcessEvent(GameMap& map, MapCharacter& playerChar)
		{
			map.SetExit(this);
		}

		bool MapExitComponent::GetClearAssets() const
		{
			return ClearAssets;
		}
		void MapExitComponent::SetClearAssets(const bool clear)
		{
			ClearAssets = clear;
		}

		bool MapExitComponent::GetClearMusic() const
		{
			return ClearMusic;
		}
		void MapExitComponent::SetClearMusic(const bool clear)
		{
			ClearMusic = clear;
		}

		MapExitComponent::RawClonePtr MapExitComponent::RawClone() const
		{
			return new MapExitComponent(*this);
		}

		AreaMapExitComponent::AreaMapExitComponent(MapObject* owner, const sf::IntRect& eventArea, std::string& targetMapName, std::string& targetMapFile, int newMapx, int newMapy, int newMaplayer, bool active)
			: MapExitComponent(owner, targetMapName, targetMapFile, newMapx, newMapy, newMaplayer, active), Area(eventArea)
		{

		}

		bool AreaMapExitComponent::InEventRange(const MapCharacter& character)
		{
			//Assume Area is positive for now

			return 
				OwnerObject != nullptr && character.DrawLayer == OwnerObject->MapTilePosition.z &&
				//x test
				!(static_cast<int>(character.MapTilePosition.x) > (OwnerObject->MapTilePosition.x + (Area.width - 1)) || (static_cast<int>(character.MapTilePosition.x) < OwnerObject->MapTilePosition.x)) && 
				//y test
				!(static_cast<int>(character.MapTilePosition.y) > (OwnerObject->MapTilePosition.y + (Area.height - 1)) || (static_cast<int>(character.MapTilePosition.y) < OwnerObject->MapTilePosition.y));
		}

		AreaMapExitComponent::RawClonePtr AreaMapExitComponent::RawClone() const
		{
			return new AreaMapExitComponent(*this);
		}
	}
}