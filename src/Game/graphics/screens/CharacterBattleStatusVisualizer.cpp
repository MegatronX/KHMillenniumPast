#include "CharacterBattleStatusVisualizer.h"
#include <thor/Math.hpp>
#include <thor/Vectors.hpp>
#include <boost/bind.hpp>
namespace Game
{
	using namespace Character;
	namespace Graphics
	{
		CharacterBattleStatusVisualizer::CharacterBattleStatusVisualizer(Engine* eng, Character::BaseCharacter& character) : EntityVisualizer(eng, &character), VisualizingCharacter(character)
		{
			
		}
		void CharacterBattleStatusVisualizer::BindOnCharacter()
		{
			VisualizingCharacter.GetStatsManager().AddStatChangeHandler(BattleOverviewStatusVisualizerIndex, boost::bind(&CharacterBattleStatusVisualizer::HandleStatChange, this, _1, _2, _3, _4));
			VisualizingCharacter.GetStatusEffectsManager().AddStatusEffectChangedHandler(BattleOverviewStatusVisualizerIndex, boost::bind(&CharacterBattleStatusVisualizer::HandleStatusEffectChange, this, _1, _2, _3));
		}
		void CharacterBattleStatusVisualizer::UnBindOnCharacter()
		{
			VisualizingCharacter.GetStatsManager().RemoveStatChangeHandler(BattleOverviewStatusVisualizerIndex);
			VisualizingCharacter.GetStatusEffectsManager().RemoveStatusEffectChangedHandler(BattleOverviewStatusVisualizerIndex);
		}

	
		void CharacterBattleStatusVisualizer::HandleStatChange(Character::StatsManager& mng, const Character::Stat stat, const int oldVal, const int newVal)
		{

		}
		void CharacterBattleStatusVisualizer::HandleStatusEffectChange(StatusEffects::StatusEffectsManager* mng, const std::string& seName, const bool removed)
		{

		}


		//HP Bar Sprite

		HPBarSprite::HPBarSprite(boost::shared_ptr<sf::Texture> targetTexture, const sf::Vector2f& barSectionSize, const float circleRadius, const float circleDegrees, const float startAngle, const bool clockwise, const unsigned int circlePoints, const float thickness, const float barHPPortion)
			: TargetTexture(targetTexture), BarPortion(barHPPortion), CircleRadius(circleRadius), ArcAngle(circleDegrees), StartAngle(startAngle), BarSize(barSectionSize), BarPortionPath(barSectionSize), PointCount(circlePoints),
			CircleThickness(thickness), CirclePortionPath(sf::TrianglesStrip)
		{
			ArcAngle = std::fmod(ArcAngle, 360);
			if (circlePoints > 0 && ArcAngle > 0)
			{
				const unsigned int nbTotalPoints = (static_cast<float>(PointCount) / ArcAngle) * 360.f;
				const unsigned int nbActualPoints = static_cast<unsigned int>(ArcAngle / 360.f * nbTotalPoints);

				// Add center point, unless the pie is full
				//if (filledAngle != 0.f)
				//addPoint(shape, sf::Vector2f(0.f, 0.f));

				thor::PolarVector2f vector;//(innerRadius, StartingAngle);
				thor::PolarVector2f vectorOut;//(innerRadius + Thickness, StartingAngle);

				vector.r = CircleRadius;
				vectorOut.r = CircleRadius + CircleThickness;
				vector.phi = vectorOut.phi = startAngle;
				float incrementer = (360.f / nbTotalPoints) * (clockwise ? 1 : -1);
				for (unsigned int i = 0; i <= nbActualPoints; ++i)
				{
					vector.phi += incrementer;//incrementer * i + StartAngle;
					vectorOut.phi += incrementer;// * i + StartAngle;
					sf::Vector2f effVector = vector;
					//std::cout << "Vector Phi: " << vector.phi << ", Vector R: " << vector.r << " | Effective Vector X: " << effVector.x << ", Y: " << effVector.y << "\n";
					CirclePortionPath.append(sf::Vertex(effVector));//, sf::Color::Black));
					CirclePortionPath.append(sf::Vertex(vectorOut));//, sf::Color::Black));
					//addPoint(*this, vector);
				}
			}
			
			BarPortionPath.setTexture(TargetTexture.get());
			this->setTexture(TargetTexture.get());
			
			MapTexture();
		}

