#pragma once

//#include <actions/Action.h>
#include <character/BaseCharacter.h>
#include <character/Party.h>
#include <battle/BattleParty.h>
#include <battle/BattleCharacterComponent.h>
namespace Game
{
	namespace Actions
	{
		class Action;
		struct ActionUserTarget
		{
			
			ActionUserTarget();
			ActionUserTarget(Battle::BattleCharacterComponent* bchar);
			ActionUserTarget(Character::BaseCharacter* participant);

			void SetCharacter(Character::BaseCharacter* character);

			bool operator==(const ActionUserTarget& user);
			bool operator!=(const ActionUserTarget& action);

			//Struct members
			Battle::BattleCharacterComponent* AttachedBattleCharacter;
			Character::BaseCharacter* AttachedCharacter;
			boost::shared_ptr<Action> action;
		};

		class ActionGroup : public Entity
		{
		public:
			ActionGroup();
			ActionGroup(Character::BaseParty& sourceParty);
			ActionGroup(Battle::BattleParty& sourceParty);
			ActionGroup(Character::BaseCharacter& character);

			void AddCharacter(Character::BaseCharacter* character, bool Validate = true);
			void AddActionUser(const ActionUserTarget& targ, bool Validate = true);

			int GetGroupAverageStat(const Character::Stat stat, bool inBattle = false);

			void AddBattleCharacter(Battle::BattleCharacterComponent* bcharacter, bool Validate = true);

			boost::unordered_map<std::string, ActionUserTarget>& GetGroup();
			int GroupSize() const;
			ActionUserTarget* GetFirst();

			ActionUserTarget* GetMember(const std::string& index);

			ActionUserTarget& GetMember(const std::string& index, bool& valid);

			bool AddMember(ActionUserTarget& ref);

			bool AddMember(ActionUserTarget* ref);

			bool AddMember(ActionUserTarget& ref, const std::string& index);

			bool RemoveMember(const std::string& index);

			bool RemoveMember(const ActionUserTarget* targ);

			bool IsMember(const ActionUserTarget* targ);

			bool IsMember(Character::BaseCharacter* character);

			void Clear();

			ActionUserTarget* GetAt(unsigned int index);

			ActionUserTarget& operator[](const std::string& index);

			
		protected:
		private:
			int InvalidCharacterCount;
			//std::vector<ActionUserTarget> Group;
			boost::unordered_map<std::string, ActionUserTarget> Group;
		};

		/*class ActionTargets : public Entity
		{
		public:
			ActionTargets(Character::Party& sourceParty)
			{

			}
			ActionTargets(Battle::BattleParty& sourceParty)
			{

			}
			ActionTargets(Character::BaseCharacter& character)
			{
				Targets.push_back(ActionTarget(&character));
			}

			void AddTarget(Character::BaseCharacter* character, bool Validate = true)
			{

			}

			void AddBattleTarget(Battle::BattleCharacter* bcharacter, bool Validate = true)
			{

			}

			std::vector<ActionTarget>& GetTargets()
			{
				return Targets;
			}

			ActionTarget& GetFirst()
			{
				return *(Targets.begin());
			}
			ActionTarget& GetTarget(const int index)
			{
				return Targets[index];
			}

			ActionTarget& operator[](const int index)
			{
				return Targets[index];
			}
		protected:
		private:
			std::vector<ActionTarget> Targets;
		};*/


	}
}