#include "CharacterOverviewVisualizer.h"

namespace Game
{
	using namespace Character;
	namespace Graphics
	{

		ActiveStatusEffectsStackVisualizer::ActiveStatusEffectsStackVisualizer(const sf::Vector2f& pos, bool growLeft) : Position(pos), GrowLeft(growLeft)
		{

		}
		void ActiveStatusEffectsStackVisualizer::PushStatusEffect(const std::string& name)
		{

		}
		void ActiveStatusEffectsStackVisualizer::PushStatusEffectToPosition(const std::string& name, const unsigned int pos)
		{

		}
		bool ActiveStatusEffectsStackVisualizer::VisualizingStatusEffect(const std::string& name)
		{
			return false;
		}
		bool ActiveStatusEffectsStackVisualizer::RemoveStatusEffect(const std::string& name)
		{
			return false;
		}

		//Stat Bar Vis


		StatBarVisualizer::StatBarVisualizer(Engine* eng, Character::BaseCharacter& character, Character::Stat targetstat, sf::Vector2f& pos) : TargetCharacter(character), Eng(eng), TargetStat(targetstat),
			StaticBackgroundTx(eng->GetContentManager().RequestTexture(StatNameLookup.find(targetstat)->second + " Bar", Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::GUIBattleElement, eng->GetTime())), 
			StaticBackground(*StaticBackgroundTx), StatBar(eng->GetContentManager().RequestTexture(StatNameLookup.find(targetstat)->second, Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::GUIBattleElement, eng->GetTime())),
			Position(pos), HandlerIndexer(StatBarStatChangeIndex + StatNameLookup.find(targetstat)->second), StatTextFont(eng->GetContentManager().RequestFont("calibri", eng->GetTime()))
		{
			//BarPercent = static_cast<float>(val) / static_cast<float>(maxVal);
			
			
			//boost::shared_ptr<::Graphics::AnimatedDraw>
			float StartRatio = 1.f;
			StaticBackground.setPosition(pos);
			StatBar.SetPosition(pos + sf::Vector2f(4.f, 5.f));
			switch(targetstat)
			{
			case Character::Stat::HP:
				{
					CValue = character.GetStatsManager().GetCurrentHP();
					MValue = character.GetStatsManager().GetBattleStat(targetstat);
					StartRatio = static_cast<float>(CValue) / static_cast<float>(MValue);
					//StartRatio = static_cast<float>(character.GetStatsManager().GetCurrentHP()) / static_cast<float>(character.GetStatsManager().GetBattleStat(targetstat)); 
					break;
				}
			case Character::Stat::MP:
				{
					CValue = character.GetStatsManager().GetCurrentMP();
					MValue = character.GetStatsManager().GetBattleStat(targetstat);
					StartRatio = static_cast<float>(CValue) / static_cast<float>(MValue);
					//StartRatio = static_cast<float>(character.GetStatsManager().GetCurrentMP()) / static_cast<float>(character.GetStatsManager().GetBattleStat(targetstat));
					break;
				}
			case Character::SP:
				{
					CValue = character.GetStatsManager().GetCurrentSP();
					MValue = character.GetStatsManager().GetBattleStat(targetstat);
					StartRatio = static_cast<float>(CValue) / static_cast<float>(MValue);
					//StartRatio = static_cast<float>(character.GetStatsManager().GetCurrentSP()) / static_cast<float>(character.GetStatsManager().GetBattleStat(targetstat));
					break;
				}
			}
			CurrentValue.setString(boost::lexical_cast<std::string>(CValue));
			CurrentValue.setFont(*StatTextFont);
			CurrentValue.setPosition(pos);
			Divider.setString("/");
			Divider.setPosition(CurrentValue.getPosition() + sf::Vector2f(52, 0));
			Divider.setFont(*StatTextFont);
			MaxValue.setString(boost::lexical_cast<std::string>(MValue));
			MaxValue.setPosition(Divider.getPosition() + sf::Vector2f(12, 0));
			MaxValue.setFont(*StatTextFont);
			StatBar.SetScale(StartRatio, 1.f);
		}
		StatBarVisualizer::StatBarVisualizer(Engine* eng, Character::BaseCharacter& character, Character::Stat targetstat, sf::Vector2f& pos, boost::shared_ptr<sf::Font> statValFont, const sf::Uint32 statValSize, const sf::Color& statValColour, const sf::Color& statValShadow): TargetCharacter(character), Eng(eng), TargetStat(targetstat),
			StaticBackgroundTx(eng->GetContentManager().RequestTexture(StatNameLookup.find(targetstat)->second + " Bar", Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::GUIBattleElement, eng->GetTime())), 
			StaticBackground(*StaticBackgroundTx), StatBar(eng->GetContentManager().RequestTexture(StatNameLookup.find(targetstat)->second, Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::GUIBattleElement, eng->GetTime())),
			Position(pos), HandlerIndexer(StatBarStatChangeIndex + StatNameLookup.find(targetstat)->second), StatTextFont(statValFont)
		{
			float StartRatio = 1.f;
			StaticBackground.setPosition(pos);
			StatBar.SetPosition(pos + sf::Vector2f(5.f, 8.f));
			switch(targetstat)
			{
			case Character::Stat::HP:
				{
					CValue = character.GetStatsManager().GetCurrentHP();
					MValue = character.GetStatsManager().GetBattleStat(targetstat);
					StartRatio = static_cast<float>(CValue) / static_cast<float>(MValue);
					//StartRatio = static_cast<float>(character.GetStatsManager().GetCurrentHP()) / static_cast<float>(character.GetStatsManager().GetBattleStat(targetstat)); 
					break;
				}
			case Character::Stat::MP:
				{
					CValue = character.GetStatsManager().GetCurrentMP();
					MValue = character.GetStatsManager().GetBattleStat(targetstat);
					StartRatio = static_cast<float>(CValue) / static_cast<float>(MValue);
					//StartRatio = static_cast<float>(character.GetStatsManager().GetCurrentMP()) / static_cast<float>(character.GetStatsManager().GetBattleStat(targetstat));
					break;
				}
			case Character::SP:
				{
					CValue = character.GetStatsManager().GetCurrentSP();
					MValue = character.GetStatsManager().GetBattleStat(targetstat);
					StartRatio = static_cast<float>(CValue) / static_cast<float>(MValue);
					//StartRatio = static_cast<float>(character.GetStatsManager().GetCurrentSP()) / static_cast<float>(character.GetStatsManager().GetBattleStat(targetstat));
					break;
				}
			}
			CurrentValue.setString(boost::lexical_cast<std::string>(CValue));
			CurrentValue.setFont(*StatTextFont);
			CurrentValue.setPosition(pos);
			Divider.setString("/");
			Divider.setPosition(CurrentValue.getPosition() + sf::Vector2f(48, 0));
			Divider.setFont(*StatTextFont);
			MaxValue.setString(boost::lexical_cast<std::string>(MValue));
			MaxValue.setPosition(Divider.getPosition() + sf::Vector2f(10, 0));
			MaxValue.setFont(*StatTextFont);
			StatBar.SetScale(StartRatio, 1.f);
		}
		void StatBarVisualizer::Draw(sf::RenderTarget &window)
		{
			window.draw(StaticBackground);
			StatBar.Draw(window);
			window.draw(CurrentValue);
			window.draw(Divider);
			window.draw(MaxValue);
		}
		void StatBarVisualizer::Draw(sf::RenderTarget &window, sf::RenderStates states)
		{

			window.draw(StaticBackground, states);
			StatBar.Draw(window, states);
		}

