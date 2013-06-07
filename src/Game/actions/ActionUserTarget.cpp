#include "ActionUserTarget.h"

namespace Game
{
	namespace Actions
	{
		ActionUserTarget::ActionUserTarget()
		{
		}
		ActionUserTarget::ActionUserTarget(Battle::BattleCharacterComponent* bchar) : AttachedBattleCharacter(bchar), AttachedCharacter(nullptr)
		{
			if (bchar != nullptr)
			{
				AttachedCharacter = dynamic_cast<Character::BaseCharacter*>((bchar->GetOwner()));
			}
		}
		ActionUserTarget::ActionUserTarget(Character::BaseCharacter* participant) : AttachedCharacter(participant), AttachedBattleCharacter(nullptr)
		{
			if (participant != nullptr)
			{
				auto bchar = participant->GetComponentAs<Battle::BattleCharacterComponent*>("BattleCharacterComponent");
				if (bchar != nullptr)
					AttachedBattleCharacter = bchar;
			}
		}

		void ActionUserTarget::SetCharacter(Character::BaseCharacter* character)
		{
			AttachedCharacter = character;

		}

		bool ActionUserTarget::operator==(const ActionUserTarget& user)
		{
			return ((AttachedCharacter != NULL && user.AttachedCharacter != NULL &&
				(AttachedCharacter->GetID() == user.AttachedCharacter->GetID())) ||
				(AttachedBattleCharacter != NULL && user.AttachedBattleCharacter != NULL &&
				(AttachedBattleCharacter->GetUID() == user.AttachedBattleCharacter->GetUID())));
		}
		bool ActionUserTarget::operator!=(const ActionUserTarget& action)
		{
			return !(*this == action);
		}



		ActionGroup::ActionGroup() : InvalidCharacterCount(0)
		{

		}
		ActionGroup::ActionGroup(Character::BaseParty& sourceParty) : InvalidCharacterCount(0)
		{

		}
		ActionGroup::ActionGroup(Battle::BattleParty& sourceParty) : InvalidCharacterCount(0)
		{

		}
		ActionGroup::ActionGroup(Character::BaseCharacter& character) : InvalidCharacterCount(0)
		{

		}

		void ActionGroup::AddCharacter(Character::BaseCharacter* character, bool Validate)
		{
			if (character != nullptr)
			{
				Group[character->GetName()] = ActionUserTarget(character);
			}

		}
		void ActionGroup::AddActionUser(const ActionUserTarget& targ, bool Validate)
		{
			if (targ.AttachedCharacter != nullptr)
			{
				Group[targ.AttachedCharacter->GetName()] = targ;
			}
		}

		int ActionGroup::GetGroupAverageStat(const Character::Stat stat, bool inBattle)
		{
			int sval = 0;
			int runningStat = 0;
			for (auto it = Group.begin(); it != Group.end(); ++it)
			{
				auto ch = it->second.AttachedCharacter;
				if (ch != nullptr)
				{
					runningStat += ch->GetStatsManager().GetBattleStat(stat);
				}
			}
			if (Group.size() > 0)
			{
				sval = runningStat / Group.size();
			}
			return sval;
		}

		void ActionGroup::AddBattleCharacter(Battle::BattleCharacterComponent* bcharacter, bool Validate)
		{
			if (bcharacter != nullptr)
			{
				auto character = dynamic_cast<Character::BaseCharacter*>(bcharacter->GetOwner());
				AddCharacter(character, Validate);
			}
		}

		boost::unordered_map<std::string, ActionUserTarget>& ActionGroup::GetGroup()
		{
			return Group;
		}
		int ActionGroup::GroupSize() const
		{
			return Group.size();
		}
		ActionUserTarget* ActionGroup::GetFirst()
		{
			return &((Group.begin()->second));
		}

		ActionUserTarget* ActionGroup::GetMember(const std::string& index)
		{
			auto it = Group.find(index);
			if (it != Group.end())
				return &(it->second);
			return nullptr;
		}

		ActionUserTarget& ActionGroup::GetMember(const std::string& index, bool& valid)
		{
			valid = false;
			auto it = Group.find(index);
			if (it != Group.end())
			{
				valid = true;
				return (it->second);
			}
			return ActionUserTarget();
		}

		bool ActionGroup::AddMember(ActionUserTarget& ref)
		{
			if (ref.AttachedCharacter != nullptr)
			{
				return AddMember(ref, ref.AttachedCharacter->GetName());
			}
			return false;
		}

		bool ActionGroup::AddMember(ActionUserTarget* ref)
		{
			if (ref != nullptr && ref->AttachedCharacter != nullptr)
			{
				return AddMember(*ref, ref->AttachedCharacter->GetName());
			}
			return false;
		}

		bool ActionGroup::AddMember(ActionUserTarget& ref, const std::string& index)
		{
			Group[index] = ActionUserTarget(ref);
			return true;
		}


		bool ActionGroup::RemoveMember(const std::string& index)
		{
			auto it = Group.find(index);
			if (it != Group.end())
			{
				Group.erase(it);
				return true;
			}
			return false;
		}

		bool ActionGroup::RemoveMember(const ActionUserTarget* targ)
		{
			if (targ != nullptr)
			{
				for (auto it = Group.begin(); it != Group.end(); ++it)
				{
					if (it->second == *targ)
					{
						Group.erase(it);
						return true;
					}
				}
			}
			return false;
		}

		bool ActionGroup::IsMember(const ActionUserTarget* targ)
		{
			for (auto ch = Group.begin(); ch != Group.end(); ++ch)
			{
				if (ch->second == *targ)
				{
					return true;
				}
			}
			return false;
		}

		bool ActionGroup::IsMember(Character::BaseCharacter* character)
		{
			for (auto ch = Group.begin(); ch != Group.end(); ++ch)
			{
				if (*(ch->second.AttachedCharacter) == *character)
				{
					return true;
				}
			}
			return false;
		}

		void ActionGroup::Clear()
		{
			Group.clear();
		}

		ActionUserTarget* ActionGroup::GetAt(unsigned int index)
		{
			if (index >= Group.size())
				return nullptr;
			unsigned int tindex = 0;
			auto it = Group.begin();
			for (; it != Group.end() && tindex < index; ++tindex, ++it)
			{

			}
			return &(it->second);
		}

		ActionUserTarget& ActionGroup::operator[](const std::string& index)
		{
			auto it = Group.find(index);
			if (it != Group.end())
				return it->second;
			return ActionUserTarget();
		}
	}
}