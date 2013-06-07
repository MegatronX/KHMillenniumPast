#pragma once

namespace Game
{
	namespace Battle
	{
		class BattleField;
	}
	namespace Actions
	{
		class Action;
		class ActionInterface
		{
		public:
			ActionInterface(bool HasPreUse = false, bool HasBattlePreUse = false, bool HasUse = false, bool HasBattleUse = false, bool HasPostUse = false, bool HasBattlePostUse = false)
				: _PreUse(HasPreUse), _BattlePreUse(HasBattlePreUse), _Use(HasUse), _BattleUse(HasBattleUse), _PostUse(HasPostUse), _BattlePostUse(HasBattlePostUse)
			{

			}
			virtual bool PreUse(Action* action)
			{
				return false;
			}
			virtual bool BattlePreUse(Action* action, Battle::BattleField* field)
			{
				return false;
			}
			virtual bool Use(Action* action)
			{
				return false;
			}
			virtual bool BattleUse(Action* action, Battle::BattleField* field)
			{
				return false;
			}
			virtual bool PostUse(Action* action)
			{
				return false;
			}
			virtual bool BattlePostUse(Action* action, Battle::BattleField* field)
			{
				return false;
			}
			inline bool ImplementsPreUse() const
			{
				return _PreUse;
			}
			inline bool ImplementsBattlePreUse() const
			{
				return _BattlePreUse;
			}
			inline bool ImplementsUse() const
			{
				return _Use;
			}
			inline bool ImplementsBattleUse() const
			{
				return _BattleUse;
			}
			inline bool ImplementsPostUse() const
			{
				return _PostUse;
			}
			inline bool ImplementsBattlePostUse() const
			{
				return _BattlePostUse;
			}
		private:
			bool _PreUse;
			bool _BattlePreUse;
			bool _Use;
			bool _BattleUse;
			bool _PostUse;
			bool _BattlePostUse;
			int _Priority;
		};
	}
}