#pragma once
#include <components/UseComponent.h>
#include <boost/python.hpp>
namespace Game
{
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
			UseComponentWrap(PyObject* self_);
			UseComponentWrap(PyObject* self_, const std::string& name, bool hasUse, bool hasBattleUse);
			UseComponentWrap(PyObject* self_, const Components::UseComponent& cmp);
			bool Use(std::vector<Character::BaseCharacter*>& Users, std::vector<Character::BaseCharacter*>& Targets) override;
			bool UseDefault(std::vector<Character::BaseCharacter*>& Users, std::vector<Character::BaseCharacter*>& Targets);
			bool BattleUse(std::vector<Battle::BattleCharacter*>& Users, std::vector<Battle::BattleCharacter*>& Targets, Battle::BattleField* field) override;
			bool BattleUseDefault(std::vector<Battle::BattleCharacter*>& Users, std::vector<Battle::BattleCharacter*>& Targets, Battle::BattleField* field);
			Components::UseComponent::ClonePtr Clone() const override;
			Components::UseComponent::ClonePtr CloneDefault() const;
			PyObject* self;


		private:

		};
	}
}
