#include "SpriteInterface.h"

namespace Graphics
{
	SpriteInterface::SpriteInterface(const sf::Uint32 StartTime) : LastUpdate(0), DrawEnabled(true), ID(0), SpriteName(""), AlphaTransitionDelta(0), AlphaTransitionValue(0), TargetAlpha(0), AlphaTransValue(0), CurrentAlpha(255), DefaultAlpha(255),
			AlphaTime(0), LastAlphaUpdate(StartTime), AlphaPhasing(false), TargetPosition(ZeroVec), PositionDelta(ZeroVec), DefaultPosition(ZeroVec), CurrentPosition(ZeroVec), PositionTime(0), LastPositionUpdate(StartTime),
			Transiting(false), TargetScale(1.0f, 1.0f), ScaleDelta(ZeroVec), DefaultScale(1.0f, 1.0f), CurrentScale(1.0f, 1.0f), ScaleTime(0), LastScaleUpdate(StartTime), Scaling(false), TargetAngle(0.0f), AngleDelta(0.0f),
			DefaultAngle(0.0f), CurrentAngle(0.0f), AngleTime(0), LastAngleUpdate(StartTime), Rotating(false)
		{

		}
		SpriteInterface::SpriteInterface(const std::string& name, const int ID, const sf::Uint32 StartTime) : LastUpdate(0), DrawEnabled(true), ID(ID), SpriteName(name), AlphaTransitionDelta(0), AlphaTransitionValue(0), TargetAlpha(0), AlphaTransValue(0), CurrentAlpha(255), DefaultAlpha(255),
			AlphaTime(0), LastAlphaUpdate(StartTime), AlphaPhasing(false), TargetPosition(ZeroVec), PositionDelta(ZeroVec), DefaultPosition(ZeroVec), CurrentPosition(ZeroVec), PositionTime(0), LastPositionUpdate(StartTime),
			Transiting(false), TargetScale(1.0f, 1.0f), ScaleDelta(ZeroVec), DefaultScale(1.0f, 1.0f), CurrentScale(1.0f, 1.0f), ScaleTime(0), LastScaleUpdate(StartTime), Scaling(false), TargetAngle(0.0f), AngleDelta(0.0f),
			DefaultAngle(0.0f), CurrentAngle(0.0f), AngleTime(0), LastAngleUpdate(StartTime), Rotating(false)
		{

		}
		void SpriteInterface::Update(const sf::Uint32 time, const float TimeScale)
		{
			if (!Paused)
			{
				/*sf::Uint32 Elapsed = (time - LastUpdate);// * TimeScale;
				if (LastUpdate > time)
					Elapsed = 0;
				sf::Uint32 ScaledElapsed = Elapsed;
				if (TimeScale != 1.0f)
				{
					ScaledElapsed = (sf::Uint32)((float)Elapsed * TimeScale);
				}
				bool AdjustTimes = Elapsed != ScaledElapsed;*/
				if (Transiting && PositionDelta != ZeroVec)
				{
					sf::Uint32 ElapsedPosTime = time - LastPositionUpdate;
					if (time < LastPositionUpdate)
						ElapsedPosTime = 0;
					if (TimeScale < 0.99f && TimeScale > 1.01f)
					{
						sf::Uint32 ScaledPosTime = (sf::Uint32)((float)(ElapsedPosTime) * TimeScale);
						PositionTime += (ElapsedPosTime - ScaledPosTime);
						ElapsedPosTime = ScaledPosTime;
					}
					
					if (time < PositionTime)
					{
						SetSpritePosition(GetSpritePosition() + PositionDelta * (float)ElapsedPosTime, false);
					}
					else
					{
						SetSpritePosition(TargetPosition);
						PositionDelta = ZeroVec;
						Transiting = false;
						DispatchTranslationEvents();
					}
					LastPositionUpdate = time;
				}
				if (Scaling && ScaleDelta != ZeroVec)
				{
					sf::Uint32 ElapsedScaleTime = time - LastScaleUpdate;
					if (time < LastScaleUpdate)
						ElapsedScaleTime = 0;	
					if (TimeScale < 0.99f && TimeScale > 1.01f)
					{
						sf::Uint32 ScaledScaleTime = (sf::Uint32)((float)(ElapsedScaleTime) * TimeScale);
						ScaleTime += (ElapsedScaleTime - ScaledScaleTime);
						ElapsedScaleTime = ScaledScaleTime; 
					}
					if (time < ScaleTime)
					{
						SetSpriteScale(GetSpriteScale() + ScaleDelta * (float)ElapsedScaleTime, false);
					}
					else
					{
						SetSpriteScale(TargetScale);
						ScaleDelta = ZeroVec;
						Scaling = false;
						DispatchScalingEvents();
					}
					LastScaleUpdate = time;
				}
				if (AlphaPhasing && AlphaTransitionDelta != 0)
				{
					sf::Uint32 ElapsedAlphaTime = time - LastAlphaUpdate;
					if (time < LastAlphaUpdate)
						ElapsedAlphaTime = 0;
					if (TimeScale < 0.99f && TimeScale > 1.01f)
					{
						sf::Uint32 ScaledAlphaTime = (sf::Uint32)((float)(ElapsedAlphaTime) * TimeScale);
						AlphaTime += (ElapsedAlphaTime - ScaledAlphaTime);
						ElapsedAlphaTime = ScaledAlphaTime;
					}
					if (time < AlphaTime)
					{
						AlphaTransitionValue += AlphaTransitionDelta * (float)ElapsedAlphaTime;
						SetAlpha((sf::Uint8)(AlphaTransitionValue), false);
					}
					else
					{
						SetAlpha(TargetAlpha);
						AlphaTransitionDelta = 0;
						AlphaPhasing = false;
						DispatchAlphaPhaseEvents();
					}
					LastAlphaUpdate = time;
				}
				if (Rotating && AngleDelta != 0)
				{
					sf::Uint32 ElapsedAngleTime = time - LastAngleUpdate;
					if (time < LastAngleUpdate)
						ElapsedAngleTime = 0;
					if (TimeScale < 0.99f && TimeScale > 1.01f)
					{
						sf::Uint32 ScaledAngleTime = (sf::Uint32)((float)(ElapsedAngleTime) * TimeScale);
						AngleTime += (ElapsedAngleTime - ScaledAngleTime);
						ElapsedAngleTime = ScaledAngleTime;
					}
					if (time < AngleTime)
					{
						SetAngle(GetAngle() + AngleDelta * (float)ElapsedAngleTime, false);
					}
					else
					{
						SetAngle(TargetAngle);
						AngleDelta = 0;
						Rotating = false;
						DispatchRotationEvents();
					}
				}
			}
			else
			{
				sf::Uint32 Elapsed = (time - LastUpdate);
				if (Transiting)
				{
					PositionTime += Elapsed;
					LastPositionUpdate = time;
				}
				if (Scaling)
				{
					ScaleTime += Elapsed;
					LastScaleUpdate = time;
				}
				if (Rotating)
				{
					AngleTime += Elapsed;
					LastAngleUpdate = time;
				}
				if (AlphaPhasing)
				{
					AlphaTime += Elapsed;
					LastAlphaUpdate = time;
				}
			}
			LastUpdate = time;
		}
		void SpriteInterface::Update(const float time, const float TimeScale)
		{
			Update(time * 1000.0f, TimeScale);
		}
		bool SpriteInterface::AddTranslationEvent(const std::string &index, const TranslationFinishedEvent &transEvent)
		{
			bool added = false;
			auto it = translationEvents.find(index);
			if (it == translationEvents.end())
			{
				translationEvents[index] = transEvent;
				added = true;
			}
			return added;
		}
		bool SpriteInterface::RemoveTranslationEvent(const std::string &index)
		{
			bool removed = false;
			auto it = translationEvents.find(index);
			if (it != translationEvents.end())
			{
				translationEvents.erase(it);
				removed = true;
			}
			return removed;
		}
		void SpriteInterface::MarkTranslationEventForDeletion(std::map<std::string, TranslationFinishedEvent>::iterator it)
		{
			this->TranslationEventDeletionVector.push_back(it);
		}
		void SpriteInterface::MarkTranslationEventForDeletion(const std::string &index)
		{
			auto it = translationEvents.find(index);
			if (it != translationEvents.end())
			{
				MarkTranslationEventForDeletion(it);
			}
		}
		void SpriteInterface::DispatchTranslationEvents()
		{
			for(auto it = translationEvents.begin(); it != translationEvents.end(); ++it)
			{
				it->second(this);
			}
			if (TranslationEventDeletionVector.size() > 0)
			{
				for (auto current = TranslationEventDeletionVector.begin(); current != TranslationEventDeletionVector.end(); ++current)
				{
					translationEvents.erase((*current));
				}
				TranslationEventDeletionVector.clear();
			}
		}
		void SpriteInterface::ClearTranslationEvents()
		{
			translationEvents.clear();
		}