		void StatBarVisualizer::Update(const sf::Uint32 time, const float TimeScale)
		{
			StatBar.Update(time, TimeScale);
		}

		void StatBarVisualizer::BindToStat()
		{
			TargetCharacter.GetStatsManager().AddStatChangeHandler(HandlerIndexer, boost::bind(&StatBarVisualizer::HandleStatChange, this, _1, _2, _3, _4));
		}
		void StatBarVisualizer::UnbindToStat()
		{
			TargetCharacter.GetStatsManager().RemoveStatChangeHandler(HandlerIndexer);
		}
		void StatBarVisualizer::HandleStatChange(Character::StatsManager& mng, const Character::Stat stat, const int oldVal, const int newVal)
		{
			if (stat == TargetStat && oldVal != newVal)
			{

				float statRatio = 0.f;
				int newCVal = 0;
				int newMVal = 0;
				switch (stat)
				{
				case Stat::HP:
					newCVal = mng.GetCurrentHP();
					newMVal = mng.GetBattleStat(stat);
					statRatio = static_cast<float>(newCVal) / static_cast<float>(newMVal);
					break;
				case Stat::MP:
					newCVal = mng.GetCurrentMP();
					newMVal = mng.GetBattleStat(stat);
					statRatio = static_cast<float>(newCVal) / static_cast<float>(newMVal);
					break;
				case Stat::SP:
					newCVal = mng.GetCurrentSP();
					newMVal = mng.GetBattleStat(stat);
					statRatio = static_cast<float>(newCVal) / static_cast<float>(newMVal);
					break;
				default:
					break;
				}
				if (newCVal != CValue || newMVal != MValue)
				{
					StatBar.ClearTransforms(Eng->GetTime(), false);
					StatBar.AddTransform("ScaleTransform", boost::shared_ptr<::Graphics::BaseTransform>(new ::Graphics::ScaleTransform(StatBar, sf::Vector2f(statRatio, StatBar.GetScale().y), Eng->GetTime(), 1250)));
					CurrentValue.setString(boost::lexical_cast<std::string>(newCVal));
					MaxValue.setString(boost::lexical_cast<std::string>(newMVal));
					CValue = newCVal;
					MValue = newMVal;
				}
				
			}
		}

		/*StatBarVisualizer::~StatBarVisualizer()
		{
			
		}*/
		//CharacterBattleOverviewVisualizer

