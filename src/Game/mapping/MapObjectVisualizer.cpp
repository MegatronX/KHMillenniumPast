#include "MapObjectVisualizer.h"

namespace Game
{
	namespace Mapping
	{
		MapObjectVisualizer::MapObjectVisualizer(MapObject* owner) : OwnerObject(owner), Component(owner, owner != nullptr ? owner->GetName() + "MapObjectVisComponent" : "NoOwnerMapObjectVisComponent", "MapObjectVisComponent")
		{
			if (owner != nullptr)
			{
				objectSprite.SetPosition(owner->MapPosition.x, owner->MapPosition.y);
				layer = owner->MapPosition.z;
			}
		}
		::Graphics::AnimatedSprite& MapObjectVisualizer::GetSprite()
		{
			return objectSprite;
		}
		void MapObjectVisualizer::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(objectSprite, states);
		}
		void MapObjectVisualizer::Draw(sf::RenderTarget &window)
		{
			objectSprite.Draw(window);
		}
		void MapObjectVisualizer::Draw(sf::RenderTarget &window, sf::RenderStates states)
		{
			objectSprite.Draw(window, states);
		}

		void MapObjectVisualizer::Update(const sf::Uint32 time, const float TimeScale)
		{
			if (OwnerObject != nullptr && enforcePosition)
			{
				if (OwnerObject->MapPosition.x != x || OwnerObject->MapPosition.y != y)
				{
					x = OwnerObject->MapPosition.x;
					y = OwnerObject->MapPosition.y;
					objectSprite.SetPosition(x, y);
				}
			}
			objectSprite.Update(time, TimeScale);
		}

		bool MapObjectVisualizer::GetPositionEnforced() const
		{
			return enforcePosition;
		}
		void MapObjectVisualizer::SetPositionEnforced(const bool enf)
		{
			enforcePosition = enf;
		}

		/*MapObjectVisualizer::RawClonePtr MapObjectVisualizer::RawClone() const 
		{
			return new MapObjectVisualizer(*this);
		}*/
	}
}