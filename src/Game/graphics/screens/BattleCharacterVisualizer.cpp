#include "BattleCharacterVisualizer.h"

namespace Game
{
	namespace Graphics
	{
		BattleCharacterVisualizer::BattleCharacterVisualizer(Engine* eng, Character::BaseCharacter& character, Cache::GameStyle style, Cache::World world, Cache::ResourceClass rclass) : VisualizingCharacter(&character), EntityVisualizer(eng, &character)
		{
			auto tx = eng->GetContentManager().RequestTexture(character.GetName() + " Battle", style, world, rclass, eng->GetTime());
			bool validImport = false;
			auto& sprData = eng->GetContentManager().RequestSpriteImportData(character.GetName() + " Battle", style, validImport);
			
			//auto spr = boost::shared_ptr<::Graphics::AnimatedSprite>(new ::Graphics::AnimatedSprite(tx, sprData));
			auto chSpr = boost::make_shared<::Graphics::AnimatedSprite>(tx, sprData);
			//chSpr->GetAnimator().playAnimation("Idle", true);
			
			CharacterPrimarySprite = chSpr;
			CharacterSpriteAndEffects[0][character.GetName()] = chSpr;//boost::shared_ptr<::Graphics::AnimatedSprite>(new ::Graphics::AnimatedSprite(tx, sprData));//spr;
			//auto spr = boost::shared_ptr<::Graphics::AnimatedSprite>(new ::Graphics::AnimatedSprite())
			//CharacterSpriteAndEffects[0][character.GetName()] = boost::shared_ptr<::Graphics::AnimatedSprite>(new ::Graphics)
		}
		BattleCharacterVisualizer::BattleCharacterVisualizer(Engine* eng, Character::BaseCharacter& character, Battle::BattleCharacterComponent& bcharacter, Cache::GameStyle style, Cache::World world, Cache::ResourceClass rclass) : VisualizingCharacter(&character), VisualizingBattleCharacter(&bcharacter), EntityVisualizer(eng, &character)
		{
			auto tx = eng->GetContentManager().RequestTexture(character.GetName() + " Battle", style, world, rclass, eng->GetTime());
			bool validImport = false;
			auto& sprData = eng->GetContentManager().RequestSpriteImportData(character.GetName() + " Battle", style, validImport);

			//auto spr = boost::shared_ptr<::Graphics::AnimatedSprite>(new ::Graphics::AnimatedSprite(tx, sprData));
			CharacterSpriteAndEffects[0][character.GetName()] = boost::make_shared<::Graphics::AnimatedSprite>(tx, sprData);
		}

		void BattleCharacterVisualizer::Draw(sf::RenderTarget &window)
		{
			sf::RenderStates states;
			states.transform = GetTransform();
			for (auto priority = CharacterSpriteAndEffects.rbegin(); priority != CharacterSpriteAndEffects.rend(); ++priority)
			{
				for (auto drawable = priority->second.begin(); drawable != priority->second.end(); ++drawable)
				{
					drawable->second->Draw(window, states);
				}
			}
		}
		void BattleCharacterVisualizer::Draw(sf::RenderTarget &window, sf::RenderStates states)
		{
			states.transform *= GetTransform();
			for (auto priority = CharacterSpriteAndEffects.rbegin(); priority != CharacterSpriteAndEffects.rend(); ++priority)
			{
				for (auto drawable = priority->second.begin(); drawable != priority->second.end(); ++drawable)
				{
					drawable->second->Draw(window, states);
				}
			}
		}

		void BattleCharacterVisualizer::Update(const sf::Uint32 time, const float TimeScale)
		{
			for (auto priority = CharacterSpriteAndEffects.rbegin(); priority != CharacterSpriteAndEffects.rend(); ++priority)
			{
				for (auto drawable = priority->second.begin(); drawable != priority->second.end(); ++drawable)
				{
					drawable->second->Update(time, TimeScale);
				}
			}
		}

		void BattleCharacterVisualizer::StatusEffectTriggeredHandler(const StatusEffects::StatusEffect& eff)
		{

		}
		::Graphics::AnimatedSprite& BattleCharacterVisualizer::GetPrimarySprite()
		{
			return *CharacterPrimarySprite;
		}
	}
}