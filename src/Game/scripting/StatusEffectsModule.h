#pragma once
#ifndef _STATUSEFFECTSMODULE_H_
#define _STATUSEFFECTSMODULE_H_
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <statuseffects/StatusEffect.h>
#include <statuseffects/StatusEffectsManager.h>
#include <scripting/Python/ScriptHelpers.h>
#include <components/ApplyEffectComponent.h>
using namespace boost::python;
namespace Game
{
	namespace Scripting
	{
		class StatusEffectWrap : public StatusEffects::StatusEffect
		{
		public:
			StatusEffectWrap(PyObject* self_, Character::BaseCharacter* holder, const std::string& name, bool pos, const int priority, const int ticks) : self(self_),
				StatusEffect(holder, name, pos, priority, ticks)
			{

			}
			StatusEffectWrap(PyObject* self, const StatusEffects::StatusEffect& ref) : self(self), StatusEffect(ref)
			{

			}
			StatusEffects::StatusEffect::ClonePtr Clone() const override
			{
				return call_method<StatusEffects::StatusEffect::ClonePtr>(self, "Clone");
			}
			StatusEffects::StatusEffect::ClonePtr CloneDefault() const
			{
				return this->StatusEffects::StatusEffect::Clone();
			}
			PyObject* self;
		};

		class ApplyEffectWrap : public Components::ApplyEffectComponent
		{
		public:
			ApplyEffectWrap(PyObject* self, Entity* owner) : self(self), Components::ApplyEffectComponent(owner)
			{

			}
			ApplyEffectWrap(PyObject* self, const Components::ApplyEffectComponent& eff) : self(self), Components::ApplyEffectComponent(eff)
			{

			}
			virtual void Apply(Character::BaseCharacter* character) override
			{
				call_method<void>(self, "Apply", ptr(character));
			}
			virtual void ApplyDefault(Character::BaseCharacter* character)
			{
				this->Components::ApplyEffectComponent::Apply(character);
			}
			virtual void UnApply(Character::BaseCharacter* character) override
			{
				call_method<void>(self, "UnApply", ptr(character));
			}
			virtual void UnApplyDefault(Character::BaseCharacter* character)
			{
				this->Components::ApplyEffectComponent::UnApply(character);
			}
			Components::ApplyEffectComponent::ClonePtr Clone() const override
			{
				return call_method<Components::ApplyEffectComponent::ClonePtr>(self, "Clone");
			}
			Components::ApplyEffectComponent::ClonePtr CloneDefault() const
			{
				return this->Components::ApplyEffectComponent::Clone();
			}
			PyObject* self;
		};

