#include "CharacterPartyOverview.h"

namespace Game
{
	namespace Graphics
	{
		CharacterPartyOverview::CharacterPartyOverview(Engine* eng, Character::bparty_ptr playerParty) : EntityVisualizer(eng, playerParty.get())
		{
			int size = playerParty->GetPartyMembersInOrder().size();
			int count = 0;
			for (auto member = playerParty->GetPartyMembersInOrder().begin(); member != playerParty->GetPartyMembersInOrder().end(); ++member)
			{
				auto ch = boost::make_shared<CharacterBattleOverviewVisualizer>(eng, *(*member), sf::Vector2f(400, 350 + count * 80));
				CharacterOverviews[size - count][(*member)->GetName() + CharacterVisualHandlerIndex] = ch;
				ch->BindToCharacter();
				//Need code to unbind somewhere
				++count;
			}
		}

		void CharacterPartyOverview::Draw(sf::RenderTarget &window)
		{
			for (auto pmemberset = CharacterOverviews.rbegin(); pmemberset != CharacterOverviews.rend(); ++pmemberset)
			{
				for (auto pmember = pmemberset->second.begin(); pmember != pmemberset->second.end(); ++pmember)
				{
					pmember->second->Draw(window);
				}
			}
		}
		void CharacterPartyOverview::Draw(sf::RenderTarget &window, sf::RenderStates states)
		{
			for (auto pmemberset = CharacterOverviews.rbegin(); pmemberset != CharacterOverviews.rend(); ++pmemberset)
			{
				for (auto pmember = pmemberset->second.begin(); pmember != pmemberset->second.end(); ++pmember)
				{
					pmember->second->Draw(window, states);
				}
			}
		}

		void CharacterPartyOverview::Update(const sf::Uint32 time, const float TimeScale)
		{
			for (auto pmemberset = CharacterOverviews.rbegin(); pmemberset != CharacterOverviews.rend(); ++pmemberset)
			{
				for (auto pmember = pmemberset->second.begin(); pmember != pmemberset->second.end(); ++pmember)
				{
					pmember->second->Update(time, TimeScale);
				}
			}
		}
	}
}