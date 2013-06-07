#include "ScreenManager.h"
#include <Engine.h>
namespace Graphics
{
	namespace Screens
	{
		ScreenManager::ScreenManager() : Iterating(false), ScreensAdded(false)
		{

		}
		void ScreenManager::AddScreen(screen_ptr screen, const int index)
		{
			if (screen.get() != nullptr)
			{
				ScreenStack newStack(screen->GetScreenName(), screen->engine->GetUID(), true, true);
				if (!Iterating)
				{
					newStack.AddScreen(screen, screen->GetDrawPriority());
					StackByName[newStack.GetScreenName()] = newStack;
					(&StackByName[newStack.GetScreenName()])->SetDrawPriority(index);
					StackByID[newStack.GetUID()] = &StackByName[newStack.GetScreenName()];
					StacksInDrawOrder[index].push_back(&StackByName[newStack.GetScreenName()]);
				}
				else
				{
					AddedStacks[newStack.GetScreenName()] = newStack;
					(&AddedStacks[newStack.GetScreenName()])->SetDrawPriority(index);
					(&AddedStacks[newStack.GetScreenName()])->AddScreen(screen, screen->GetDrawPriority());
				}
				//StacksInDrawOrder[index]
				//StacksInDrawOrder.push_back(&StackByName[newStack.GetScreenName()]);
			}
			
		}
		void ScreenManager::AddScreenToStack(screen_ptr screen, const std::string& stackName)
		{
			if (screen.get() != nullptr)
			{
				auto it = StackByName.find(stackName);
				if (it != StackByName.end())
				{
					it->second.AddScreen(screen, screen->GetDrawPriority());
				}
				else
				{
					ScreenStack newStack(screen->GetScreenName(), screen->engine->GetUID(), true, true);
					newStack.AddScreen(screen, screen->GetDrawPriority());
					StackByName[newStack.GetScreenName()] = newStack;
					StackByID[newStack.GetUID()] = &StackByName[newStack.GetScreenName()];
				}
			}

		}
		void ScreenManager::AddScreenStack(const std::string& name, const ScreenStack& stack, const int DrawIndex, bool registerIndividualScreens)
		{
			//ScreenStack st(stack);
			if (!Iterating)
			{
				StackByName[name] = stack;
				StackByID[stack.GetUID()] = &StackByName[name];
				(&StackByName[name])->SetDrawPriority(DrawIndex);
				StacksInDrawOrder[DrawIndex].push_back(&StackByName[name]);
				
			}
			else
			{
				AddedStacks[name] = stack;
				(&AddedStacks[name])->SetDrawPriority(DrawIndex);
			}
		}
		ScreenStack* ScreenManager::GetScreenStack(const std::string& name)
		{
			auto it = StackByName.find(name);
			if (it != StackByName.end())
			{
				return &(it->second);
			}
			return nullptr;
			//return *(*StacksInDrawOrder.begin());
		}
		bool ScreenManager::DoesScreenExist(const std::string& name)
		{
			return AllScreensByName.find(name) != AllScreensByName.end();
		}
		bool ScreenManager::DoesStackExist(const std::string& name)
		{
			return StackByName.find(name) != StackByName.end() && AddedStacks.find(name) != AddedStacks.end();
		}
		bool ScreenManager::RemoveStack(const std::string& name)
		{
			bool Removed = false;
			auto it = StackByName.find(name);
			if (it != StackByName.end())
			{
				if (!Iterating)
				{
					auto id = StackByID.find(it->second.GetUID());
					if (id != StackByID.end())
					{
						StackByID.erase(id);
					}
					int priority = it->second.GetDrawPriority();
					if (StacksInDrawOrder[priority].size() > 0)
					{
						for (auto st = StacksInDrawOrder[priority].begin(); st != StacksInDrawOrder[priority].end(); ++st)
						{
							if (*(*st) == it->second)
							{
								StacksInDrawOrder[priority].erase(st);
								break;
							}
						}
					}
					StackByName.erase(it);
				}
				else
				{
					RemovedStacks.push_back(name);
				}
				Removed = true;
			}
			return Removed;
		}

		bool ScreenManager::RegisterStackCreationFunction(const std::string& name)
		{
			return false;
		}
		ScreenStack ScreenManager::CreateStack(const std::string stackname, const std::string creationFunction, bool registerStack, bool registerIndividualSscreens)
		{
			//need to do a switch here
			return ScreenStack();
		}

