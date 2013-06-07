#include "BaseMechanics.h"
#include <algorithm>
#include <actions/Action.h>
#include <actions/ActionModifierComponent.h>
#include <character/BaseCharacter.h>
#include <battle/BattleField.h>
#include <abilities/AbilityManager.h>
#include <battle/BattleCharacterComponent.h>
#include <battle/BattleParty.h>
#include <character/Party.h>
namespace Game
{
	namespace Battle
	{
		BaseMechanics::BaseMechanics(BattleField* owner) : Mechanics(owner)
		{

		}
		bool BaseMechanics::ApplyStatusEffect(Character::BaseCharacter& target, const std::string& se, int turns, float seApplyRate)
		{
			bool Applied = false;
			auto seCmp = target.GetComponentAs<StatusEffects::StatusEffectsManager*>("StatusEffectManager");
			float Resistance = 0.f;
			if (seCmp != nullptr)
			{
				Resistance = seCmp->GetStatusResistance(se);
			}
			float effectiveChance = seApplyRate - Resistance;
			if (effectiveChance > 0.f)
			{
				if (effectiveChance >= (1.0f - GenerateFloat(0.f, 1.0f)))
				{
					Applied = true;
					seCmp->AddStatusEffect(se, turns);
				}	
			}
			return Applied;
		}
		void BaseMechanics::ProcessAction(Actions::Action& action)
		{
			std::vector<Character::BaseCharacter*> characters;
			//Stage 1: PreUse
			//auto pUse = action.GetComponentAs<PreUseComponent>("PreUse");
			//if (pUse != nullptr)
			//	pUse->PreUse(this);
			if (!action.IgnoreUserSE && !action.IgnoreUserAbil)
			{
				auto SEAbils = GetEffectsWithCallCondition(PreUse, action.Users.GetGroup(), !action.IgnoreUserSE, !action.IgnoreUserAbil);
				auto SEAbilDef = GetEffectsWithCallCondition(PreUse, action.Targets.GetGroup(), !action.IgnoreTargetSE, !action.IgnoreTargetAbil);
				bool cont = true;
				for (auto it = SEAbils.begin(); it != SEAbils.end() && cont; ++it)
				{
					auto puseCmp = (*it)->GetComponentAs<Actions::ActionModifierComponent*>("PreUse");
					if (puseCmp != nullptr)
					{
						cont = puseCmp->ModifyAction(action, *this);
					}
				}

				//Stage 2: Attacker Setup
				//2.1 Action Users outgoing action modifiers
				SEAbils = GetEffectsWithCallCondition(OutgoingAttack, action.Users.GetGroup());
				cont = true;
				for (auto it = SEAbils.begin(); it != SEAbils.end() && cont; ++it)
				{
					auto puseCmp = (*it)->GetComponentAs<Actions::ActionModifierComponent*>("OutgoingAttack");
					if (puseCmp != nullptr)
					{
						cont = puseCmp->ModifyAction(action, *this);
					}
				}
				//2.2 Action Users party members outgoing action modifiers
				characters.clear();
				if (action.Users.GetGroup().size() > 1)
				{

					std::unordered_set<Character::BaseCharacter*> PartyMembers;
					for (auto it = action.Users.GetGroup().begin(); it != action.Users.GetGroup().end(); ++it)
					{
						auto btlChr = (*it).second.AttachedCharacter->GetComponentAs<BattleCharacterComponent*>("BattleCharacterComponent");
						if (btlChr != nullptr)
						{
							auto party = btlChr->GetBaseParty();
							auto vec = party->GetRawPartyMembers();
							PartyMembers.insert(vec.begin(), vec.end());
						}
					}
					characters.insert(characters.end(), PartyMembers.begin(), PartyMembers.end());
				}
				else
				{
					auto btlChr = (*action.Users.GetGroup().begin()).second.AttachedCharacter->GetComponentAs<BattleCharacterComponent*>("BattleCharacterComponent");
					if (btlChr != nullptr)
					{
						auto party = btlChr->GetBaseParty();
						auto vec = party->GetRawPartyMembers();
						characters.insert(characters.end(), vec.begin(), vec.end());
					}

				}
				//Users can't be part of party member has outgoing action group. Remove users from party list
				for (auto it = action.Users.GetGroup().begin(); it != action.Users.GetGroup().end(); ++it)
				{
					for (auto next = characters.begin(); next != characters.end();)
					{

						if ((*(*next)) == ((*(*it).second.AttachedCharacter)))
						{
							next = characters.erase(next);
						}
						else
						{
							++next;
						}
					}
				}
				//No party member should have preference over another, shuffle them
				if (characters.size() > 1)
					std::random_shuffle(characters.begin(), characters.end());
				SEAbils = GetEffectsWithCallCondition(PartyMemberOutgoingAttack, characters, !action.IgnoreUserSE, !action.IgnoreUserAbil);
				cont = true;
				for (auto it = SEAbils.begin(); it != SEAbils.end() && cont; ++it)
				{
					auto puseCmp = (*it)->GetComponentAs<Actions::ActionModifierComponent*>("PartyMemberHadOutgoingAttack");
					if (puseCmp != nullptr)
					{
						cont = puseCmp->ModifyAction(action, *this);
					}
				}
			}
			//Stage 3: Deciding Targets
			auto SEAbils = GetEffectsWithCallCondition(FinalizingTargets, action.Users.GetGroup(), !action.IgnoreUserSE, !action.IgnoreUserAbil);
			auto SEAbilDef = GetEffectsWithCallCondition(FinalizingTargets, action.Targets.GetGroup(), !action.IgnoreTargetSE, !action.IgnoreTargetAbil);
			bool cont = true;
			for (auto it = SEAbils.begin(); it != SEAbils.end() && cont; ++it)
			{
				auto puseCmp = (*it)->GetComponentAs<Actions::ActionModifierComponent*>("FinalizingTargets");
				if (puseCmp != nullptr)
				{
					cont = puseCmp->ModifyAction(action, *this);
				}
			}
			//Stage 4: Split Action into Action/Target Pairs

			//Stage 5: Party Memeber has Incoming Attack

			//Stage 6: Target Has Incoming Attack

			//Stage 7: Usage


			//Stage 8: Post Usage


			/*for (auto it = SEAbils.begin(), it != SEAbils.end(), ++it)
			{
			}
			for (auto it = SEAbils.begin(), it != SEAbils.end(), ++it)
			{
			}
			for (auto it = SEAbils.begin(), it != SEAbils.end(), ++it)
			{
			}
			for (auto it = SEAbils.begin(), it != SEAbils.end(), ++it)
			{
			}
			for (auto it = SEAbils.begin(), it != SEAbils.end(), ++it)
			{
			}*/
		}
		std::vector<StatusEffects::StatusEffect*> BaseMechanics::GetEffectsWithCallCondition(CallCondition cc, std::vector<Character::BaseCharacter*>& characters, bool IncludeSE, bool IncludeAbil)
		{
			std::vector<StatusEffects::StatusEffect*> ineffect;
			ineffect.reserve(characters.size() * 2);
			for(auto it = characters.begin(); it != characters.end(); ++it)
			{
				if (IncludeSE)
				{
					auto SEMng = (*it)->GetStatusEffectsManager();
					if (SEMng != nullptr)
					{
						auto SEs = SEMng.GetStatusEffectsWithCallCondition(cc, false);
						if (SEs.size() > 0)
						{
							ineffect.insert(ineffect.end(), SEs.begin(), SEs.end());
						}
					}
				}
				if (IncludeAbil)
				{
					auto AbilMng = (*it)->GetComponentAs<Abilities::AbilityManager*>("AbilityManager");
					if (AbilMng != nullptr)
					{
						auto Abils = AbilMng->GetAbilitiesWithCallCondition(cc, false);
						if (Abils.size() > 0)
						{
							ineffect.insert(ineffect.end(), Abils.begin(), Abils.end());
						}
					}
				}

			}
			std::sort(ineffect.begin(), ineffect.end(), [](const StatusEffects::StatusEffect* a, const StatusEffects::StatusEffect* b) -> bool { return a->GetPriority() > b->GetPriority(); }); 
			return ineffect;
		}
		std::vector<StatusEffects::StatusEffect*> BaseMechanics::GetEffectsWithCallCondition(CallCondition cc, std::vector<Actions::ActionUserTarget>& characters, bool IncludeSE, bool IncludeAbil)
		{
			std::vector<StatusEffects::StatusEffect*> ineffect;
			ineffect.reserve(characters.size() * 2);
			for(auto it = characters.begin(); it != characters.end(); ++it)
			{
				std::vector<StatusEffects::StatusEffect*> ineffect;
				if (IncludeSE)
				{
					auto SEMng = (*it).AttachedCharacter->GetComponentAs<StatusEffects::StatusEffectsManager*>("StatusEffectManager");
					if (SEMng != nullptr)
					{
						auto SEs = SEMng->GetStatusEffectsWithCallCondition(cc, false);
						if (SEs.size() > 0)
						{
							ineffect.insert(ineffect.end(), SEs.begin(), SEs.end());
						}
					}
				}
				if (IncludeAbil)
				{
					auto AbilMng = (*it).AttachedCharacter->GetComponentAs<Abilities::AbilityManager*>("AbilityManager");
					if (AbilMng != nullptr)
					{
						auto Abils = AbilMng->GetAbilitiesWithCallCondition(cc, false);
						if (Abils.size() > 0)
						{
							ineffect.insert(ineffect.end(), Abils.begin(), Abils.end());
						}
					}
				}

			}
			std::sort(ineffect.begin(), ineffect.end(), [](const StatusEffects::StatusEffect* a, const StatusEffects::StatusEffect* b) -> bool { return a->GetPriority() > b->GetPriority(); }); 
			return ineffect;
		}

