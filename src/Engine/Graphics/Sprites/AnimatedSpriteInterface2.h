#pragma once
#ifndef _ANIMATEDSPRITEINTERFACE_H_
#define _ANIMATEDSPRITEINTERFACE_H_

#include <graphics/AnimatedDraw.h>
#include <graphics/Sprites/SpriteInterface.h>
#include <boost/signals2.hpp>
#include <Utilities/Cloneable.h>
#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <vector>
namespace Graphics
{
	class AnimatedSpriteInterface;
	typedef boost::function<void(AnimatedSpriteInterface *sprite)> TranslationFinishedEvent;
	typedef boost::function<void(AnimatedSpriteInterface *sprite)> ScalingFinishedEvent;
	typedef boost::function<void(AnimatedSpriteInterface* sprite)> AlphaPhaseFinishedEvent;
	typedef boost::function<void(AnimatedSpriteInterface* sprite)> RotationFinishedEvent;
//	typedef boost::signals2::signal<void (SpriteInterface* sprite)> TranslationFinishedEvent;
//	typedef boost::signals2::signal<void (SpriteInterface* sprite)> ScalingFinishedEvent;
//	typedef boost::signals2::signal<void (SpriteInterface* sprite)> AlphaPhaseFinishedEvent;
//	typedef boost::signals2::signal<void (SpriteInterface* sprite)> RotationFinishedEvent;

	class AnimatedSpriteInterface : public AnimatedDraw, public virtual SpriteInterface
	{
	public:
		AnimatedSpriteInterface();
		AnimatedSpriteInterface(const sf::Uint32 time);
		//virtual void Update(const float time, const float TimeScale = 1.0)
		virtual void Update(const sf::Uint32 time, const float TimeScale = 1.0) override;

		bool AddTranslationEvent(const std::string& name, const TranslationFinishedEvent& event, bool overwriteExisting = true);
		bool RemoveTranslationEvent(const std::string &index);
	protected:
	private:
		//Rotation Variables

		//Position Variable
		bool Translating;
		sf::Vector2f TargetPosition;
		sf::Vector2f PositionDelta;
		sf::Vector2f DefaultPosition;

		sf::Uint32 PositionTime;
		sf::Uint32 LastPositionUpdate;
		//ScaleVariables
		bool Scaling;
		sf::Vector2f TargetScale;
		sf::Vector2f ScaleDelta;
		sf::Vector2f DefaultScale;

		sf::Uint32 ScaleTime;
		sf::Uint32 LastScaleUpdate;
		//Alpha Variables

		/*std::map<std::string, TranslationFinishedEvent> translationEvents;
		std::map<std::string, ScalingFinishedEvent> scalingEvents;
		std::map<std::string, AlphaPhaseFinishedEvent> alphaEvents;
		std::map<std::string, RotationFinishedEvent> rotationEvents;
		std::vector<std::map<std::string, TranslationFinishedEvent>::iterator> TranslationEventDeletionVector;
		std::vector<std::map<std::string, ScalingFinishedEvent>::iterator> ScaleEventDeletionVector;
		std::vector<std::map<std::string, AlphaPhaseFinishedEvent>::iterator> AlphaPhaseEventDeletionVector;
		std::vector<std::map<std::string, RotationFinishedEvent>::iterator> RotationEventDeletionVector;*/


		/*sf::Uint32 LastUpdate;
		boost::shared_ptr<TranslationFinishedEvent> TransEvents;
		boost::unordered_map<std::string, boost::signals2::connection> ActiveTranslationEvents;
		std::vector<boost::unordered_map<std::string, boost::signals2::connection>::iterator> TranslationEventDeletion;

		boost::shared_ptr<ScalingFinishedEvent> ScalingEvents;
		boost::unordered_map<std::string, boost::signals2::connection> ActiveScalingEvents;
		std::vector<boost::unordered_map<std::string, boost::signals2::connection>::iterator> ScalingEventDeletion;

		boost::shared_ptr<AlphaPhaseFinishedEvent> AlphaPhaseEvents;
		boost::unordered_map<std::string, boost::signals2::connection> ActiveAlphaPhaseEvents;
		std::vector<boost::unordered_map<std::string, boost::signals2::connection>::iterator> AlphaPhaseEventDeletion;

		boost::shared_ptr<RotationFinishedEvent> RotationEvents;
		boost::unordered_map<std::string, boost::signals2::connection> ActiveRotationEvents;
		std::vector<boost::unordered_map<std::string, boost::signals2::connection>::iterator> RotationEventDeletion;*/
	};
}

#endif