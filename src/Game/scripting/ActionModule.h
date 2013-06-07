#pragma once
#include <actions/Action.h>
#include <actions/Attack.h>
#include <actions/ActionLibrary.h>
#include <actions/ActionUserTarget.h>
#include <actions/ActionModifierComponent.h>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <scripting/Python/ScriptHelpers.h>
#include <actions/ActionUserTarget.h>
using namespace boost::python;
namespace Game
{
	namespace Scripting
	{
		struct ActionWrap : public Actions::Action
		{
			ActionWrap(PyObject* self_) : self(self_)
			{

			}
			ActionWrap(PyObject* self_, const std::string& name, int mpCost = 0, int spCost = 0, float Accr = 1.f) : self(self_), Actions::Action(name, mpCost, spCost, Accr)
			{

			}
			ActionWrap(PyObject* self_, const Actions::Action& action) : self(self_), Actions::Action(action)
			{

			}
			ClonePtr Clone() const override
			{
				return call_method<ClonePtr>(self, "Clone");
			}
			ClonePtr CloneDefault() const
			{
				return this->Actions::Action::Clone();
			}
			PyObject* self;
		};

		struct AttackWrap : public Actions::Attack
		{
			AttackWrap(PyObject* self_) : self(self_)
			{

			}

			AttackWrap(PyObject* self_, const std::string& name, int basePower = 100, int mpCost = 0, int spCost = 0, float accr = 1.f, float physWgt = 1.f, float magicWgt = 0.f, float critCh = 1.f) : self(self_), Actions::Attack(name, basePower, mpCost, spCost, accr, physWgt, magicWgt, critCh)
			{

			}

			AttackWrap(PyObject* self_, const std::string& name, const std::string& displayName, int basePower = 100, int mpCost = 0, int spCost = 0, float accr = 1.f, float physWgt = 1.f, float magicWgt = 0.f, float critCh = 1.f) : self(self_), Actions::Attack(name, displayName, basePower, mpCost, spCost, accr, physWgt, magicWgt, critCh)
			{

			}
			AttackWrap(PyObject* self, const Actions::Attack& atk) : self(self), Actions::Attack(atk)
			{

			}
			AttackWrap(PyObject* self, const AttackWrap& atk) : self(self), Actions::Attack(atk)
			{

			}
			ClonePtr Clone() const override
			{
				return call_method<ClonePtr>(self, "Clone");
			}
			ClonePtr CloneDefault() const
			{
				return this->Actions::Attack::Clone();
			}

			PyObject* self;
		};

		struct ActionModifierComponentWrap : public Actions::ActionModifierComponent
		{
			ActionModifierComponentWrap(PyObject* self, Entity* owner) : self(self), Actions::ActionModifierComponent(owner)
			{

			}
			ActionModifierComponentWrap(PyObject* self, const Actions::ActionModifierComponent& modCmp) : self(self), Actions::ActionModifierComponent(modCmp)
			{

			}
			ActionModifierComponentWrap(PyObject* self, const ActionModifierComponentWrap& modCmp) : self(self), Actions::ActionModifierComponent(modCmp)
			{

			}
			ActionModifierComponentWrap(PyObject* self, boost::shared_ptr<ActionModifierComponent> cp) : self(self), Actions::ActionModifierComponent(*cp)
			{

			}
			virtual bool ModifyAction(Actions::Action& action, Battle::Mechanics& mechanics) override
			{
				return call_method<bool>(self, "ModifyAction", boost::ref(action), boost::ref(mechanics));
			}

			bool ModifyActionDefault(Actions::Action& action, Battle::Mechanics& mechanics)
			{
				return this->Actions::ActionModifierComponent::ModifyAction(action, mechanics);
			}

			ClonePtr Clone() const override
			{
				return call_method<ClonePtr>(self, "Clone");
			}
			ClonePtr CloneDefault() const
			{
				return this->Actions::ActionModifierComponent::Clone();
			}

