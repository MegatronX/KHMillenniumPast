#pragma once
#ifndef _MAPOBJECTVISUALIZER_H_
#define _MAPOBJECTVISUALIZER_H_

#include <mapping/MapObject.h>
#include <Graphics/Sprites/AnimatedSprite.h>
namespace Game
{
	namespace Mapping
	{
		class MapObjectVisualizer : public Components::Component, public ::Graphics::AnimatedDraw
		{
		public:
			MapObjectVisualizer(MapObject* owner);
			::Graphics::AnimatedSprite& GetSprite();

			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
			virtual void Draw(sf::RenderTarget &window) override;
			virtual void Draw(sf::RenderTarget &window, sf::RenderStates states) override;

			virtual void Update(const sf::Uint32 time, const float TimeScale = 1.0) override;

			bool GetPositionEnforced() const;
			void SetPositionEnforced(const bool enf);

			using Components::Component::RawClone;

			//Components::Component::RawClonePtr Components::Component::RawClone() const override;
		protected:
			::Graphics::AnimatedSprite objectSprite;
			MapObject* OwnerObject;
			float x, y;
			int layer;
			bool enforcePosition;
			friend class MapObject;
		};
	}
}

#endif