		std::vector<StatusEffects::StatusEffect*> BaseMechanics::GetEffectsWithCallCondition(CallCondition cc, boost::unordered_map<std::string, Actions::ActionUserTarget>& characters, bool IncludeSE, bool IncludeAbil)
		{
			std::vector<StatusEffects::StatusEffect*> ineffect;
			ineffect.reserve(characters.size() * 2);
			for(auto it = characters.begin(); it != characters.end(); ++it)
			{
				auto name = it->second.AttachedCharacter->GetName();
				if (IncludeSE)
				{
					auto SEMng = (*it).second.AttachedCharacter->GetComponentAs<StatusEffects::StatusEffectsManager*>("StatusEffectsManager");
					if (SEMng != nullptr)
					{
						auto SEs = SEMng->GetStatusEffectsWithCallCondition(cc, false);
						if (SEs.size() > 0)
						{
							ineffect.insert(ineffect.end(), SEs.begin(), SEs.end());
						}
					}
				}
				if (IncludeAbil)
				{
					auto AbilMng = (*it).second.AttachedCharacter->GetComponentAs<Abilities::AbilityManager*>("AbilityManager");
					if (AbilMng != nullptr)
					{
						auto Abils = AbilMng->GetAbilitiesWithCallCondition(cc, false);
						if (Abils.size() > 0)
						{
							ineffect.insert(ineffect.end(), Abils.begin(), Abils.end());
						}
					}
				}

			}
			std::sort(ineffect.begin(), ineffect.end(), [](const StatusEffects::StatusEffect* a, const StatusEffects::StatusEffect* b) -> bool { return a->GetPriority() > b->GetPriority(); }); 
			return ineffect;
		}

