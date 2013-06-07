#pragma once
#ifndef _TEXTTRANSFORMS_H_
#define _TEXTTRANSFORMS_H_

#include <sfml/Graphics.hpp>
#include <Graphics/Updater.h>
#include <boost/function.hpp>
#include <boost/unordered_map.hpp>

namespace Graphics
{
	class TextTransform;

	typedef boost::function<void (sf::Uint32 time, TextTransform* transform)> TextTransformationCompletedSignal;

	class TextTransform : public Updater
	{
	public:
		TextTransform(sf::Text& text, const sf::Uint32 time, const sf::Uint32 transformTime = 0, const sf::Uint32 delay = 0);

		void Update(const sf::Uint32 time, const float TimeScale  = 1.f) override;

		sf::Text& GetTarget();

		void AddTransformationCompleteEvent(const std::string& index, const TextTransformationCompletedSignal& eventHandler);
		bool RemoveTransformationCompleteEvent(const std::string& index);

		void DispatchEvents(const sf::Uint32 time);

		sf::Uint32 GetTargetTime() const;

		bool GetExpired()const;
		void SetExpired(const bool val);
	protected:
		void SetTarget(sf::Text& target);

		boost::unordered_map<std::string, TextTransformationCompletedSignal> TransformationEvents;
		sf::Text& TargetText;

		sf::Uint32 TargetTime;
		sf::Uint32 TransformTime;
		sf::Uint32 StartTime;
		sf::Uint32 LastUpdate;
		sf::Uint32 Delay;

		bool Transitioning;
		bool Expired;
	private:
	};

	class TextCountdownTransform : public TextTransform
	{
	public:
		TextCountdownTransform(int initialValue, int targetValue, sf::Text& text, const sf::Uint32 time, const sf::Uint32 transformTime = 0, const sf::Uint32 delay = 0);

		void Update(const sf::Uint32 time, const float TimeScale  = 1.f) override;

		sf::Uint32 GetTargetValue();

		float GetTransformationRate();
	protected:
		sf::Uint32 TargetValue;
		float TransitionRate;
		float RunningValue;
	};
}

#endif