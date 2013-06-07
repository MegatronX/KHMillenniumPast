#include "TextTransforms.h"
#include <boost/lexical_cast.hpp>
namespace Graphics
{
	TextTransform::TextTransform(sf::Text& text, const sf::Uint32 time, const sf::Uint32 transformTime, const sf::Uint32 delay) 
		: TargetText(text), TransformTime(transformTime), TargetTime(time + transformTime + delay), Delay(delay), StartTime(time + delay), Transitioning(delay > 0 ? false : true), Expired(false)
	{

	}

	void TextTransform::Update(const sf::Uint32 time, const float TimeScale)
	{
		if (time > LastUpdate)
			LastUpdate = time;
		if (time >= TargetTime && !Expired)
		{
			DispatchEvents(time);
			Expired = true;
		}
		else if (!Transitioning && time >= StartTime && !Expired)
		{
			Transitioning = true;
		}
		LastUpdate = time;
	}

	sf::Text& TextTransform::GetTarget()
	{
		return TargetText;
	}

	void TextTransform::AddTransformationCompleteEvent(const std::string& index, const TextTransformationCompletedSignal& eventHandler)
	{
		TransformationEvents[index] = eventHandler;
	}
	bool TextTransform::RemoveTransformationCompleteEvent(const std::string& index)
	{
		auto it = TransformationEvents.find(index);
		if (it != TransformationEvents.end())
		{
			TransformationEvents.erase(it);
			return true;
		}
		return false;
	}

	void TextTransform::DispatchEvents(const sf::Uint32 time)
	{
		for (auto ev = TransformationEvents.begin(); ev != TransformationEvents.end(); ++ev)
		{
			ev->second(time, this);
		}
	}

	sf::Uint32 TextTransform::GetTargetTime() const
	{
		return TargetTime;
	}

	bool TextTransform::GetExpired() const
	{
		return Expired;
	}
	void TextTransform::SetExpired(const bool val)
	{
		Expired = val;
	}

	void TextTransform::SetTarget(sf::Text& target)
	{
		TargetText = target;
	}

	//Text countdown

	TextCountdownTransform::TextCountdownTransform(int initialValue, int targetValue, sf::Text& text, const sf::Uint32 time, const sf::Uint32 transformTime, const sf::Uint32 delay) 
		: TextTransform(text, time, transformTime, delay), TargetValue(targetValue), RunningValue(static_cast<float>(initialValue)), TransitionRate(0.f)
	{
		TargetText.setString(boost::lexical_cast<std::string>(initialValue));
		TransitionRate = (static_cast<float>(targetValue) - static_cast<float>(initialValue)) / static_cast<float>(transformTime);
	}

	void TextCountdownTransform::Update(const sf::Uint32 time, const float TimeScale)
	{
		if (!Expired)
		{
			sf::Uint32 Elapsed = time - LastUpdate;
			if (LastUpdate > time)
				Elapsed = 0;
			if (Elapsed > 0 && Transitioning)
			{
				/*sf::Vector2f CurrentPosition(Target.GetPosition());
				if (TransformationRate.x != 0.f)
				{
					CurrentPosition.x += TransformationRate.x * static_cast<float>(Elapsed);

				}
				if (TransformationRate.y != 0.f)
				{
					CurrentPosition.y += TransformationRate.y * static_cast<float>(Elapsed);
				}
				Target.SetPosition(CurrentPosition);*/

				RunningValue += TransitionRate * static_cast<float>(Elapsed);
				TargetText.setString(boost::lexical_cast<std::string>(static_cast<int>(RunningValue)));

			}
			TextTransform::Update(time, TimeScale);
			if (Expired)
			{
				//Target.SetPosition(TargetPosition);
				//TransformationRate = sf::Vector2f(0.f, 0.f);
				RunningValue = static_cast<float>(TargetValue);
				TransitionRate = 0.f;
				TargetText.setString(boost::lexical_cast<std::string>(TargetValue));
			}
		}
	}

	sf::Uint32 TextCountdownTransform::GetTargetValue()
	{
		return TargetValue;
	}

	float TextCountdownTransform::GetTransformationRate()
	{
		return TransitionRate;
	}
}