		/*
		std::vector<StatusEffects::StatusEffect*> BaseMechanics::GetEffectsWithCallCondition(CallCondition cc, std::vector<Actions::ActionUserTarget>& characters, bool IncludeSE, bool IncludeAbil)
		{
			std::vector<StatusEffects::StatusEffect*> ineffect;
			ineffect.reserve(characters.size() * 2);
			for(auto it = characters.begin(); it != characters.end(); ++it)
			{
				std::vector<StatusEffects::StatusEffect*> ineffect;
				if (IncludeSE)
				{
					auto SEMng = (*it).AttachedCharacter->GetComponentAs<StatusEffects::StatusEffectsManager*>("StatusEffectManager");
					if (SEMng != nullptr)
					{
						auto SEs = SEMng->GetStatusEffectsWithCallCondition(cc, false);
						if (SEs.size() > 0)
						{
							ineffect.insert(ineffect.end(), SEs.begin(), SEs.end());
						}
					}
				}
				if (IncludeAbil)
				{
					auto AbilMng = (*it).AttachedCharacter->GetComponentAs<Abilities::AbilityManager*>("AbilityManager");
					if (AbilMng != nullptr)
					{
						auto Abils = AbilMng->GetAbilitiesWithCallCondition(cc, false);
						if (Abils.size() > 0)
						{
							ineffect.insert(ineffect.end(), Abils.begin(), Abils.end());
						}
					}
				}

			}
			std::sort(ineffect.begin(), ineffect.end(), [](const StatusEffects::StatusEffect* a, const StatusEffects::StatusEffect* b) -> bool { return a->GetPriority() > b->GetPriority(); }); 
			return ineffect;
		}
		*/
		/*bool BaseMechanics::IsCritical(Character::BaseCharacter& target, Actions::Action& action)
		{
			bool Critical = false;
			return Critical;

		}
		bool BaseMechanics::IsHit(Character::BaseCharacter& target, Actions::Action& action)
		{
			bool Hit = false;
			Hit = true;
			return Hit;
		}*/
	}
}