		void HPBarSprite::MapTexture()
		{
			auto texture = getTexture();
			if (texture != nullptr && CirclePortionPath.getVertexCount() > 0)
			{
				auto size = texture->getSize();
				float xInc = size.x / static_cast<float>(CirclePortionPath.getVertexCount());
				for (int i = 0; i < CirclePortionPath.getVertexCount(); i += 2)
				{
					float mappedX = xInc * static_cast<float>(i);
					CirclePortionPath[i].texCoords.x = mappedX;
					CirclePortionPath[i].texCoords.y = 0;
					CirclePortionPath[i + 1].texCoords.x = mappedX;
					CirclePortionPath[i + 1].texCoords.y = size.y;
				}
			}
		}

		void HPBarSprite::Update(const sf::Uint32 time, const float TimeScale)
		{

		}

		void HPBarSprite::SetHPPositon(float ratio)
		{
			if (ratio < BarPortion)
			{
				if (!BarCleared)
				{
					BarCleared = true;
					BarPortionPath.setScale(0, BarPortionPath.getScale().y);
				}
				
				float circleFillRatio = ratio / (1 - BarPortion);
				unsigned int targetVertex = static_cast<int>(static_cast<float>(CirclePortionPath.getVertexCount()));
			}
			else
			{
				if (PreviouslyClearedCircleVertexes > 0)
				{
					for (int i = PreviouslyClearedCircleVertexes; i < CirclePortionPath.getVertexCount(); i++)
					{
						CirclePortionPath[i].color.a = 255;
					}
				}
				if (BarCleared)
				{
					BarCleared = true;
				}
			}
		}
		void HPBarSprite::SlideToPosition(float ratio)
		{

		}

		void HPBarSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			if (!BarCleared)
				target.draw(BarPortionPath);

			states.transform *= getTransform();
			states.texture = getTexture();
			
			target.draw(CirclePortionPath, states);
		}
		unsigned int HPBarSprite::getPointCount(void) const
		{
			return CirclePortionPath.getVertexCount();
		}
		sf::Vector2f HPBarSprite::getPoint(unsigned int point) const
		{
			return CirclePortionPath[point].position;
		}

		//Current SE Vis
		CurrentStatusEffectsVisualizer::CurrentStatusEffectsVisualizer(Engine* eng, Character::BaseCharacter& ch, bool growLeft) : VisCharacter(ch), Eng(eng), GrowLeft(growLeft), GrowthAdder(0)
		{
			for (auto se = VisCharacter.GetStatusEffectsManager().GetActiveStatusEffects().begin(); se != VisCharacter.GetStatusEffectsManager().GetActiveStatusEffects().end(); ++se)
			{
				AddStatusEffectIcon(se->second->GetName(), sf::Vector2f(0.f, 0.f), 0, 255, 255, 0);
			}
		}
		void CurrentStatusEffectsVisualizer::Draw(sf::RenderTarget& target)
		{
			sf::RenderStates st;
			st.transform = GetTransform();
			for (auto it = ActiveStatusEffects.begin(); it != ActiveStatusEffects.end(); ++it)
			{
				it->second->Draw(target, st);
			}
			for (auto it = RemovedStatuses.begin(); it != RemovedStatuses.end(); ++it)
			{
				it->second->Draw(target, st);
			}
		}
		void CurrentStatusEffectsVisualizer::Draw(sf::RenderTarget& target, sf::RenderStates states)
		{
			states.transform *= GetTransform();
			for (auto it = ActiveStatusEffects.begin(); it != ActiveStatusEffects.end(); ++it)
			{
				it->second->Draw(target, states);
			}
			for (auto it = RemovedStatuses.begin(); it != RemovedStatuses.end(); ++it)
			{
				it->second->Draw(target, states);
			}
		}

