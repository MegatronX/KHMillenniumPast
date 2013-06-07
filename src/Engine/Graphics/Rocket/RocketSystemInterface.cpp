#include "RocketSystemInterface.h"
#include <Rocket/Core.h>

namespace RKey = Rocket::Core::Input;

namespace Graphics
{
	namespace RocketInterface
	{
		Rocket::Core::Input::KeyIdentifier RocketSystemInterface::TranslateKey(sf::Keyboard::Key key)
		{
			switch (key)
			{
			case sf::Keyboard::Key::A:
				return RKey::KI_A;
				break;
			case sf::Keyboard::Key::B:
				return RKey::KI_B;
				break;
			case sf::Keyboard::Key::C:
				return RKey::KI_C;
				break;
			case sf::Keyboard::Key::D:
				return RKey::KI_D;
				break;
			case sf::Keyboard::Key::E:
				return RKey::KI_E;
				break;
			case sf::Keyboard::Key::F:
				return RKey::KI_F;
				break;
			case sf::Keyboard::Key::G:
				return RKey::KI_G;
				break;
			case sf::Keyboard::Key::H:
				return RKey::KI_H;
				break;
			case sf::Keyboard::Key::I:
				return RKey::KI_I;
				break;
			case sf::Keyboard::Key::J:
				return RKey::KI_J;
				break;
			case sf::Keyboard::Key::K:
				return RKey::KI_K;
				break;
			case sf::Keyboard::Key::L:
				return RKey::KI_L;
				break;
			case sf::Keyboard::Key::M:
				return RKey::KI_M;
				break;
			case sf::Keyboard::Key::N:
				return RKey::KI_N;
				break;
			case sf::Keyboard::Key::O:
				return RKey::KI_O;
				break;
			case sf::Keyboard::Key::P:
				return RKey::KI_P;
				break;
			case sf::Keyboard::Key::Q:
				return RKey::KI_Q;
				break;
			case sf::Keyboard::Key::R:
				return RKey::KI_R;
				break;
			case sf::Keyboard::Key::S:
				return RKey::KI_S;
				break;
			case sf::Keyboard::Key::T:
				return RKey::KI_T;
				break;
			case sf::Keyboard::Key::U:
				return RKey::KI_U;
				break;
			case sf::Keyboard::Key::V:
				return RKey::KI_V;
				break;
			case sf::Keyboard::Key::W:
				return RKey::KI_W;
				break;
			case sf::Keyboard::Key::X:
				return RKey::KI_X;
				break;
			case sf::Keyboard::Key::Y:
				return RKey::KI_Y;
				break;
			case sf::Keyboard::Key::Z:
				return RKey::KI_Z;
				break;
			case sf::Keyboard::Key::Num0:
				return RKey::KI_0;
				break;
			case sf::Keyboard::Key::Num1:
				return RKey::KI_1;
				break;
			case sf::Keyboard::Key::Num2:
				return RKey::KI_2;
				break;
			case sf::Keyboard::Key::Num3:
				return RKey::KI_3;
				break;
			case sf::Keyboard::Key::Num4:
				return RKey::KI_4;
				break;
			case sf::Keyboard::Key::Num5:
				return RKey::KI_5;
				break;
			case sf::Keyboard::Key::Num6:
				return RKey::KI_6;
				break;
			case sf::Keyboard::Key::Num7:
				return RKey::KI_7;
				break;
			case sf::Keyboard::Key::Num8:
				return RKey::KI_8;
				break;
			case sf::Keyboard::Key::Num9:
				return RKey::KI_9;
				break;
			
			}
			return RKey::KI_UNKNOWN;
		}
		int RocketSystemInterface::GetKeyModifiers(sf::Window* window)
		{

			int Modifiers = 0;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) ||
				(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift)))
				Modifiers |= Rocket::Core::Input::KM_SHIFT;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) ||
				(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl)))
				Modifiers |= Rocket::Core::Input::KM_CTRL;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LAlt) ||
				(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RAlt)))
				Modifiers |= Rocket::Core::Input::KM_ALT;
			return Modifiers;
			
		}
		float RocketSystemInterface::GetElapsedTime()
		{
			return timer.getElapsedTime().asSeconds();// * 0.001f;
		}
		bool RocketSystemInterface::LogMessage(Rocket::Core::Log::Type type, const Rocket::Core::String& message)
		{
			std::string Type;

			switch(type)
			{
			case Rocket::Core::Log::LT_ALWAYS:
				Type = "[Always]";
				break;
			case Rocket::Core::Log::LT_ERROR:
				Type = "[Error]";
				break;
			case Rocket::Core::Log::LT_ASSERT:
				Type = "[Assert]";
				break;
			case Rocket::Core::Log::LT_WARNING:
				Type = "[Warning]";
				break;
			case Rocket::Core::Log::LT_INFO:
				Type = "[Info]";
				break;
			case Rocket::Core::Log::LT_DEBUG:
				Type = "[Debug]";
				break;
			};

			printf("%s - %s\n", Type.c_str(), message.CString());

			return true;
		}
	}
}