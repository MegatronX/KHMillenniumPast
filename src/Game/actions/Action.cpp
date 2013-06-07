#include "Action.h"
#include <components/ActionUseComponent.h>
#include <algorithm>
namespace Game
{
	using namespace Components;
	namespace Actions
	{
		Action::Action() : Entity(), ActionHits(false), IgnoreTargetAbil(false), IgnoreTargetSE(false), IgnoreUserAbil(false), IgnoreUserSE(false), CopyUsers(true), CopyTargets(false)//, ActionInterface(true, true, true, true, true, true)
		{

		}
		Action::Action(const std::string& name,  int mpCost, int spCost, float acr, const int type) : Entity(name, type), MpCost(mpCost), SpCost(spCost), Accuracy(acr), IgnoreTargetAbil(false), IgnoreTargetSE(false), IgnoreUserAbil(false), IgnoreUserSE(false), CopyUsers(true), CopyTargets(false),
			ActionHits(false)//, ActionInterface(true, true, true, true, true, true)
		{

		}
		Action::Action(const Action& action) : Entity(action), MpCost(action.MpCost), SpCost(action.SpCost), Accuracy(action.GetAccuracy()), IgnoreTargetAbil(action.IgnoreTargetAbil), IgnoreTargetSE(action.IgnoreTargetSE), IgnoreUserAbil(action.IgnoreUserAbil), IgnoreUserSE(action.IgnoreUserSE), CopyUsers(action.CopyUsers), CopyTargets(action.CopyTargets)
		{
			if (CopyTargets)
			{
				Targets = action.Targets;
			}
			if(CopyUsers)
			{
				Users = action.Users;
			}
		}
		/*bool Action::PreUse(Action* action)//, ActionInterface(true, true, true, true, true, true)
		{
			std::vector<Actions::ActionInterface*> comps;
			comps.reserve(10);
			for (auto comp = ComponentCollection.begin(); comp != ComponentCollection.end(); ++comp)
			{
				auto compPtr = dynamic_cast<ActionUseComponent*>(comp->second.get());
				if ((compPtr) != nullptr && compPtr->ImplementsPreUse())
				{
					comps.push_back(compPtr);
				}
			}
			if (comps.size() < 0)
			{
				for (auto comp = comps.begin(); comp != comps.end(); ++comp)
				{
					(*comp)->PreUse(this);
				}
				return true;
			}
			return false;
		}
		bool Action::Use(Action* action)
		{
			std::vector<Actions::ActionInterface*> comps;
			comps.reserve(10);
			for (auto comp = ComponentCollection.begin(); comp != ComponentCollection.end(); ++comp)
			{
				auto compPtr = dynamic_cast<ActionUseComponent*>(comp->second.get());
				if ((compPtr) != nullptr && compPtr->ImplementsUse())
				{
					comps.push_back(compPtr);
				}
			}
			if (comps.size() < 0)
			{
				for (auto comp = comps.begin(); comp != comps.end(); ++comp)
				{
					(*comp)->Use(this);
				}
				return true;
			}
			return false;
		}
		bool Action::PostUse(Action* action)
		{
			std::vector<Actions::ActionInterface*> comps;
			comps.reserve(10);
			for (auto comp = ComponentCollection.begin(); comp != ComponentCollection.end(); ++comp)
			{
				auto compPtr = dynamic_cast<ActionUseComponent*>(comp->second.get());
				if ((compPtr) != nullptr && compPtr->ImplementsPostUse())
				{
					comps.push_back(compPtr);
				}
			}
			if (comps.size() < 0)
			{
				for (auto comp = comps.begin(); comp != comps.end(); ++comp)
				{
					(*comp)->PostUse(this);
				}
				return true;
			}
			return false;
		}

		bool Action::BattlePreUse(Action* action, Battle::BattleField* field)
		{
			return false;
		}
		bool Action::BattleUse(Action* action, Battle::BattleField* field)
		{
			return false;
		}
		bool Action::BattlePostUse(Action* action, Battle::BattleField* field)
		{
			return false;
		}*/

		Action::RawClonePtr Action::RawClone() const
		{
			return new Action(*this);
		}

		void Action::PushActionToTargets()
		{
			for (auto it = Targets.GetGroup().begin(); it != Targets.GetGroup().end(); ++it)
			{
				(*it).second.action = boost::dynamic_pointer_cast<Action>(this->Clone());
			}
		}

		float Action::GetAccuracy() const
		{
			return this->Accuracy;
		}
		void Action::SetAccuracy(const float ac)
		{
			this->Accuracy = ac;
		}
		bool Action::GetActionHits() const
		{
			return ActionHits;
		}
		void Action::SetActionHits(const bool hit)
		{
			ActionHits = hit;
		}

		Action& Action::operator=(const Action& act)
		{
			if (this != &act)
			{
				this->Accuracy = act.Accuracy;
				this->ActionHits = act.ActionHits;
				this->CopyTargets = act.CopyTargets;
				this->CopyUsers = act.CopyUsers;
				this->MpCost = act.MpCost;
				this->IgnoreTargetAbil = act.IgnoreTargetAbil;
				this->IgnoreTargetSE = act.IgnoreTargetSE;
				this->IgnoreUserAbil = act.IgnoreUserAbil;
				this->IgnoreUserSE = act.IgnoreUserSE;
				this->SpCost = act.SpCost;
				if (this->CopyTargets)
				{
					this->Targets = act.Targets;
				}
				if (this->CopyUsers)
				{
					this->Users = act.Users;
				}
				
			}
			return *this;
		}
		
		Action::~Action()
		{

		}
	}
}