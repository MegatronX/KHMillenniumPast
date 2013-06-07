#include "BaseTransform.h"

namespace Graphics
{
	BaseTransform::BaseTransform(::Graphics::SpriteInterface& targetDrawabale, const sf::Uint32 time, const sf::Uint32 transformTime, const sf::Uint32 delay) 
		: Target(targetDrawabale), TransformTime(transformTime), TargetTime(time + transformTime + delay), Delay(delay), StartTime(time + delay), Transitioning(delay > 0 ? false : true), Expired(false)
	{
		
	}

	void BaseTransform::Update(const sf::Uint32 time, const float scale)
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

	::Graphics::SpriteInterface& BaseTransform::GetTarget()
	{
		return Target;
	}


	void BaseTransform::SetTarget(::Graphics::SpriteInterface& target)
	{
		Target = target;
	}

	void BaseTransform::AddTransformationCompleteEvent(const std::string& index, const TransformationCompletedSignal& eventHandler)
	{
		TransformationEvents[index] = eventHandler;
	}
	bool BaseTransform::RemoveTransformationCompleteEvent(const std::string& index)
	{
		auto it = TransformationEvents.find(index);
		if (it != TransformationEvents.end())
		{
			TransformationEvents.erase(it);
			return true;
		}
		return false;
	}

	void BaseTransform::DispatchEvents(const sf::Uint32 time)
	{
		for (auto event = TransformationEvents.begin(); event != TransformationEvents.end(); ++event)
		{
			event->second(time, this);
		}
	}

	sf::Uint32 BaseTransform::GetTargetTime() const
	{
		return TargetTime;
	}

	bool BaseTransform::GetExpired() const
	{
		return Expired;
	}
	void BaseTransform::SetExpired(const bool val)
	{
		Expired = val;
	}

	//Position Time
	PositionTransform::PositionTransform(::Graphics::SpriteInterface& target, const sf::Vector2f& targetPosition, const sf::Uint32 time, const sf::Uint32 transformTime, const sf::Uint32 delay) 
		: BaseTransform(target, time, transformTime, delay), TargetPosition(targetPosition)
	{
		if (transformTime > 0)
		{
			TransformationRate = (TargetPosition - Target.GetPosition()) / static_cast<float>(transformTime); 
		}
		else
		{
			TransformationRate = sf::Vector2f(0.f, 0.f);
			target.SetPosition(TargetPosition);
		}
	}

	void PositionTransform::Update(const sf::Uint32 time, const float scale)
	{
		if (!Expired)
		{
			sf::Uint32 Elapsed = time - LastUpdate;
			if (LastUpdate > time)
				Elapsed = 0;
			if (Elapsed > 0 && Transitioning)
			{
				sf::Vector2f CurrentPosition(Target.GetPosition());
				if (TransformationRate.x != 0.f)
				{
					CurrentPosition.x += TransformationRate.x * static_cast<float>(Elapsed);
					
				}
				if (TransformationRate.y != 0.f)
				{
					CurrentPosition.y += TransformationRate.y * static_cast<float>(Elapsed);
				}
				Target.SetPosition(CurrentPosition);
			}
			BaseTransform::Update(time, scale);
			if (Expired)
			{
				Target.SetPosition(TargetPosition);
				TransformationRate = sf::Vector2f(0.f, 0.f);
			}

		}
	}

	const sf::Vector2f& PositionTransform::GetTargetPosition() const
	{
		return TargetPosition;
	}

	const sf::Vector2f& PositionTransform::GetTransformationRate() const
	{
		return TransformationRate;
	}

	//Scale tranform

