#pragma once
#ifndef _BATTLEPARTYVIS_H_
#define _BATTLEPARTYVIS_H_

#include <Graphics/visualizers/EntityComponentVisualizer.h>
#include <Graphics/Screens/BattleCharacterVisualizer.h>
#include <Graphics/Screens/CharacterBattleStatusVisualizer.h>
#include <character/Party.h>

namespace Game
{
	namespace Graphics
	{

		struct PartyFormationData
		{
			PartyFormationData();
			//Used for dedicated positioning
			std::vector<std::pair<sf::Vector2f, bool> > Positions; //Vector2f = position, bool = orient right if true, else orient left
			boost::unordered_map<std::string, std::pair<sf::Vector2f, bool> > NameIndexedPositions;
			//Used for automatic spacing calculation
			sf::Vector2f MemberSpacing;
			float RowOffset; //spacing different between being in front/back rows
			bool OrientLeft;
			sf::FloatRect AreaConstraint;
		};
		extern const std::string BattlePartyVisIndexer;
		class BattlePartyVisualizer : public EntityVisualizer
		{
		public:
			BattlePartyVisualizer(Engine* eng, Character::bparty_ptr characterParty, PartyFormationData& partyFormationData, bool playerParty = false, Cache::GameStyle style = Cache::GameStyle::Main, Cache::World world = Cache::World::Any, Cache::ResourceClass rclass = Cache::ResourceClass::Guardian);
			BattlePartyVisualizer(Engine* eng, Character::bparty_ptr characterParty, Battle::battleparty_ptr battleParty, bool playerParty = false);

			void Draw(sf::RenderTarget &window) override;
			void Draw(sf::RenderTarget &window, sf::RenderStates states) override;

			void Update(const sf::Uint32 time, const float TimeScale = 1.0) override;
			~BattlePartyVisualizer();
		protected:
		private:
			//std::vector<boost::shared_ptr<BattleCharacterVisualizer> > CharacterVisualizers;
			std::vector<std::pair<std::string, boost::shared_ptr<BattleCharacterVisualizer> > > CharacterVisualizersInOrder;
			std::vector<std::pair<std::string, boost::shared_ptr<CharacterBattleStatusVisualizer> > > CharacterOverviewVisualizersInOrder;
			boost::unordered_map<std::string, boost::shared_ptr<BattleCharacterVisualizer> > CharacterVisualizers;
			boost::unordered_map<std::string, boost::shared_ptr<CharacterBattleStatusVisualizer> > CharacterOverviewVisualizers;
			//std::map<int, boost::unordered_map<std::string, boost::shared_ptr<::Graphics::AnimatedDraw> > DrawLists;
			//boost::unordered_map<std::string, void*> CharacterVisualizers;
		};
	}
}

#endif