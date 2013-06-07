#include "Attack.h"

namespace Game
{
		namespace Actions
		{
			int Attack::PowerModerator = 100;

			Attack::Attack() : Action("EmptyAttack"), BasePower(0), PhysicalWeight(1.f), MagicWeight(0.f), Power(0)
			{

			}
		/*	Attack::Attack(const std::string& name) : Action(name)
			{

			}*/
			Attack::Attack(const std::string& name, int basePower, int mpCost, int spCost, float accr, float physWgt, float magicWgt, float critCh) : Action(name, mpCost, spCost, accr), BasePower(basePower), PhysicalWeight(physWgt), MagicWeight(magicWgt), CritChance(critCh), ActionCritical(false), CalculatedDamage(0), Power(BasePower)
			{

			}
			Attack::Attack(const std::string& name, const std::string& displayName, int basePower, int mpCost, int spCost, float accr, float physWgt, float magicWgt, float critCh) : Action(name, mpCost, spCost, accr), BasePower(basePower), PhysicalWeight(physWgt), MagicWeight(magicWgt), CritChance(critCh), ActionCritical(false), CalculatedDamage(0),
				Power(BasePower)
			{

			}
			float Attack::GetMagicWeight() const
			{
				return MagicWeight;
			}
			float Attack::GetPhysicalWeight() const
			{
				return PhysicalWeight;
			}

			float Attack::GetCriticalChance() const
			{
				return CritChance;
			}

			int Attack::GetBasePower() const
			{
				return BasePower;
			}
			int Attack::GetPower() const
			{
				return Power;
			}
			void Attack::SetPower(const int power)
			{
				Power = power;
			}
			int Attack::GetPowerModerator()
			{
				return PowerModerator;
			}

			bool Attack::IsAttackCritical() const
			{
				return ActionCritical;
			}
			void Attack::SetAttackCritical(const bool crit)
			{
				ActionCritical = crit;
			}

			int Attack::GetCalculatedDamage() const
			{
				return CalculatedDamage;
			}
			void Attack::SetCalculatedDamage(const int dmg)
			{
				CalculatedDamage = dmg;
			}

			Attack::RawClonePtr Attack::RawClone() const
			{
				return new Attack(*this);
			}

			Attack::~Attack()
			{

			}
		}
}