#pragma once
#ifndef _ENEMYDATABASE_H_
#define _ENEMYDATABASE_H_

#include <character/PlayerParty.h>
#include <Math/MathFormula.h>
namespace Game
{
	namespace Character
	{
		class CharacterEntry
		{
		public:
			CharacterEntry() : EntryValid(true)
			{
			}
			virtual boost::shared_ptr<BaseCharacter> GetAtLevel(const int lv)
			{
				boost::shared_ptr<BaseCharacter> ch(new BaseCharacter("Invalid Character"));
				ch->SetValid(false);
				return ch;
			}
			virtual bool ValidForLevel(const int lv)
			{
				return false;
			}

			static boost::shared_ptr<BaseCharacter> GetAtLevelFromEntry(CharacterEntry& entry)
			{

			}
			bool EntryValid;
			boost::shared_ptr<BaseCharacter> RootEntry;
		};
		/*class FormulaBasedLevelGeneration : public EnemyEntry
		{
		public:
		private:
			MathFormula StatGenerators[StatCount];
		};

		class EntryBasedLevelGeneration : public EnemyEntry
		{
		public:
		private:
			boost::unordered_map<int, boost::shared_ptr<BaseCharacter> > Entries;
		};*/
		class CharacterDatabase
		{
		public:
			void AddCharacterEntry(const std::string& index, boost::shared_ptr<CharacterEntry> entry)
			{
				Characters[index] = entry;
			}
			boost::shared_ptr<CharacterEntry> GetEntry(const std::string& name)
			{
				auto it = Characters.find(name);
				if (it != Characters.end())
				{
					return it->second;
				}
				auto ch = boost::shared_ptr<CharacterEntry>(new CharacterEntry());
				ch->EntryValid = false;
				return ch;
			}
			boost::shared_ptr<BaseCharacter> GetCharacter(const std::string& name, const int lv)
			{
				auto entry = GetEntry(name);
				if (entry->EntryValid)
				{
					auto ch = entry->GetAtLevel(lv);
					if (ch->GetValid())
						return boost::dynamic_pointer_cast<BaseCharacter>(ch->Clone());
				}
				auto ch = boost::shared_ptr<BaseCharacter>(new BaseCharacter());
				ch->SetValid(false);
				return ch;
			}

			const boost::shared_ptr<BaseCharacter> GetRootCharacter(const std::string& name, const int lv)
			{
				auto entry = GetEntry(name);
				if (entry->EntryValid)
				{
					return entry->GetAtLevel(lv);
				}
				auto ch = boost::shared_ptr<BaseCharacter>(new BaseCharacter());
				ch->SetValid(false);
				return ch;
			}

		private:
			boost::unordered_map<std::string, boost::shared_ptr<CharacterEntry> > Characters;
			
		};
	}
}

#endif