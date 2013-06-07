#include "SpriteInterface.h"

namespace Graphics
{
	SpriteInterface::SpriteInterface() : Rotation(0.f), Position(0.f, 0.f), Scale(1.f, 1.f)
	{

	}
	void SpriteInterface::Rotate(const float angle, bool absolute)
	{
		if (absolute)
		{
			if (angle != Rotation)
			{
				LocalTransform.rotate(angle - Rotation, GetPosition());
				Rotation = angle;
			}
		}
		else
		{
			if (angle != 0.f)
			{
				LocalTransform.rotate(angle, GetPosition());
				Rotation += angle;
			}

		}

	}
	void SpriteInterface::Rotate(const float angle, const sf::Vector2f& rotateAbout, bool absolute)
	{
		if (absolute)
		{
			if (angle != Rotation)
			{
				LocalTransform.rotate(angle - Rotation, rotateAbout);
				Rotation = angle;
			}
		}
		else
		{
			if (angle != 0.f)
			{
				LocalTransform.rotate(angle, rotateAbout);
				Rotation += angle;
			}

		}
	}
	float SpriteInterface::GetRotation() const
	{
		return Rotation;
	}

	void SpriteInterface::SetPosition(const sf::Vector2f& pos)
	{
		if (Position != pos)
		{
			LocalTransform.translate(pos - Position);
			Position = pos;
		}
	}
	void SpriteInterface::SetPosition(const float x, const float y)
	{
		SetPosition(sf::Vector2f(x, y));
	}
	const sf::Vector2f& SpriteInterface::GetPosition() const
	{
		return Position;
	}

	void SpriteInterface::IncrementPosition(const sf::Vector2f& incrpos)
	{
		SetPosition(Position + incrpos);
	}
	void SpriteInterface::IncrementPosition(const float xAdd, const float yAdd)
	{
		SetPosition(Position.x + xAdd, Position.y + yAdd);
	}

	void SpriteInterface::SetScale(const sf::Vector2f& scale)
	{
		if (Scale != scale)
		{
			sf::Vector2f effScale(scale);
			if (scale.x <= 0.0001f && scale.x >= -0.0001f)
				effScale.x = 0.0001f;
			if (scale.y <= 0.0001f && scale.y >= -0.0001f)
				effScale.y = 0.0001f;
			LocalTransform.scale(sf::Vector2f(effScale.x / Scale.x, effScale.y / Scale.y));
			Scale = effScale;
		}
	}
	void SpriteInterface::SetScale(const float xScale, const float yScale)
	{
		SetScale(sf::Vector2f(xScale, yScale));
	}
	const sf::Vector2f SpriteInterface::GetScale() const
	{
		return Scale;
	}

	void SpriteInterface::SetAlpha(const sf::Uint8 alpha)
	{
		Alpha = alpha;
	}
	void SpriteInterface::IncrementAlpha(const sf::Uint8 alphaAdd)
	{
		Alpha += alphaAdd;
	}
	sf::Uint8 SpriteInterface::GetAlpha() const
	{
		return Alpha;
	}

	sf::Transform& SpriteInterface::GetTransform()
	{
		return LocalTransform;
	}

	const sf::Transform& SpriteInterface::GetTransformConst() const
	{
		return LocalTransform;
	}

	SpriteInterface::~SpriteInterface()
	{

	}
}