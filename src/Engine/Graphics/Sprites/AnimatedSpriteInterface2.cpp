#include "AnimatedSpriteInterface.h"

namespace Graphics
{
	AnimatedSpriteInterface::AnimatedSpriteInterface()/* : TransEvents(new TranslationFinishedEvent), ScalingEvents(new ScalingFinishedEvent), RotationEvents(new RotationFinishedEvent), AlphaPhaseEvents(new AlphaPhaseFinishedEvent),
		LastPositionUpdate(0), Translating(false), TargetPosition(0.f, 0.f), PositionDelta(0.f, 0.f), DefaultPosition(0.f, 0.f), PositionTime(0), 
		LastScaleUpdate(0), TargetScale(1.f, 1.f), ScaleDelta(0.f, 0.f), DefaultScale(1.f, 1.f), ScaleTime(0),
		LastUpdate(0)*/
	{

	}

	AnimatedSpriteInterface::AnimatedSpriteInterface(const sf::Uint32 time)/* : TransEvents(new TranslationFinishedEvent), ScalingEvents(new ScalingFinishedEvent), RotationEvents(new RotationFinishedEvent), AlphaPhaseEvents(new AlphaPhaseFinishedEvent),
		LastPositionUpdate(time), Translating(false), TargetPosition(0.f, 0.f), PositionDelta(0.f, 0.f), DefaultPosition(0.f, 0.f), PositionTime(0), 
		LastScaleUpdate(time), TargetScale(1.f, 1.f), ScaleDelta(0.f, 0.f), DefaultScale(1.f, 1.f), ScaleTime(0),
		LastUpdate(time)*/
	{

	}

	void AnimatedSpriteInterface::Update(const sf::Uint32 time, const float TimeScale)
	{
		sf::Uint32 Elapsed = LastUpdate > time ? 0 : time - LastUpdate;
		bool ScaledTime = (TimeScale < 0.99f || TimeScale > 1.01f);
		//Do Update stuff here

		LastUpdate = time;
	}
	/*
	bool AnimatedSpriteInterface::AddTranslationEvent(const std::string& name, const TranslationFinishedEvent::slot_type& event, bool overwriteExisting)
	{
		bool added = false;
		auto existingEvent = ActiveTranslationEvents.find(name);
		if (existingEvent != ActiveTranslationEvents.end() && overwriteExisting)
		{
			existingEvent->second.disconnect();
			ActiveTranslationEvents[name] = TransEvents->connect(event);
			added = true;
		}
		else if (existingEvent == ActiveTranslationEvents.end())
		{
			ActiveTranslationEvents[name] = TransEvents->connect(event);
			added = true;
		}
		return added;
	}
	bool AnimatedSpriteInterface::RemoveTranslationEvent(const std::string &index)
	{
		bool removed = false;
		auto existingEvent = ActiveTranslationEvents.find(index);
		if (existingEvent != ActiveTranslationEvents.end())
		{
			existingEvent->second.disconnect();
			removed = true;
		}
		return removed;
	}
	*/
}