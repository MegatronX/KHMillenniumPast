#pragma once
#include <Entity.h>
#include <Mapping/MapEvent.h>
namespace Game
{
	namespace Mapping
	{
		const std::string OpenChestComponentIndex = "OpenChestComponent";
		const std::string CloseChestComponentIndex = "CloseChestComponent";
		class MapChestComponent : public MapEventComponent
		{
		public:
			MapChestComponent(MapObject* owner, const std::string& name = "LayerTransition", bool active = false);

			//MapChest(const std::string& name, sf::Vector3i Position, const std::string style = "Default");

			//MapChest(const std::string& name, const int x, const int y, const int layer, const std::string style = "Default");

			virtual MapChestComponent::RawClonePtr RawClone() const override;

			//MapObjectVisualizer* GenerateVisualizer() override;
		protected:
			std::string ChestStyle;
			boost::unordered_map<std::string, int> LootTable;
			static boost::unordered_map<std::string, std::string> StyleSpriteMapping;
		};
	}
}