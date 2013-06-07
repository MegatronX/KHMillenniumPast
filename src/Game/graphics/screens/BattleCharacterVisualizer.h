#pragma once
#ifndef _BATTLECHARACTERVISUALIZER_H_
#define _BATTLECHARACTERVISUALIZER_H_

#include <Graphics/visualizers/EntityComponentVisualizer.h>
#include <Graphics/Sprites/AnimatedSprite.h>
#include <Character/BaseCharacter.h>
#include <Battle/BattleCharacterComponent.h>

namespace Game
{
	namespace Graphics
	{
		class BattleCharacterVisualizer : public EntityVisualizer
		{
		public:
			BattleCharacterVisualizer(Engine* eng, Character::BaseCharacter& character, Cache::GameStyle style = Cache::GameStyle::Main, Cache::World world = Cache::World::Any, Cache::ResourceClass rclass = Cache::ResourceClass::Guardian);
			BattleCharacterVisualizer(Engine* eng, Character::BaseCharacter& character, Battle::BattleCharacterComponent& bcharacter, Cache::GameStyle style = Cache::GameStyle::Main, Cache::World world = Cache::World::Any, Cache::ResourceClass rclass = Cache::ResourceClass::Guardian);

			virtual void Draw(sf::RenderTarget &window) override;
			virtual void Draw(sf::RenderTarget &window, sf::RenderStates states) override;

			virtual void Update(const sf::Uint32 time, const float TimeScale = 1.0) override;

			void StatusEffectTriggeredHandler(const StatusEffects::StatusEffect& eff);

			::Graphics::AnimatedSprite& GetPrimarySprite();
		protected:
		private:
			boost::shared_ptr<::Graphics::AnimatedSprite> CharacterPrimarySprite;
			std::map<int, boost::unordered_map<std::string, boost::shared_ptr<::Graphics::AnimatedSprite> > > CharacterSpriteAndEffects;
			Character::BaseCharacter* VisualizingCharacter;
			Battle::BattleCharacterComponent* VisualizingBattleCharacter;
		};

	}
}

#endif