		bool SpriteInterface::AddScalingEvent(const std::string &index, const ScalingFinishedEvent &scalingEvent)
		{
			bool added = false;
			auto it = scalingEvents.find(index);
			if (it == scalingEvents.end())
			{
				scalingEvents[index] = scalingEvent;
				added = true;
			}
			return added;
		}
		bool SpriteInterface::RemoveScalingEvent(const std::string &index)
		{
			bool removed = false;
			auto it = scalingEvents.find(index);
			if (it != scalingEvents.end())
			{
				scalingEvents.erase(it);
				removed = true;
			}
			return removed;
		}
		void SpriteInterface::MarkScalingEventForDeletion(std::map<std::string, ScalingFinishedEvent>::iterator it)
		{
			this->ScaleEventDeletionVector.push_back(it);
		}
		void SpriteInterface::MarkScalingEventForDeletion(const std::string& index)
		{
			auto it = scalingEvents.find(index);
			if (it != scalingEvents.end())
			{
				MarkScalingEventForDeletion(it);
			}
		}
		void SpriteInterface::DispatchScalingEvents()
		{
			for (auto it = scalingEvents.begin(); it != scalingEvents.end(); ++it)
			{
				it->second(this);
			}
			if (ScaleEventDeletionVector.size() > 0)
			{
				for (auto current = ScaleEventDeletionVector.begin(); current != ScaleEventDeletionVector.end(); ++current)
				{
					scalingEvents.erase(*current);
				}
				ScaleEventDeletionVector.clear();
			}
		}
		void SpriteInterface::ClearScalingEvents()
		{
			scalingEvents.clear();
		}

