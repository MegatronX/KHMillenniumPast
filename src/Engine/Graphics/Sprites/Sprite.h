#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <graphics/Sprites/SpriteInterface.h>
#include <SFML/Graphics.hpp>

namespace Graphics
{
	class Sprite : public virtual SpriteInterface
	{
	public:
		Sprite(bool SetCenter = true);
		Sprite(boost::shared_ptr<sf::Texture> texture, bool SetCenter = true);

		virtual void SetTexture(boost::shared_ptr<sf::Texture> txt);

		virtual void Rotate(const float angle, bool absolute = true) override;

		virtual void SetPosition(const float x, const float y) override;

		virtual void SetPosition(const sf::Vector2f& pos) override;

		virtual void IncrementPosition(const float xAdd, const float yAdd = 0) override;

		virtual void IncrementPosition(const sf::Vector2f& pos) override;

		virtual void SetScale(const sf::Vector2f& scale) override;

		virtual void SetScale(const float xScale, const float yScale) override;

		virtual void SetAlpha(const sf::Uint8 alpha) override;

		virtual void IncrementAlpha(const sf::Uint8 alphaAdd) override;

		//Draw Interface Implementation
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual void Draw(sf::RenderTarget &window, sf::RenderStates states) override;

		virtual void Draw(sf::RenderTarget &window) override;

		sf::Sprite& GetBaseSprite();

		virtual ~Sprite();
	protected:
		sf::Sprite sp;
		boost::shared_ptr<sf::Texture> heldTexture;
	};
}

#endif