#include "BattleScreen.h"
#include <Engine.h>
#include <graphics/visualizers/EntityComponentVisualizer.h>
#include <Graphics/Screens/BattlePartyVisualizer.h>
#include <Graphics/Screens/BattleQueueVisualizer.h>
#include <Graphics/Screens/CharacterPartyOverview.h>
#include <battle/mechanics/QueueTurnGenerator.h>
namespace Game
{
	using namespace Battle;
	namespace Graphics
	{
		namespace Screens
		{
			BattleScreen::BattleScreen(Engine* engine, boost::shared_ptr<Battle::BattleField> field, const std::string& background) : GameRocket::BasicRMLScreen("Battle Screen", "BattleScreen.rml", engine, engine->GetUID()), Field(field), SFGUIWindow(sfg::Window::Create()), LastUpdate(engine->GetTime()),
				BackgroundImage(engine->GetContentManager().RequestTexture(background, Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::BattleBack, engine->GetTime())), CommandVis(boost::make_shared<StandardCharacterCommandVisualizer>(engine)),
				ActiveCharacter(nullptr)
				//BackgroundImage(engine->GetContentManager().RequestTexture(background, Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::BattleBack, engine->GetTime()))
			{
				sf::Vector2f scale;
				auto size = BackgroundImage.GetBaseSprite().getGlobalBounds();
				scale.x = engine->GetResolution().x / size.width;
				scale.y = engine->GetResolution().y / size.height;
				BackgroundImage.SetScale(scale);
			}
			BattleScreen::BattleScreen(Engine* engine, Character::bparty_ptr characterParty, Character::bparty_ptr enemyParty, const std::string& background) : GameRocket::BasicRMLScreen("Battle Screen", "BattleScreen.rml", engine, engine->GetUID()),
				Field(new BattleField(characterParty, enemyParty)), SFGUIWindow(sfg::Window::Create()), LastUpdate(engine->GetTime()),
				BackgroundImage(engine->GetContentManager().RequestTexture(background, Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::BattleBack, engine->GetTime())), 
				CommandVis(boost::make_shared<StandardCharacterCommandVisualizer>(engine)), ActiveCharacter(nullptr)
				//BackgroundImage(engine->GetContentManager().RequestTexture(background, Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::BattleBack, engine->GetTime()))
			{
				CommandVis->SetPosition(5.f, 405.f);
				for (auto it = characterParty->GetPartyMembers().begin(); it != characterParty->GetPartyMembers().end(); ++it)
				{
					it->second->GetStatsManager().SyncAllBattleStats();
				}
				sf::Vector2f QueueVisPosition(700.f, 50.f);
				//Field->PreBattlePhase();
				sf::Vector2f scale;
				auto size = BackgroundImage.GetBaseSprite().getGlobalBounds();
				scale.x = engine->GetResolution().x / size.width;
				scale.y = engine->GetResolution().y / size.height;
				BackgroundImage.SetScale(scale);

				engine->GetSoundSystem().AddSound("Rage Awakened", "Rage Awakened");
				engine->GetSoundSystem().PlaySectionWithStart("Rage Awakened", 0, true, 0, 15500, 205000);

				//Determine Character Positions
				PartyFormationData pData;
				sf::Vector2f cStartPos(525.f, 225.f);
				sf::Vector2f MemberSpacing(0, 85.f);
				sf::Vector2f AlternateSpace(15.f, 0.f);
				int i = 0;
				for (auto ch = characterParty->GetPartyMembersInOrder().begin(); ch != characterParty->GetPartyMembersInOrder().end(); ++ch, ++i)
				{
					pData.Positions.push_back(std::pair<sf::Vector2f, bool>(cStartPos + MemberSpacing * static_cast<float>(i) + AlternateSpace * (i % 2 == 0 ? 0.f : 1.f), false));
				}

				auto pvis = boost::make_shared<BattlePartyVisualizer>(engine, characterParty, pData, true, Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::Guardian);
				pvis->SetDrawPriority(0);
				AddToDrawList(characterParty->GetName() + BattlePartyVisIndexer, pvis);
				AddToUpdateList(characterParty->GetName() + BattlePartyVisIndexer, 0, pvis);

				pData.Positions.clear();
				i = 0;
				float enemyMax = 400.f - 25.f;
				for (auto ch = enemyParty->GetPartyMembersInOrder().begin(); ch != enemyParty->GetPartyMembersInOrder().end(); ++ch, ++i)
				{
					sf::Vector2f EnemyPosition (0.f, 0.f);
					auto enemySize = sf::Vector2f(548.f, 441.f);
					if (enemySize.x > enemyMax)
					{
						EnemyPosition.x = enemyMax - enemySize.x;
					}
					EnemyPosition.y += (500 - enemySize.y) / 2.f;
					pData.Positions.push_back(std::pair<sf::Vector2f, bool>(EnemyPosition, true));
				}

				auto epvis = boost::make_shared<BattlePartyVisualizer>(engine, enemyParty, pData, false, Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::Enemy);
				epvis->SetDrawPriority(0);
				AddToDrawList(enemyParty->GetName() + BattlePartyVisIndexer, epvis);
				AddToUpdateList(enemyParty->GetName() + BattlePartyVisIndexer, 0, epvis);

				auto genVis = boost::make_shared<BattleQueueVisualizer>(engine, dynamic_cast<QueueTurnGenerator*>(Field->GetTurnGenerator()), Field.get());
				Field->RegisterComponent(BattleQueueVisualizerIndex, genVis);
				genVis->SetDrawPriority(10);
				genVis->SetPosition(QueueVisPosition);
				AddToDrawList(BattleQueueVisualizerIndex, genVis);
				AddToUpdateList(BattleQueueVisualizerIndex, 0, genVis);
				Field->PreBattlePhase();
				Field->GetTurnGenerator()->AddQueueModifiedEventHandler(boost::bind(&BattleScreen::HandleQueueModified, this, _1, _2));
				/*sfg::Box::Ptr box = sfg::Box::Create( sfg::Box::HORIZONTAL );
				sfg::Button::Ptr button1 = sfg::Button::Create();
				sfg::Button::Ptr button2 = sfg::Button::Create();
				sfg::Label::Ptr label = sfg::Label::Create();
				sfg::Label::Ptr labelx = sfg::Label::Create();
				button1->SetLabel( "Foo" );
				button2->SetLabel( "Bar" );
				label->SetText( "Baz" );
				labelx->SetText( "Bazar" );

				// To add our widgets to the box we use the Pack() method instead of the
				// Add() method. This makes sure the widgets are added and layed out
				// properly in the box.
				box->Pack( button1, true );
				box->Pack( label );
				box->Pack( button2 );
				box->Pack(labelx);

				// Just as with the window we can set the spacing between widgets
				// withing a box.
				box->SetSpacing( 5.f );
				SFGUIWindow->SetStyle( SFGUIWindow->GetStyle() ^ sfg::Window::TITLEBAR );
				engine->GetActiveDesktop().Add(SFGUIWindow);
				engine->GetActiveDesktop().LoadThemeFromFile(engine->GetContentManager().GetResourcesDirectory() + "guithemes\\battlescreen.theme");
				SFGUIWindow->Add(box);*/

			}


