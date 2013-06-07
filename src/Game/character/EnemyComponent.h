#pragma once
#include <components/Component.h>
#include <boost/unordered_map.hpp>
namespace Game
{
	namespace Character
	{
		class EnemyComponent : public Components::Component
		{
		public:
			EnemyComponent();

			const boost::unordered_map<std::string, float>& GetLootTable() const;

			void AddLootEntry(const std::string& itemName, const float dropRate, bool AbsoluteDropRate = false);

			void RemoveLootEntry(const std::string& itemName);

			void IncrementLootEntry(const std::string& itemName, float inc);

			float GetDropRate(const std::string& itemName) const;

			int GetExpGranted(const std::string& index);

			int GetXpGranted() const;

			int GetMgXpGranted() const;

			int GetAPXpGranted() const;
		protected:
		private:
			boost::unordered_map<std::string, float> LootTable;
			boost::unordered_map<std::string, int> ExpGranters;
		};
	}
}