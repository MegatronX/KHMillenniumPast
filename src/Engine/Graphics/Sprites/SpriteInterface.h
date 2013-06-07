#pragma once
#ifndef _SPRITEINTERFACE_H_
#define _SPRITEINTERFACE_H_

#include <Graphics/DrawInterface.h>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

namespace Graphics
{
	class SpriteInterface;
	

	class SpriteInterface : public virtual DrawInterface
	{
	public:
		SpriteInterface();
		virtual void Rotate(const float angle, bool absolute = true);
		virtual void Rotate(const float angle, const sf::Vector2f& rotateAbout, bool absolute = true);
		float GetRotation() const;

		virtual void SetPosition(const sf::Vector2f& pos);
		virtual void SetPosition(const float x, const float y);
		const sf::Vector2f& GetPosition() const;

		virtual void IncrementPosition(const sf::Vector2f& incrpos);
		virtual void IncrementPosition(const float xAdd, const float yAdd = 0);

		virtual void SetScale(const sf::Vector2f& scale);
		virtual void SetScale(const float xScale, const float yScale);
		const sf::Vector2f GetScale() const;

		virtual void SetAlpha(const sf::Uint8 alpha);
		virtual void IncrementAlpha(const sf::Uint8 alphaAdd);
		sf::Uint8 GetAlpha() const;

		sf::Transform& GetTransform();

		const sf::Transform& GetTransformConst() const;

		virtual ~SpriteInterface();
	private:
		sf::Transform LocalTransform;
		float Rotation;
		sf::Vector2f Position;
		sf::Vector2f Scale;
		sf::Uint8 Alpha;
		bool ScaleSet;
	};
	typedef boost::shared_ptr<SpriteInterface> sprintr_ptr;
}

#endif