		bool SpriteInterface::AddAlphaPhaseEvent(const std::string& index, const AlphaPhaseFinishedEvent &alphaEvent)
		{
			alphaEvents[index] = alphaEvent;
			return true;
		}
		bool SpriteInterface::RemoveAlphaPhaseEvent(const std::string &index)
		{
			bool removed = false;
			auto it = alphaEvents.find(index);
			if (it != alphaEvents.end())
			{
				alphaEvents.erase(it);
				removed = true;
			}
			return removed;
		}
		void SpriteInterface::MarkAlphaPhaseEventForDeletion(std::map<std::string, AlphaPhaseFinishedEvent>::iterator it)
		{
			this->AlphaPhaseEventDeletionVector.push_back(it);
		}
		void SpriteInterface::MarkAlphaPhaseEventForDeletion(const std::string& index)
		{
			auto it = alphaEvents.find(index);
			if (it != alphaEvents.end())
			{
				MarkAlphaPhaseEventForDeletion(it);
			}
		}
		void SpriteInterface::DispatchAlphaPhaseEvents()
		{
			for (auto alphaevent = alphaEvents.begin(); alphaevent != alphaEvents.end(); ++alphaevent)
			{
				alphaevent->second(this);
			}
			if (AlphaPhaseEventDeletionVector.size() > 0)
			{
				for (auto event = AlphaPhaseEventDeletionVector.begin(); event != AlphaPhaseEventDeletionVector.end(); ++event)
				{
					alphaEvents.erase(*event);
				}
			}
			AlphaPhaseEventDeletionVector.clear();
		}
		void SpriteInterface::ClearAlphaPhaseEvents()
		{
			alphaEvents.clear();
		}

