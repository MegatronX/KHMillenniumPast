#pragma once
#ifndef _BATTLESCREEN_H_
#define _BATTLESCREEN_H_

#include <Graphics/Sprites/AnimatedSprite.h>
#include <graphics/Screens/BasicRMLScreen.h>
#include <Graphics/Rocket/ElementTransformer.h>
#include <Graphics/Rocket/ElementTransformInterface.h>
#include <Graphics/Screens/CharacterCommandVisualizer.h>
#include <battle/BattleField.h>

#include <SFGUI/SFGUI.hpp>
namespace Game
{
	namespace Graphics
	{
		namespace Screens
		{
			class BattleScreen : public GameRocket::BasicRMLScreen
			{
			public:
				BattleScreen(Engine* engine, boost::shared_ptr<Battle::BattleField> field, const std::string& background = "");
				BattleScreen(Engine* engine, Character::bparty_ptr characterParty, Character::bparty_ptr enemyParty, const std::string& background = "");

				virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
				virtual void Draw(sf::RenderTarget &window) override;
				virtual void Draw(sf::RenderTarget &window, sf::RenderStates shader) override;
				virtual void Update(const sf::Uint32 time, const float timescale = 1.f) override;

				virtual bool HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult);
				virtual bool HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult);


				boost::shared_ptr<Battle::BattleField> GetBattleField() const;
			protected:
				void HandleQueueModified(Battle::TurnGenerator& gen, Battle::BattleMode mode); 
				void HandleCharacterTurnEnd(Character::BaseCharacter* character);
				Character::BaseCharacter* ActiveCharacter;
				boost::shared_ptr<Battle::BattleField> Field;
				boost::shared_ptr<CharacterCommandVisualizer> CommandVis;
				::Graphics::AnimatedSprite BackgroundImage;
				sfg::Window::Ptr SFGUIWindow;
				sfg::Label::Ptr labelx;
				sf::Uint32 LastUpdate;
			private:
			};
		}
	}
}

#endif