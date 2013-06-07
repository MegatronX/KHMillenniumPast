#include "EquipmentComponent.h"
#include <components/StatusEffectivenessComponent.h>
#include <components/ElementEffectivenessComponent.h>
namespace Game
{
	namespace Items
	{
		EquipmentComponent::EquipmentComponent(Entity* owner) : EquipComponent(owner)
		{

		}
		bool EquipmentComponent::Equip(Character::BaseCharacter& character)
		{
			auto statAdd = GetOwner()->GetComponentAs<Components::StatComponent<int>*>(StatAdderIndex);
			auto statMult = GetOwner()->GetComponentAs<Components::StatComponent<float>*>(StatMultIndex);
			if (statAdd != nullptr || statMult != nullptr)
			{
				auto & sm = character.GetStatsManager();//GetComponentAs<Character::StatsManager*>(Character::StatManagerIndex);
				for (auto st = 0; st < Character::StatCount; ++st)
				{
					if (statAdd != nullptr)
						sm.IncrementEquipmentStatAdder(static_cast<Character::Stat>(st), statAdd->GetStat(static_cast<Character::Stat>(st)));
					if (statMult != nullptr)
						sm.IncrementEquipmentStatMultiplier(static_cast<Character::Stat>(st), statMult->GetStat(static_cast<Character::Stat>(st)));
				}
			}
			auto SEAdd = GetOwner()->GetComponentAs<Components::StatusEffectivenessComponent*>(StatusEffectAdderIndex);
			if (SEAdd != nullptr)
			{
				auto & SEM = character.GetStatusEffectsManager();
				for (auto se = SEAdd->GetEffectivenessTable().begin(); se != SEAdd->GetEffectivenessTable().end(); ++se)
				{
					SEM.IncrementStatusResistance(se->first, se->second);
				}
			}
			auto EleAdd = GetOwner()->GetComponentAs<Components::ElementEffectivenessComponent*>(ElementEffectAdderIndex);
			if (EleAdd != nullptr)
			{
				auto & EleM = character.GetElementEffectiveness();
				for (auto ele = EleAdd->GetEffectivenessTable().begin(); ele != EleAdd->GetEffectivenessTable().end(); ++ele)
				{
					EleM.IncrementEffectiveness(ele->first, ele->second);
				}
			}
			return true;
		}
		bool EquipmentComponent::UnEquip(Character::BaseCharacter& character)
		{
			auto statAdd = GetOwner()->GetComponentAs<Components::StatComponent<int>*>(StatAdderIndex);
			auto statMult = GetOwner()->GetComponentAs<Components::StatComponent<float>*>(StatMultIndex);
			if (statAdd != nullptr || statMult != nullptr)
			{
				auto sm = character.GetComponentAs<Character::StatsManager*>(Character::StatManagerIndex);
				if (sm != nullptr)
				{
					for (auto st = 0; st < Character::StatCount; ++st)
					{
						if (statAdd != nullptr)
							sm->IncrementEquipmentStatAdder(static_cast<Character::Stat>(st), -(statAdd->GetStat(static_cast<Character::Stat>(st))));
						if (statMult != nullptr)
							sm->IncrementEquipmentStatMultiplier(static_cast<Character::Stat>(st), -(statAdd->GetStat(static_cast<Character::Stat>(st))));
					}
				}
			}
			auto SEAdd = GetOwner()->GetComponentAs<Components::StatusEffectivenessComponent*>(StatusEffectAdderIndex);
			if (SEAdd != nullptr)
			{
				auto & SEM = character.GetStatusEffectsManager();
				for (auto se = SEAdd->GetEffectivenessTable().begin(); se != SEAdd->GetEffectivenessTable().end(); ++se)
				{
					SEM.IncrementStatusResistance(se->first, -(se->second));
				}
			}
			auto EleAdd = GetOwner()->GetComponentAs<Components::ElementEffectivenessComponent*>(ElementEffectAdderIndex);
			if (EleAdd != nullptr)
			{
				auto & EleM = character.GetElementEffectiveness();
				for (auto ele = EleAdd->GetEffectivenessTable().begin(); ele != EleAdd->GetEffectivenessTable().end(); ++ele)
				{
					EleM.IncrementEffectiveness(ele->first, -(ele->second));
				}
			}
			return true;
		}
	}
}