#include "Sprite.h"

namespace Graphics
{

	Sprite::Sprite(bool SetCenter)
	{
		if (SetCenter)
		{
			sp.setOrigin(sp.getGlobalBounds().width * 0.5, sp.getGlobalBounds().height * 0.5);
		}
	}
	Sprite::Sprite(boost::shared_ptr<sf::Texture> texture, bool SetCenter) : heldTexture(texture), sp(*texture)
	{
		if (SetCenter)
		{
			sp.setOrigin(sp.getGlobalBounds().width * 0.5, sp.getGlobalBounds().height * 0.5);
		}
	}

	void Sprite::SetTexture(boost::shared_ptr<sf::Texture> txt)
	{
		heldTexture = txt;
		sp.setTexture(*txt);
	}

	void Sprite::Rotate(const float angle, bool absolute)
	{
		SpriteInterface::Rotate(angle, absolute);
		if (absolute)
		{
			sp.setRotation(angle);
		}
		else
		{
			sp.rotate(angle);
		}
	}

	void Sprite::SetPosition(const float x, const float y)
	{
		SpriteInterface::SetPosition(x, y);
		//sp.setPosition(x, y);
	}

	void Sprite::SetPosition(const sf::Vector2f& pos)
	{
		SpriteInterface::SetPosition(pos);
		//sp.setPosition(pos);
	}

	void Sprite::IncrementPosition(const float xAdd, const float yAdd)
	{
		SpriteInterface::IncrementPosition(xAdd, yAdd);
		SetPosition(this->GetPosition());
	}

	void Sprite::IncrementPosition(const sf::Vector2f& pos)
	{
		SpriteInterface::IncrementPosition(pos);
		SetPosition(this->GetPosition());
	}

	void Sprite::SetScale(const sf::Vector2f& scale)
	{
		SpriteInterface::SetScale(scale);
		//sp.setScale(scale);
	}

	void Sprite::SetScale(const float xScale, const float yScale)
	{
		SpriteInterface::SetScale(xScale, yScale);
		//sp.setScale(xScale, yScale);
	}

	void Sprite::SetAlpha(const sf::Uint8 alpha) 
	{
		SpriteInterface::SetAlpha(alpha);
		auto col = sp.getColor();
		sp.setColor(sf::Color(col.r, col.g, col.b, this->GetAlpha()));
	}

	void Sprite::IncrementAlpha(const sf::Uint8 alphaAdd)
	{
		SpriteInterface::IncrementAlpha(alphaAdd);
		auto col = sp.getColor();
		sp.setColor(sf::Color(col.r, col.g, col.b, this->GetAlpha()));
	}

	void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= GetTransformConst();
		target.draw(sp, states);
	}

	
	void Sprite::Draw(sf::RenderTarget &window, sf::RenderStates states)
	{
		if (Drawing)
		{
			states.transform *= GetTransform();
			window.draw(sp, states);
		}
	}

	void Sprite::Draw(sf::RenderTarget &window)
	{
		if (Drawing)
		{
			sf::RenderStates st;
		
			st.transform *= GetTransform();
			//st.transform *= GetTransform();
			window.draw(sp, st);
		}
	}
	
	sf::Sprite& Sprite::GetBaseSprite()
	{
		return sp;
	}
	Sprite::~Sprite()
	{

	}
}