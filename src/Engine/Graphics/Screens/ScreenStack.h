#pragma once
#ifndef _SCREENSTACK_H_
#define _SCREENSTACK_H_
#include <graphics/Screens/Screen.h>
#include <System/Input/InputInterface.h>
#include <System/Input/InputModule.h>
#include <string>
#include <vector>
namespace Graphics
{
	namespace Screens
	{
		class ScreenManager;
		class ScreenStack : public ::Input::InputInterface, public AnimatedDraw
		{
		public:
			ScreenStack();
			ScreenStack(const std::string& screenName, const int uid);

			ScreenStack(const std::string& screenName, const int uid, bool sendInputs, bool drawStack, bool valid = true, bool deleteStack = false);

			ScreenStack(const std::string& screenName, const int uid, const std::vector<screen_ptr>& screenOwned, bool sendInputs, bool drawStack, bool valid = true, bool deleteStack = false);

			const std::string& GetScreenName();
			int GetUID() const;

			bool GetValid() const;
			bool SetValid(const bool valid = true);

			bool GetDraw() const;
			void SetDraw(const bool draw = true);

			bool GetSendingInputs() const;
			void SetSendingInputs(const bool Send_Inputs = true);

			bool GetDeletable() const;
			void SetDeletable(const bool deletable);
			
			void AddScreen(screen_ptr screen, int drawPriority);
			bool RemoveScreen(const std::string& screenName);

			const std::map<int, std::vector<screen_ptr> >& GetOwnedScreens() const;

			//Input Interface
			virtual bool HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& action) override;
			virtual bool HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& action) override;

			//Animate Draw
			virtual void Update(const sf::Uint32 time, const float TimeScale = 1.0) override;
			virtual void Update(const float time, const float TimeScale = 1.0) override;

			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
			virtual void Draw(sf::RenderTarget &window) override;
			virtual void Draw(sf::RenderTarget &window, sf::RenderStates states) override;
			bool operator==(const ScreenStack& stackComp) const;
			bool operator!=(const ScreenStack& stackComp) const;
		protected:
			void SetScreenName(const std::string& screenName);
		private:
			friend class ScreenManager;
			std::string ScreenName;
			int UID;

			bool Valid;
			bool DrawStack;
			bool UpdateStack;
			bool SendInputs;
			bool DeleteStack;

			std::map<int, std::vector<screen_ptr> > OwnedScreens;
		};
	}
}

#endif