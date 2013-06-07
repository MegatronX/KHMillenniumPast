#pragma once
#ifndef _BASETRANSFORM_H_
#define _BASETRANSFORM_H_

#include <Graphics/Sprites/SpriteInterface.h>
#include <Graphics/Updater.h>
#include <boost/function.hpp>
#include <boost/unordered_map.hpp>

namespace Graphics
{
	class BaseTransform;

	typedef boost::function<void (sf::Uint32 time, BaseTransform* transform)> TransformationCompletedSignal;

	class BaseTransform : public virtual Updater
	{
	public:
		BaseTransform(::Graphics::SpriteInterface& targetDrawabale, const sf::Uint32 time, const sf::Uint32 transformTime = 0, const sf::Uint32 delay = 0);

		void Update(const sf::Uint32 time, const float scale = 1.f) override;

		::Graphics::SpriteInterface& GetTarget();

		void AddTransformationCompleteEvent(const std::string& index, const TransformationCompletedSignal& eventHandler);
		bool RemoveTransformationCompleteEvent(const std::string& index);

		void DispatchEvents(const sf::Uint32 time);

		sf::Uint32 GetTargetTime() const;

		bool GetExpired()const;
		void SetExpired(const bool val);
		
	protected:
		void SetTarget(::Graphics::SpriteInterface& target);
		::Graphics::SpriteInterface& Target;

		boost::unordered_map<std::string, TransformationCompletedSignal> TransformationEvents;

		sf::Uint32 TargetTime;
		sf::Uint32 TransformTime;
		sf::Uint32 StartTime;
		sf::Uint32 LastUpdate;
		sf::Uint32 Delay;

		bool Transitioning;
		bool Expired;
	private:
		
	};

	class PositionTransform : public BaseTransform
	{
	public:
		PositionTransform(::Graphics::SpriteInterface& target, const sf::Vector2f& targetPositon, const sf::Uint32 time, const sf::Uint32 transformTime = 0, const sf::Uint32 delay = 0);

		void Update(const sf::Uint32 time, const float scale = 1.f) override;
		
		const sf::Vector2f& GetTargetPosition() const;

		const sf::Vector2f& GetTransformationRate() const;

		
	protected:
		sf::Vector2f TransformationRate;
		sf::Vector2f TargetPosition;
		sf::Vector2f RunningPosition;
		
	};

	class ScaleTransform : public BaseTransform
	{
	public:
		ScaleTransform(::Graphics::SpriteInterface& target, const sf::Vector2f& targetScale, const sf::Uint32 time, const sf::Uint32 transformTime = 0, const sf::Uint32 delay = 0);
		//ScaleTransform(::Graphics::SpriteInterface& target, const sf::Vector2f& initialScale, const sf::Vector2f& targetScale, const sf::Uint32 time, const sf::Uint32 transformTime);

		void Update(const sf::Uint32 time, const float scale = 1.f) override;

		const sf::Vector2f& GetTargetScale() const;

		const sf::Vector2f& GetTransformationRate() const;
	protected:
		bool NegativeGrowth;
		sf::Vector2f TransformationRate;
		sf::Vector2f TargetScale;
		sf::Uint32 TargetTime;
	};
	class AlphaTransform : public BaseTransform
	{
	public:
		AlphaTransform(::Graphics::SpriteInterface& target, const sf::Uint8 targetAlpha, const sf::Uint32 time, const sf::Uint32 transformTime = 0, const sf::Uint32 delay = 0);
		//ScaleTransform(::Graphics::SpriteInterface& target, const sf::Vector2f& initialScale, const sf::Vector2f& targetScale, const sf::Uint32 time, const sf::Uint32 transformTime);

		void Update(const sf::Uint32 time, const float scale = 1.f) override;

		const sf::Uint8 GetTargetAlpha() const;

		const sf::Uint8 GetTransformationRate() const;
	protected:
		bool NegativeGrowth;
		float TransformationRate;
		float TransitionValue;
		sf::Uint8 TargetAlpha;
		sf::Uint32 TargetTime;
	};

}

#endif