			void BattleScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
			{
				GameScreen::draw(target, states);
			}

			void BattleScreen::Draw(sf::RenderTarget &window)
			{
				BackgroundImage.Draw(window);
				GameScreen::Draw(window);
				//engine->GetSFGUI().Display(window);
				CommandVis->Draw(window);
			}
			void BattleScreen::Draw(sf::RenderTarget &window, sf::RenderStates states)
			{
				BackgroundImage.Draw(window, states);
				GameScreen::Draw(window, states);
				CommandVis->Draw(window, states);
				//BasicRMLScreen::Draw(window, shader);
			}
			void BattleScreen::Update(const sf::Uint32 time, const float timescale)
			{
				BasicRMLScreen::Update(time, timescale);
				auto elapsed = sf::milliseconds(time - LastUpdate);
				Field->Update(time, timescale);
				CommandVis->Update(time, timescale);
				
				/*if (ActiveCharacter == nullptr)
				{
					ActiveCharacter = dynamic_cast<Character::BaseCharacter*>(Field->GetTurnGenerator()->GetReadyCharater()->GetOwner());
					if (ActiveCharacter != nullptr)
					{
						CommandVis->SetCharacter(ActiveCharacter);
					}
				}*/
				//Field->GetTurnGenerator()->
				//SFGUIWindow->Update(elapsed.asSeconds());
			}

			bool BattleScreen::HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult)
			{
				//SFGUIWindow->HandleEvent(inputModule->GetCurrentEvent());
				CommandVis->HandleKeyPressed(time, inputModule, actionResult);
				if (actionResult.IAction == ::Input::Confirm)
				{
					Field->EndCharacterTurn();
				}
				return true;
			}
			bool BattleScreen::HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult)
			{
				//SFGUIWindow->HandleEvent(inputModule->GetCurrentEvent());
				CommandVis->HandleKeyReleased(time, inputModule, actionResult);
				return true;
			}

			boost::shared_ptr<Battle::BattleField> BattleScreen::GetBattleField() const
			{
				return Field;
			}
			void BattleScreen::HandleQueueModified(Battle::TurnGenerator& gen, Battle::BattleMode mode)
			{
				if (mode == Battle::BattleMode::Real && gen.GetTurnQueue(mode).size() > 0)
				{
					std::cout << "Character ready " << (*gen.GetTurnQueue(mode).begin())->GetOwner()->GetName() << "\n";
					ActiveCharacter = dynamic_cast<Character::BaseCharacter*>((*gen.GetTurnQueue(mode).begin())->GetOwner());
				}
				
			}
			void BattleScreen::HandleCharacterTurnEnd(Character::BaseCharacter* character)
			{
			}
		}
	}
}