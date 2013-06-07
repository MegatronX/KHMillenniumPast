#pragma once
#ifndef _SPRITEINTERFACE_H_
#define _SPRITEINTERFACE_H_
#include <graphics/AnimatedDraw.h>
#include <graphics/GraphicsConstants.h>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
namespace Graphics
{
	class SpriteInterface;
	typedef boost::function<void(SpriteInterface *sprite)> TranslationFinishedEvent;
	typedef boost::function<void(SpriteInterface *sprite)> ScalingFinishedEvent;
	typedef boost::function<void(SpriteInterface* sprite)> AlphaPhaseFinishedEvent;
	typedef boost::function<void(SpriteInterface* sprite)> RotationFinishedEvent;
	class SpriteInterface : public AnimatedDraw
	{
	public:
		SpriteInterface(const sf::Uint32 StartTime = 0);
		SpriteInterface(const std::string& name, const int ID, const sf::Uint32 StartTime = 0);

		virtual void Update(const sf::Uint32 time, const float TimeScale = 1.0f) override;
		virtual void Update(const float time, const float TimeScale = 1.0f) override;

		bool AddTranslationEvent(const std::string &index, const TranslationFinishedEvent &transEvent);
		bool RemoveTranslationEvent(const std::string &index);
		void MarkTranslationEventForDeletion(std::map<std::string, TranslationFinishedEvent>::iterator it);
		void MarkTranslationEventForDeletion(const std::string &index);
		void DispatchTranslationEvents();
		void ClearTranslationEvents();

		bool AddScalingEvent(const std::string &index, const ScalingFinishedEvent &scalingEvent);
		bool RemoveScalingEvent(const std::string &index);
		void MarkScalingEventForDeletion(std::map<std::string, ScalingFinishedEvent>::iterator it);
		void MarkScalingEventForDeletion(const std::string& index);
		
		void DispatchScalingEvents();
		void ClearScalingEvents();
		bool AddAlphaPhaseEvent(const std::string& index, const AlphaPhaseFinishedEvent &alphaEvent);
		bool RemoveAlphaPhaseEvent(const std::string &index);
		void MarkAlphaPhaseEventForDeletion(std::map<std::string, AlphaPhaseFinishedEvent>::iterator it);
		void MarkAlphaPhaseEventForDeletion(const std::string& index);
		void DispatchAlphaPhaseEvents();
		void ClearAlphaPhaseEvents();

		bool AddRotationEvent(const std::string& index, const RotationFinishedEvent &rotEvent);
		bool RemoveRotationEvent(const std::string &index);
		void MarkRotationEventForDeletion(std::map<std::string, RotationFinishedEvent>::iterator it);
		void MarkRotationEventForDeletion(const std::string& index);
		void DispatchRotationEvents();
		void ClearRotationEvents();
		//Getters/Setters
		void SetDrawEnable(const bool drawenabled);
		bool GetDrawEnabled() const;
		int GetID() const;
		std::string GetName() const;
		float GetLastUpdate() const;

