#pragma once
#ifndef _STATUSEFFECTSLIBRARY_H_
#define _STATUSEFFECTSLIBRARY_H_
#include "StatusEffect.h"
#include <boost/unordered_map.hpp>
namespace Game
{
	namespace StatusEffects
	{
		class StatusEffectsLibrary
		{
		public:
			const StatusEffect* GetStatusEffect(const std::string& name) const
			{
				auto se = NameToStatusEffect.find(name);
				if (se != NameToStatusEffect.end())
				{
					return se->second.get();
				}
				return nullptr;
			}
			const StatusEffect* GetStatusEffectRawClone(const std::string& name) const
			{
				auto se = NameToStatusEffect.find(name);
				if (se != NameToStatusEffect.end())
				{
					return dynamic_cast<StatusEffect*>(se->second->RawClone());
				}
				return nullptr;
			}
			const se_ptr GetStatusEffectClone(const std::string& name) const
			{
				auto se = NameToStatusEffect.find(name);
				if (se != NameToStatusEffect.end())
				{
					auto res = se->second->Clone();
					return boost::dynamic_pointer_cast<StatusEffect>(res);
				}
				return se_ptr();
			}

			void AddStatusEffect(se_ptr se)
			{
				if (se.get() != nullptr)
				{
					NameToStatusEffect[se->GetName()] = se;
				}
			}
		private:
			boost::unordered_map<std::string, se_ptr> NameToStatusEffect;
		};
	}
}

#endif