	ScaleTransform::ScaleTransform(::Graphics::SpriteInterface& target, const sf::Vector2f& targetScale, const sf::Uint32 time, const sf::Uint32 transformTime, const sf::Uint32 delay)
		: BaseTransform(target, time, transformTime, delay), TargetScale(targetScale), NegativeGrowth(false)
	{
		if (transformTime > 0)
		{
			TransformationRate = (targetScale - target.GetScale()) / static_cast<float>(transformTime); 
			NegativeGrowth = (TransformationRate.x < 0 || TransformationRate.y < 0);
		}
		else
		{
			TransformationRate = sf::Vector2f(0.f, 0.f);
			target.SetScale(TargetScale);
		}
	}
	//ScaleTransform(::Graphics::SpriteInterface& target, const sf::Vector2f& initialScale, const sf::Vector2f& targetScale, const sf::Uint32 time, const sf::Uint32 transformTime);

	void ScaleTransform::Update(const sf::Uint32 time, const float scale)
	{
		if (!Expired)
		{
			sf::Uint32 Elapsed = time - LastUpdate;
			if (LastUpdate > time)
				Elapsed = 0;
			if (Elapsed > 0 && Transitioning)
			{
				
				sf::Vector2f CurrentScale(Target.GetScale());
				if (TransformationRate.x != 0.f)
				{
					CurrentScale.x += TransformationRate.x * static_cast<float>(Elapsed);

				}
				if (TransformationRate.y != 0.f)
				{
					CurrentScale.y += TransformationRate.y * static_cast<float>(Elapsed);
				}
				//if (NegativeGrowth)
				//{
				//	std::cout << "Setting to scale " << CurrentScale.x << " | " << CurrentScale.y << "\n";
				//}
				Target.SetScale(CurrentScale);
			}
			BaseTransform::Update(time, scale);
			if (Expired)
			{
				Target.SetScale(TargetScale);
				TransformationRate = sf::Vector2f(0.f, 0.f);
			}

		}
	}

	const sf::Vector2f& ScaleTransform::GetTargetScale() const
	{
		return TargetScale;
	}

	const sf::Vector2f& ScaleTransform::GetTransformationRate() const
	{
		return TransformationRate;
	}

	AlphaTransform::AlphaTransform(::Graphics::SpriteInterface& target, const sf::Uint8 targetAlpha, const sf::Uint32 time, const sf::Uint32 transformTime, const sf::Uint32 delay)
		: BaseTransform(target, time, transformTime, delay), TargetAlpha(targetAlpha), TransitionValue(static_cast<float>(target.GetAlpha()))
	{
		if (transformTime > 0)
		{
			TransformationRate = (targetAlpha - target.GetAlpha()) / static_cast<float>(transformTime); 
			NegativeGrowth = TransformationRate < 0.f;//(TransformationRate.x < 0 || TransformationRate.y < 0);
		}
		else
		{

			TransformationRate = 0;
			target.SetAlpha(TargetAlpha);
		}
	}
	//ScaleTransform(::Graphics::SpriteInterface& target, const sf::Vector2f& initialScale, const sf::Vector2f& targetScale, const sf::Uint32 time, const sf::Uint32 transformTime);

	void AlphaTransform::Update(const sf::Uint32 time, const float scale)
	{

		if (!Expired)
		{
			sf::Uint32 Elapsed = time - LastUpdate;
			if (LastUpdate > time)
				Elapsed = 0;
			if (Elapsed > 0 && Transitioning)
			{
				TransitionValue += TransformationRate * static_cast<float>(Elapsed);
				//if (NegativeGrowth)
				//{
				//	std::cout << "Setting to scale " << CurrentScale.x << " | " << CurrentScale.y << "\n";
				//}
				Target.SetAlpha(static_cast<sf::Uint8>(TransitionValue));
				//Target.SetScale(CurrentScale);
			}
			BaseTransform::Update(time, scale);
			if (Expired)
			{
				Target.SetAlpha(TargetAlpha);
				TransformationRate = 0.f;
			}

		}
	}

	const sf::Uint8 AlphaTransform::GetTargetAlpha() const
	{
		return TargetAlpha;
	}

	const sf::Uint8 AlphaTransform::GetTransformationRate() const
	{
		return TransformationRate;
	}
}