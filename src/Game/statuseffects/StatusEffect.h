#pragma once
#ifndef _STATUSEFFECT_H_
#include <Entity.h>
#include <Utilities/Cloneable.h>
#include <boost/unordered_set.hpp>
#include <boost/signals2.hpp>
#include <vector>
namespace Game
{
	namespace Character
	{
		class BaseCharacter;
	}
	enum CallCondition
	{
		PreUse,						//Used to apply any effects before move processing begins
		OutgoingAttack,				//Used to apply effects to an attack instigated by the effect holder
		PartyMemberOutgoingAttack,	//Used to apply effects to an attack instigated by a party member - need to check holder isn't a user
		FinalizingTargets,			//Used once the action has left the attackers effects stage, and when targets are being finalized. Used for things like reflect
		IncomingAttack,				//used to apply effects to an action targetted at the effect holder
		DeterminingCrit,
		DeterminingHit,
		PartyMemberIncomingAttack,	//Used to apply effects to an action targetted at (a) party member(s)
		ApplyingDamage,				//Used to adjust the final incoming damage
		DamageTaken,				//Used to apply effects to holder after taking damage (if they survive)
		DamageDealt,
		Apply,
		Tick,
		MPInspection,				//Used for MP One/MP Half
		SPInspection,			
	};
	
	

	namespace StatusEffects
	{
		class StatusEffect;
		typedef boost::signals2::signal<void (StatusEffects::StatusEffect*, const std::string&)> EffectActivatedSignal;
		class StatusEffect : public Entity
		{
		public:
			StatusEffect(Character::BaseCharacter * holder, const std::string& name, bool IsPos = false, const int priority = 0, const int RecommendedTickCount = 7, const std::vector<CallCondition>& conditions = std::vector<CallCondition>());
			StatusEffect(Character::BaseCharacter * holder, const std::string& name, const std::string& desc, bool IsPos = false, const int priority = 0, const int RecommendedTickCount = 7, const std::vector<CallCondition>& conditions = std::vector<CallCondition>());
			//StatusEffect(Character::BaseCharacter * holder, const std::string& name, bool IsPos = false, const int priority = 0, const int RecommendedTickCount = 7, const boost::unordered_set<CallCondition>& conditions = boost::unordered_set<CallCondition>());
			//StatusEffect(Character::BaseCharacter * holder, const std::string& name, bool IsPos = false, const int priority = 0, const int RecommendedTickCount = 7);
			StatusEffect(const StatusEffect& eff);
			int GetRemainingTicks() const;
			int GetPriority() const;
			int GetRecommendedTicks() const;
			virtual RawClonePtr RawClone() const override;
			bool IsPositive() const;
			const Character::BaseCharacter* GetHolder() const;
			void SetHolder(Character::BaseCharacter* holder);
			bool IsRefreshable() const;
			
			boost::signals2::connection AddEffectActivatedSignal(const EffectActivatedSignal::slot_type& event);
			boost::signals2::connection AddEffectDeactivatedSignal(const EffectActivatedSignal::slot_type& event);
			void DispatchActivatedSignal(const std::string& activationCondition);
			void DispatchDeactivatedSignal(const std::string& deactivatedCondition);

			void AddCallCondition(const CallCondition condition);
			bool HasCondition(const CallCondition condition) const;
			bool RemoveCondition(const CallCondition condition);

			const std::string& GetDescription() const;

			StatusEffect& operator=(const StatusEffect& eff);
			bool operator==(const StatusEffect& eff);
			bool operator!=(const StatusEffect& eff);
		protected:
			void SetDescription(const std::string& desc);

			void SetRemainingTicks(const int ticks);
			void SetIsPositive(const bool pos);
			
			void SetPriority(const int prior);
			void SetRefreshable(const bool val);

		private:
			std::string Description;
			EffectActivatedSignal EffectSignal;
			EffectActivatedSignal EffectDeactivatedSignal;
			bool NetPositive;
			bool Refreshable;
			int RemainingTicks;
			int RecommendedTicks;
			int Priority;
			boost::unordered_set<CallCondition> CallConditions;
			Character::BaseCharacter* Holder;
			friend class Character::BaseCharacter;
			friend class StatusEffectsManager;
		};
		typedef boost::shared_ptr<StatusEffect> se_ptr;
	}

}
#endif