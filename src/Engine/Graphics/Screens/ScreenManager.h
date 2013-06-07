#pragma once
#ifndef _SCREENMANAGER_H_
#define _SCREENMANAGER_H_

#include <Graphics/Screens/Screen.h>
#include <Graphics/Screens/ScreenStack.h>
#include <boost/unordered_map.hpp>
#include <system/Input/InputModule.h>
#include <map>
class Engine;

namespace Graphics
{
	namespace Screens
	{
		class ScreenManager : public ::Input::InputInterface, public AnimatedDraw
		{
		public:
			ScreenManager();
			void AddScreen(screen_ptr screen, const int index = 0);
			void AddScreenToStack(screen_ptr screen, const std::string& stackName);
			void AddScreenStack(const std::string& name, const ScreenStack& stack, const int DrawIndex = 0, bool registerIndividualScreens = true);
			ScreenStack* GetScreenStack(const std::string& name);
			bool DoesScreenExist(const std::string& name);
			bool DoesStackExist(const std::string& name);
			bool RemoveStack(const std::string& name);

			bool RegisterStackCreationFunction(const std::string& name);
			ScreenStack CreateStack(const std::string stackname, const std::string creationFunction, bool registerStack = true, bool registerIndividualScreens = true);


			//Input Interface
			virtual bool HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& action) override;
			virtual bool HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& action) override;

			//Animate Draw
			virtual void Update(const sf::Uint32 time, const float TimeScale = 1.0) override;
			virtual void Update(const float time, const float TimeScale = 1.0) override;

			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
			virtual void Draw(sf::RenderTarget &window) override;
			virtual void Draw(sf::RenderTarget &window, sf::RenderStates states) override;

			void ClearStacks();
		protected:
			void SyncUpScreens();
			
		private:
			Engine* engine;
			boost::unordered_map<std::string, Screen*> AllScreensByName;
			boost::unordered_map<int, Screen*> AllScreensByID;

			boost::unordered_map<std::string, ScreenStack> StackByName;
			boost::unordered_map<int, ScreenStack*> StackByID;
			std::map<int, std::vector<ScreenStack*> > StacksInDrawOrder;
			boost::unordered_map<std::string, ScreenStack> AddedStacks;
			std::vector<std::string> RemovedStacks;
			//std::map<int, std::vector<ScreenStack> > AddedStacks;
			//std::map<int, std::vector<ScreenStack> > RemovedStacks;
			bool Iterating;
			bool ScreensAdded;
			//std::vector<ScreenStack*> StacksInDrawOrder;
		};
	}
}

#endif