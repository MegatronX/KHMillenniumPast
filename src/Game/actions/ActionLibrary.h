#pragma once
#ifndef _ACTIONLIBRARY_H_
#define _ACTIONLIBRARY_H_

#include <actions/Action.h>
#include <boost/unordered_map.hpp>

namespace Game
{
	namespace Actions
	{
		class ActionsLibrary
		{
		public:
		/*	const Action* GetAction(const std::string& name) const
			{
				auto act = NameToAction.find(name);
				if (act != NameToAction.end())
				{
					return act->second.get();
				}
				return nullptr;
			}*/

			action_ptr GetAction(const std::string& name) const
			{
				auto act = NameToAction.find(name);
				if (act != NameToAction.end())
				{
					auto res = act->second->Clone();
					return boost::dynamic_pointer_cast<Action>(res);
				}
				return action_ptr();
			}

			/*action_ptr GetRandomAction() const
			{

				auto act = NameToAction.find(name);
				if (act != NameToAction.end())
				{
					auto res = act->second->Clone();
					return boost::dynamic_pointer_cast<Action>(res);
				}
				return action_ptr();
			}*/

			const Action* GetActionRawClone(const std::string& name) const
			{
				auto act = NameToAction.find(name);
				if (act != NameToAction.end())
				{
					return dynamic_cast<Action*>(act->second->RawClone());
				}
				return nullptr;
			}
			const Action* GetActionBase(const std::string& name) const
			{
				auto act = NameToAction.find(name);
				if (act != NameToAction.end())
				{
					return act->second.get();
				}
				return nullptr;
			}

			void AddAction(action_ptr act)
			{
				if (act.get() != nullptr)
				{
					NameToAction[act->GetName()] = act;
				}
			}

		
		private:
			boost::unordered_map<std::string, action_ptr> NameToAction;
		};
	}
}

#endif