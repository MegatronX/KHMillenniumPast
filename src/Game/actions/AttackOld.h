#pragma once
#ifndef _ATTACK_H_
#define _ATTACK_H_
#include <actions/Action.h>
#include <actions/AttackTargetsComponent.h>
namespace Game
{
	namespace Actions
	{
		class Attack : public Action
		{
		public:
		private:
			AttackTargetsComponent AttackTargets;
		};
	}
}

#endif