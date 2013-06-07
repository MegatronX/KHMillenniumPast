#pragma once

#include <character/BaseCharacter.h>
#include <character/StatsManager.h>
#include <character/PlayerParty.h>
#include <character/CharacterDatabase.h>
#include <character/CharacterSpawner.h>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
using namespace Game::Character;
using namespace boost::python;
namespace Game
{
	namespace Scripting
	{
		class CharacterEntryWrap : public CharacterEntry
		{
		public:
			CharacterEntryWrap(PyObject* obj) : self(obj)
			{

			}
			
			CharacterEntryWrap(PyObject* obj, const CharacterEntryWrap& cp) : self(obj), CharacterEntry(cp)
			{

			}
			CharacterEntryWrap(PyObject* obj, const CharacterEntry& cp) : self(obj), CharacterEntry(cp)
			{

			}
			virtual boost::shared_ptr<BaseCharacter> GetAtLevel(const int lv) override
			{
				return call_method<boost::shared_ptr<BaseCharacter>>(self, "GetAtLevel", lv);// this->get_override("GetAtLevel")(lv, boost::ref(valid));
				//return boost::shared_ptr<BaseCharacter>(new BaseCharacter());
			}
			boost::shared_ptr<BaseCharacter> GetAtLevelDefault(const int lv)
			{
				//return this->get_override("GetAtLevel")(lv, boost::ref(valid));
				return CharacterEntry::GetAtLevel(lv);//boost::shared_ptr<BaseCharacter>(new BaseCharacter());
			}
			virtual bool ValidForLevel(const int lv) override
			{
				return call_method<bool>(self, "ValidForLevel", lv);//call_method<bool>(self, "ValidForLevel", lv);
			}
			virtual bool ValidForLevelDefault(const int lv)
			{
				return CharacterEntry::ValidForLevel(lv);
			}
			PyObject* self;
		private:
		};

		/*class CharacterEntryWrap : public CharacterEntry, public wrapper<CharacterEntry>
		{
		public:
			
			virtual boost::shared_ptr<BaseCharacter> GetAtLevel(const int lv, bool& valid) override
			{
				//return this->get_override("GetAtLevel")(lv, boost::ref(valid));
				return boost::shared_ptr<BaseCharacter>(new BaseCharacter());
			}
			boost::shared_ptr<BaseCharacter> GetAtLevelDefault(const int lv, bool& valid)
			{
				//return this->get_override("GetAtLevel")(lv, boost::ref(valid));
				return CharacterEntry::GetAtLevel(lv, valid);//boost::shared_ptr<BaseCharacter>(new BaseCharacter());
			}
			virtual bool ValidForLevel(const int lv) override
			{
				return this->get_override("ValidForLevel")(lv);//call_method<bool>(self, "ValidForLevel", lv);
			}
			virtual bool ValidForLevelDefault(const int lv)
			{
				return CharacterEntry::ValidForLevel(lv);
			}
		private:
		};*/

