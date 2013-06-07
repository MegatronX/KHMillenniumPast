#include "ScreenStack.h"

namespace Graphics
{
	namespace Screens
	{
		ScreenStack::ScreenStack()
			: ScreenName("Invalid"), UID(-1), Valid(false), DrawStack(false), SendInputs(false), DeleteStack(true)
		{

		}
		ScreenStack::ScreenStack(const std::string& screenName, const int uid) 
			: ScreenName(screenName), UID(uid), Valid(true), DrawStack(true), SendInputs(true), DeleteStack(false)
		{
		}

		ScreenStack::ScreenStack(const std::string& screenName, const int uid, bool sendInputs, bool drawStack, bool valid, bool deleteStack) 
			: ScreenName(screenName), UID(uid), Valid(valid), DrawStack(drawStack), SendInputs(sendInputs), DeleteStack(deleteStack)
		{
		}

		ScreenStack::ScreenStack(const std::string& screenName, const int uid, const std::vector<screen_ptr>& screenOwned, bool sendInputs, bool drawStack, bool valid, bool deleteStack) 
			: ScreenName(screenName), UID(uid), Valid(valid), DrawStack(drawStack), SendInputs(sendInputs), DeleteStack(deleteStack)//, OwnedScreens(screenOwned)
		{
			for (auto screen = screenOwned.begin(); screen != screenOwned.end(); ++screen)
			{
				OwnedScreens[(*screen)->GetDrawPriority()].push_back(*screen);
			}
		}

		const std::string& ScreenStack::GetScreenName()
		{
			return ScreenName;
		}
		int ScreenStack::GetUID() const
		{
			return UID;
		}

		bool ScreenStack::GetValid() const
		{
			return Valid;
		}
		bool ScreenStack::SetValid(const bool valid)
		{
			Valid = valid;
			return valid;
		}

		bool ScreenStack::GetDraw() const 
		{
			return DrawStack;
		}
		void ScreenStack::SetDraw(const bool draw)
		{
			DrawStack = draw;
		}

		bool ScreenStack::GetSendingInputs() const
		{
			return SendInputs;
		}
		void ScreenStack::SetSendingInputs(const bool Send_Inputs)
		{
			SendInputs = Send_Inputs;
		}

		bool ScreenStack::GetDeletable() const
		{
			return DeleteStack;
		}
		void ScreenStack::SetDeletable(const bool deletable) 
		{
			DeleteStack = deletable;
		}
		void ScreenStack::AddScreen(screen_ptr screen, int drawPriority)
		{
			if (screen.get() != nullptr)
			{
				OwnedScreens[drawPriority].push_back(screen);
			}
			
		}
		bool ScreenStack::RemoveScreen(const std::string& screenName)
		{
			for(auto priority = OwnedScreens.begin(); priority != OwnedScreens.end(); ++priority)
			{
				for (auto screen = priority->second.begin(); screen != priority->second.end(); ++screen)
				{
					if ((*screen)->GetScreenName() == screenName)
					{
						priority->second.erase(screen);
						return true;
					}
				}
				
			}
			return false;
		}
		const std::map<int, std::vector<screen_ptr> >& ScreenStack::GetOwnedScreens() const
		{
			return OwnedScreens;
		}
		bool ScreenStack::HandleKeyPressed(const sf::Uint32 time, const Input::InputModule* inputModule, ::Input::InputActionResult& action)
		{
			bool inputConsumed = false;
			for(auto priority = OwnedScreens.begin(); priority != OwnedScreens.end(); ++priority)
			{
				for (auto screen = priority->second.rbegin(); screen != priority->second.rend(); ++screen)
				{
					if ((*screen)->IsAcceptingInputs())
					{
						inputConsumed |= (*screen)->HandleKeyPressed(time, inputModule, action);
					}
				}
			}
			return inputConsumed;
		}
		bool ScreenStack::HandleKeyReleased(const sf::Uint32 time, const Input::InputModule* inputModule, ::Input::InputActionResult& action)
		{
			bool inputConsumed = false;
			for(auto priority = OwnedScreens.begin(); priority != OwnedScreens.end(); ++priority)
			{
				for (auto screen = priority->second.rbegin(); screen != priority->second.rend(); ++screen)
				{
					if ((*screen)->IsAcceptingInputs())
					{
						inputConsumed |= (*screen)->HandleKeyReleased(time, inputModule, action);
					}
				}
			}
			return inputConsumed;
		}
		//Input Interface
		/*bool ScreenStack::HandleKeyPressed(const sf::Uint32 time, const Input::InputModule* inputModule, Input::PlayerInput pInput, Input::InputAction& action)
		{
			bool inputConsumed = false;
			for (auto it = OwnedScreens.begin(); it != OwnedScreens.end(); ++it)
			{
				if ((*it)->IsAcceptingInputs())
					inputConsumed |= (*it)->HandleKeyPressed(time, inputModule, pInput, action);
			}
			return inputConsumed;
		}
		bool ScreenStack::HandleKeyReleased(const sf::Uint32 time, const Input::InputModule* inputModule, Input::PlayerInput pInput, Input::InputAction& action)
		{
			bool inputConsumed = false;
			for (auto it = OwnedScreens.begin(); it != OwnedScreens.end(); ++it)
			{
				if ((*it)->IsAcceptingInputs())
					inputConsumed |= (*it)->HandleKeyReleased(time, inputModule, pInput, action);
			}
			return inputConsumed;
		}*/
		//Animate Draw
		void ScreenStack::Update(const sf::Uint32 time, const float TimeScale)
		{
			for(auto priority = OwnedScreens.begin(); priority != OwnedScreens.end(); ++priority)
			{
				for (auto screen = priority->second.rbegin(); screen != priority->second.rend(); ++screen)
				{
					(*screen)->Update(time, TimeScale);
				}
			}
		}
		void ScreenStack::Update(const float time, const float TimeScale)
		{
			for(auto priority = OwnedScreens.begin(); priority != OwnedScreens.end(); ++priority)
			{
				for (auto screen = priority->second.rbegin(); screen != priority->second.rend(); ++screen)
				{
					(*screen)->Update(time, TimeScale);
				}
			}
		}

		void ScreenStack::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			for(auto priority = OwnedScreens.begin(); priority != OwnedScreens.end(); ++priority)
			{
				for (auto screen = priority->second.rbegin(); screen != priority->second.rend(); ++screen)
				{
					target.draw(*(*screen), states);
					//(*screen)->Draw(window);
				}
			}

		}

		
		void ScreenStack::Draw(sf::RenderTarget &window)
		{
			for(auto priority = OwnedScreens.begin(); priority != OwnedScreens.end(); ++priority)
			{
				for (auto screen = priority->second.rbegin(); screen != priority->second.rend(); ++screen)
				{
					(*screen)->Draw(window);
				}
			}
		}
		void ScreenStack::Draw(sf::RenderTarget &window, sf::RenderStates states)
		{
			for(auto priority = OwnedScreens.begin(); priority != OwnedScreens.end(); ++priority)
			{
				for (auto screen = priority->second.rbegin(); screen != priority->second.rend(); ++screen)
				{
					(*screen)->Draw(window, states);
				}
			}
		}
		bool ScreenStack::operator==(const ScreenStack& stackComp) const
		{
			return this->UID == stackComp.UID;
		}
		bool ScreenStack::operator!=(const ScreenStack& stackComp) const
		{
			return !((*this) == stackComp);
		}
		void ScreenStack::SetScreenName(const std::string& screenName)
		{
			ScreenName = screenName;
		}
	}
}