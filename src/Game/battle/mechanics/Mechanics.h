#pragma once
#ifndef _MECHANICS_H_
#define _MECHANICS_H_
#include <cmath>
#include <ctime>
#include <deque>
#include <components/Component.h>
#include <statuseffects/StatusEffect.h>
#include <battle/BattleCharacterComponent.h>
#include <boost/random.hpp>
#include <actions/Action.h>
//#include "BattleField.h"
namespace Game
{
	namespace Actions
	{
		class Action;
	}
	namespace Character
	{
		class BaseCharacter;
	}
	/*namespace StatusEffects
	{
		class StatusEffect;
	}*/
	namespace Battle
	{
		//Index String
		const std::string OutgoingAttackIndexer = "OutgoingActionModifier";
		const std::string FinalizeTargettingIndexer = "FinalizeTargetsModifier";
		const std::string IncomingAttackIndexer = "IncomingAttackModifier";
		const std::string DamageFinalizerIndex = "DamageModifier";
		const std::string DamageCalculationIndex = "DamageCalculatorComponent";
		const std::string PreUseIndex = "PreUseComponent";
		const std::string PostUseIndex = "PostUseComponent";
		const std::string UseIndex = "UseComponent";
		const std::string HitIndex = "HitComponent";
		const std::string CriticalHitIndex = "CriticalHitComponent";
		const std::string StatExtractionIndex = "StatExtractionComponent";
		const std::string ElementalWeightIndex = "ElementalWeightComponent";
		const std::string CharacterElementalEffectivenessIndex = "ElementEffectivenessComponent";
		const std::string DamageSplitIndex = "DamageSplitComponent";
		//Flag Strings
		const std::string AlwaysHitFlag = "AlwaysHit";
		const std::string NeverMissFlag = "NeverMiss";
		const std::string NoCritsFlag = "NoCrits";
		const std::string AlwaysCritsFlag = "AlwaysCrits";
		const std::string IgnoreElementsFlag = "IgnoreElements";
		class BattleField;
		class TurnGenerator;

		//typedef boost::function<void (Character::BaseCharacter*, BattleCharacterComponent*, bool)> CharacterTurnStartSignal; //bool = AI controled
		//typedef boost::function<void (Character::BaseCharacter*, BattleCharacterComponent*, bool)> CharacterTurnEndSignal; //bool = AI controled

		class Mechanics : public Components::Component
		{
		public:
			Mechanics(BattleField* owner, unsigned int RandomSeed = static_cast<unsigned int>(std::time(0)));

			virtual void Init();

			virtual bool ApplyStatusEffect(Character::BaseCharacter& target, const std::string& se, int turns, float seApplyRate = 1.0f);

			virtual void ProcessActionDefault(Actions::Action& action, bool InBattle = true);

			//virtual void ProcessAction(Actions::Action& action, bool InBattle = true);

			virtual void PreUsePhase(Actions::Action& action, bool InBattle = true);

			virtual void PostUsePhase(Actions::Action& action, bool InBattle = true);

			virtual void ActionStatKeeper(boost::shared_ptr<Actions::Action> action);

			virtual void UsePhase(Actions::Action& action, bool InBattle = true);

			virtual bool IsHit(Character::BaseCharacter& target, Actions::Action& action);

			virtual bool ApplyHitFormula(Character::BaseCharacter& target, Actions::Action& action);

			virtual bool IsCritical(Character::BaseCharacter& target, Actions::Action& action);

			virtual bool ApplyCriticalFormula(Character::BaseCharacter& target, Actions::Action& action);

			virtual int CalculateDamage(Character::BaseCharacter& target, Actions::Action& action);

			virtual int ApplyDamageFormula(Character::BaseCharacter& target, Actions::Action& action);

			virtual void ReadyCharacter(Character::BaseCharacter& character, BattleCharacterComponent& battlecharactercomponent, BattleField& field);

			virtual std::vector<StatusEffects::StatusEffect*> GetEffectsWithCallCondition(CallCondition cc, std::vector<Actions::ActionUserTarget>& characters, bool IncludeSE = true, bool IncludeAbil = true);

			virtual std::vector<StatusEffects::StatusEffect*> GetEffectsWithCallCondition(CallCondition cc, std::vector<Character::BaseCharacter*>& characters, bool IncludeSE = true, bool IncludeAbil = true);

