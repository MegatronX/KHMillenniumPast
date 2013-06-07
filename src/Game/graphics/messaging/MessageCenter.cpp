#include "MessageCenter.h"
#include <Engine.h>
#include <Graphics/Rocket/RocketUtilities.h>
#include <boost/lexical_cast.hpp>
using namespace Rocket::Core;
namespace Game
{
	namespace Graphics
	{
		namespace Messaging
		{
			MessageCenter::MessageCenter(const std::string& rmlDoc, Engine* engine) : BasicRMLScreen("Message Center", rmlDoc, engine, engine->GetUID())
			{
				MessagePane = GetDocument()->GetElementById("MessagePanel");
			}
			
			bool MessageCenter::HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionRes)
			{
				for (auto actMsg = ActiveMessages.begin(); actMsg != ActiveMessages.end(); ++actMsg)
				{
					if ((*actMsg)->WaitForButton)
					{
						if ((*actMsg)->ActionSet.size() > 0)
						{
							if ((*actMsg)->ActionSet.find(actionRes.IAction) != (*actMsg)->ActionSet.end())
							{
							}
						}
						else if (actionRes.IAction == ::Input::InputAction::Confirm)
						{
						}
					}
				}
				return false;
			}
			bool MessageCenter::HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionRes)
			{
				return false;
			}
			void MessageCenter::AddMessage(const std::string& message)
			{
				auto msgDiv = Factory::InstanceElement(MessagePane, "div", "div", Rocket::Core::XMLAttributes());
				//msgDiv->SetInnerRML("<div>" + message.c_str() + "</div>");
				auto textDiv = Factory::InstanceElement(msgDiv, "div", "div", Rocket::Core::XMLAttributes());
				textDiv->SetInnerRML(message.c_str());
				msgDiv->AppendChild(textDiv);
				MessagePane->AppendChild(msgDiv);
			}
			void MessageCenter::AddMessage(const std::string& message, const std::string& messageIndex)
			{
				auto msgDiv = Factory::InstanceElement(MessagePane, "div", "div", Rocket::Core::XMLAttributes());
				//msgDiv->SetInnerRML("<div>" + message.c_str() + "</div>");
				auto textDiv = Factory::InstanceElement(msgDiv, "div", "div", Rocket::Core::XMLAttributes());
				textDiv->SetInnerRML(message.c_str());
				msgDiv->AppendChild(textDiv);
				MessagePane->AppendChild(msgDiv);
			}
			void MessageCenter::AddMessage(const std::string& message, const MessageFormatting& formatting)
			{
				auto msgDiv = Factory::InstanceElement(MessagePane, "div", "div", Rocket::Core::XMLAttributes());
				//msgDiv->SetInnerRML("<div>" + message.c_str() + "</div>");
				auto textDiv = Factory::InstanceElement(msgDiv, "div", "div", Rocket::Core::XMLAttributes());
				textDiv->SetInnerRML(message.c_str());
				msgDiv->AppendChild(textDiv);
				MessagePane->AppendChild(msgDiv);
			}
			void MessageCenter::AddMessage(const std::string& message, const std::string& messageIndex, const MessageFormatting& formatting)
			{
				auto msgDiv = MakeMessageElement(message, formatting);
				MessagePane->AppendChild(msgDiv);

				Message msg;
				msg.MessageElement = msgDiv;

				msg.TimesOut = formatting.TimesOut;
				msg.WaitForButton = formatting.WaitForButton;
				if (formatting.TimesOut)
				{

				}
				if (formatting.WaitForButton)
				{

				}
				//Add Message
				auto it = AllMessages.find(messageIndex);
				if (it != AllMessages.end())
				{
					it->second.MessageElement->GetParentNode()->RemoveChild(it->second.MessageElement);
					AllMessages.erase(it);
				}

				AllMessages[messageIndex] = msg;
			}

			void MessageCenter::AddCompoundMessage(const std::vector<std::string>& messageParts, const std::string messageIndex, const std::vector<MessageFormatting>& formatParts)
			{

			}