		BOOST_PYTHON_MODULE(StatusEffectsModule)
		{
			boost::python::scope().attr("DEFAULT_TURNS") = DEFAULT_TURNS;
			boost::python::scope().attr("ApplyEffectIndex") = StatusEffects::ApplyEffectIndexer;
			enum_<CallCondition>("CallCondition")
				.value("Apply", CallCondition::Apply)
				.value("ApplyingDamage", CallCondition::ApplyingDamage)
				.value("DamageDealt", CallCondition::DamageDealt)
				.value("DamageTaken", CallCondition::DamageTaken)
				.value("DeterminingCrit", CallCondition::DeterminingCrit)
				.value("DeterminingHit", CallCondition::DeterminingHit)
				.value("FinalizingTargets", CallCondition::FinalizingTargets)
				.value("IncomingAttack", CallCondition::IncomingAttack)
				.value("MPInspection", CallCondition::MPInspection)
				.value("OutgoingAttack", CallCondition::OutgoingAttack)
				.value("PartyMemberOutgoingAttack", CallCondition::PartyMemberOutgoingAttack)
				.value("PartyMemberIncomingAttack", CallCondition::PartyMemberIncomingAttack)
				.value("PreUse", CallCondition::PreUse)
				.value("SPInspection", CallCondition::SPInspection)
				.value("Tick", CallCondition::Tick)
				//.value("", CallCondition:)
				//.value("", CallCondition:)
				;

			class_<std::vector<CallCondition> >("CallConditionSet")
				.def(vector_indexing_suite<std::vector<CallCondition> >())
				;
			class_<std::vector<StatusEffects::StatusEffect*> >("StatusEffectList")
				.def(vector_indexing_suite<std::vector<StatusEffects::StatusEffect*>, true >())
				;
			class_<StatusEffects::StatusEffect, bases<Entity> >("StatusEffect", init<Character::BaseCharacter*, const std::string&, boost::python::optional<bool, const int, const int, const std::vector<CallCondition>& > >())
				.def(init<Character::BaseCharacter*, const std::string&, const std::string&, boost::python::optional<bool, const int, const int, const std::vector<CallCondition>& > >())
				.def(init<const StatusEffects::StatusEffect&>())
				.def("SetHolder", &StatusEffects::StatusEffect::SetHolder)
				.def("GetHolder", &StatusEffects::StatusEffect::GetHolder, return_value_policy<reference_existing_object>())
				.def("Clone", &StatusEffectWrap::CloneDefault)
				.def("__eq__", &StatusEffects::StatusEffect::operator==)
				.def("__neq__", &StatusEffects::StatusEffect::operator!=)
				.def("__copy__", &generic__copy__<StatusEffects::StatusEffect>)
				.def("__deepcopy__", &generic__deepcopy__<StatusEffects::StatusEffect>)
				;

			class_<StatusEffects::StatusEffectsManager, noncopyable>("StatusEffectManager", no_init)
				.def("AddStatusEffect", (void (StatusEffects::StatusEffectsManager::*)(StatusEffects::StatusEffect*, const int))&StatusEffects::StatusEffectsManager::AddStatusEffect)
				.def("AddStatusEffect", (void (StatusEffects::StatusEffectsManager::*)(StatusEffects::se_ptr, int))&StatusEffects::StatusEffectsManager::AddStatusEffect)
				.def("AddStatusEffect", (void (StatusEffects::StatusEffectsManager::*)(const std::string&, int))&StatusEffects::StatusEffectsManager::AddStatusEffect)
				.def("GetBaseResistance", &StatusEffects::StatusEffectsManager::GetBaseResistance)
				.def("GetNegativeStatusEffects", &StatusEffects::StatusEffectsManager::GetNegativeStatusEffects, boost::python::arg("SortyByPriority") = false)
				.def("GetPositiveStatusEffects", &StatusEffects::StatusEffectsManager::GetPositiveStatusEffects, boost::python::arg("SortyByPriority") = false)
				.def("GetStatusEffectsWithCallCondition", &StatusEffects::StatusEffectsManager::GetStatusEffectsWithCallCondition, return_value_policy<reference_existing_object>())
				.def("GetStatusResistance", (float (StatusEffects::StatusEffectsManager::*)(const StatusEffects::StatusEffect*) const)&StatusEffects::StatusEffectsManager::GetStatusResistance)
				.def("GetStatusResistance", (float (StatusEffects::StatusEffectsManager::*)(StatusEffects::se_ptr) const)&StatusEffects::StatusEffectsManager::GetStatusResistance)
				.def("GetStatusResistance", (float (StatusEffects::StatusEffectsManager::*)(const std::string&) const)&StatusEffects::StatusEffectsManager::GetStatusResistance)
				.def("IncrementStatusResistance", (void (StatusEffects::StatusEffectsManager::*)(const StatusEffects::StatusEffect*, const float))&StatusEffects::StatusEffectsManager::IncrementStatusResistance)
				.def("IncrementStatusResistance", (void (StatusEffects::StatusEffectsManager::*)(StatusEffects::se_ptr, const float))&StatusEffects::StatusEffectsManager::IncrementStatusResistance)
				.def("IncrementStatusResistance", (void (StatusEffects::StatusEffectsManager::*)(const std::string&, const float))&StatusEffects::StatusEffectsManager::IncrementStatusResistance)
				.def("IncrementBaseResistance", &StatusEffects::StatusEffectsManager::IncrementBaseResistance)
				.def("RemoveNegativeStatusEffects", &StatusEffects::StatusEffectsManager::RemoveNegativeStatusEffects, boost::python::arg("AtRandom") = false)
				.def("RemovePositiveStatusEffects", &StatusEffects::StatusEffectsManager::RemovePositiveStatusEffects, boost::python::arg("AtRandom") = false)
				.def("RemoveStatusEffect", &StatusEffects::StatusEffectsManager::RemoveStatusEffect)
				.def("RemoveStatusEffects", &StatusEffects::StatusEffectsManager::RemoveStatusEffects, boost::python::arg("AtRandom") = false)
				.def("SetBaseResistance", &StatusEffects::StatusEffectsManager::SetBaseResistance)
				//.def("", &StatusEffects::StatusEffectsManager::)
				//.def("", &StatusEffects::StatusEffectsManager:)
				;

			class_<StatusEffects::StatusEffectsLibrary, noncopyable>("StatusEffectsLibrary", no_init)

				.def("AddStatusEffect", &StatusEffects::StatusEffectsLibrary::AddStatusEffect)
				;

			class_<boost::unordered_map<std::string, float> >("StatusEffectWeightMap")
				.def(map_indexing_suite<boost::unordered_map<std::string, float> >())
				;

			class_<Components::ApplyEffectComponent, boost::shared_ptr<ApplyEffectWrap>, bases<Components::Component> >("ApplyEffectComponent", init<Entity*>())
				.def(init<const Components::ApplyEffectComponent&>())
				.def("Apply", &ApplyEffectWrap::ApplyDefault)
				.def("UnApply", &ApplyEffectWrap::UnApplyDefault)
				.def("Clone", &ApplyEffectWrap::CloneDefault)
				.def("__copy__", &generic__copy__<Components::ApplyEffectComponent>)
				.def("__deepcopy__", &generic__deepcopy__<Components::ApplyEffectComponent>)
				;
		}
	}
}
#endif