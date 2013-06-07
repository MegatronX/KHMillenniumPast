#pragma once
#ifndef _MESSAGE_H_
#define _MESSAGE_H_
#include <sfml/Graphics.hpp>
namespace Game
{
	namespace Graphics
	{
		namespace Messaging
		{
			class Message
			{
			public:
				Message(const std::string& messageText = "");
			private:
				bool Display;
			};
		}
	}
}
#endif