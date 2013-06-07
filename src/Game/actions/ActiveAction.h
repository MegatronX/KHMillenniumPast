#pragma once
#ifndef _ACTIVEACTION_H_
#define _ACTIVEACTION_H_
//#include <battle/Action.h>
#include <battle/BattleCharacter.h>
#include <character/BaseCharacter.h>
namespace Game
{
	namespace Character
	{
		class BaseCharacter;
	}
	namespace Actions
	{
		class Action;
		
		struct ActionUser : public Entity
		{
			Battle::BattleCharacter* BattleUser;
			Character::BaseCharacter* User;
			ActionUser(Character::BaseCharacter* participant) : User(participant)
			{
				if (participant != nullptr)
				{
					auto bchar = participant->GetComponentAs<Battles::BattleCharacter>("BattleCharacterComponent");
					if (bchar != nullptr)
						BattleUser = bchar;
				}
		}
		
		struct ActionTarget : public Entity
		{
			ActionTarget(Character::BaseCharacter* participant) : Target(participant)
			{
				if (participant != nullptr)
				{
					auto bchar = participant->GetComponentAs<Battles::BattleCharacter>("BattleCharacterComponent");
					if (bchar != nullptr)
						BattleTarget = bchar;
				}
			}
			Battle::BattleCharacter* BattleTarget;
			Character::BaseCharacter* Target;
			boost::shared_ptr<Game::Actions::Action> action;
			bool operator==(const ActionTarget& action)
			{
				return ((Target != NULL && action.Target != NULL &&
					(Target->GetID() == action.Target->GetID())) ||
					(BattleTarget != NULL && action.BattleTarget != NULL &&
					(BattleTarget->GetID() == action.BattleTarget->GetID())));
			}
			bool operator!=(const ActionTarget& action)
			{
				return (*this == action);
			}
		};
		
		class ActionUsers : public Entity
		{
		public:
			ActionUsers(Character::Party& sourceParty)
			{
				
			}
			ActionUsers(Battle::BattleParty& sourceParty)
			{
				
			}
			ActionUsers(Character::BaseCharacter& character)
			{
				
			}
			
			void AddUser(Character::BaseCharacter* character, bool Validate = true)
			{
				
			}
			
			void AddBattleUser(Battle::BattleCharacter* bcharacter, bool Validate = true)
			{
				
			}
			
			ActionUser& GetFirst()
			{
				return *(Users.begin());
			}
			ActionUser& GetTarget(const int index)
			{
				return Users[index];
			}
			
			ActionUser& operator[](const int index)
			{
				return Users[index];
			}
		protected:
		private:
			std::vector<ActionUser> Users;
		}
		
		class ActionTargets : public Entity
		{
		public:
			ActionUsers(Character::Party& sourceParty)
			{
				
			}
			ActionTargets(Battle::BattleParty& sourceParty)
			{
				
			}
			ActionTargets(Character::BaseCharacter& character)
			{
				Targets.push_back(ActionTarget(character));
			}
			
			void AddTarget(Character::BaseCharacter* character, bool Validate = true)
			{
				
			}
			
			void AddBattleTarget(Battle::BattleCharacter* bcharacter, bool Validate = true)
			{
				
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
			std::vector<ActionTargets> Targets;
		}
		
		class ActionParticipants : public Entity
		{
		public:
			ActionParticipants(Character::BaseParty& sourceparty)
			{
				
			}
			ActionParticipants(Character::BaseCharacter& character)
			{
				AddCharacter(&character);
			}
			ActionParticipants(const std::vector<Character::BaseCharacter*> participants)
			{
				for (auto it = participants.begin(); it != participants.end(); ++it)
				{
					AddCharacter(*it);
				}
			}
			
			void AddCharacter(Character::BaseCharacter* character, bool Validate = true)
			{
				if (Validate && character != nullptr || !Validate)
				{
					Participants.push_back(ActionParticipant(character));
				}	
			}
			
			ActionParticipant& GetCharacter(int index)
			{
				
			}
		protected:
		private:
			std::vector<ActionParticipant> Participants;
		}
	}
}
#endif