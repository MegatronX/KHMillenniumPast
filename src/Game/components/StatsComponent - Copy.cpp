#include "StatsComponent.h"
#include "Entity.h"
namespace Game
{
	using namespace Character;
	namespace Components
	{
		StatComponent::StatComponent(Entity* owner) : Component(owner, owner != nullptr ? "EmptyStatComponent" + owner->GetName() : "EmptyStatComponent", "StatsComponent")
		{
			for (int i = 0; i < StatCount; ++i)
			{
				Stats[i] = 0;
				Multipliers[i] = 1.f;
				StatAdders[i] = 0;
			}
			ResetAllStats();
		}
		StatComponent::StatComponent(Entity* owner, int initialValue) : Component(owner, owner != nullptr ? "EmptyStatComponent" + owner->GetName() : "EmptyStatComponent", "StatsComponent")
		{
			for (int i = 0; i < StatCount; ++i)
			{
				Stats[i] = initialValue;
				Multipliers[i] = 1.f;
				StatAdders[i] = 0;
			}
			ResetAllStats();
		}
		StatComponent::StatComponent(Entity* owner, const std::string& name) : Component(owner, name, "StatsComponent")
		{
			for (int i = 0; i < StatCount; ++i)
			{
				Stats[i] = 0;
				Multipliers[i] = 1.f;
				StatAdders[i] = 0;
			}
			ResetAllStats();
		}
		StatComponent::StatComponent(Entity* owner, int initialValue, const std::string& name) : Component(owner, name, "StatsComponent")
		{
			for (int i = 0; i < StatCount; ++i)
			{
				Stats[i] = 0;
				Multipliers[i] = 1.f;
				StatAdders[i] = 0;
			}
			ResetAllStats();
		}
		StatComponent::StatComponent(Entity* owner, int initialValues[Character::StatCount])
		{
			for (int i = 0; i < StatCount; ++i)
			{
				Stats[i] = initialValues[i];
				Multipliers[i] = 1.f;
				StatAdders[i] = 0;
			}
			ResetAllStats();
		}
		StatComponent::StatComponent(Entity* owner, const int InitialStats[StatCount], const std::string& name) : Component(owner, name, "StatsComponent")//: Stats(InitialStats)
		{
			for (int i = 0; i < StatCount; ++i)
			{
				Stats[i] = InitialStats[i];
				Multipliers[i] = 1.f;
				StatAdders[i] = 0;
			}
			ResetAllStats();
		}

		//NOTE that the copy constructor does NOT copy the signals
		StatComponent::StatComponent(const StatComponent& base) : Component(base)
		{
			for (int i = 0; i < StatCount; ++i)
			{
				Stats[i] = base.Stats[i];
				Multipliers[i] = base.Multipliers[i];
				EffectiveStats[i] = base.EffectiveStats[i];
				StatAdders[i] = base.StatAdders[i];
			}
		}
		int StatComponent::GetStat(const Stat stat) const
		{
			return EffectiveStats[stat];
		}

		int StatComponent::GetBaseStat(const Character::Stat stat) const
		{
			return Stats[stat];
		}
		int StatComponent::GetStatAdder(const Character::Stat stat) const
		{
			return StatAdders[stat];
		}
		float StatComponent::GetStatMultiplier(const Character::Stat stat) const
		{
			return Multipliers[stat];
		}

		bool StatComponent::SetStatAdder(const Character::Stat stat, const int value, const bool Sync)
		{
			if (stat >= 0 && stat < StatCount)
			{
				StatAdders[stat] = value;
				if (Sync)
					ResetStat(stat);
				return true;
			}
			return false;
		}
		bool StatComponent::SetStatMultiplier(const Character::Stat stat, const float value, const bool Sync)
		{
			if (stat >= 0 && stat < StatCount)
			{
				Multipliers[stat] = value;
				if (Sync)
					ResetStat(stat);
				return true;
			}
			return false;
		}

		bool StatComponent::IncrementStatAdder(const Character::Stat stat, const int value, const bool Sync)
		{
			if (stat >= 0 && stat < StatCount)
			{
				StatAdders[stat] += value;
				if (Sync)
					ResetStat(stat);
				return true;
			}
			return false;
		}
		bool StatComponent::IncrementStatMultiplier(const Character::Stat stat, const float value, const bool Sync)
		{
			if (stat >= 0 && stat < StatCount)
			{
				Multipliers[stat] += value;
				if (Sync)
					ResetStat(stat);
				return true;
			}
			return false;
		}

		bool StatComponent::SetBaseStat(const Stat stat, const int value, const bool Sync)
		{
			if (stat >= 0 && stat < StatCount)
			{
				Stats[stat] = value;
				if (Sync)
					ResetStat(stat);
				return true;
			}
			return false;
		}
		bool StatComponent::SetStat(const Stat stat, const int value, const bool Sync)
		{
			if (stat >= 0 && stat < StatCount)
			{
				EffectiveStats[stat] = value;
				if (Sync)
					ResetStat(stat);
				return true;
			}
			return false;
		}
		boost::signals2::connection StatComponent::AddStatChangedEvent(const StatChangedSignal::slot_type& event)
		{
			return StatChangedEvent.connect(event);
		}
		void StatComponent::DispatchStatChangedEvents(Stat stat, int prevVal, int newVal)
		{
			(StatChangedEvent)(Component::GetName(), this, stat, prevVal, Stats[stat]);
		}
		StatComponent::~StatComponent()
		{
			//delete StatChangedEvent;
			//StatChangedEvent = nullptr;
		}
		StatComponent& StatComponent::operator=(const StatComponent& reference)
		{
			if (this == &reference)
				return *this;
			Component::operator=(reference);
			for (int i = 0; i < StatCount; ++i)
			{
				Stats[i] = reference.Stats[i];
				Multipliers[i] = reference.Multipliers[i];
				EffectiveStats[i] = reference.EffectiveStats[i];

				StatAdders[i] = reference.EffectiveStats[i];
			}
			return *this;
		}
		StatComponent::ClonePtr StatComponent::Clone() const
		{
			return StatComponent::ClonePtr(new StatComponent(*this));
		}

		void StatComponent::ResetStat(const Character::Stat stat)
		{
			if (stat >= 0 && stat < StatCount)
			{
				int oldStat = EffectiveStats[stat];
				EffectiveStats[stat] = static_cast<int>(static_cast<float>(Stats[stat] + StatAdders[stat]) * Multipliers[stat]);
				if ((oldStat) != EffectiveStats[stat])
				{
					DispatchStatChangedEvents(stat, oldStat, EffectiveStats[stat]);
				}
			}
		}
		void StatComponent::ResetAllStats()
		{
			for (int stat = 0; stat < StatCount; ++stat)
			{
				ResetStat(static_cast<Character::Stat>(stat));
			}
		}

		int& StatComponent::operator[](const Stat stat)
		{
			return EffectiveStats[stat];
		}
		int& StatComponent::operator[](const int stat)
		{
			if (stat >= 0 && stat < StatCount)
				return EffectiveStats[stat];
#ifdef _DEBUG
			std::cerr << "Attempted to access a stat component stat with index " << stat << std::endl;
#endif
			return EffectiveStats[0];
		}
	}
}