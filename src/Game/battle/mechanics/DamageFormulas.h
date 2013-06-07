#pragma once
#ifndef _DAMAGEFORMULAS_H_
#define _DAMAGEFORMULAS_H_

#include <components/Component.h>
namespace Game
{
	namespace Actions
	{
		class Action;
	}
	namespace Battle
	{
		class Mechanics;
		class DamageFormulas : public Component
		{
			int CalculateDamage(Action::Action& action, Mechanics& mechanics);
		};
	}
}

#endif