#pragma once
#ifndef _CHARACTEROVERVIEWVISUALIZER_H_
#define _CHARACTEROVERVIEWVISUALIZER_H_

#include <Graphics/Visualizers/EntityComponentVisualizer.h>
#include <battle/BattleCharacterComponent.h>
#include <Graphics/Sprites/AnimatedSprite.h>
namespace Game
{
	namespace Graphics
	{
		const std::string CharacterVisualHandlerIndex = "VisualizerHandler";

		//Sub Visualization Classes

		//Visualize active status effects

		class ActiveStatusEffectsStackVisualizer : public ::Graphics::AnimatedDraw
		{
		public:
			ActiveStatusEffectsStackVisualizer(const sf::Vector2f& pos, bool growLeft = true);
			void PushStatusEffect(const std::string& name);
			void PushStatusEffectToPosition(const std::string& name, const unsigned int pos);
			bool VisualizingStatusEffect(const std::string& name);
			bool RemoveStatusEffect(const std::string& name);
		protected:
		private:
			sf::Vector2f Position;
			bool GrowLeft;
			std::deque<boost::shared_ptr<::Graphics::DrawInterface> > StatusEffectIcons;
		};

		//Stat bar visualizer
		const std::string StatBarStatChangeIndex = "StatBarChangeIndex";
		class StatBarVisualizer : public ::Graphics::AnimatedDraw
		{
		public:
			StatBarVisualizer(Engine* eng, Character::BaseCharacter& character, Character::Stat targetstat, sf::Vector2f& pos);
			StatBarVisualizer(Engine* eng, Character::BaseCharacter& character, Character::Stat targetstat, sf::Vector2f& pos, boost::shared_ptr<sf::Font> statValFont, const sf::Uint32 statValSize, const sf::Color& statValColour = sf::Color::White, const sf::Color& statValShadow = sf::Color::Black);
			//StatBarVisualizer(const StatBarVisualizer& ref);
			void Draw(sf::RenderTarget &window) override;
			void Draw(sf::RenderTarget &window, sf::RenderStates states) override;

			void Update(const sf::Uint32 time, const float TimeScale = 1.0) override;

			//Used to bind/unbind to stat change events
			void BindToStat();
			void UnbindToStat();
			//StatBarVisualizer& operator=(const StatBarVisualizer& ref);

			//~StatBarVisualizer();
		protected:

			void HandleStatChange(Character::StatsManager& mng, const Character::Stat stat, const int oldVal, const int newVal);
			std::string HandlerIndexer;
			Character::Stat TargetStat;
			float BarPercent;
			Character::BaseCharacter& TargetCharacter;
			boost::shared_ptr<sf::Texture> StaticBackgroundTx;
			sf::Sprite StaticBackground;
			::Graphics::AnimatedSprite StatBar;
			sf::Vector2f Position;
			sf::Vector2f InitScale;
			boost::shared_ptr<sf::Font> StatTextFont;
			sf::Text CurrentValue;
			sf::Text Divider;
			sf::Text MaxValue;
			int CValue;
			int MValue;
			Engine* Eng;
			sf::VertexArray HealthBarPath;
		};

		//Main Visualization Class

		class CharacterBattleOverviewVisualizer : public EntityVisualizer
		{
		public:
			CharacterBattleOverviewVisualizer(Engine* engine, Character::BaseCharacter& characterVis, sf::Vector2f& pos);
			//CharacterBattleOverviewVisualizer(const CharacterBattleOverviewVisualizer& ref);
			void Draw(sf::RenderTarget &window) override;
			void Draw(sf::RenderTarget &window, sf::RenderStates states) override;

			void Update(const sf::Uint32 time, const float TimeScale = 1.0) override;
			//Used to add/remove event handlers on character
			void BindToCharacter();
			void UnbindToCharacter();
			//CharacterBattleOverviewVisualizer& operator=(const CharacterBattleOverviewVisualizer& ref);
			//~CharacterBattleOverviewVisualizer();
		protected:
			void HandleStatChange(Character::StatsManager& mng, const Character::Stat stat, const int oldVal, const int newVal);
			void HandleStatusEffectChange(StatusEffects::StatusEffectsManager* mng, const std::string& seName, const bool removed);

			void AddStatusEffectToOverview(StatusEffects::StatusEffectsManager* mng, const std::string& seName, const bool removed);
		private:
			std::vector<std::pair<std::string, boost::shared_ptr<::Graphics::DrawInterface> > > SEIcons;
			//std::array< StatBarVisualizer, 3> StatBars;
			std::vector<StatBarVisualizer> StatBars;
			//std::map<std::string, boost::shared_ptr<::Graphics::DrawInterface> > SEIcons;
			Character::BaseCharacter& VisualizingCharacter;
			sf::Vector2f Position;
		};
	}
}

#endif