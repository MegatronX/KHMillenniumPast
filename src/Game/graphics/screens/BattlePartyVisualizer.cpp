#include "BattlePartyVisualizer.h"

namespace Game
{
	namespace Graphics
	{
		const std::string BattlePartyVisIndexer = "BattlePartyVisualizer";

		PartyFormationData::PartyFormationData() : MemberSpacing(0.f, 0.f), RowOffset(0.f), OrientLeft(true), AreaConstraint(0.f, 0.f, 0.f, 0.f)
		{
		}
		BattlePartyVisualizer::BattlePartyVisualizer(Engine* eng, Character::bparty_ptr characterParty, PartyFormationData& pFormData, bool playerParty, Cache::GameStyle style, Cache::World world, Cache::ResourceClass rclass) : EntityVisualizer(eng, characterParty.get())
		{
			if (characterParty.get() != nullptr)
			{
				int i = 0;
				for (auto member = characterParty->GetPartyMembersInOrder().begin(); member != characterParty->GetPartyMembersInOrder().end(); ++member, ++i)
				{
					auto chVis = boost::make_shared<BattleCharacterVisualizer>(eng, *(*member), style, world, rclass);
					CharacterVisualizers[(*member)->GetName()] = chVis;//boost::make_shared<BattleCharacterVisualizer>(eng, *(*member), style, world, rclass);
					CharacterVisualizersInOrder.push_back(std::pair<std::string, boost::shared_ptr<BattleCharacterVisualizer> >((*member)->GetName(), chVis));
					auto& chSpr = chVis->GetPrimarySprite();

					//check Formatio Data for position/orientation
					bool OrientLeft = pFormData.OrientLeft;
					auto posFromMap = pFormData.NameIndexedPositions.find((*member)->GetName());
					if (posFromMap != pFormData.NameIndexedPositions.end())
					{
						//Found position data
						OrientLeft = posFromMap->second.second;
						chVis->SetPosition(posFromMap->second.first);
					}
					else
					{
						if (i < pFormData.Positions.size())
						{
							OrientLeft = pFormData.Positions[i].second;
							chVis->SetPosition(pFormData.Positions[i].first);
						}
						else
						{
							//Need to calculate positioning
						}
					}

					if (!OrientLeft)
					{
						//Need to flip sprite
						auto sprSize = chSpr.GetBaseSprite().getLocalBounds();
						chSpr.GetAnimator().setFlipped(true);
						//auto& prevOrigin = chSpr.GetBaseSprite().getOrigin();
						//chSpr.GetBaseSprite().setOrigin(sprSize.width  / 2.f, sprSize.height / 2.f);
						//chSpr.GetBaseSprite().setScale(chSpr.GetBaseSprite().getScale().x * -1, chSpr.GetBaseSprite().getScale().y);
						//chSpr.SetPosition(chSpr.GetPosition() + sf::Vector2f(sprSize.width, sprSize.height));
						//chSpr.GetBaseSprite().setOrigin(prevOrigin);
					}
					if (playerParty)
					{
						//chVis->SetPosition(eng->GetResolution().x / 2 + 110, eng->GetResolution().y / 2 + 100 * i - 128);
						auto ovVis = boost::make_shared<StandardBattleStatusVisualizer>(eng, *(*member));
						ovVis->SetPosition(sf::Vector2f(500, 400) + sf::Vector2f(60 * i, 50 * i));
						CharacterOverviewVisualizers[(*member)->GetName()] = ovVis;
						CharacterOverviewVisualizersInOrder.push_back(std::pair<std::string, boost::shared_ptr<CharacterBattleStatusVisualizer> >((*member)->GetName(), ovVis));
						ovVis->BindOnCharacter();
					}
					else
					{
						
					}
					chSpr.GetAnimator().playAnimation("Idle", true);
					//chSpr->GetAnimator().playAnimation("Idle", true);
					//CharacterVisualizers.push_back(boost::make_shared<BattleCharacterVisualizer>(eng, *(*member), style, world, rclass));
					//CharacterVisualizers[i]->
				}
			}
		}
		BattlePartyVisualizer::BattlePartyVisualizer(Engine* eng, Character::bparty_ptr characterParty, Battle::battleparty_ptr battleParty, bool playerParty) : EntityVisualizer(eng, characterParty.get())
		{

		}

		void BattlePartyVisualizer::Draw(sf::RenderTarget &window)
		{
			//sf::RenderStates states;
			//states.transform *= GetTransform();
			for (auto it = CharacterVisualizersInOrder.begin(); it != CharacterVisualizersInOrder.end(); ++it)
			{
				it->second->Draw(window);
			}
			for (auto it = CharacterOverviewVisualizersInOrder.begin(); it != CharacterOverviewVisualizersInOrder.end(); ++it)
			{
				it->second->Draw(window);
			}
		}
		void BattlePartyVisualizer::Draw(sf::RenderTarget &window, sf::RenderStates states)
		{
			//states.transform *= GetTransform();
			for (auto it = CharacterVisualizersInOrder.rbegin(); it != CharacterVisualizersInOrder.rend(); ++it)
			{
				(*it).second->Draw(window, states);
			}
			for (auto it = CharacterOverviewVisualizersInOrder.rbegin(); it != CharacterOverviewVisualizersInOrder.rend(); ++it)
			{
				it->second->Draw(window, states);
			}
		}

		void BattlePartyVisualizer::Update(const sf::Uint32 time, const float TimeScale)
		{
			for (auto it = CharacterVisualizersInOrder.rbegin(); it != CharacterVisualizersInOrder.rend(); ++it)
			{
				(*it).second->Update(time, TimeScale);
			}
			for (auto it = CharacterOverviewVisualizersInOrder.begin(); it != CharacterOverviewVisualizersInOrder.end(); ++it)
			{
				it->second->Update(time, TimeScale);
			}
		}

		BattlePartyVisualizer::~BattlePartyVisualizer()
		{
			for (auto it = CharacterOverviewVisualizers.begin(); it != CharacterOverviewVisualizers.end(); ++it)
			{
				it->second->UnBindOnCharacter();
			}
		}
	}
}