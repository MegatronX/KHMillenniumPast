#include "Screen.h"
#include <Engine.h>
namespace Graphics
{
	namespace Screens
	{
		Screen::Screen(const std::string& name, Engine* engine, int id) : ScreenName(name), engine(engine), ScreenID(id)
		{

		}
		Screen::~Screen()
		{

		}
		int Screen::GetID() const
		{
			return ScreenID;
		}
		const std::string& Screen::GetScreenName() const
		{
			return ScreenName;
		}
		void Screen::SetScreenName(const std::string& name)
		{
			ScreenName = name;
		}

		bool Screen::AddOwner(const std::string& name, ScreenStack* stack)
		{
			OwningStacks[name] = stack;
			return true;
		}
		bool Screen::RemoveOwner(const std::string& name)
		{
			auto it = OwningStacks.find(name);
			if (it != OwningStacks.end())
			{
				OwningStacks.erase(it);
				return true;
			}
			return false;
		}
		bool Screen::HasOwner(const std::string& name)
		{
			return OwningStacks.find(name) != OwningStacks.end();
		}
		const boost::unordered_map<std::string, ScreenStack*>& Screen::GetOwners() const
		{
			return OwningStacks;
		}
		void Screen::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			states.transform *= GetTransformConst();
			for (auto drpr = DrawLists.begin(); drpr != DrawLists.end(); ++drpr)
			{
				for (auto dr = drpr->second.begin(); dr != drpr->second.end(); ++dr)
				{
					target.draw(*(*dr).second, states);
					//(*dr).second->Draw(window);
				}
			}
		}
		
		void Screen::Draw(sf::RenderTarget &window)
		{
			for (auto drpr = DrawLists.begin(); drpr != DrawLists.end(); ++drpr)
			{
				for (auto dr = drpr->second.begin(); dr != drpr->second.end(); ++dr)
				{
					(*dr).second->Draw(window);
				}
			}
		}
		void Screen::Draw(sf::RenderTarget &window, sf::RenderStates states)
		{
			for (auto drpr = DrawLists.begin(); drpr != DrawLists.end(); ++drpr)
			{
				for (auto dr = drpr->second.begin(); dr != drpr->second.end(); ++dr)
				{
					(*dr).second->Draw(window, states);
				}
			}
		}

		void Screen::Update(const sf::Uint32 time, const float TimeScale)
		{
			for (auto uppr = UpdateLists.begin(); uppr != UpdateLists.end(); ++uppr)
			{
				for (auto up = uppr->second.begin(); up != uppr->second.end(); ++up)
				{
					(*up).second->Update(time, TimeScale);
				}
			}
		}

		void Screen::AddToDrawList(const std::string& index, boost::shared_ptr<DrawInterface> drawable)
		{
			DrawLists[drawable->GetDrawPriority()][index] = drawable;
		}
		void Screen::AddToUpdateList(const std::string& index, const int priority, boost::shared_ptr<Updater> updateable)
		{
			UpdateLists[priority][index] = updateable;
		}

		bool Screen::operator==(const Screen& screen) const
		{
			return ScreenID == screen.ScreenID;
		}
		bool Screen::operator!=(const Screen& screen) const
		{
			return !((*this) == screen);
		}
	}
}