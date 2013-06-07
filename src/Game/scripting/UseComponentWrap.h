#pragma once
#include <components/UseComponent.h>
#include <boost/python.hpp>
namespace Game
{
	class Entity;
	namespace Character
	{
		class BaseCharacter;

	}
	namespace Battle
	{
		class BattleCharacter;
	}
	namespace Scripting
	{

		class UseComponentWrap : public Components::UseComponent
		{
		public:
			UseComponentWrap(PyObject* self_, Entity* owner);
			UseComponentWrap(PyObject* self_, Entity* owner, const std::string& name, bool hasUse = false, bool hasBattleUse = false);
			UseComponentWrap(PyObject* self_, Entity* owner, bool HasUse = false, bool HasBattleUse = false);
			UseComponentWrap(PyObject* self_, const Components::UseComponent& cmp);
			//UseComponentWrap(const Components::UseComponentWrap& cmp);
			bool Use(Actions::Action* action) override;
			bool UseDefault(Actions::Action* action);
			bool BattleUse(Actions::Action* action, Battle::BattleField* field) override;
			bool BattleUseDefault(Actions::Action* action, Battle::BattleField* field);
			Components::UseComponent::ClonePtr Clone() const override;
			Components::UseComponent::ClonePtr CloneDefault() const;
			PyObject* self;


		private:

		};
	}
}
