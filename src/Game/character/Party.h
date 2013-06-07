#pragma once
#ifndef _PARTY_H_
#define _PARTY_H_
#include <Entity.h>
//#include <character/BaseCharacter.h>
#include <vector>
#include <boost/lexical_cast.hpp>
namespace Game
{
	namespace Character
	{

		template <class T>
		class PartyInterface : public Entity
		{
		public:
			typedef boost::shared_ptr<T> MemberPtr;
			typedef T* MemberRawPtr;
			PartyInterface(const std::string& name) : Entity(name, EntityTypes::CharacterEntity)
			{

			}

			PartyInterface(std::vector<MemberPtr> Members, const std::string& name) : Entity(name, EntityTypes::CharacterEntity)
			{
				int i = 0;
				for (auto it = Members.begin(); it != Members.end(); ++it, ++i)
				{
					if ((*it).get() != nullptr)
					{
						auto entity = boost::dynamic_pointer_cast<Entity>(*it);
						if (entity != nullptr)
						{
							AddMember((*it), entity->GetName());
						}
						else
						{
							AddMember(*it, "Member" + boost::lexical_cast<std::string>(i));
						}
					}
#ifdef DEBUG
					else
					{
						std::cerr << "Attempted to add invalid character to party\n"; 
					}
#endif
				}
			}

			/*virtual void AddMember(MemberPtr member, bool overwriteExisting = false)
			{
				if (member.get() != nullptr)
				{
					auto it = PartyMembers.find(member)
				}
			}*/
			virtual void AddMember(MemberPtr member, const std::string& index, bool overwriteExisting = false)
			{
				if (member.get() != nullptr)
				{
					auto it = PartyMembers.find(index);
					if (it != PartyMembers.end())
					{
						if (overwriteExisting)
						{
							PartyMembers.erase(it);
							PartyMembers[index] = member;
						}
					}
					else
					{
						PartyMembers[index] = member;
					}
				}
				for (auto it = MembersInOrder.begin(); it != MembersInOrder.end(); ++it)
				{
					if ((*(*it)) == *member)
					{
						if (overwriteExisting)
						{
							MembersInOrder.erase(it);
							MembersInOrder.push_back(member);
							break;
						}
						else
						{
							return;
						}
					}
				}
				MembersInOrder.push_back(member);
			}
			virtual bool RemoveMemberByName(const std::string& name)
			{
				bool Removed = false;
				auto it = PartyMembers.find(name);
				if (it != PartyMembers.end())
				{
					PartyMembers.erase(it);
					Removed = true;
					for (auto mem = MembersInOrder.begin(); mem != MembersInOrder.end(); ++mem)
					{
						if ((*mem)->GetName() == name)
						{
							MembersInOrder.erase(mem);
							break;
						}
					}
				}
				return Removed;
			}
			virtual void RemoveMemberByMemberPtr(const MemberPtr member)
			{
				
			}

			std::vector<MemberRawPtr> GetRawPartyMembers() const
			{
				std::vector<MemberRawPtr> chars;
				for(auto it = PartyMembers.begin(); it != PartyMembers.end(); ++it)
				{
					chars.push_back(it->second.get());
				}
				return chars;
			}

			boost::unordered_map<std::string, MemberPtr>& GetPartyMembers()
			{
				return PartyMembers;
			}
			MemberPtr GetPartyMember(const std::string& name)
			{
				auto member = PartyMembers.find(name);
				if (member != PartyMembers.end())
				{
					return member->second;
				}
				return MemberPtr();
			}
			std::vector<MemberPtr>& GetPartyMembersInOrder()
			{
				return MembersInOrder;
			}
		protected:
			boost::unordered_map<std::string, MemberPtr> PartyMembers;
			std::vector<MemberPtr> MembersInOrder;
		private:

		};

		/*class Party : public PartyInterface<Character::BaseCharacter>
		{
		public:
			Party(const std::string& name) : PartyInterface(name)
			{

			}

			
		};*/

		

	}
}

#endif