		bool ScreenManager::HandleKeyPressed(const sf::Uint32 time, const Input::InputModule* inputModule, ::Input::InputActionResult& action)
		{
			
			bool handled = false;
			Iterating = true;
			//std::cout << "Start iteration \n";
			for (auto index = StacksInDrawOrder.rbegin(); index != StacksInDrawOrder.rend() && !handled; ++index)
			{
				for (auto stack = index->second.begin(); stack != index->second.end(); ++stack)
				{
					//std::cout << "Iterating through stack " << (*stack)->GetScreenName() << "\n";
					handled |= (*stack)->HandleKeyPressed(time, inputModule, action);
				}
			}
			//std::cout << "Done iteration \n\n";
			Iterating = false;
			SyncUpScreens();
			return handled;
		}
		bool ScreenManager::HandleKeyReleased(const sf::Uint32 time, const Input::InputModule* inputModule, ::Input::InputActionResult& action)
		{
			bool handled = false;
			Iterating = true;
			for (auto index = StacksInDrawOrder.begin(); index != StacksInDrawOrder.end(); ++index)
			{
				for (auto stack = index->second.begin(); stack != index->second.end(); ++stack)
				{
					handled |= (*stack)->HandleKeyReleased(time, inputModule, action);
				}
			}
			Iterating = false;
			return handled;
		}

		//Animate Draw
		void ScreenManager::Update(const sf::Uint32 time, const float TimeScale)
		{
			Iterating = true;
			for (auto index = StacksInDrawOrder.rbegin(); index != StacksInDrawOrder.rend(); ++index)
			{
				for (auto stack = index->second.begin(); stack != index->second.end();)
				{
					if ((*stack)->GetDeletable())
					{
						stack = index->second.erase(stack);
					}
					else
					{
						(*stack)->Update(time, TimeScale);
						++stack;
					}
				}
			}
			Iterating = false;
			SyncUpScreens();
		}
		void ScreenManager::Update(const float time, const float TimeScale)
		{
			Iterating = true;
			for (auto index = StacksInDrawOrder.rbegin(); index != StacksInDrawOrder.rend(); ++index)
			{
				for (auto stack = index->second.begin(); stack != index->second.end();)
				{
					if ((*stack)->GetDeletable())
					{
						stack = index->second.erase(stack);
					}
					else
					{
						(*stack)->Update(time, TimeScale);
						++stack;
					}
				}
			}
			Iterating = false;
			SyncUpScreens();
		}

		void ScreenManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			//Iterating = true;
			for (auto index = StacksInDrawOrder.begin(); index != StacksInDrawOrder.end(); ++index)
			{
				for (auto stack = index->second.begin(); stack != index->second.end(); ++stack)
				{
					target.draw(*(*stack), states);
					//(*stack)->Draw(window);
				}
			}
			//Iterating = false;
		}
		void ScreenManager::Draw(sf::RenderTarget &window)
		{
			Iterating = true;
			for (auto index = StacksInDrawOrder.begin(); index != StacksInDrawOrder.end(); ++index)
			{
				for (auto stack = index->second.begin(); stack != index->second.end(); ++stack)
				{
					(*stack)->Draw(window);
				}
			}
			Iterating = false;
		}
		void ScreenManager::Draw(sf::RenderTarget &window, sf::RenderStates states)
		{
			Iterating = true;
			for (auto index = StacksInDrawOrder.begin(); index != StacksInDrawOrder.end(); ++index)
			{
				for (auto stack = index->second.begin(); stack != index->second.end(); ++stack)
				{
					(*stack)->Draw(window, states);
				}
			}
			Iterating = false;
		}
		void ScreenManager::SyncUpScreens()
		{
			if (AddedStacks.size() > 0)
			{
				auto orig = AddedStacks;
				AddedStacks.clear();
				for (auto stack = orig.begin(); stack != orig.end(); ++stack)
				{
					AddScreenStack(stack->first, stack->second, stack->second.GetDrawPriority(), true);
				}
			}
			if (RemovedStacks.size() > 0)
			{
				auto orig = RemovedStacks;
				RemovedStacks.clear();
				for (auto stack = orig.begin(); stack != orig.end(); ++stack)
				{
					RemoveStack(*stack);
				}
			}
		}

		void ScreenManager::ClearStacks()
		{
			for (auto stack = StackByName.begin(); stack != StackByName.end(); ++stack)
			{
				RemoveStack(stack->first);
			}
		}
	}
}