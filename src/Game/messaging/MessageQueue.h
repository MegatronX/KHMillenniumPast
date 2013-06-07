#pragma once
#ifndef _MESSAGEQUEUE_H_
#define _MESSAGEQUEUE_H_
#include <deque>
#include <string>
#include <boost/unordered_map.hpp>
#include <graphics/Visualizer.h>
#include <sfml/System.hpp>
namespace Game
{
	namespace Graphics
	{
		enum MessageEmotion
		{
			Angry,
			Annoyed,
			Content,
			Curious,
			Happy,
			Hurt, 
			Laugh,
			Sad,
			Scared,
			Unsure,
			None
		};
		extern boost::unordered_map<MessageEmotion, std::string> EmotionNameMap;
		extern boost::unordered_map<std::string, MessageEmotion> NameEmotionMap;
		struct DisplayMessage
		{
			DisplayMessage() : BlockInputs(false), TimesOut(false), TimeOut(0)
			{

			}
			DisplayMessage(const std::string& message, const std::string& speaker, const std::string& speakerDisp, const MessageEmotion emotion, bool BlkInput = false, bool TOuts = false, sf::Uint32 TOut = 0) : Message(message), Speaker(speaker), SpeakerDisplayName(speakerDisp), Emotion(emotion), BlockInputs(BlkInput), TimesOut(TOuts), TimeOut(TOut)
			{
			}
			std::string Message;
			std::string Speaker;
			std::string SpeakerDisplayName;
			MessageEmotion Emotion;
			bool BlockInputs;
			bool TimesOut;
			sf::Uint32 TimeOut;

			std::string GetMessage(bool IncludeNewLine = false)
			{
				return (IncludeNewLine ? SpeakerDisplayName + ": " + Message + "\n" : SpeakerDisplayName + ": " + Message);
			}
		};

		class MessageQueue
		{
		public:
			void AddMessage(const DisplayMessage& message);
			void AddMessage(const std::string& message, const std::string& speaker, const MessageEmotion emotion = MessageEmotion::None, bool blockInput = false, bool timeOut = false, sf::Uint32 timeOutTime = 0);
			void AddMessage(const std::string& message, const std::string& speaker, const std::string& speakerDisplayName, const MessageEmotion emotion = MessageEmotion::None, bool blockInput = false, bool timeOut = false, sf::Uint32 timeOutTime = 0);
			bool MessageReady() const;
			DisplayMessage GetNextMessage(bool& Valid, bool Pop = true);
		protected:
		private:
			std::deque<DisplayMessage> QueuedMessages;
		};

		
	}
}

#endif