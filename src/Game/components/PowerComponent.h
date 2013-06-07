#pragma once
#ifndef _POWERCOMPONENT_H_
#define _POWERCOMPONENT_H_

namespace Game
{
	namespace Components
	{
	public:
		virtual float GetPower(const std::vector<BaseCharacter*>& Users, const BaseCharacter* target)
		{
			return Accuracy;
		}
		virtual float GetVariability(std::vector<BaseCharacter*> Users, BaseCharacter* target)
		{
			return Variability;
		}
		virtual ClonePtr Clone()
		{
			return ClonePtr(new AccuracyComponent(*this));
		}
	private:
		float Power;
		float Variability;
		bool Fixed;
	}
}

#endif