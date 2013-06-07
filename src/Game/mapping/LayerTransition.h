#pragma once
#ifndef _LAYERTRANSITION_H_
#define _LAYERTRANSITION_H_

#include <mapping/MapEvent.h>

namespace Game
{
	namespace Mapping
	{
		struct MapCharacter;
		class GameMap;
		class LayerTransitionComponent : public MapEventComponent
		{
		public:
			LayerTransitionComponent(MapObject* owner, const std::string& name = "LayerTransition", bool active = false);

			virtual bool InEventRange(const MapCharacter& character) override;

			virtual void ProcessEvent(GameMap& map, MapCharacter& playerChar) override;

			void AddLayerTransition(const int activeLayer, const int targetLayer);

			bool RemoveLayerTransition(const int activelayer);

			virtual LayerTransitionComponent::RawClonePtr RawClone() const override;
		private:
			boost::unordered_map<int, int> Transitions;
		};
		class AreaLayerTransitionComponent : public LayerTransitionComponent
		{
		public:
			AreaLayerTransitionComponent(MapObject* owner, const sf::IntRect& eventArea, const std::string& name = "LayerTransition", bool active = false);

			bool InEventRange(const MapCharacter& character) override;

			virtual LayerTransitionComponent::RawClonePtr RawClone() const override;
		private:
			sf::IntRect Area;
		};

	}
}

#endif