		CharacterBattleOverviewVisualizer::CharacterBattleOverviewVisualizer(Engine* engine, Character::BaseCharacter& characterVis, sf::Vector2f& pos) : EntityVisualizer(engine, &characterVis), VisualizingCharacter(characterVis), Position(pos)
		{
			
			for (auto effect = characterVis.GetStatusEffectsManager().GetActiveStatusEffects().begin(); effect != characterVis.GetStatusEffectsManager().GetActiveStatusEffects().end(); ++effect)
			{
				AddStatusEffectToOverview(&characterVis.GetStatusEffectsManager(), effect->first, false);
			}
			sf::Vector2f BarPos = sf::Vector2f(100.f, 500.f);
			StatBars.reserve(VolateStatCount);
			for (int i = 0; i < Character::VolatileStats.size(); ++i)
			{
				StatBars.push_back(StatBarVisualizer(engine, characterVis, Character::VolatileStats[i], BarPos + sf::Vector2f(20.f * i, 15.f * i)));
			}
		}

		/*CharacterBattleOverviewVisualizer::CharacterBattleOverviewVisualizer(const CharacterBattleOverviewVisualizer& ref) : EntityVisualizer(ref), VisualizingCharacter(ref.VisualizingCharacter), Position(ref.Position)
		{

		}
		CharacterBattleOverviewVisualizer& CharacterBattleOverviewVisualizer::operator=(const CharacterBattleOverviewVisualizer& ref)
		{

		}*/

		void CharacterBattleOverviewVisualizer::BindToCharacter()
		{
			VisualizingCharacter.GetStatsManager().AddStatChangeHandler(CharacterVisualHandlerIndex, boost::bind(&CharacterBattleOverviewVisualizer::HandleStatChange, this, _1, _2, _3, _4));
			VisualizingCharacter.GetStatusEffectsManager().AddStatusEffectChangedHandler(CharacterVisualHandlerIndex, boost::bind(&CharacterBattleOverviewVisualizer::HandleStatusEffectChange, this, _1, _2, _3));
			for (auto sb = StatBars.begin(); sb != StatBars.end(); ++sb)
			{
				sb->BindToStat();
			}
		}
		void CharacterBattleOverviewVisualizer::UnbindToCharacter()
		{
			for (auto sb = StatBars.begin(); sb != StatBars.end(); ++sb)
			{
				sb->UnbindToStat();
			}
			VisualizingCharacter.GetStatsManager().RemoveStatChangeHandler(CharacterVisualHandlerIndex);
			VisualizingCharacter.GetStatusEffectsManager().RemoveStatusEffectChangedHandler(CharacterVisualHandlerIndex);
		}

		/*(CharacterBattleOverviewVisualizer::~CharacterBattleOverviewVisualizer()
		{
			
			
		}*/
		void CharacterBattleOverviewVisualizer::HandleStatChange(Character::StatsManager& mng, const Character::Stat stat, const int oldVal, const int newVal)
		{
			switch (stat)
			{
			}
		}
		void CharacterBattleOverviewVisualizer::HandleStatusEffectChange(StatusEffects::StatusEffectsManager* mng, const std::string& seName, const bool removed)
		{
			AddStatusEffectToOverview(mng, seName, removed);
		}

		void CharacterBattleOverviewVisualizer::Draw(sf::RenderTarget &window)
		{
			for (auto icon = SEIcons.begin(); icon != SEIcons.end(); ++icon)
			{
				icon->second->Draw(window);
			}
			for (auto bar = StatBars.begin(); bar != StatBars.end(); ++bar)
			{
				bar->Draw(window);
			}
		}
		void CharacterBattleOverviewVisualizer::Draw(sf::RenderTarget &window, sf::RenderStates states)
		{

		}

		void CharacterBattleOverviewVisualizer::Update(const sf::Uint32 time, const float TimeScale)
		{
			for (auto bar = StatBars.begin(); bar != StatBars.end(); ++bar)
			{
				bar->Update(time, TimeScale);
			}
		}

		void CharacterBattleOverviewVisualizer::AddStatusEffectToOverview(StatusEffects::StatusEffectsManager* mng, const std::string& seName, const bool removed)
		{
			if (removed)
			{
				for (auto it = SEIcons.begin(); it != SEIcons.end(); ++it)
				{
					if (it->first == seName)
					{
						SEIcons.erase(it);
						break;
					}
				}
			}
			else
			{
				auto tx = Eng->GetContentManager().RequestTexture(seName + "Icon", Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::GUIBattleElement, Eng->GetTime());
				auto spr = boost::make_shared<::Graphics::AnimatedSprite>(tx);
				spr->SetPosition(Position + sf::Vector2f(-30 * SEIcons.size(), 0));
				SEIcons.push_back(std::pair<std::string, boost::shared_ptr<::Graphics::DrawInterface>>(seName, spr));
				//SEIcons[seName] = make_shared<sf::Sprite>()
			}
		}

	}
}