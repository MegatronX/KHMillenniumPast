#pragma once

namespace Game
{
	namespace Actions
	{
		struct ActionResult
		{
		public:
			ActionResult() : HPDamage(0), HPDamageSplit(1.0f), MPDamage(0), MPDamageSplit(1.0f), SPDamage(0), SPDamageSplit(1.0f)
			{

			}
			float GetHPDamage() const
			{
				return HPDamage;
			}
			void SetHPDamage(const float dam)
			{
				HPDamage = dam;
			}
			float GetMPDamage() const
			{
				return MPDamage;
			}
			void SetMPDamage(const float dam)
			{
				MPDamage = dam;
			}
			float GetSPDamage() const
			{
				return HPDamage;
			}
			void SetSPDamage(const float dam)
			{
				HPDamage = dam;
			}
		protected:
			float HPDamage;
			float HPDamageSplit;
			float MPDamage;
			float MPDamageSplit;
			float SPDamage;
			float SPDamageSplit;
			int TimerMod;
			//std::vector<std::string> InflictStatusEffects
		};
	}
}