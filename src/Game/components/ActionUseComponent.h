#pragma once
#include <components/Component.h>
namespace Game
{
	namespace Battle
	{
		class Action;
		class BattleField;
	}
	namespace Components
	{
		class ActionUseComponent : public Component//, public Actions::ActionInterface
		{
		public:
			ActionUseComponent(Entity* owner, const std::string& name, const int priority = 0, 
				bool hasPreUse = false, bool hasBattlePreUse = false,
				bool hasUse = false, bool hasBattleUse = false, 
				bool hasPostUse = false, bool hasBattlePostUse = false) 
				: Priority(priority), Component(owner, name, "ActionUseComponent")//, 
				//ActionInterface(hasPreUse, hasBattlePreUse, hasUse, hasBattlePreUse, hasPostUse, hasBattlePostUse)
			{

			}

			inline int GetPriority() const
			{
				return Priority;
			}
		private:
			bool PreUse_;
			bool Use_;
			bool PostUse_;
			bool BattlePreUse_;
			bool BattleUse_;
			bool BattlePostUse_;
			int Priority;
		};
	}
}