		bool SpriteInterface::AddRotationEvent(const std::string& index, const RotationFinishedEvent &rotationEvent)
		{
			rotationEvents[index] = rotationEvent;
			return true;
		}
		bool SpriteInterface::RemoveRotationEvent(const std::string &index)
		{
			bool removed = false;
			auto it = rotationEvents.find(index);
			if (it != rotationEvents.end())
			{
				rotationEvents.erase(it);
				removed = true;
			}
			return removed;
		}
		void SpriteInterface::MarkRotationEventForDeletion(std::map<std::string, RotationFinishedEvent>::iterator it)
		{
			this->RotationEventDeletionVector.push_back(it);
		}
		void SpriteInterface::MarkRotationEventForDeletion(const std::string& index)
		{
			auto it = rotationEvents.find(index);
			if (it != rotationEvents.end())
			{
				MarkRotationEventForDeletion(it);
			}
		}
		void SpriteInterface::DispatchRotationEvents()
		{
			for (auto rotevent = rotationEvents.begin(); rotevent != rotationEvents.end(); ++rotevent)
			{
				rotevent->second(this);
			}
			for (auto event = RotationEventDeletionVector.begin(); event != RotationEventDeletionVector.end(); ++event)
			{
				rotationEvents.erase(*event);
			}
			RotationEventDeletionVector.clear();
		}
		void SpriteInterface::ClearRotationEvents()
		{
			rotationEvents.clear();
		}
		//Getters/Setters
		void SpriteInterface::SetDrawEnable(const bool drawenabled)
		{
			this->DrawEnabled = drawenabled;
		}
		bool SpriteInterface::GetDrawEnabled() const
		{
			return DrawEnabled;
		}
		int SpriteInterface::GetID() const
		{
			return ID;
		}
		std::string SpriteInterface::GetName() const
		{
			return SpriteName;
		}
		float SpriteInterface::GetLastUpdate() const
		{
			return LastUpdate;
		}

		sf::Vector2f SpriteInterface::GetTargetPosition() const
		{
			return this->TargetPosition;
		}
		sf::Vector2f SpriteInterface::GetDefaultPosition() const
		{
			return this->DefaultPosition;
		}
		sf::Vector2f SpriteInterface::GetSpritePosition() const
		{
			return CurrentPosition;
		}
		void SpriteInterface::SetDefaultPosition( const sf::Vector2f &position)
		{
			DefaultPosition = position;
		}
		void SpriteInterface::SetSpritePosition(const sf::Vector2f &pos, bool StopAnyTranslation)
		{
			if (StopAnyTranslation)
			{
				Transiting = false;
				TargetPosition = pos;
				PositionDelta = ZeroVec;
			}
			CurrentPosition = pos;
		}
		void SpriteInterface::SetSpritePosition(const float x, const float y, bool StopAnyTranslation)
		{
			SetSpritePosition(sf::Vector2f(x, y), StopAnyTranslation);
		}
		sf::Vector2f SpriteInterface::GetTargetSpriteScale() const
		{
			return TargetScale;
		}
		sf::Vector2f SpriteInterface::GetDefaultScale() const
		{
			return DefaultScale;
		}
		sf::Vector2f SpriteInterface::GetSpriteScale() const
		{
			return CurrentScale;
		}
		void SpriteInterface::SetDefaultScale(const sf::Vector2f &scale)
		{
			DefaultScale = scale;
		}
		//Does NOT dispatch events
		void SpriteInterface::SetSpriteScale(const sf::Vector2f& scale, bool StopAnyScaling)
		{
			if (StopAnyScaling)
			{
				Scaling = false;
				TargetScale = scale;
				ScaleDelta = ZeroVec;

			}
			CurrentScale = scale;
		}
		void SpriteInterface::SetSpriteScale(const float x, const float y, bool StopAnyScaling)
		{
			SetSpriteScale(sf::Vector2f(x, y), StopAnyScaling);
		}
		sf::Uint8 SpriteInterface::GetTargetAlpha() const
		{
			return TargetAlpha;
		}
		sf::Uint8 SpriteInterface::GetDefaultAlpha() const
		{
			return DefaultAlpha; 
		}
		sf::Uint8 SpriteInterface::GetAlpha() const
		{
			return CurrentAlpha;
		}
		void SpriteInterface::SetDefaultAlpha(const sf::Uint8 alpha)
		{
			DefaultAlpha = alpha;
		}
		//Does NOT dispatch events
		void SpriteInterface::SetAlpha(const sf::Uint8 alpha, bool StopAnyAlphaPhase)
		{
			if (StopAnyAlphaPhase)
			{
				AlphaPhasing = false;
				TargetAlpha = alpha;
				AlphaTransitionDelta = 0.0f;
				AlphaTransitionValue = 0.0f;
			}
			CurrentAlpha = alpha;
		}

