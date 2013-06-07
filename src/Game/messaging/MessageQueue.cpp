#include "MessageQueue.h"
#include <boost/assign.hpp>
namespace Game
{
	namespace Graphics
	{
		boost::unordered_map<std::string, MessageEmotion> NameEmotionMap = boost::assign::map_list_of
			("Angry", MessageEmotion::Angry)
			("Annoyed", MessageEmotion::Annoyed)
			("Content", MessageEmotion::Content)
			("Curious", MessageEmotion::Curious)
			("Happy", MessageEmotion::Happy)
			("Hurt", MessageEmotion::Hurt)
			("Laugh", MessageEmotion::Laugh)
			("Sad", MessageEmotion::Sad)
			("Scared", MessageEmotion::Scared)
			("Unsure", MessageEmotion::Unsure)
			("None", MessageEmotion::None)
			;
		boost::unordered_map<MessageEmotion, std::string> EmotionNameMap = boost::assign::map_list_of
			(MessageEmotion::Angry, "Angry")
			(MessageEmotion::Annoyed, "Annoyed")
			(MessageEmotion::Content, "Content")
			(MessageEmotion::Curious, "Curious")
			(MessageEmotion::Happy, "Happy")
			(MessageEmotion::Hurt, "Hurt")
			(MessageEmotion::Laugh, "Laugh")
			(MessageEmotion::Sad, "Sad")
			(MessageEmotion::Scared, "Scared")
			(MessageEmotion::Unsure, "Unsure")
			(MessageEmotion::None, "None")
			;
		void MessageQueue::AddMessage(const DisplayMessage& message)
		{
			QueuedMessages.push_back(message);
		}
		void MessageQueue::AddMessage(const std::string& message, const std::string& speaker, const MessageEmotion emotion, bool blockInput, bool timeOut, sf::Uint32 timeOutTime)
		{
			AddMessage(message, speaker, speaker, emotion, blockInput, timeOut, timeOutTime);
		}
		void MessageQueue::AddMessage(const std::string& message, const std::string& speaker, const std::string& speakerDisplayName, const MessageEmotion emotion, bool blockInput, bool timeOut, sf::Uint32 timeOutTime)
		{
			QueuedMessages.push_back(DisplayMessage(message, speaker, speakerDisplayName, emotion, blockInput, timeOut, timeOutTime));
		}
		bool MessageQueue::MessageReady() const
		{
			return QueuedMessages.size() > 0;
		}
		DisplayMessage MessageQueue::GetNextMessage(bool& Valid, bool Pop) 
		{
			if (QueuedMessages.size() > 0)
			{
				Valid = true;
				DisplayMessage RMes(QueuedMessages.front());
				if (Pop)
				{
					QueuedMessages.pop_front();
				}
				return RMes;
			}
			else
			{
				Valid = false;
				return DisplayMessage();
			}
		}
	}
}