		void CurrentStatusEffectsVisualizer::Update(const sf::Uint32 time, const float TimeScale)
		{
			for (auto it = ActiveStatusEffects.begin(); it != ActiveStatusEffects.end(); ++it)
			{
				it->second->Update(time, TimeScale);
			}
			for (auto it = RemovedStatuses.begin(); it != RemovedStatuses.end();)
			{
				bool Expired = true;
				for (auto trans = it->second->GetActiveTransforms().begin(); trans != it->second->GetActiveTransforms().end(); ++trans)
				{
					if (!trans->second->GetExpired())
					{
						Expired = false;
						break;
					}
				}
				if (Expired)
				{
					it = RemovedStatuses.erase(it);
				}
				else
				{
					it->second->Update(time, TimeScale);
					++it;
				}
			}
		}
		void CurrentStatusEffectsVisualizer::AddStatusEffectIcon(const std::string& seName, sf::Vector2f slideInOffset, sf::Uint32 addTime, sf::Uint8 startAlpha, sf::Uint8 targetAlpha, sf::Uint32 alphaTime)
		{
			
			auto seSpr = boost::make_shared<::Graphics::AnimatedSprite>(Eng->GetContentManager().RequestTexture(seName + "Icon", Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::GUIBattleElement, Eng->GetTime()));

			ActiveStatusEffects.push_back(std::pair<std::string, boost::shared_ptr<::Graphics::AnimatedSprite> >(seName, seSpr));
			int Mult = GrowLeft ? -1 : 1;
			GrowthAdder += seSpr->GetBaseSprite().getGlobalBounds().width;
			std::cout << "Growth Adder: " << GrowthAdder << "\n";
			if (addTime > 0)
			{
				sf::Vector2f TargetPos = sf::Vector2f(GrowthAdder * Mult + slideInOffset.x, slideInOffset.y - 30);
				seSpr->SetPosition(TargetPos);
				std::cout << "Target Position - x: " << TargetPos.x << " | y: " << TargetPos.y << "\n";
				//::Graphics::SpriteInterface& target, const sf::Vector2f& targetPositon, const sf::Uint32 time, const sf::Uint32 transformTime = 0, const sf::Uint32 delay = 0
				seSpr->AddTransform(seName + boost::lexical_cast<std::string>(Eng->GetTime()), boost::make_shared<::Graphics::PositionTransform>(*seSpr, TargetPos - slideInOffset, Eng->GetTime(), addTime));
			}
			else
			{
				sf::Vector2f TargetPos = sf::Vector2f(seSpr->GetBaseSprite().getGlobalBounds().width * Mult, 0.f);
				seSpr->SetPosition(TargetPos);
			}
			if (alphaTime > 0)
			{
				//seSpr->SetAlpha(startAlpha);
				//::Graphics::SpriteInterface& target, const sf::Uint8 targetAlpha, const sf::Uint32 time, const sf::Uint32 transformTime = 0, const sf::Uint32 delay = 0
				//seSpr->AddTransform(seName + "Alpha", boost::make_shared<::Graphics::AlphaTransform>(*seSpr, targetAlpha, Eng->GetTime(), alphaTime));
			}
			else
			{
				//seSpr->SetAlpha(targetAlpha);
			}
		}
		void CurrentStatusEffectsVisualizer::RemoveStatusEffectIcon(const std::string& seName, sf::Vector2f slideOutOffset, sf::Uint32 RemoveTime, sf::Uint8 startAlpha, sf::Uint8 targetAlpha, sf::Uint32 alphaTime)
		{
			int index = 0;
			auto it = ActiveStatusEffects.begin();
			for (; it != ActiveStatusEffects.end(); ++it, ++index)
			{
				if (it->first == seName)
				{
					break;
				}
			}
			if (it != ActiveStatusEffects.end())
			{
				int width = it->second->GetBaseSprite().getGlobalBounds().width;
				GrowthAdder -= width;
				std::cout << "Growth Adder: " << GrowthAdder << "\n";
				if (RemoveTime > 0)
				{
					it->second->ClearTransforms(Eng->GetTime());
					it->second->AddTransform(it->first + boost::lexical_cast<std::string>(Eng->GetTime()), boost::make_shared<::Graphics::PositionTransform>(*(it->second), it->second->GetPosition() + sf::Vector2f(0, 40), Eng->GetTime(), RemoveTime));
					//it->second->AddTransform(it->first + "VisRemoveAlpha", boost::make_shared<::Graphics::AlphaTransform>(*(it->second), 0, Eng->GetTime(), RemoveTime));
					RemovedStatuses.push_back(std::pair<std::string, boost::shared_ptr<::Graphics::AnimatedSprite> >(it->first, it->second));
					auto others = ActiveStatusEffects.erase(it);
					if (others != ActiveStatusEffects.end())
					{
						for (; others != ActiveStatusEffects.end(); ++others)
						{
							others->second->ClearTransforms(Eng->GetTime());
							if (GrowLeft)
								others->second->AddTransform(others->first + boost::lexical_cast<std::string>(Eng->GetTime()), boost::make_shared<::Graphics::PositionTransform>(*(others->second), others->second->GetPosition() + sf::Vector2f(width, 0), Eng->GetTime(), RemoveTime));
							else
								others->second->AddTransform(others->first + boost::lexical_cast<std::string>(Eng->GetTime()), boost::make_shared<::Graphics::PositionTransform>(*(others->second), others->second->GetPosition() + sf::Vector2f(-width, 0), Eng->GetTime(), RemoveTime));
							//others->second->AddTransform(others->first + "VisRemoveAlpha", boost::make_shared<::Graphics::AlphaTransform>(*(others->second), 0, Eng->GetTime(), RemoveTime));
						}
					}
				}
				else
				{

				}
			}
		}
		void CurrentStatusEffectsVisualizer::Bind()
		{
			VisCharacter.GetStatusEffectsManager().AddStatusEffectChangedHandler(SEVisIndex, boost::bind(&CurrentStatusEffectsVisualizer::HandleStatusEffectChange, this, _1, _2, _3));
		}
		void CurrentStatusEffectsVisualizer::UnBind()
		{
			VisCharacter.GetStatusEffectsManager().RemoveStatusEffectChangedHandler(SEVisIndex);
		}
		void CurrentStatusEffectsVisualizer::HandleStatusEffectChange(StatusEffects::StatusEffectsManager* mng, const std::string& seName, const bool Removed)
		{
			auto it = SENames.find(seName);
			bool Available = it != SENames.end();
			if ((Available && !Removed) || (Removed && !Available))
				return;
			if (Removed)
			{
				std::cout << "Removing " << seName << "\n";
				SENames.erase(it);
				RemoveStatusEffectIcon(seName, sf::Vector2f(0, 15), 4450U, 255, 70, 900U);
			}
			else
			{
				std::cout << "Adding " << seName << "\n";
				SENames.insert(seName);
				AddStatusEffectIcon(seName, sf::Vector2f(0, 15), 4450U, 70, 255, 900U);
				//ActiveStatusEffects.push_back()
				//ActiveStatusEffects.push_back(std::pair<std::string, boost::shared_ptr<::Graphics::AnimatedSprite> >(seName, boost::make_shared<::Graphics::AnimatedSprite>()));
			}
		}

