#include "ActionHistory.h"
#include <actions/Action.h>
namespace Game
{
	namespace Battle
	{
		ActionHistory::ActionHistory(const int HistoryLength)
		{

		}

		void ActionHistory::AddToHistory(boost::shared_ptr<Actions::Action> action)
		{
			if (action.get() != nullptr)
			{
				history.push_front(action);
			}
		}
		// ----ActionCount----
		//  name - name of the action to look up
		//	fullHistory = whether to use full battle move history, or recommended history size
		//	returns number of actions in selected history that match the name
		int ActionHistory::ActionCount(const std::string& name, bool fullHistory)
		{
			int count = 0;
			int index = 0;
			for (auto act = history.begin(); act != history.end() && (index < Historylength || fullHistory); ++act, ++index)
			{
				if ((*act)->GetName() == name)
					++count;
			}
			return count;
		}

		int ActionHistory::ActionCount(const std::string& name, int maxHistory)
		{
			int count = 0;
			int index = 0;
			for (auto act = history.begin(); act != history.end() && index < maxHistory; ++act)
			{
				if ((*act)->GetName() == name)
					++count;
			}
			return count;
		}

		boost::shared_ptr<Actions::Action> ActionHistory::GetAction(int index)
		{
			if (index >= history.size())
				return boost::shared_ptr<Actions::Action>();
			return history[index];
		}
		//Returns the first action that matches the name, a boost::shared_ptr<Actions::Action>() otherwise
		boost::shared_ptr<Actions::Action> ActionHistory::GetAction(const std::string& name)
		{
			for (auto act = history.begin(); act != history.end(); ++act)
			{
				if ((*act)->GetName() == name)
					return *act;
			}
			return boost::shared_ptr<Actions::Action>();
		}
	}
}
