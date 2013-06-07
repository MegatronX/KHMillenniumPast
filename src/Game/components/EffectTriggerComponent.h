#pragma once
#ifndef _EFFECTTRIGGER_H_
#define _EFFECTTRIGGER_H_
#include <components/Component.h>
#include <boost/signal.hpp>
namespace Game
{
	namespace StatusEffects
	{
		class StatusEffect;
	}
	namespace Components
	{
		typedef boost::signal<void (const StatusEffect* effect)> EffectTriggeredEvent;

		class EffectTriggerComponent : public Component
		{

		};
	}
}

#endif