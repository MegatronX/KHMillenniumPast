#include <battle/mechanics/TurnGenerator.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
namespace Game
{
	namespace Battle
	{
		class ATBTurnGenerator : public TurnGenerator
		{
		public:
			ATBTurnGenerator(Entity* owner, const sf::Uint32 UpdateRate = 20, float TicksPerSecond = 30, const std::string& CType = "ATBTurnGenerator");
			ATBTurnGenerator(const ATBTurnGenerator& gen);
			virtual RawClonePtr RawClone() const override;
			virtual void TrackCharacter(BattleCharacterComponent* character);
			virtual bool StopTrackingCharacter(const std::string& name);
			virtual bool StopTrackingCharacter(BattleCharacterComponent* character);

			BattleCharacterComponent* GetCharacter(const std::string& name);

			virtual void GenerateNextCharacter(int GenCounter = 1);

			virtual void TickCharacter(BattleCharacterComponent* character) override;

			void Pause();

			void UnPause();
			//virtual void TickCharacter(BattleCharacterComponent* character);

			virtual ~ATBTurnGenerator();
		protected:
			void GeneratorFunction();
			//virtual void HandleTimerOverflow(BattleCharacterComponent*, BattleMode) override;
		private:
			float UpdateMult;
			bool Update;
			bool Launched;
			int GenCount;
			sf::Time UpdateRate;
			sf::Mutex mtx;
			sf::Thread UpdaterThread;
		};
	}
}