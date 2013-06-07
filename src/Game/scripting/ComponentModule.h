#pragma once
#include <components/Component.h>
#include <components/UseComponent.h>
#include <components/ApplyEffectComponent.h>
#include <components/ElementWeightComponent.h>
#include <statuseffects/StatusEffectsManager.h>
#include <battle/BattleField.h>
#include <character/BaseCharacter.h>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <Entity.h>
#include <vector>
#include <memory>
#include <scripting/Python/ScriptHelpers.h>
#include <Scripting/UseComponentWrap.h>
#include <components/InputComponent.h>

using namespace boost;
using namespace boost::python;

namespace Game
{
	namespace Scripting
	{
		template<class T>
		void CloneWrapper(PyObject* self)
		{
			//boost::shared_ptr<T> 
		}

		class ComponentWrap : public Components::Component
		{
		public:
			ComponentWrap(PyObject* self_) : self(self_), Components::Component()
			{

			}
			ComponentWrap(PyObject* self_, Entity* owner, bool valid) : self(self_), Components::Component(owner, valid)
			{

			}
			ComponentWrap(PyObject* self_, Entity* owner, const std::string& name, int type, bool valid = true) : self(self_), Components::Component(owner, name, type, valid)
			{

			}
			ComponentWrap(PyObject* self_, Entity* owner, const std::string& name, const std::string& type, bool valid = true ) : self(self_), Components::Component(owner, name, type, valid)
			{

			}
			ComponentWrap(PyObject* self_, const Components::Component& comp) : self(self_), Component(comp)
			{

			}
			ComponentWrap(PyObject* self_, const ComponentWrap& comp) : self(self_), Component(comp)
			{

			}
			Components::Component::ClonePtr Clone() const override
			{
				return call_method<Components::Component::ClonePtr>(self, "Clone");
			}
			Components::Component::ClonePtr CloneDefault() const
			{
				return this->Components::Component::Clone();
			}
			PyObject* self;
		}; 

		class InputComponentWrap : public Components::InputComponent
		{
		public:
			InputComponentWrap(PyObject* self_, Entity* owner) : self(self_), Components::InputComponent(owner)
			{

			}

			InputComponentWrap(PyObject* self_, const Components::InputComponent& inComp) : self(self_), InputComponent(inComp)
			{

			}

			bool HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult) override
			{ 
				return call_method<bool>(self, "HandleKeyPressed", time, boost::python::ptr(inputModule), boost::ref(actionResult));
				//return call_method<bool>(self, "IsCritical", boost::ref(target), boost::ref(action), boost::ref(mechanics));
			}
			bool HandleKeyPressedDefault(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult)
			{ 
				return this->::Input::InputInterface::HandleKeyPressed(time, inputModule, actionResult);
			}
			bool HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult) override
			{
				return call_method<bool>(self, "HandleKeyReleased", time, boost::python::ptr(inputModule), boost::ref(actionResult));
			}
			bool HandleKeyReleasedDefault(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult)
			{ 
				return this->::Input::InputInterface::HandleKeyReleased(time, inputModule, actionResult);
			}
			Components::InputComponent::ClonePtr Clone() const override
			{
				return call_method<Components::Component::ClonePtr>(self, "Clone");
			}
			Components::InputComponent::ClonePtr CloneDefault() const
			{
				return this->Components::InputComponent::Clone();
			}
			PyObject* self;
		};

		BOOST_PYTHON_MODULE(ComponentModule)
		{

			class_<std::vector<Character::BaseCharacter*> >("BaseCharacterVector")
				.def(vector_ptr_indexing_suite<std::vector<Character::BaseCharacter*> >())
				;

			bool (Components::Component::*IsType1)(const std::string&) = &Components::Component::IsType;
			bool (Components::Component::*IsType2)(int) = &Components::Component::IsType;

			class_<Components::Component, boost::shared_ptr<ComponentWrap> >("Component")
				.def(init<>())
				.def(init<const Components::Component&>())
				.def(init<const ComponentWrap&>())
				.def(init<Entity*, bool>())
				.def(init<Entity*, const std::string&, int, boost::python::optional<bool>  >())
				.def(init<Entity*, const std::string&, const std::string&, boost::python::optional<bool> >())
				.def("GetComponentType", &Components::Component::GetComponentType)
				.def("GetName", &Components::Component::GetNameByVal)
				.def("GetNameHash", &Components::Component::GetNameHash)
				.def("GetOwner", &Components::Component::GetOwner, return_value_policy<reference_existing_object>())
				.def("GetUID", &Components::Component::GetUID)
				.def("IsType", IsType1)
				.def("IsType", IsType2)
				.def("IsValid", &Components::Component::IsValid)
				.def("SetValid", &Components::Component::SetValid)
				//.def("SmartClone", &Components::Component::SmartClone)
				.def("Clone", &ComponentWrap::CloneDefault)
				.def("__eq__", &Components::Component::operator==)
				.def("__neq__", &Components::Component::operator!=)
				.def("__copy__", &generic__copy__<Components::Component>)
				.def("__deepcopy__", &generic__deepcopy__<Components::Component>)
				;
			class_<Components::ElementWeightComponent, bases<Components::Component> >("ElementWeightComponent", init<Entity*>())
				.def(init<Entity*, boost::unordered_map<Elements::Element, float>&>())
				.def("AddWeight", &Components::ElementWeightComponent::AddWeight)
				.def("GetElementWeight", &Components::ElementWeightComponent::GetElementWeights, return_value_policy<reference_existing_object>())
				.def("GetWeight", &Components::ElementWeightComponent::GetWeight)
				.def("Moderate", &Components::ElementWeightComponent::Moderate)
				;
			class_<Components::InputComponent, boost::shared_ptr<InputComponentWrap>, bases<Components::Component> >("InputComponent", init<Entity*>())
				.def("HandleKeyPressed", &InputComponentWrap::HandleKeyPressedDefault)
				.def("HandleKeyReleased", &InputComponentWrap::HandleKeyReleasedDefault)
				;
			/*class_<Components::UseComponent, boost::shared_ptr<UseComponentWrap>, bases<Components::Component> >("UseComponent")
				.def(init<>())
				.def(init<const std::string&,bool, bool>())
				.def(init<const Components::UseComponent&>())
				.def("BattleUse", &Components::UseComponent::BattleUse, &UseComponentWrap::BattleUseDefault)
				.def("Use", &Components::UseComponent::Use, &UseComponentWrap::UseDefault)
				.def("HasUse", &Components::UseComponent::HasUse)
				//.def("HasBattleUse", &Components::UseComponent::HasBattleUse)
				.def("Clone", &Components::UseComponent::Clone, &UseComponentWrap::Clone)
				.def("__copy__", &generic__copy__<UseComponentWrap>)
				.def("__deepcopy__", &generic__deepcopy__<UseComponentWrap>)
				;*/

//			class_<Components::StatComponent, boost::shared_ptr<Components::StatComponent>, bases<Components::Component> >("StatsComponent")
	//			;
/*
Component(bool valid = false);
Component(bool valid = false, const int id = ++ComponentIDCounter);
Component(const std::string& name, int type, bool valid = true, const int id = ++ComponentIDCounter);
Component(const std::string& name, const std::string& type, bool valid = true, const int id = ++ComponentIDCounter);
*/
		}
	}
}