		//Standard visualizer

		StandardBattleStatusVisualizer::StandardBattleStatusVisualizer(Engine* eng, Character::BaseCharacter& character) : CharacterBattleStatusVisualizer(eng, character),
			BackFrame(eng->GetContentManager().RequestTexture("OverviewFrame", Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::GUIBattleElement, eng->GetTime())),
			HPBar(eng->GetContentManager().RequestTexture("HP-Full", Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::GUIBattleElement, eng->GetTime()), sf::Vector2f(181.f, 7.f), 0.6f, 32.f, 269.f, 180.f),
			MPBar(eng->GetContentManager().RequestTexture("MP-Full", Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::GUIBattleElement, eng->GetTime())),
			SPBar(eng->GetContentManager().RequestTexture("SP-Full", Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::GUIBattleElement, eng->GetTime())),
			CharacterPortrait(eng->GetContentManager().RequestTexture(character.GetName() + "Status", Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::GUIBattleElement, eng->GetTime())),
			SEVisualizer(eng, character)
		{
			HPBar.SetPosition(1, 81 - 7);
			HPBar.SetTargetRatio(static_cast<float>(character.GetStatsManager().GetCurrentHP()) / static_cast<float>(character.GetStatsManager().GetBattleStat(Stat::HP)));

			auto statRatio = static_cast<float>(character.GetStatsManager().GetCurrentHP()) / static_cast<float>(character.GetStatsManager().GetBattleStat(Stat::HP));
			HPBar.SetTargetRatio(statRatio);//, Eng->GetTime(), 25000, 0);

			//MP Bar
			auto size = MPBar.GetBaseSprite().getLocalBounds();
			DefaultBarScale.x = 153 / size.width;
			DefaultBarScale.y = 6 / size.height;

			statRatio = static_cast<float>(character.GetStatsManager().GetCurrentMP()) / static_cast<float>(character.GetStatsManager().GetBattleStat(Stat::MP));
			MPBar.SetPosition(1 + size.width * DefaultBarScale.x, 60);
			MPBar.SetScale(DefaultBarScale.x * statRatio, DefaultBarScale.y);
			MPBar.GetBaseSprite().setOrigin(size.width, MPBar.GetBaseSprite().getOrigin().y);
			
			auto pos = MPBar.GetBaseSprite().getPosition();
			//SPBar
			SPBar.SetPosition(1 + size.width * DefaultBarScale.x, 67);
			SPBar.SetScale(DefaultBarScale.x, DefaultBarScale.y);
			SPBar.GetBaseSprite().setOrigin(size.width, SPBar.GetBaseSprite().getOrigin().y);
			
			
			statRatio = static_cast<float>(character.GetStatsManager().GetCurrentSP()) / static_cast<float>(character.GetStatsManager().GetBattleStat(Stat::SP));
			SPBar.SetScale(DefaultBarScale.x * statRatio, DefaultBarScale.y);
			pos = SPBar.GetBaseSprite().getPosition();
			//MPBar.
			//DefaultScale
			//Resize potrait
			CharacterPortrait.SetPosition(144, 4);
			sf::Vector2f PotraitSize(70, 70);
			sf::Vector2f PotraitScale(PotraitSize.x / CharacterPortrait.GetBaseSprite().getGlobalBounds().width, PotraitSize.y / CharacterPortrait.GetBaseSprite().getGlobalBounds().height);
			CharacterPortrait.SetScale(PotraitScale);
			
			SEVisualizer.SetPosition(142, 57);
		}