			Rocket::Core::Element* MessageCenter::MakeMessageElement(const std::string& message, const MessageFormatting& formatting)
			{
				auto msgDiv = Factory::InstanceElement(MessagePane, "div", "div", Rocket::Core::XMLAttributes());
				//msgDiv->SetInnerRML("<div>" + message.c_str() + "</div>");
				auto textDiv = Factory::InstanceElement(msgDiv, "div", "div", Rocket::Core::XMLAttributes());
				textDiv->SetInnerRML(message.c_str());

				//Format Message
				msgDiv->SetProperty("left", (boost::lexical_cast<std::string>(formatting.ScreenOffset.x) + "px").c_str());
				msgDiv->SetProperty("top", (boost::lexical_cast<std::string>(formatting.ScreenOffset.y) + "px").c_str());
				msgDiv->SetProperty("z-index", (boost::lexical_cast<std::string>(formatting.ZIndex).c_str()));
				msgDiv->SetProperty("position", "absolute");
				//msgDiv->SetProperty("display", "inline");
				//msgDiv->SetProperty("float", "left");
				//Set picture data
				//Character Image
				if (formatting.CharacterSpeaking)
				{
					std::string emote = formatting.Speaker + "_" + formatting.Emotion + ".png";
					std::string path = "C:\\Kingdom Hearts MP\\resources\\Graphics\\Expressions\\" + emote;
					auto imgDiv = Factory::InstanceElement(msgDiv, "div", "div", Rocket::Core::XMLAttributes());
					auto img = Factory::InstanceElement(imgDiv, "img", "img", Rocket::Core::XMLAttributes());

					img->SetAttribute("src", path.c_str());
					img->SetProperty("width", "180px");
					imgDiv->AppendChild(img);
					//imgDiv->SetProperty("float", "left");
					imgDiv->SetProperty("position", "relative");
					//imgDiv->SetProperty("display", "inline");
					msgDiv->AppendChild(imgDiv);
				}
				//Background

				//Format Text
				textDiv->SetProperty("color", ::Graphics::ColorToRGBARocketString(formatting.TextColor));
				textDiv->SetProperty("position", "relative");
				textDiv->SetProperty("font-size", (boost::lexical_cast<std::string>(formatting.FontSize)).c_str());
				textDiv->SetProperty("white-space", "pre");
				textDiv->SetProperty("top", "10px");
				//textDiv->SetProperty("float", "left");
				//textDiv->SetProperty("width", "350px");
				if (formatting.CharacterSpeaking)
				{
					//textDiv->SetProperty("left", "185px");
				}
				//textDiv->SetProperty("position", "relative");
				//textDiv->SetProperty("display", "inline");
				if (formatting.FontSet)
				{
					textDiv->SetProperty("font-family", formatting.FontFamily.c_str());
				}
				if (formatting.TextOffset.x != 0)
				{
					textDiv->SetProperty("left", (boost::lexical_cast<std::string>(formatting.TextOffset.x) + "px").c_str());
				}
				if (formatting.TextOffset.y != 0)
				{
					textDiv->SetProperty("top", (boost::lexical_cast<std::string>(formatting.TextOffset.y) + "px").c_str());
				}

				if (formatting.BoldText)
				{

				}
				if (formatting.ItalicText)
				{

				}
				if (formatting.UnderlineText)
				{

				}
				if (formatting.ShadowText)
				{
					textDiv->SetProperty("shadow-font-effect", "shadow");
					auto px = (boost::lexical_cast<std::string>(formatting.ShadowOffset.x) + "px " + boost::lexical_cast<std::string>(formatting.ShadowOffset.y) + "px");
					textDiv->SetProperty("shadow-offset", px.c_str());
					textDiv->SetProperty("shadow-color", ::Graphics::ColorToRGBARocketString(formatting.ShadowColor));
					auto off = textDiv->GetProperty("shadow-offset");
					auto co = textDiv->GetProperty("shadow-color");
					int c = 0;
					// shadow-font-effect: shadow;
					//shadow-offset: 1px 1px;
					//shadow-color: black;
				}
				if (formatting.ClassSet)
				{
					textDiv->SetClass(formatting.TextClass.c_str(), true);
				}
				msgDiv->AppendChild(textDiv);
				return msgDiv;
			}

			bool MessageCenter::RemoveMessage(const std::string& messageindex)
			{
				auto msg = AllMessages.find(messageindex);
				if (msg != AllMessages.end())
				{
					for (auto amsg = ActiveMessages.begin(); amsg != ActiveMessages.end(); ++msg)
					{
					}
					msg->second.ReleaseMessage();
					AllMessages.erase(msg);
					return true;
				}
				return false;
			}
		}

	}
}