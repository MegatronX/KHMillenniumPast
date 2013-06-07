#pragma once
#include <deque>
#include <boost/shared_ptr.hpp>
namespace Game
{
	namespace Actions
	{
		class Action;
	}
	namespace Battle
	{
		class ActionHistory
		{
		public:
			ActionHistory(const int HistoryLength = 30);

			void AddToHistory(boost::shared_ptr<Actions::Action> action);
			// ----ActionCount----
			//  name - name of the action to look up
			//	fullHistory = whether to use full battle move history, or recommended history size
			//	returns number of actions in selected history that match the name
			int ActionCount(const std::string& name, bool fullHistory = false);

			int ActionCount(const std::string& name, int maxHistory = 30);

			boost::shared_ptr<Actions::Action> GetAction(int index);
			//Returns the first action that matches the name, a boost::shared_ptr<Actions::Action>() otherwise
			boost::shared_ptr<Actions::Action> GetAction(const std::string& name);
		private:
			int Historylength;
			std::deque<boost::shared_ptr<Actions::Action>> history;
		};
	}
}