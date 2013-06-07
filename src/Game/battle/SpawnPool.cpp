#include "SpawnPool.h"
#include <battle/BattleField.h>
namespace Game
{
	namespace Battle
	{
		SpawnConfiguration::SpawnConfiguration() : AlwaysSpawnSet(false)
		{

		}

		void SpawnConfiguration::AddSpawnableParty(const std::string& index, const std::vector<std::string>& members, float chance, bool absChance)
		{
		}

		void SpawnConfiguration::SetSpawnChance(const std::string& index, float chance, bool absChance)
		{
		}

		void SpawnConfiguration::NormalizeSpawnChances()
		{
		}


		SpawnPool::SpawnPool(BattleField* owner)
		{
			
		}
		SpawnPool::SpawnPool(BattleField* owner, const SpawnConfiguration& config) : SpConfig(config), Component(owner, owner != nullptr ? "SpawnPool" + owner->GetName() : "SpawnPoolNoOwner", "SpawnPool")
		{

		}

		void SpawnPool::SetSpawnConfiguration(const SpawnConfiguration& config)
		{
			SpConfig = config;
		}

		SpawnConfiguration& SpawnPool::GetConfiguration()
		{
			return SpConfig;
		}

		Character::bparty_ptr SpawnPool::SpawnParty(std::string partyName)
		{
			Character::bparty_ptr Party = Character::bparty_ptr();
			if (partyName.empty())
			{
				Party = Character::bparty_ptr(new Character::BaseParty(std::string(std::string("EnemyParty") + boost::lexical_cast<std::string>(SpawnPartyIDCounter))));
			}
			return Party;
		}

		//Character::party_ptr SpawnPool::SpawnBattleParty(std::string partyName)
		//{
		//}

		Character::bparty_ptr SpawnPool::SpawnParty(const std::vector<std::string>& members, std::string partyName)
		{
			Character::bparty_ptr Party = Character::bparty_ptr();
			if (partyName.empty())
			{
				Party = Character::bparty_ptr(new Character::BaseParty(std::string(std::string("EnemyParty") + boost::lexical_cast<std::string>(SpawnPartyIDCounter))));
			}
			return Party;
		}

		//Character::bparty_ptr SpawnPool::SpawnBattleParty(const std::vector<std::string>& members, std::string partyName)
		//{
		//}
	}
}