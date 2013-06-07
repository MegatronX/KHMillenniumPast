#pragma once
#ifndef _CHARACTERPARTYOVERVIEW_H_
#define _CHARACTERPARTYOVERVIEW_H_

#include <graphics/Screens/CharacterOverviewVisualizer.h>
#include <character/Party.h>

namespace Game
{
	namespace Graphics
	{
		const std::string PartyOverviewIndex = "PartyOverviewVis";
		class CharacterPartyOverview : public EntityVisualizer
		{
		public:
			CharacterPartyOverview(Engine* eng, Character::bparty_ptr playerParty);

			void Draw(sf::RenderTarget &window) override;
			void Draw(sf::RenderTarget &window, sf::RenderStates states) override;

			void Update(const sf::Uint32 time, const float TimeScale = 1.0) override;
		protected:
		private:
			std::map<int, boost::unordered_map<std::string, boost::shared_ptr<CharacterBattleOverviewVisualizer> > > CharacterOverviews;
		};
	}
}

#endif