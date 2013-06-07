#pragma once
#ifndef _MESSAGE_H_
#define _MESSAGE_H_
#include <sfml/Graphics.hpp>
#include <Graphics/Screens/BasicRMLScreen.h>
#include <boost/unordered_set.hpp>
namespace Game
{
	namespace Graphics
	{
		namespace Messaging
		{
			struct MessageFormatting
			{
				MessageFormatting() : TextColor(sf::Color::White), ScreenOffset(0.f, 0.f), ZIndex(0), BoldText(false), ItalicText(false), UnderlineText(false), FontSet(false), FontSize(22), ShadowText(false), TimesOut(false), WaitForButton(false),
					CharacterSpeaking(false), HasBackground(false), ClassSet(false)
				{

				}
				sf::Vector2f ScreenOffset;
				sf::Vector2f TextOffset;
				int ZIndex;

				//Text Format
				bool BoldText;
				bool ItalicText;
				bool UnderlineText;
				sf::Color TextColor;
				bool FontSet;
				std::string FontFamily;
				int FontSize;

				//Text Shadow Fields
				bool ShadowText;
				sf::Color ShadowColor;
				sf::Vector2i ShadowOffset;

				//Character Data
				bool CharacterSpeaking;
				std::string Speaker;
				std::string Emotion;

				//Border
				bool HasBackground;
				std::string BackgroundName;

				//Timing Fields
				bool TimesOut;
				sf::Uint32 TimeOutPeriod;

				//Button Fields
				bool WaitForButton;
				boost::unordered_set<::Input::InputAction> ActionSet;

				bool ClassSet;
				std::string TextClass;
			};
			class Message
			{
			public:
				bool Expired;
				Rocket::Core::Element* MessageElement;

				sf::Uint32 LastUpdate;
				sf::Uint32 ExpiryTime;
				bool TimesOut;

				bool WaitForButton;
				boost::unordered_set<::Input::InputAction> ActionSet;

				int ID;
				std::string Index;
				bool ReleaseMessage()
				{
					bool freed = false;
					if (MessageElement != nullptr && MessageElement->GetParentNode() != nullptr)
					{
						MessageElement->GetParentNode()->RemoveChild(MessageElement);
						freed = true;
					}
					return freed;
				}
			};
			class MessageCenter : public GameRocket::BasicRMLScreen
			{
			public:
				MessageCenter(const std::string& rmlDoc, Engine* engine);

				//Basic Screen Functions
				virtual bool HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionRes) override;
				virtual bool HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionRes) override;

				void AddMessage(const std::string& message);
				void AddMessage(const std::string& message, const std::string& messageIndex);
				void AddMessage(const std::string& message, const MessageFormatting& formatting);
				void AddMessage(const std::string& message, const std::string& messageIndex, const MessageFormatting& formatting);
				void AddCompoundMessage(const std::vector<std::string>& messageParts, const std::string messageIndex, const std::vector<MessageFormatting>& formatParts);
				bool RemoveMessage(const std::string& messageindex);
				const std::string& GetElementText(const std::string& messageIndex);
				void SetMessageText(const std::string& messageIndex, const std::string& message);

				bool MessagesReady() const;

				boost::unordered_set<Message*> GetNextMessageSet(bool pop = true);
			protected:

				Rocket::Core::Element* MakeMessageElement(const std::string& message, const MessageFormatting& formatting);
			private:
				int MessageID;
				boost::unordered_map<std::string, Message> AllMessages;
				boost::unordered_set<Message*> ActiveMessages;
				std::deque<boost::unordered_set<Message*>> ActiveMessageQueue;

				Rocket::Core::Element* MessagePane;
				MessageFormatting DefaultFormat;
			};
		}
	}
}
#endif