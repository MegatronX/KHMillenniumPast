#pragma once
#ifndef _ACTION_H_
#define _ACTION_H_

#include <Entity.h>
#include <boost/shared_ptr.hpp>
#include <actions/ActionUserTarget.h>
namespace Game
{
	namespace Actions
	{
		class ActionGroup;
		class Action : public Entity//, public ActionInterface
		{
		public:
			Action();
			Action(const std::string& name, int mpCost = 0, int spCost = 0, float Accr = 1.f, const int type = EntityTypes::ActionEntity);
			Action(const Action& action);
			ActionGroup Users;
			ActionGroup Targets;

			bool IgnoreUserSE;
			bool IgnoreUserAbil;
			
			bool IgnoreTargetSE;
			bool IgnoreTargetAbil;

			int MpCost;
			int SpCost;

			bool CopyUsers;
			bool CopyTargets;
			/*virtual bool PreUse(Action* action) override;
			virtual bool Use(Action* action) override;
			virtual bool PostUse(Action* action) override;
			virtual bool BattlePreUse(Action* action, Battle::BattleField* field) override;
			virtual bool BattleUse(Action* action, Battle::BattleField* field) override;
			virtual bool BattlePostUse(Action* action, Battle::BattleField* field) override;*/
			RawClonePtr RawClone() const override;

			void PushActionToTargets();

			float GetAccuracy() const;
			void SetAccuracy(const float ac);

			bool GetActionHits() const;
			void SetActionHits(const bool hit);

			Action& operator=(const Action& action);

			virtual ~Action();
		protected:

			bool ActionHits;
			float Accuracy;
		};
		typedef boost::shared_ptr<Action> action_ptr;
	}
}

#endif