		/*void StandardBattleStatusVisualizer::Rotate(const float angle, bool absolute)
		{

		}*/
		/*
		void StandardBattleStatusVisualizer::IncrementPosition(const sf::Vector2f& incrpos)
		{

		}
		void StandardBattleStatusVisualizer::IncrementPosition(const float xAdd, const float yAdd)
		{

		}

		void StandardBattleStatusVisualizer::SetScale(const sf::Vector2f& scale)
		{

		}
		void StandardBattleStatusVisualizer::SetScale(const float xScale, const float yScale)
		{

		}*/

		void StandardBattleStatusVisualizer::SetAlpha(const sf::Uint8 alpha)
		{

		}
		void StandardBattleStatusVisualizer::IncrementAlpha(const sf::Uint8 alphaAdd)
		{

		}


		void StandardBattleStatusVisualizer::BindOnCharacter()
		{
			VisualizingCharacter.GetStatsManager().AddStatChangeHandler(BattleOverviewStatusVisualizerIndex, boost::bind(&StandardBattleStatusVisualizer::HandleStatChange, this, _1, _2, _3, _4));
			VisualizingCharacter.GetStatusEffectsManager().AddStatusEffectChangedHandler(BattleOverviewStatusVisualizerIndex, boost::bind(&StandardBattleStatusVisualizer::HandleStatusEffectChange, this, _1, _2, _3));
			SEVisualizer.Bind();
		}
		void StandardBattleStatusVisualizer::UnBindOnCharacter()
		{
			SEVisualizer.UnBind();
			VisualizingCharacter.GetStatsManager().RemoveStatChangeHandler(BattleOverviewStatusVisualizerIndex);
			VisualizingCharacter.GetStatusEffectsManager().RemoveStatusEffectChangedHandler(BattleOverviewStatusVisualizerIndex);
		}
	