			PyObject* self;
		};
		BOOST_PYTHON_MODULE(ActionModule)
		{
			//class_<boost::unordered_map<std::string, Actions::ActionUserTarget> >("ActionUserMap")
			//	.def(map_indexing_suite<boost::unordered_map<std::string, Actions::ActionUserTarget> >())
			//	;
			class_<Actions::ActionUserTarget>("ActionUserTarget", init<>())
				.def(init<Battle::BattleCharacterComponent*> ())
				.def(init<Character::BaseCharacter*> ())
				.def("__eq__", &Actions::ActionUserTarget::operator ==)
				.def("__neq__", &Actions::ActionUserTarget::operator !=)
				//.def_readwrite("AttachedBattleCharacter", &Actions::ActionUserTarget::AttachedBattleCharacter)
				//.def_readwrite("AttachedCharacter", &Actions::ActionUserTarget::AttachedCharacter)
				.add_property("AttachedBattleCharacter", 
				make_getter(&Actions::ActionUserTarget::AttachedBattleCharacter, return_value_policy<reference_existing_object>()),
				make_setter(&Actions::ActionUserTarget::AttachedBattleCharacter, return_value_policy<reference_existing_object>()))
				.add_property("AttachedCharacter", 
				make_getter(&Actions::ActionUserTarget::AttachedCharacter, return_value_policy<reference_existing_object>()),
				make_setter(&Actions::ActionUserTarget::AttachedCharacter, return_value_policy<reference_existing_object>()))
				.def_readwrite("Action", &Actions::ActionUserTarget::action)
				;

			class_<Actions::ActionGroup, bases<Entity> >("ActionGroup", init<>())
				.def(init<Character::BaseParty&>())
				.def(init<Battle::BattleParty&>())
				.def(init<Character::BaseCharacter&>())
				.def("AddBattleCharacter", &Actions::ActionGroup::AddBattleCharacter, (boost::python::arg("validate") = false))
				.def("AddCharacter", &Actions::ActionGroup::AddCharacter, (boost::python::arg("validate") = false))
				.def("GetFirst", &Actions::ActionGroup::GetFirst, return_value_policy<reference_existing_object>())
				.def("GetGroup", &Actions::ActionGroup::GetGroup, return_value_policy<reference_existing_object>())
				.def("GetAt", &Actions::ActionGroup::GetAt, return_value_policy<reference_existing_object>())
				.def("GetMember",  (Actions::ActionUserTarget* (Actions::ActionGroup::*)(const std::string&))&Actions::ActionGroup::GetMember, return_value_policy<reference_existing_object>())//&Actions::ActionGroup::GetMember, return_value_policy<reference_existing_object>())
				.def("GetMember",  (Actions::ActionUserTarget& (Actions::ActionGroup::*)(const std::string&, bool &))&Actions::ActionGroup::GetMember, return_value_policy<reference_existing_object>())//&Actions::ActionGroup::GetMember, return_value_policy<reference_existing_object>())
				//.def("RemoveTarget", (bool (Actions::ActionGroup::*)(const std::string&))&Actions::ActionGroup::RemoveTarget)
				//.def("RemoveTarget", (bool (Actions::ActionGroup::*)(const Actions::ActionUserTarget*))&Actions::ActionGroup::RemoveTarget)
				.def("RemoveMember", (bool (Actions::ActionGroup::*)(const std::string&))&Actions::ActionGroup::RemoveMember)
				.def("RemoveMember", (bool (Actions::ActionGroup::*)(const Actions::ActionUserTarget*))&Actions::ActionGroup::RemoveMember)
				.def("AddMember", (bool (Actions::ActionGroup::*)(Actions::ActionUserTarget&))&Actions::ActionGroup::AddMember)
				.def("AddMember", (bool (Actions::ActionGroup::*)(Actions::ActionUserTarget*))&Actions::ActionGroup::AddMember)
				.def("AddMember", (bool (Actions::ActionGroup::*)(Actions::ActionUserTarget&, const std::string&))&Actions::ActionGroup::AddMember)
				.def("AddCharacter", &Actions::ActionGroup::AddCharacter)
				.def("AddBattleCharacter", &Actions::ActionGroup::AddBattleCharacter)
				.def("GroupSize", &Actions::ActionGroup::GroupSize)
				.def("Clear", &Actions::ActionGroup::Clear)
				;
			//(int (Battle::BattleCharacterComponent::*)() const)&Battle::BattleCharacterComponent::GetTimerValue
			class_<Actions::Action, boost::shared_ptr<ActionWrap>, bases<Entity> >("Action")
				.def(init<>())
				.def(init<const std::string&, boost::python::optional<int, int, float> >())
				.def(init<const Actions::Action&>())
				.def_readwrite("Users", &Actions::Action::Users)
				.def_readwrite("Targets", &Actions::Action::Targets)
				.def_readwrite("IgnoreTargetAbil", &Actions::Action::IgnoreTargetAbil)
				.def_readwrite("IgnoreTargetSE", &Actions::Action::IgnoreTargetSE)
				.def_readwrite("IgnoreUserAbil", &Actions::Action::IgnoreUserAbil)
				.def_readwrite("IgnoreUserSE", &Actions::Action::IgnoreUserSE)
				.def_readwrite("MpCost", &Actions::Action::MpCost)
				.def_readwrite("SpCost", &Actions::Action::SpCost)
				.def("GetAccuracy", &Actions::Action::GetAccuracy)
				.def("SetAccuracy", &Actions::Action::SetAccuracy)
				.def("PushActionToTargets", &Actions::Action::PushActionToTargets)
				.def("GetActionHits", &Actions::Action::GetActionHits)
				.def("SetActionHits", &Actions::Action::SetActionHits)
				.def("Clone", &Actions::Action::Clone, &ActionWrap::CloneDefault)
				.def("__copy__", &generic__copy__< Actions::Action >)
				.def("__deepcopy__", &generic__deepcopy__< Actions::Action >)
				;

			class_<Actions::Attack, boost::shared_ptr<AttackWrap>, bases<Actions::Action> >("Attack", init<>())
				.def(init<const std::string&, boost::python::optional<int, int, int, float, float, float, float> >())
				.def(init<const std::string&, const std::string&, boost::python::optional<int, int, int, float, float, float, float> >())
				.def("GetBasePower", &Actions::Attack::GetBasePower)
				.def("GetCalculatedDamage", &Actions::Attack::GetCalculatedDamage)
				.def("GetCriticalChance", &Actions::Attack::GetCriticalChance)
				.def("GetMagicWeight", &Actions::Attack::GetMagicWeight)
				.def("GetPhysicalWeight", &Actions::Attack::GetPhysicalWeight)
				.def("GetPower", &Actions::Attack::GetPower)
				.def("SetAttackCritical", &Actions::Attack::SetAttackCritical)
				.def("SetCalculatedDamage", &Actions::Attack::SetCalculatedDamage)
				.def("SetPower", &Actions::Attack::SetPower)
				.def("GetPowerModerator", &Actions::Attack::GetPowerModerator)
				.staticmethod("GetPowerModerator")
				.def("Clone", &Actions::Attack::Clone, &AttackWrap::CloneDefault)
				.def("__copy__", &generic__copy__< AttackWrap >)
				.def("__deepcopy__", &generic__deepcopy__< AttackWrap >)
				;

			class_<Actions::ActionModifierComponent, boost::shared_ptr<ActionModifierComponentWrap>, bases<Components::Component> >("ActionModifierComponent", init<Entity*>())
				.def(init<const Actions::ActionModifierComponent&>())
				.def(init<const ActionModifierComponentWrap&>())
				.def("ModifyAction", &ActionModifierComponentWrap::ModifyAction, &ActionModifierComponentWrap::ModifyActionDefault)
				.def("Clone", &Actions::ActionModifierComponent::Clone, &ActionModifierComponentWrap::CloneDefault)
				.def("__eq__", &Actions::ActionModifierComponent::operator==)
				.def("__neq__", &Actions::ActionModifierComponent::operator!=)
				.def("__copy__", &generic__copy__< ActionModifierComponentWrap >)
				.def("__deepcopy__", &generic__deepcopy__< ActionModifierComponentWrap >)
				;

			class_<Actions::ActionsLibrary>("ActionLibrary", no_init)
				.def("AddAction", &Actions::ActionsLibrary::AddAction)
				;
		}
	}
}