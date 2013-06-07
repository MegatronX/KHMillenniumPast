#pragma once
#ifndef _MESSAGEQUEUEVISUALIZER_H_
#define _MESSAGEQUEUEVISUALIZER_H_

#include "MessageQueue.h"
#include <Engine.h>
#include <graphics/Screens/BasicRMLScreen.h>
#include <System/Input/InputInterface.h>
namespace Game
{
	namespace Graphics
	{
		class MessageQueueVisualizer : public ::Graphics::Visualizer<MessageQueue>, public ::Input::InputInterface
		{
		public:
			MessageQueueVisualizer(MessageQueue* que, Engine* engine, GameRocket::BasicRMLScreen* OverlayScreen);
			static void SetupEmoteDubDir(Engine* engine);
			virtual void Update(sf::Uint32 time, const float TimeScale = 1.0) override;

			virtual bool HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult) override;
			virtual bool HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult) override;
		protected:
			void SetMessage();
			void SetUpMessage();
		private:
			sf::Vector2f TopPos;
			sf::Vector2f TopSize;
			sf::Vector2f BottomPos;
			sf::Vector2f BottomSize;

			sf::Vector2f DefaultTopPos;
			sf::Vector2f DefaultTopSize;
			sf::Vector2f DefaultBottomPos;
			sf::Vector2f DefaultBottomSize;

			bool ProcessingMessage;
			bool WaitingOnInput;
			static std::string EmoteSubDir;
			DisplayMessage MessageInProcessing;
			GameRocket::BasicRMLScreen* OverlayScreen;
			Rocket::Core::Element* TargetBottomElement;
			Rocket::Core::Element* TargetTopElement;
		};
	}
}
#endif