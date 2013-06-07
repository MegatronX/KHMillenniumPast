#pragma once

#include <actions/Action.h>

namespace Game
{
		namespace Actions
		{
			class Attack : public Action
			{
			public:
				Attack();
				//Attack(const std::string& name);
				Attack(const std::string& name, int basePower = 0, int mpCost = 0, int spCost = 0, float accr = 1.f, float physWgt = 1.f, float magicWgt = 0.f, float critCh = 1.f);
				Attack(const std::string& name, const std::string& displayName, int basePower = 100, int mpCost = 0, int spCost = 0, float accr = 1.f, float physWgt = 1.f, float magicWgt = 0.f, float critCh = 1.f);
				float GetMagicWeight() const;
				float GetPhysicalWeight() const;
				float GetCriticalChance() const;
				
				int GetBasePower() const;

				int GetPower() const;
				void SetPower(const int power);

				static int GetPowerModerator();

				bool IsAttackCritical() const;
				void SetAttackCritical(const bool crit);

				int GetCalculatedDamage() const;
				void SetCalculatedDamage(const int dmg);

				Attack::RawClonePtr Attack::RawClone() const;

				virtual ~Attack();
			private:

				bool ActionCritical;
				int CalculatedDamage;

				float MagicWeight;
				float PhysicalWeight;
				float CritChance;
				int BasePower;
				int Power;
				static int PowerModerator;
			};

		}
	
}