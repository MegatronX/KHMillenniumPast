#pragma once
#include <components/Component.h>
#include <components/UseComponent.h>
#include <battle/BattleField.h>
#include <battle/BattleCharacter.h>
#include <character/BaseCharacter.h>
#include <boost/python.hpp>
#include <vector>
#include <memory>
#include <scripting/Python/ScriptHelpers.h>
#include <Scripting/UseComponentWrap.h>
using namespace boost;
using namespace boost::python;

namespace Game
{
	namespace Scripting
	{

		BOOST_PYTHON_MODULE(ComponentModule)
		{
			class_<std::vector<Battle::BattleCharacter*> >("BattleCharacterVector")
				.def(vector_ptr_indexing_suite<std::vector<Battle::BattleCharacter*> >())
				;

			class_<std::vector<Character::BaseCharacter*> >("BaseCharacterVector")
				.def(vector_ptr_indexing_suite<std::vector<Character::BaseCharacter*> >())
				;

			bool (Components::Component::*IsType1)(const std::string&) = &Components::Component::IsType;
			bool (Components::Component::*IsType2)(int) = &Components::Component::IsType;

			class_<Components::Component, std::auto_ptr<Components::Component> >("Component")
				.def(init<>())
				.def(init<bool, boost::python::optional<const int> >())
				.def(init<const std::string&, int, boost::python::optional<bool, const int>  >())
				.def(init<const std::string&, const std::string&, boost::python::optional<bool, const int>  >())
				.def("GetComponentType", &Components::Component::GetComponentType)
				.def("GetName", &Components::Component::GetName, return_value_policy<reference_existing_object>())
				.def("GetNameHash", &Components::Component::GetNameHash)
				.def("GetUID", &Components::Component::GetUID)
				.def("IsType", IsType1)
				.def("IsType", IsType2)
				.def("IsValid", &Components::Component::IsValid)
				.def("SetValid", &Components::Component::SetValid)
				.def("SmartClone", &Components::Component::SmartClone)
				.def("Clone", &Components::Component::Clone, return_value_policy<reference_existing_object>())
				.def("__eq__", &Components::Component::operator==)
				.def("__neq__", &Components::Component::operator!=)
				.def("__copy__", &generic__copy__<Components::Component>)
				.def("__deepcopy__", &generic__deepcopy__<Components::Component>)
				;

			class_<Components::UseComponent, std::auto_ptr<UseComponentWrap>, bases<Components::Component> >("UseComponent")
				.def(init<>())
				.def(init<const std::string&,bool, bool>())
				.def(init<const Components::UseComponent&>())
				.def("BattleUse", &Components::UseComponent::BattleUse, &UseComponentWrap::BattleUseDefault)
				.def("Use", &Components::UseComponent::Use, &UseComponentWrap::UseDefault)
				.def("HasUse", &Components::UseComponent::HasUse)
				.def("HasBattleUse", &Components::UseComponent::HasBattleUse)
				.def("Clone", &Components::UseComponent::Clone, &UseComponentWrap::CloneDefault, return_value_policy<reference_existing_object>())
				.def("__copy__", &generic__copy__<Components::UseComponent>)
				.def("__deepcopy__", &generic__deepcopy__<Components::UseComponent>)
				;
/*
Component(bool valid = false);
Component(bool valid = false, const int id = ++ComponentIDCounter);
Component(const std::string& name, int type, bool valid = true, const int id = ++ComponentIDCounter);
Component(const std::string& name, const std::string& type, bool valid = true, const int id = ++ComponentIDCounter);
*/
		}
	}
}