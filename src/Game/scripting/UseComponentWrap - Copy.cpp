#include "UseComponentWrap.h"
#include <character/BaseCharacter.h>
#include <battle/BattleCharacter.h>
#include <battle/BattleField.h>
using namespace boost::python;
namespace Game
{
	namespace Scripting
	{
		UseComponentWrap::UseComponentWrap(PyObject* self_) : self(self_)
		{

		}
		UseComponentWrap::UseComponentWrap(PyObject* self_, const std::string& name, bool hasUse, bool hasBattleUse) : self(self_), 
			UseComponent(name, hasUse, hasBattleUse)
		{

		}
		UseComponentWrap::UseComponentWrap(PyObject* self_, const Components::UseComponent& cmp) : self(self_), Components::UseComponent(cmp)
		{

		}
		bool UseComponentWrap::Use(std::vector<Character::BaseCharacter*>& Users, std::vector<Character::BaseCharacter*>& Targets)
		{
			return call_method<bool>(self, "Use", boost::ref(Users), boost::ref(Targets));
		}
		bool UseComponentWrap::UseDefault(std::vector<Character::BaseCharacter*>& Users, std::vector<Character::BaseCharacter*>& Targets)
		{
			return this->UseComponent::Use((Users), (Targets));
		}
		bool UseComponentWrap::BattleUse(std::vector<Battle::BattleCharacter*>& Users, std::vector<Battle::BattleCharacter*>& Targets, Battle::BattleField* field)
		{
			return call_method<bool>(self, "BattleUse", boost::ref(Users), boost::ref(Targets), ptr(field));
		}
		bool UseComponentWrap::BattleUseDefault(std::vector<Battle::BattleCharacter*>& Users, std::vector<Battle::BattleCharacter*>& Targets, Battle::BattleField* field)
		{
			return this->UseComponent::BattleUse(Users, Targets, field);
		}
		Components::UseComponent::ClonePtr UseComponentWrap::Clone() const
		{
			return call_method<Components::UseComponent::ClonePtr>(self, "Clone");
		}
		Components::UseComponent::ClonePtr UseComponentWrap::CloneDefault() const
		{
			return this->Components::UseComponent::Clone();
		}
	}
}