		void StandardBattleStatusVisualizer::Draw(sf::RenderTarget &window)
		{
			sf::RenderStates st;
			st.transform = GetTransform();
			
			BackFrame.Draw(window, st);
			HPBar.Draw(window, st);
			MPBar.Draw(window, st);
			SPBar.Draw(window, st);
			
			CharacterPortrait.Draw(window, st);
			SEVisualizer.Draw(window, st);
		}
		void StandardBattleStatusVisualizer::Draw(sf::RenderTarget &window, sf::RenderStates states)
		{
			states.transform *= GetTransform();
			
			BackFrame.Draw(window, states);
			HPBar.Draw(window, states);
			MPBar.Draw(window, states);
			SPBar.Draw(window, states);
			CharacterPortrait.Draw(window, states);
			SEVisualizer.Draw(window, states);
		}
#define TRANSTIME 800
		void StandardBattleStatusVisualizer::Update(const sf::Uint32 time, const float TimeScale)
		{
			HPBar.Update(time, TimeScale);
			MPBar.Update(time, TimeScale);
			SPBar.Update(time, TimeScale);
			CharacterPortrait.Update(time, TimeScale);
			SEVisualizer.Update(time, TimeScale);
		}

		void StandardBattleStatusVisualizer::HandleStatChange(Character::StatsManager& mng, const Character::Stat stat, const int oldVal, const int newVal)
		{
			if (oldVal != newVal)
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
					HPBar.ScaleToTargetRatio(statRatio, Eng->GetTime(), TRANSTIME, 0);
					//HPBar.SetTargetRatio(statRatio);
					break;
				case Stat::MP:
					newCVal = mng.GetCurrentMP();
					newMVal = mng.GetBattleStat(stat);
					statRatio = static_cast<float>(newCVal) / static_cast<float>(newMVal);
					MPBar.ClearTransforms(Eng->GetTime());
					MPBar.AddTransform("MPBarScaleTrans", boost::make_shared<::Graphics::ScaleTransform>(MPBar, sf::Vector2f(DefaultBarScale.x * statRatio, DefaultBarScale.y), Eng->GetTime(), 800, 20));
					//MPBar.SetScale(DefaultBarScale.x * statRatio, DefaultBarScale.y);
					break;
				case Stat::SP:
					newCVal = mng.GetCurrentSP();
					newMVal = mng.GetBattleStat(stat);
					statRatio = static_cast<float>(newCVal) / static_cast<float>(newMVal);
					SPBar.ClearTransforms(Eng->GetTime());
					SPBar.AddTransform("MPBarScaleTrans", boost::make_shared<::Graphics::ScaleTransform>(SPBar, sf::Vector2f(DefaultBarScale.x * statRatio, DefaultBarScale.y), Eng->GetTime(), 800, 20));
					break;
				default:
					break;
				}
				/*if (newCVal != CValue || newMVal != MValue)
				{
					StatBar.ClearTransforms(Eng->GetTime(), false);
					StatBar.AddTransform("ScaleTransform", boost::shared_ptr<::Graphics::BaseTransform>(new ::Graphics::ScaleTransform(StatBar, sf::Vector2f(statRatio, StatBar.GetScale().y), Eng->GetTime(), 1250)));
					CurrentValue.setString(boost::lexical_cast<std::string>(newCVal));
					MaxValue.setString(boost::lexical_cast<std::string>(newMVal));
					CValue = newCVal;
					MValue = newMVal;
				}*/

			}
		}
		void StandardBattleStatusVisualizer::HandleStatusEffectChange(StatusEffects::StatusEffectsManager* mng, const std::string& seName, const bool removed)
		{

		}

	}
}