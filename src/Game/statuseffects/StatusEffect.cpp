#include "StatusEffect.h"

namespace Game
{
	namespace StatusEffects
	{

		StatusEffect::StatusEffect(Character::BaseCharacter * holder, const std::string& name, bool IsPos, const int priority, const int TickCount, const std::vector<CallCondition>& conditions) : Holder(holder), RecommendedTicks(TickCount), NetPositive(IsPos), Priority(priority), CallConditions(conditions.begin(), conditions.end()), Entity(name, Entity::StringHasher("StatusEffect"))
		{

		}
		StatusEffect::StatusEffect(Character::BaseCharacter * holder, const std::string& name, const std::string& desc, bool IsPos, const int priority, const int TickCount, const std::vector<CallCondition>& conditions) : Holder(holder), Description(desc), RecommendedTicks(TickCount), NetPositive(IsPos), Priority(priority), CallConditions(conditions.begin(), conditions.end()), Entity(name, Entity::StringHasher("StatusEffect"))
		{

		}
		/*StatusEffect::StatusEffect(Character::BaseCharacter * holder, const std::string& name, bool IsPos, const int priority, const int TickCount, const boost::unordered_set<CallCondition>& conditions) : Holder(holder), RecommendedTicks(TickCount), NetPositive(IsPos), Priority(priority), CallConditions(conditions), Entity(name, Entity::StringHasher("StatusEffect"))
		{

		}*/
		StatusEffect::StatusEffect(const StatusEffect& eff) : NetPositive(eff.NetPositive), Refreshable(eff.Refreshable), RemainingTicks(eff.RemainingTicks), RecommendedTicks(eff.RecommendedTicks), Priority(eff.Priority), CallConditions(eff.CallConditions), 
			Holder(eff.Holder), Entity(eff)
		{

		}
		int StatusEffect::GetRemainingTicks() const
		{
			return RemainingTicks;
		}
		int StatusEffect::GetPriority() const
		{
			return Priority;
		}
		int StatusEffect::GetRecommendedTicks() const
		{
			return RecommendedTicks;
		}
		StatusEffect::RawClonePtr StatusEffect::RawClone() const
		{
			return new StatusEffect(*this);
		}

		void StatusEffect::SetRemainingTicks(const int ticks)
		{
			RemainingTicks = ticks;
		}
		bool StatusEffect::IsPositive() const
		{
			return NetPositive;
		}
		void StatusEffect::SetIsPositive(const bool pos)
		{
			NetPositive = pos;
		}
		const Character::BaseCharacter* StatusEffect::GetHolder() const
		{
			return Holder;
		}
		void StatusEffect::SetHolder(Character::BaseCharacter* holder)
		{
			Holder = holder;
		}

		bool StatusEffect::IsRefreshable() const
		{
			return Refreshable;
		}
		void StatusEffect::SetRefreshable(const bool val)
		{
			Refreshable = val;
		}

		void StatusEffect::SetPriority(const int prior)
		{
			Priority = prior;
		}

		boost::signals2::connection StatusEffect::AddEffectActivatedSignal(const EffectActivatedSignal::slot_type& event)
		{
			return EffectSignal.connect(event);
		}
		boost::signals2::connection StatusEffect::AddEffectDeactivatedSignal(const EffectActivatedSignal::slot_type& event)
		{
			return EffectDeactivatedSignal.connect(event);
		}
		void StatusEffect::DispatchActivatedSignal(const std::string& activationCondition)
		{
			EffectSignal(this, activationCondition);
		}
		void StatusEffect::DispatchDeactivatedSignal(const std::string& deactivatedCondition)
		{
			EffectDeactivatedSignal(this, deactivatedCondition);
		}

		void StatusEffect::AddCallCondition(const CallCondition condition)
		{
			CallConditions.insert(condition);
		}
		bool StatusEffect::HasCondition(const CallCondition condition) const
		{
			return CallConditions.find(condition) != CallConditions.end();
		}
		bool StatusEffect::RemoveCondition(const CallCondition condition)
		{
			auto it = CallConditions.find(condition);
			if (it != CallConditions.end())
			{
				CallConditions.erase(it);
				return true;
			}
			return false;
		}

		const std::string& StatusEffect::GetDescription() const
		{
			return Description;
		}

		void StatusEffect::SetDescription(const std::string& desc)
		{
			Description = desc;
		}

		StatusEffect& StatusEffect::operator=(const StatusEffect& eff)
		{
			if ((*this) == eff)
				return *this;
			Entity::operator=(eff);
			NetPositive = eff.NetPositive;
			Refreshable = eff.Refreshable;
			RemainingTicks = eff.RemainingTicks;
			RecommendedTicks = eff.RecommendedTicks;
			Priority = eff.Priority;
			CallConditions = eff.CallConditions;
			Holder = eff.Holder;
			return *this;
		}
		bool StatusEffect::operator==(const StatusEffect& eff)
		{
			return this->GetName() == eff.GetName();
		}
		bool StatusEffect::operator!=(const StatusEffect& eff)
		{
			return !(*this == eff);
		}
	}
}