			virtual std::vector<StatusEffects::StatusEffect*> GetEffectsWithCallCondition(CallCondition cc, boost::unordered_map<std::string, Actions::ActionUserTarget>& characters, bool IncludeSE = true, bool IncludeAbil = true);

			virtual int GenerateInt(const int min, const int max, float bias = 1.0f);

			virtual float GenerateFloat(const float min, const float max, float bias = 1.0f);

			virtual float DetermineElementalMultiplier(Character::BaseCharacter& character, Actions::Action& action);

			virtual float DetermineDamageSplit(Actions::Action& action, int TargetCount = 1, bool inBattle = true);

			bool AreRandomsEnabled() const;

			void SetRandomEnabled(const bool Enabled = true);

			virtual void EnforceActionCosts(Character::BaseCharacter& user, const Actions::Action& action);
			
			virtual int EnforceCalculatedDamage(Character::BaseCharacter& target, const Actions::Action& action, int calculatedDamage);

			BattleField* GetField() const;

			virtual RawClonePtr RawClone() const override;

			virtual int PhysicalDamageForumla(Actions::Action& action, Character::BaseCharacter& character, const int AtkStat, const int DefStat, const int AtkRating, const int ArmorRating);

			virtual int MagicDamageForumla(Actions::Action& action, Character::BaseCharacter& character, const int AtkStat, const int DefStat, const int AtkRating, const int ArmorRating);

			const Actions::Action* GetActionInProgress() const
			{
				return ActionInProgress;
			}

			virtual void StartCharacterTurn(Character::BaseCharacter& character, BattleCharacterComponent& bcharacter);

			virtual void EndCharacterTurn(Character::BaseCharacter& character, BattleCharacterComponent& bcharacter);

			void AddTurnStartEventHandler(const std::string& name, const CharacterTurnStartSignal& turnHandler);

			bool RemoveTurnStartEventHandler(const std::string& name);

			void DispatchTurnStartEvents(Character::BaseCharacter& character, BattleCharacterComponent& bcharacter, bool aiControlled);

			void AddTurnEndEventHandler(const std::string& name, const CharacterTurnEndSignal& turnHandler);

			bool RemoveTurnEndEventHandler(const std::string& name);

			void DispatchTurnEndEvents(Character::BaseCharacter& character, BattleCharacterComponent& bcharacter, bool aiControlled);

			//Targetting Functions
			
		protected:
			Actions::Action* ActionInProgress;
		private:
			boost::unordered_map<std::string, CharacterTurnStartSignal> TurnStartSignals;
			boost::unordered_map<std::string, CharacterTurnEndSignal> TurnEndSignals;


			bool RandomsEnabled;
			boost::random::mt19937 RNG;
			//boost::uniform_real<> RNGRealDefault;
			BattleField* Field;
			std::deque<Actions::action_ptr> QueuedActions;
		};
		/*namespace Mechanics
		{
			class Mechanics_
			{
			public:

				int BasicPhysicalDamageCalc(const int atkStat, const int defStat, const int atkStr, const int atkReg)
				{
					double Dmg1 = (((atkStat * atkStat * atkStat) / 44) + 32) * (atkStr / atkReg);
					double Def1 = ((defStat - 1000.4) * (defStat - 1000.4)) / 110 + 16;
					double Dmg2 = (pow((Dmg1 * Def1) / 3800.0), (7.0 / 9.0)) + 100 (atkStat / defStat);
					double Dmg3 = (pow(Dmg2), (5.0 / 6.0)) * 2.1;
					return static_cast<int>(Dmg3);
					/*
					Dmg1 = (((AtkStat) ^ 3 / 32) + 32) * (16 / 16)
					Def1 = (((DefStat - 1000.4) ^ 2) / 110) + 16
					Dmg2 = ((Dmg1 * Def1) / 3800) ^ (7 / 9) + 100 * (AtkStat / DefStat)
					Dmg3 = ((DefStat)) ^ 2 / AtkStat
					If (Dmg3 > Dmg2) Then
					Dmg3 = 0
					End If
					Dmg4 = Dmg2 - Dmg3
					
				}
			protected:
			private:
			};
		}*/
	}
}

#endif