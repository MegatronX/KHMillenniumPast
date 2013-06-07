#include "LayerTransition.h"
#include <Mapping/MapCharacter.h>
#include <Mapping/GameMap.h>

namespace Game
{
	namespace Mapping
	{
		LayerTransitionComponent::LayerTransitionComponent(MapObject* owner, const std::string& name, bool active) : MapEventComponent(owner, name, active)
		{

		}

		bool LayerTransitionComponent::InEventRange(const MapCharacter& character)
		{
			return OwnerObject != nullptr && 
				static_cast<int>(character.MapTilePosition.x)			== OwnerObject->MapTilePosition.x &&
				static_cast<int>(character.MapTilePosition.y)			== OwnerObject->MapTilePosition.y &&
				Transitions.find(static_cast<int>(character.DrawLayer)) != Transitions.end();//OwnerObject->MapTilePosition.z;
		}

		void LayerTransitionComponent::ProcessEvent(GameMap& map, MapCharacter& playerChar)
		{
			auto trgLayer = Transitions.find(playerChar.DrawLayer);
			if (trgLayer != Transitions.end())
			{
				playerChar.DrawLayer = trgLayer->second;
			}
		}

		void LayerTransitionComponent::AddLayerTransition(const int activeLayer, const int targetLayer)
		{
			Transitions[activeLayer] = targetLayer;
		}

		bool LayerTransitionComponent::RemoveLayerTransition(const int activelayer)
		{
			bool removed = false;
			auto trg = Transitions.find(activelayer);
			if (trg != Transitions.end())
			{
				Transitions.erase(trg);
				removed = true;
			}
			return removed;
		}

		LayerTransitionComponent::RawClonePtr LayerTransitionComponent::RawClone() const
		{
			return new LayerTransitionComponent(*this);
		}

		AreaLayerTransitionComponent::AreaLayerTransitionComponent(MapObject* owner, const sf::IntRect& eventArea, const std::string& name, bool active) : LayerTransitionComponent(owner, name, active)
		{

		}

		bool AreaLayerTransitionComponent::InEventRange(const MapCharacter& character)
		{
			//Assume Area is positive for now

			return 
				OwnerObject != nullptr && character.DrawLayer == OwnerObject->MapTilePosition.z &&
				//x test
				!(static_cast<int>(character.MapTilePosition.x) > (OwnerObject->MapTilePosition.x + (Area.width - 1)) || (static_cast<int>(character.MapTilePosition.x) < OwnerObject->MapTilePosition.x)) && 
				//y test
				!(static_cast<int>(character.MapTilePosition.y) > (OwnerObject->MapTilePosition.y + (Area.height - 1)) || (static_cast<int>(character.MapTilePosition.y) < OwnerObject->MapTilePosition.y));
		}

		LayerTransitionComponent::RawClonePtr AreaLayerTransitionComponent::RawClone() const
		{
			return new AreaLayerTransitionComponent(*this);
		}

	}
}