#include "Component.h"
#include <character/BaseCharacter.h>
namespace Game
{
	namespace Components
	{
		class AccuracyComponent : public Component
		{
		public:
			virtual float GetAccuracy(const std::vector<BaseCharacter*>& Users, const BaseCharacter* target)
			{
				return Accuracy;
			}
			virtual float GetVariability(std::vector<BaseCharacter*> Users, BaseCharacter* target)
			{
				return Variability;
			}
			virtual ClonePtr Clone()
			{
				return new AccuracyComponent(*this);
			}
		private:
			float Accuracy;
			float Variability;
			bool Fixed;
		};
	}
}