		BOOST_PYTHON_MODULE(CharacterModule)
		{
			enum_<Stat>("Stat")
				.value("Accuracy", Stat::Accuracy)
				.value("MgAccuracy", Stat::MgAccuracy)
				.value("Agility", Stat::Agility)
				.value("Defense", Stat::Defense)
				.value("Evasion", Stat::Evasion)
				.value("HP", Stat::HP)
				.value("Luck", Stat::Luck)
				.value("Magic", Stat::Magic)
				.value("MgEvasion", Stat::MgEvasion)
				.value("MP", Stat::MP)
				.value("Skill", Stat::Skill)
				.value("SP", Stat::SP)
				.value("Speed", Stat::Speed)
				.value("Spirit", Stat::Spirit)
				.value("MgDefense", Stat::MgDefense)
				.value("Strength", Stat::Strength)
				.value("Vitality", Stat::Vitality)
				;
			enum_<CharacterStatus>("CharacterStatus")
				.value("Normal", CharacterStatus::Normal)
				.value("Preview", CharacterStatus::Preview)
				;

			class_<boost::unordered_map<Stat, int> >("StatMap")
				.def(map_indexing_suite<boost::unordered_map<Stat, int>>())
				;
			/*class_<map<Stat, int> >("OrderedStatMap")
				.def(map_indexing_suite<std::map<Stat, int>>())
				;*/
			class_<CharacterEntry, boost::shared_ptr<CharacterEntryWrap> >("CharacterEntry", init<>())
				.def(init<const CharacterEntryWrap&>())
				.def(init<const CharacterEntry&>())
				.def("GetAtLevel", &CharacterEntryWrap::GetAtLevelDefault)
				.def("ValidForLevel", &CharacterEntryWrap::ValidForLevelDefault)
				;
			class_<CharacterDatabase, boost::noncopyable>("CharacterDatabase", no_init)
				.def("AddCharacterEntry", &CharacterDatabase::AddCharacterEntry)
				.def("GetEnemy", &CharacterDatabase::GetCharacter)
				.def("GetEntry", &CharacterDatabase::GetEntry)
				;
			class_<Character::BaseCharacter, boost::shared_ptr<Character::BaseCharacter>, bases<Entity> >("BaseCharacter", init<>())
				.def(init<const std::string&>())
				//.def(init<const std::string&, int[Character::StatCount]>())
				.def(init<const std::string&, std::vector<int>&>())
				.def(init<const std::string&, std::map<Stat, int>&>())
				.def(init<const std::string&, boost::unordered_map<Stat, int>&>())
				.def("GetStatsManager", &Character::BaseCharacter::GetStatsManager, return_value_policy<reference_existing_object>())
				.def("GetStatusEffectsManager", &Character::BaseCharacter::GetStatusEffectsManager, return_value_policy<reference_existing_object>())
				.def("GetAbilityManager", &Character::BaseCharacter::GetAbilityManager, return_value_policy<reference_existing_object>())
				.def("GetLevel", &Character::BaseCharacter::GetLevel)
				.def("__eq__", &Character::BaseCharacter::operator==)
				.def("__neq__", &Character::BaseCharacter::operator!=)
				//.def("__copy__", &generic__copy__<StatusEffectWrap>)
				//.def("__deepcopy__", &generic__deepcopy__<StatusEffectWrap>)
				//.def("GetCombinedStat", &Character::BaseCharacter::GetCombinedStat)
				//.def("GetLevel", &Character::BaseCharacter::GetLevel)
				//.def("GetName", &Character::BaseCharacter::GetName, return_value_policy<reference_existing_object>())
				//.def("GetStatus", &Character::BaseCharacter::GetStatus)
				;
			//bool (Components::Component::*IsType1)(const std::string&) = &Components::Component::IsType;
			//bool (Components::Component::*IsType2)(int) = &Components::Component::IsType;

			void (Character::StatsManager::*Sync1)(const Stat stat, bool dispatch) = &Character::StatsManager::SyncStat;
			void (Character::StatsManager::*Sync2)(const int stat, bool dispatch) = &Character::StatsManager::SyncStat;
			void (Character::StatsManager::*Sync3)(const Stat stat, bool SyncBase, bool dispatch) = &Character::StatsManager::SyncBattleStat;
			void (Character::StatsManager::*Sync4)(const int stat, bool, bool dispatch) = &Character::StatsManager::SyncBattleStat;
			class_<Character::StatsManager, boost::shared_ptr<Character::StatsManager>, bases<Components::Component>, boost::noncopyable >("StatsManager", no_init)
				.def("GetBaseStat", &Character::StatsManager::GetBaseStat, (boost::python::arg("IgnoreLimits") = false))
				.def("GetAbilityAdder", &Character::StatsManager::GetAbilityStatAdder)
				.def("GetAbilityStatMultiplier", &Character::StatsManager::GetAbilityStatMultiplier)
				.def("GetAdditionalStatAdder", &Character::StatsManager::GetAdditionalStatAdder)
				.def("GetAdditionalStatMultiplier", &Character::StatsManager::GetAdditionalStatMultiplier)
				.def("GetBattleStat", &Character::StatsManager::GetBattleStat, (boost::python::arg("IgnoreLimits") = false))
				.def("GetPermanentStatBoost", &Character::StatsManager::GetPermanentStatBoost)
				.def("GetPermanentStatMultiplier", &Character::StatsManager::GetPermanentStatMultiplier)
				.def("GetStatusEffectStatAdder", &Character::StatsManager::GetStatusEffectStatAdder)
				.def("GetStatusEffectStatMultiplier", &Character::StatsManager::GetStatusEffectStatMultiplier)
				.def("GetCurrentHP", &Character::StatsManager::GetCurrentHP)
				.def("SetCurrentHP", &Character::StatsManager::SetCurrentHP, (boost::python::arg("inBattle") = true))
				.def("IncrementCurrentHP", &Character::StatsManager::IncrementCurrentHP, (boost::python::arg("inBattle") = true, boost::python::arg("dispatch") = true))
				.def("GetCurrentMP", &Character::StatsManager::GetCurrentMP)
				.def("SetCurrentMP", &Character::StatsManager::SetCurrentMP, (boost::python::arg("inBattle") = true, boost::python::arg("dispatch") = true))
				.def("IncrementCurrentMP", &Character::StatsManager::IncrementCurrentMP, (boost::python::arg("inBattle") = true, boost::python::arg("dispatch") = true))
				.def("GetCurrentSP", &Character::StatsManager::GetCurrentSP)
				.def("SetCurrentSP", &Character::StatsManager::SetCurrentSP, (boost::python::arg("inBattle") = true, boost::python::arg("dispatch") = true))
				.def("IncrementCurrentSP", &Character::StatsManager::IncrementCurrentSP, (boost::python::arg("inBattle") = true, boost::python::arg("dispatch") = true))
				.def("IncrementAbilityStatAdder", &Character::StatsManager::IncrementAbilityStatAdder, (boost::python::arg("sync") = true, boost::python::arg("dispatch") = true))
				.def("IncrementAbilityStatMultiplier", &Character::StatsManager::IncrementAbilityStatMultiplier, (boost::python::arg("sync") = true, boost::python::arg("dispatch") = true))
				.def("IncrementAdditionalStatAdder", &Character::StatsManager::IncrementAdditionalStatAdder, (boost::python::arg("sync") = true, boost::python::arg("dispatch") = true))
				.def("IncrementAdditionalStatMultiplier", &Character::StatsManager::IncrementAdditionalStatMultiplier, (boost::python::arg("sync") = true, boost::python::arg("dispatch") = true))
				.def("IncrementStatusEffectStatAdder", &Character::StatsManager::IncrementStatusEffectStatAdder, (boost::python::arg("sync") = true, boost::python::arg("dispatch") = true))
				.def("IncrementStatusEffectStatMultiplier", &Character::StatsManager::IncrementStatusEffectStatMultiplier, (boost::python::arg("sync") = true, boost::python::arg("dispatch") = true))
				.def("SyncAllStats", &Character::StatsManager::SyncAllStats, boost::python::arg("dispatch") = true)
				.def("SyncAllBattleStats", &Character::StatsManager::SyncAllBattleStats, boost::python::arg("dispatch") = true)
				.def("AddStatChangeHandler", &Character::StatsManager::AddStatChangeHandler)
				.def("RemoveStateChangeHandler", &Character::StatsManager::RemoveStatChangeHandler)
				.def("DispatchStatChangeEvents", &Character::StatsManager::DispatchStatChangeEvents)
				.def("SyncStat", Sync1)
				.def("SyncStat", Sync2)
				.def("SyncBattleStat", Sync3, (boost::python::arg("SyncBase") = false))
				.def("SyncBattleStat", Sync4, (boost::python::arg("SyncBase") = false))
				;

			/*class_<boost::unordered_map<std::string, BaseParty::MemberPtr> >("BasePartyMemberMap")
				.def(map_indexing_suite<boost::unordered_map<std::string, BaseParty::MemberPtr> >())
				;*/


			/*class_<boost::unordered_map<std::string, boost::shared_ptr<int> > >("BasePartyMemberMap")
				.def(map_indexing_suite<boost::unordered_map<std::string, boost::shared_ptr<int> > >())
				;*/

			class_<std::map<std::string, boost::shared_ptr<Character::BaseCharacter> > >("BasePartyMemberMap")
				.def(map_indexing_suite<std::map<std::string, boost::shared_ptr<Character::BaseCharacter> > >())
				;

			class_<std::vector<int> > ("StatList")
				.def(vector_indexing_suite<std::vector<int> >())
				;

			class_<std::vector<boost::shared_ptr<BaseCharacter> > > ("CharacterList")
				.def(vector_indexing_suite<std::vector<boost::shared_ptr<BaseCharacter> >, true >())
				;

			class_<BaseParty, bases<Entity> >("BaseParty", init<const std::string&>())
				.def("AddMember", &BaseParty::AddMember)
				.def("RemoveMemberByName", &BaseParty::RemoveMemberByName)
				.def("removeMemberByMemberPtr", &BaseParty::RemoveMemberByMemberPtr)
				.def("GetRawPartyMembers", &BaseParty::GetRawPartyMembers)
				.def("GetPartyMembers", &BaseParty::GetPartyMembers, return_value_policy<reference_existing_object>())
				.def("GetPartyMembersInOrder", &BaseParty::GetPartyMembersInOrder, return_value_policy<reference_existing_object>())
				.def("GetPartyMember", &BaseParty::GetPartyMember)
				;
			
			class_<PlayerParty, bases<BaseParty> >("PlayerParty")
				.def("AddCharacter", &PlayerParty::AddCharacter)
				.def("RemoveCharacter", &PlayerParty::RemoveCharacter)
				.def("GetPlayerCharacterParty", &PlayerParty::GetPlayerCharacterParty)
				.def("GetInventory", &PlayerParty::GetInventory, return_value_policy<reference_existing_object>())
				;

			class_<EntryID>("EntryID", init<>())
				.def(init<const std::string&, const int>())
				.def("__eq__", &EntryID::operator==)
				.def("__neq__", &EntryID::operator!=)
				.def_readwrite("Name", &EntryID::Name)
				.def_readwrite("Level", &EntryID::Level)
				;

			class_<boost::unordered_map<EntryID, int> >("SpawnMap")
				.def(map_indexing_suite<boost::unordered_map<EntryID, int> >())
				;

			class_<Character::CharacterSpawner, boost::shared_ptr<Character::CharacterSpawner>, bases<Components::Component> >("CharacterSpawner", init<Entity*>())
				;
			/*class_<PartyInterface<BaseCharacter>, bases<Entity> > ("PlayerPartyInterface")
				.def("GetPartyMembers", &PartyInterface<BaseCharacter>::GetPartyMembers, return_value_policy<reference_existing_object>())
				;*/
			//class_<Character::PlayerParty, bases
		}

	}
};