		float SpriteInterface::GetTargetAngle() const
		{
			return TargetAngle;
		}
		float SpriteInterface::GetDefaultAngle() const
		{
			return DefaultAngle;
		}
		void SpriteInterface::SetDefaultAngle(const float angle)
		{
			DefaultAngle = angle;
		}
		float SpriteInterface::GetAngle() const
		{
			return CurrentAngle;
		}
		void SpriteInterface::SetAngle(const float angle, bool StopAnyRotation)
		{
			if (Rotating)
			{
				Rotating = false;
				TargetAngle = angle;
				AngleDelta = 0.0f;
			}
			CurrentAngle = angle;
		}
		bool SpriteInterface::IsTransiting() const
		{
			return this->Transiting;
		}
		bool SpriteInterface::IsScaling() const
		{
			return this->Scaling;
		}
		bool SpriteInterface::IsAlphaPhasing() const
		{
			return this->AlphaPhasing;
		}
		bool SpriteInterface::IsRotating() const
		{
			return this->Rotating;
		}
		void SpriteInterface::SlideSprite(const sf::Vector2f &targetPosition, const sf::Uint32 transitionTime, const sf::Uint32 currentTime)
		{
			this->TargetPosition = targetPosition;
			this->PositionTime = transitionTime + currentTime;
			this->LastPositionUpdate = currentTime;
			this->Transiting = true;
			if (PositionTime > 0)
			{
				this->PositionDelta.x = (targetPosition.x - this->CurrentPosition.x) / (float)transitionTime;
				this->PositionDelta.y = (targetPosition.y - this->CurrentPosition.y) / (float)transitionTime;
			}
		}
		void SpriteInterface::StopSliding(bool DispatchEvents)
		{
			Transiting = false;
			TargetPosition = CurrentPosition;
			PositionDelta = ZeroVec;
			if (DispatchEvents)
				DispatchTranslationEvents();
		}
		void SpriteInterface::ScaleSprite(const sf::Vector2f &targetScale, const sf::Uint32 scaleTime, const sf::Uint32 currentTime)
		{
			this->TargetScale = targetScale;
			this->ScaleTime = scaleTime + currentTime;
			this->LastScaleUpdate = currentTime;
			this->Scaling = true;
			if (scaleTime > 0)
			{
				this->ScaleDelta.x = (targetScale.x - this->CurrentScale.x) / (float)scaleTime;
				this->ScaleDelta.y = (targetScale.y - this->CurrentScale.y) / (float)scaleTime;
			}
		}
		void SpriteInterface::StopScaling(bool DispatchEvents)
		{
			Scaling = false;
			TargetScale = CurrentScale;
			ScaleDelta = ZeroVec;
			if (DispatchEvents)
				DispatchScalingEvents();
		}
		void SpriteInterface::AlphaPhaseSprite(const sf::Uint8 targetAlpha, const sf::Uint8 startingAlpha, const sf::Uint32 alphaTime, const sf::Uint32 currentTime)
		{
			this->TargetAlpha = targetAlpha;
			this->AlphaTime = alphaTime + currentTime;
			this->LastAlphaUpdate = currentTime;
			if (AlphaTime > 0)
			{
				this->AlphaPhasing = AlphaTime > 0;
				this->AlphaTransitionDelta = ((float)targetAlpha - (float)startingAlpha) / (float)alphaTime;
				this->AlphaTransValue = startingAlpha;
				this->AlphaTransitionValue = (float)startingAlpha;

			}

		}
		void SpriteInterface::StopAlphaPhasing(bool DispatchEvents)
		{
			AlphaPhasing = false;
			TargetAlpha = CurrentAlpha;
			AlphaTransitionDelta = 0.0f;
			AlphaTransitionValue = 0.0f;
			if (DispatchEvents)
				DispatchAlphaPhaseEvents();
		}
		void SpriteInterface::Rotate(const float targetAngle, const sf::Uint32 rotationTime, const sf::Uint32 currentTime, bool CenterRotation)
		{
			TargetAngle = targetAngle;
			AngleTime = currentTime + rotationTime;
			LastAngleUpdate = currentTime;
			if (AngleTime > 0)
			{
				Rotating = true;
				AngleDelta = (targetAngle - CurrentAngle) / (float)AngleTime; 
			}
		}
		void SpriteInterface::StopRotation(bool DispatchEvents)
		{
			Rotating = false;
			TargetAngle = CurrentAngle;
			AngleDelta = 0.0f;
			if (DispatchEvents)
				DispatchRotationEvents();

		}
}