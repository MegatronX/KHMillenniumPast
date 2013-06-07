#pragma once
#include <components/Component.h>
#include <actions/Action.h>
#include <vector>
namespace Game
{
	namespace Character
	{
		class BaseCharacter;
	}
	namespace Battle
	{
		class BattleCharacter;
		class BattleField;
	}
	namespace Components
	{
		class UseComponent : public Component
		{
		public:
			UseComponent() : Component(), ImplementsUse(false), ImplementsBattleUse(false)
			{

			}
			UseComponent(Entity* owner, const std::string& name, bool hasUse = false, bool hasBattleUse = false) 
				: Component(owner, name, "UseComponent"), ImplementsUse(hasUse), ImplementsBattleUse(hasBattleUse)
			{

			}
			UseComponent(Entity* owner, bool hasUse = false, bool hasBattleUse = false)
				: Component(owner, owner != nullptr ? owner->GetName() + "UseComponent" : nullptr, "UseComponent"), ImplementsUse(hasUse), ImplementsBattleUse(hasBattleUse)
			{

			}
			virtual bool Use(Actions::Action* action)
			{
				return false;
			}
			virtual bool BattleUse(Actions::Action* action, Battle::BattleField* field)
			{
				return false;
			}
			bool HasUse() const
			{
				return ImplementsUse;
			}
			bool HasBattleUse() const
			{
				return ImplementsBattleUse;
			}
			virtual RawClonePtr RawClone() const override
			{
				return new UseComponent(*this);
			}
		private:
			bool ImplementsUse;
			bool ImplementsBattleUse;
		};
	}
}