#pragma once
#include <boost/python.hpp>
#include <scripting/Python/ScriptHelpers.h>
#include <battle/mechanics/Mechanics.h>

#include <battle/CriticalHitComponent.h>
#include <battle/DamageCalculationComponent.h>
#include <battle/HitComponent.h>
#include <battle/BattleCharacterComponent.h>
using namespace boost::python;
namespace Game
{
	namespace Scripting
	{
		class CriticalHitComponentWrap : public Battle::CriticalHitComponent
		{
		public:
			CriticalHitComponentWrap(PyObject* self, Entity* owner) : self(self), Battle::CriticalHitComponent(owner)
			{

			}
			CriticalHitComponentWrap(PyObject* self, const Battle::CriticalHitComponent& ref) : self(self), Battle::CriticalHitComponent(ref)
			{

			}
			CriticalHitComponentWrap(PyObject* self, const CriticalHitComponentWrap& ref) : self(self), Battle::CriticalHitComponent(ref)
			{

			}
			bool IsCritical(Character::BaseCharacter& target, Actions::Action& action, Battle::Mechanics& mechanics) override
			{
				return call_method<bool>(self, "IsCritical", boost::ref(target), boost::ref(action), boost::ref(mechanics));
			}

			bool IsCriticalDefault(Character::BaseCharacter& target, Actions::Action& action, Battle::Mechanics& mechanics)
			{
				return this->Battle::CriticalHitComponent::IsCritical(target, action, mechanics);
			}

			CriticalHitComponent::ClonePtr Clone() const override
			{
				return call_method<Battle::CriticalHitComponent::ClonePtr>(self, "Clone");
			}
			CriticalHitComponent::ClonePtr CloneDefault() const
			{
				return this->Battle::CriticalHitComponent::Clone();
				//return call_method<Battle::CriticalHitComponent::ClonePtr>(self, "Clone");
			}
			PyObject* self;
		};

		class DamageCalculationComponentWrap : public Battle::DamageCalculationComponent
		{
		public:
			DamageCalculationComponentWrap(PyObject* self, Entity* owner) : self(self), Battle::DamageCalculationComponent(owner)
			{

			}
			DamageCalculationComponentWrap(PyObject* self, const Battle::DamageCalculationComponent& ref) : self(self), Battle::DamageCalculationComponent(ref)
			{

			}
			int CalculateDamage(Actions::Action& action, Character::BaseCharacter& target, Battle::Mechanics& mechanics) override
			{
				return call_method<int>(self, "CalculateDamage", boost::ref(action), boost::ref(target), boost::ref(mechanics));
			}

			int CalculateDamageDefault(Actions::Action& action, Character::BaseCharacter& target, Battle::Mechanics& mechanics)
			{
				return this->DamageCalculationComponent::CalculateDamage(action, target, mechanics);
			}
			ClonePtr Clone() const override
			{
				return call_method<Battle::CriticalHitComponent::ClonePtr>(self, "Clone");
			}
			ClonePtr CloneDefault() const
			{
				return this->Battle::DamageCalculationComponent::Clone();
				//return call_method<Battle::CriticalHitComponent::ClonePtr>(self, "Clone");
			}
			PyObject* self;
		};

		class HitComponentWrap : public Battle::HitComponent
		{
		public:

			PyObject* self;
		};

		typedef Character::PartyInterface<Battle::BattleCharacterComponent> BattleParty;

		BOOST_PYTHON_MODULE(BattleModule)
		{
			boost::python::scope().attr("DamageFinalizerIndex") = Battle::DamageFinalizerIndex;
			boost::python::scope().attr("FinalizeTargettingIndex") = Battle::FinalizeTargettingIndexer;
			boost::python::scope().attr("DamageFinalizerIndex") = Battle::IncomingAttackIndexer;
			boost::python::scope().attr("DamageFinalizerIndex") = Battle::OutgoingAttackIndexer;

			class_<Battle::BattleCharacterComponent, bases<Components::Component> >("BattleCharacterComponent", no_init)
				.def("GetBaseParty", &Battle::BattleCharacterComponent::GetBaseParty, return_value_policy<reference_existing_object>())
				.def("GetBattleParty", &Battle::BattleCharacterComponent::GetBattleParty, return_value_policy<reference_existing_object>())
				.def("GetCharacterMode", &Battle::BattleCharacterComponent::GetCharacterMode)
				.def("SetCharacterMode", &Battle::BattleCharacterComponent::SetCharacterMode)
				.def("GetTimerValue", (int (Battle::BattleCharacterComponent::*)() const)&Battle::BattleCharacterComponent::GetTimerValue)
				.def("GetTimeValue", (int (Battle::BattleCharacterComponent::*)(const Battle::BattleMode) const)&Battle::BattleCharacterComponent::GetTimerValue)
				.def("GetTimerRatio", (float (Battle::BattleCharacterComponent::*)() const)&Battle::BattleCharacterComponent::GetTimerRatio)
				.def("GetTimerRatio", (float (Battle::BattleCharacterComponent::*)(const Battle::BattleMode) const)&Battle::BattleCharacterComponent::GetTimerRatio)
				//.def("", &Battle::BattleCharacterComponent::GetTimerValue)
				//.def("", &Battle::BattleCharacterComponent:)
				.def("Clone", &Battle::BattleCharacterComponent::Clone)
				;
			class_<BattleParty>("BattleParty", no_init)
				.def("AddMember", &BattleParty::AddMember)
				.def("RemoveMemberByName", &BattleParty::RemoveMemberByName)
				.def("GetRawPartyMembers", &BattleParty::GetRawPartyMembers)
				.def("GetPartyMembers", &BattleParty::GetPartyMembers, return_value_policy<reference_existing_object>())
				;
			class_<Battle::CriticalHitComponent, boost::shared_ptr<CriticalHitComponentWrap>, bases<Components::Component> >("CriticalHitComponent", init<Entity*>())
				.def(init<const Battle::CriticalHitComponent&>())
				.def(init<const CriticalHitComponentWrap&>())
				.def("IsCritical", &CriticalHitComponentWrap::IsCriticalDefault)
				.def("Clone", &CriticalHitComponentWrap::CloneDefault)
				.def("__copy__", &generic__copy__< Battle::CriticalHitComponent >)
				.def("__deepcopy__", &generic__deepcopy__< Battle::CriticalHitComponent >)
				;

			class_<Battle::DamageCalculationComponent, boost::shared_ptr<DamageCalculationComponentWrap>, bases<Components::Component> >("DamageCalculationComponent", init<Entity*>())
				.def(init<const Battle::DamageCalculationComponent&>())
				.def("CalculateDamage", &DamageCalculationComponentWrap::CalculateDamageDefault)
				.def("Clone",  &DamageCalculationComponentWrap::CloneDefault)
				.def("__copy__", &generic__copy__< Battle::DamageCalculationComponent >)
				.def("__deepcopy__", &generic__deepcopy__< Battle::DamageCalculationComponent >)
				;


			class_<Battle::Mechanics>("Mechanics", no_init)
				.def("ApplyCriticalFormula", &Battle::Mechanics::ApplyCriticalFormula)
				.def("PreUsePhase", &Battle::Mechanics::PreUsePhase)
				.def("PostUsePhase", &Battle::Mechanics::PostUsePhase)
				.def("UsePhase", &Battle::Mechanics::UsePhase)
				.def("GenerateInt", &Battle::Mechanics::GenerateInt, (boost::python::arg("bias") = 1.f))
				//.def("", &Battle::Mechanics:)
				;
		}
	}
}