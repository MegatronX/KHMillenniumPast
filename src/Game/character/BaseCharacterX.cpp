#include "BaseCharacterX.h"

namespace Game
{
	using namespace Components;
	namespace Character
	{
		BaseCharacter::BaseCharacter() : Status(Normal), CharacterID(-1), SyncingStats(false)
		{
			BaseStats[Normal].AddStatChangedEvent(boost::bind(&BaseCharacter::HandleNormalStatsModifiedEvent, this, _1, _2, _3, _4, _5));
			BaseStats[Preview].AddStatChangedEvent(boost::bind(&BaseCharacter::HandlePreviewStatsModifiedEvent, this, _1, _2, _3, _4, _5));
		}
		BaseCharacter::BaseCharacter(const std::string& Name_, const int ID) : Entity(Name_, EntityTypes::CharacterEntity), CharacterID(ID), Status(Normal), SyncingStats(false)
		{
			BaseStats[Normal] = StatComponent(0, "BaseStatsNormal");
			BaseStats[Preview] = StatComponent(0, "BaseStatsPreview");
			BaseStats[Normal].AddStatChangedEvent(boost::bind(&BaseCharacter::HandleNormalStatsModifiedEvent, this, _1, _2, _3, _4, _5));
			BaseStats[Preview].AddStatChangedEvent(boost::bind(&BaseCharacter::HandlePreviewStatsModifiedEvent, this, _1, _2, _3, _4, _5));
		}
		BaseCharacter::BaseCharacter(const std::string& Name_, const int ID, StatComponent& statComp) : Entity(Name_, EntityTypes::CharacterEntity), CharacterID(ID), Status(Normal), SyncingStats(false)
		{
			BaseStats[Normal] = statComp;
			BaseStats[Preview] = statComp;
			SyncCombinedStats();
			BaseStats[Normal].AddStatChangedEvent(boost::bind(&BaseCharacter::HandleNormalStatsModifiedEvent, this, _1, _2, _3, _4, _5));
			BaseStats[Preview].AddStatChangedEvent(boost::bind(&BaseCharacter::HandlePreviewStatsModifiedEvent, this, _1, _2, _3, _4, _5));
		}
		BaseCharacter::BaseCharacter(const std::string& Name_, const int ID, int InitialStats[StatCount]) :Entity(Name_, EntityTypes::CharacterEntity), CharacterID(ID), Status(Normal), SyncingStats(false)
		{
			for (int i = 0; i < StatCount; ++i)
			{
				BaseStats[Normal][i] = InitialStats[i];
				BaseStats[Preview][i] = InitialStats[i];
				CombinedStats[Normal][i] = InitialStats[i];
				CombinedStats[Preview][i] = InitialStats[i];
			}
			BaseStats[Normal].AddStatChangedEvent(boost::bind(&BaseCharacter::HandleNormalStatsModifiedEvent, this, _1, _2, _3, _4, _5));
			BaseStats[Preview].AddStatChangedEvent(boost::bind(&BaseCharacter::HandlePreviewStatsModifiedEvent, this, _1, _2, _3, _4, _5));
		}
		/*BaseCharacter::BaseCharacter(const std::string& Name_, const int ID, StatComponent& statComp) : Name(Name_), CharacterID(ID), Status(Normal)//, AdditionalStatComponents(StatAdders)
		{
			//AdditionalStatComponents[Normal] = StatAdders;
			//AdditionalStatComponents[Preview] = StatAdders;
			BaseStats[Normal] = statComp;
			BaseStats[Preview] = statComp;
			SyncCombinedStats();
		}*/
		/*const std::string& BaseCharacter::GetName() const
		{
			return this->Name;
		}*/
		CharacterStatus BaseCharacter::GetStatus() const
		{
			return Status;
		}
		void BaseCharacter::SetCharacterStatus(CharacterStatus charStatus)
		{
			this->Status = charStatus;
		}
		int BaseCharacter::GetUID() const
		{
			return CharacterID;
		}
		int BaseCharacter::GetLevel() const
		{
			return Level;
		}
		void BaseCharacter::SyncCombinedStat(Stat stat)
		{
			/*SyncingStats = true;
			int statVal = BaseStats[Status][stat];
			for (auto statComp = AdditionalStatComponents[Status].begin(); statComp != AdditionalStatComponents[Status].end(); ++statComp)
			{
				statVal += (*statComp->second.second.first)[stat];
			}
			CombinedStats[Status].SetStat(stat, statVal);
			SyncingStats = false;*/
		}
		void BaseCharacter::SyncCombinedStats()
		{
			for (int stat = 0; stat < StatCount; ++stat)
				SyncCombinedStat((Stat)stat);
		}
		void BaseCharacter::SyncActualToPreview(Stat stat)
		{

		}
		void BaseCharacter::SyncActualToPreview()
		{

		}
		bool BaseCharacter::AddStatComponent(const std::string& name, StatComponent* component, const CharacterStatus status, const bool manage, const bool replaceExisting)
		{
			/*auto it = AdditionalStatComponents[status].find(name);
			if (it != AdditionalStatComponents[status].end())
			{
				if (!replaceExisting)
					return false;
				if (it->second.second.second.connected())
					it->second.second.second.disconnect();
				if (it->second.first)
					delete it->second.second.first;
				if (status == CharacterStatus::Normal)
					it->second = HeldComponent(manage, ComponentConnection(component, component->AddStatChangedEvent(boost::bind(&BaseCharacter::HandleNormalStatsModifiedEvent, this, _1, _2, _3, _4, _5))));
				else
					it->second = HeldComponent(manage, ComponentConnection(component, component->AddStatChangedEvent(boost::bind(&BaseCharacter::HandlePreviewStatsModifiedEvent, this, _1, _2, _3, _4, _5))));
				return true;
			}
			if (status == CharacterStatus::Normal)
				AdditionalStatComponents[status][name] = HeldComponent(manage, ComponentConnection(component, component->AddStatChangedEvent(boost::bind(&BaseCharacter::HandleNormalStatsModifiedEvent, this, _1, _2, _3, _4, _5))));
			else
				AdditionalStatComponents[status][name] = HeldComponent(manage, ComponentConnection(component, component->AddStatChangedEvent(boost::bind(&BaseCharacter::HandlePreviewStatsModifiedEvent, this, _1, _2, _3, _4, _5))));
			return true;*/
			return true;
		}
		bool BaseCharacter::RemoveStatComponent(const std::string& name, const CharacterStatus status)
		{
			/*auto it = AdditionalStatComponents[status].find(name);
			if (it != AdditionalStatComponents[status].end())
			{
				if (it->second.second.second.connected())
					it->second.second.second.disconnect();
				if (it->second.first)
					delete it->second.second.first;
				AdditionalStatComponents[status].erase(it);
				return true;
			}*/
			return false;
		}
		int BaseCharacter::GetCombinedStat(Stat stat) const
		{
			return (*const_cast<StatComponent*>(&CombinedStats[Status]))[stat];
		}
		void BaseCharacter::HandleNormalStatsModifiedEvent(const std::string& compName, StatComponent*, Stat stat, int oldVal, int newVal)
		{
			if (!SyncingStats)
			{
				auto oldStatus = this->Status;
				this->Status = Normal;
				SyncCombinedStat(stat);
				this->Status = oldStatus;
			}
			
		}
		void BaseCharacter::HandlePreviewStatsModifiedEvent(const std::string& compName, StatComponent*, Stat stat, int oldVal, int newVal)
		{
			if (!SyncingStats)
			{
				auto oldStatus = this->Status;
				this->Status = Preview;
				SyncCombinedStat(stat);
				this->Status = oldStatus;
			}
			
		}
		bool BaseCharacter::operator==(const BaseCharacter& character) const
		{
			return this->CharacterID == character.CharacterID;
		}
		bool BaseCharacter::operator!=(const BaseCharacter& character) const
		{
			return !(*this == character);
		}

		BaseCharacter::~BaseCharacter()
		{
			/*for (int i = 0; i < StatusCount; ++i)
			{
				for(auto it = AdditionalStatComponents[i].begin(); it != AdditionalStatComponents[i].end(); ++it)
				{
					auto first = it->first;
					auto second = it->second;
					if (it->second.second.second.connected())
						it->second.second.second.disconnect();
					if (it->second.first)
					{
						
						delete it->second.second.first;
					}
				}
			}*/
			
		}
	}
}