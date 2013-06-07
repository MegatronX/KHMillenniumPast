#include "MessageQueueVisualizer.h"
using namespace ::Input;
namespace Game
{
	namespace Graphics
	{
		std::string MessageQueueVisualizer::EmoteSubDir = std::string();

		MessageQueueVisualizer::MessageQueueVisualizer(MessageQueue* que, Engine* engine, GameRocket::BasicRMLScreen* OverlayScreen) : Visualizer<MessageQueue>(que), OverlayScreen(OverlayScreen),
			TopPos(0, 0), TopSize(800, 150), BottomPos(0, 400), BottomSize(800, 200), DefaultTopPos(0, 0), DefaultTopSize(800, 150), DefaultBottomPos(0, 400), DefaultBottomSize(800, 200),
			ProcessingMessage(false), WaitingOnInput(false)
		{
			if (OverlayScreen != nullptr)
			{
				TargetBottomElement = OverlayScreen->GetDocument()->GetElementById("BottomMessageDiv");
				TargetBottomElement->SetInnerRML("<div id=\"EmotionDiv\" class=\"EmotionDiv\" /><div id=\"MessageDiv\" class=\"BottomMessage\" />");
				TargetTopElement = OverlayScreen->GetDocument()->GetElementById("TopMessageDiv");
			}

		}
		void MessageQueueVisualizer::SetupEmoteDubDir(Engine* engine)
		{
			auto AppConfig = engine->GetApplicationConfiguration();
			EmoteSubDir = AppConfig.GetApplicationSetting("ResourcesBaseDirectory") + AppConfig.GetApplicationSetting("GraphicsSubDir")
				+ AppConfig.GetApplicationSetting("ExpressionsSubDir");
		}
		void MessageQueueVisualizer::Update(sf::Uint32 time, const float TimeScale)
		{
			if (!ProcessingMessage && Visualizing->MessageReady())
			{
				bool Valid = false;
				MessageInProcessing = Visualizing->GetNextMessage(Valid);
				if (Valid)
				{
					ProcessingMessage = true;
					SetMessage();
				}
			}
		}
		void MessageQueueVisualizer::SetMessage()
		{
			if (ProcessingMessage)
			{
				bool EmotionPresent = (MessageInProcessing.Emotion != MessageEmotion::None);
				if (EmotionPresent)
				{
					auto emote = TargetBottomElement->GetElementById("EmotionDiv");
					std::string emotePath(EmoteSubDir + MessageInProcessing.SpeakerDisplayName + "_" + EmotionNameMap[MessageInProcessing.Emotion] + ".png");
					std::string rml("<img src=\"" + emotePath + "\" class=\"EmotionImage\"/>");
					emote->SetInnerRML(rml.c_str());
				}

				auto Message = TargetBottomElement->GetElementById("MessageDiv");
				if (MessageInProcessing.SpeakerDisplayName.size() > 0)
				{
					std::string rml(MessageInProcessing.SpeakerDisplayName + ": " + MessageInProcessing.Message);
					Message->SetInnerRML(rml.c_str());
				}
				else
				{
				}
			}
		}
		void MessageQueueVisualizer::SetUpMessage()
		{

			SetMessage();
		}
		bool MessageQueueVisualizer::HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult)
		{
			
			bool BlockInput = false;
			if (ProcessingMessage && !actionResult.Cancelled)
			{
				BlockInput = MessageInProcessing.BlockInputs;
				actionResult.Cancelled = true;
				if (!MessageInProcessing.TimesOut)
				{
					if (actionResult.PInput == ::Input::PlayerInput::P1Input && actionResult.IAction == InputAction::Confirm)
					{
						if (Visualizing->MessageReady())
						{
							bool IsValid = false;
							MessageInProcessing = Visualizing->GetNextMessage(IsValid);
							if (IsValid)
							{
								SetUpMessage();
							}
						}
						
					}
				}
				
			}
			return BlockInput;
		}
		bool MessageQueueVisualizer::HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult)
		{
			return true;
		}
	}
}