		sf::Vector2f GetTargetPosition() const;
		sf::Vector2f GetDefaultPosition() const;
		virtual sf::Vector2f GetSpritePosition() const;
		void SetDefaultPosition( const sf::Vector2f &position);
		virtual void SetSpritePosition(const sf::Vector2f &pos, bool StopAnyTranslation = true);
		virtual void SetSpritePosition(const float x, const float y, bool StopAnyTranslation = true);
		sf::Vector2f GetTargetSpriteScale() const;
		sf::Vector2f GetDefaultScale() const;
		virtual sf::Vector2f GetSpriteScale() const;
		void SetDefaultScale(const sf::Vector2f &scale);
		//Does NOT dispatch events
		virtual void SetSpriteScale(const sf::Vector2f& scale, bool StopAnyScaling = true);
		virtual void SetSpriteScale(const float x, const float y, bool StopAnyScaling = true);
		sf::Uint8 GetTargetAlpha() const;
		sf::Uint8 GetDefaultAlpha() const;
		virtual sf::Uint8 GetAlpha() const;
		void SetDefaultAlpha(const sf::Uint8 alpha);
		//Does NOT dispatch events
		virtual void SetAlpha(const sf::Uint8 alpha, bool StopAnyAlphaPhase = true);
		float GetTargetAngle() const;
		float GetDefaultAngle() const;
		void SetDefaultAngle(const float angle);
		virtual float GetAngle() const;
		virtual void SetAngle(const float angle, bool StopAnyRotation = true);
		bool IsTransiting() const;
		bool IsScaling() const;
		bool IsAlphaPhasing() const;
		bool IsRotating() const;
		virtual void SlideSprite(const sf::Vector2f &targetPosition, const sf::Uint32 transitionTime, const sf::Uint32 currentTime);
		virtual void StopSliding(bool DispatchEvents = true);
		virtual void ScaleSprite(const sf::Vector2f &targetScale, const sf::Uint32 scaleTime, const sf::Uint32 currentTime);
		virtual void StopScaling(bool DispatchEvents = true);
		virtual void AlphaPhaseSprite(const sf::Uint8 targetAlpha, const sf::Uint8 startingAlpha, const sf::Uint32 alphaTime, const sf::Uint32 currentTime);
		virtual void StopAlphaPhasing(bool DispatchEvents = true);
		virtual void Rotate(const float targetAngle, const sf::Uint32 rotationTime, const sf::Uint32 currentTime, bool CenterRotation = false);
		virtual void StopRotation(bool DispatchEvents = true);
	protected:
		std::map<std::string, TranslationFinishedEvent> translationEvents;
		std::map<std::string, ScalingFinishedEvent> scalingEvents;
		std::map<std::string, AlphaPhaseFinishedEvent> alphaEvents;
		std::map<std::string, RotationFinishedEvent> rotationEvents;
		std::vector<std::map<std::string, TranslationFinishedEvent>::iterator> TranslationEventDeletionVector;
		std::vector<std::map<std::string, ScalingFinishedEvent>::iterator> ScaleEventDeletionVector;
		std::vector<std::map<std::string, AlphaPhaseFinishedEvent>::iterator> AlphaPhaseEventDeletionVector;
		std::vector<std::map<std::string, RotationFinishedEvent>::iterator> RotationEventDeletionVector;
		//TranslationFinished translationDone;
		//Transition Variables
		sf::Uint32 LastUpdate;
		bool DrawEnabled;
		int ID;
		std::string SpriteName;
		//Alpha Transitions
		float AlphaTransitionDelta, AlphaTransitionValue;
		sf::Uint8 TargetAlpha;
		sf::Uint8 AlphaTransValue;
		sf::Uint8 CurrentAlpha;
		sf::Uint8 DefaultAlpha;
		sf::Uint32 AlphaTime;
		sf::Uint32 LastAlphaUpdate;

		bool AlphaPhasing;
		//Position Transition
		sf::Vector2f TargetPosition;
		sf::Vector2f PositionDelta;
		sf::Vector2f DefaultPosition;
		sf::Vector2f CurrentPosition;
		sf::Uint32 PositionTime;
		sf::Uint32 LastPositionUpdate;
		bool Transiting;
		//Scale Transition
		sf::Vector2f TargetScale;
		sf::Vector2f ScaleDelta;
		sf::Vector2f DefaultScale;
		sf::Vector2f CurrentScale;
		sf::Uint32 ScaleTime;
		sf::Uint32 LastScaleUpdate;
		bool Scaling;

		float TargetAngle;
		float AngleDelta;
		float DefaultAngle;
		float CurrentAngle;
		sf::Uint32 AngleTime;
		sf::Uint32 LastAngleUpdate;
		bool Rotating;
	};
	typedef boost::shared_ptr<SpriteInterface> sprintr_ptr;
}

#endif