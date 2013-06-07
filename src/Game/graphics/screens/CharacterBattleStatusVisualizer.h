#pragma once
#ifndef _CHARACTERBATTLEVISUALIZER_H_
#define _CHARACTERBATTLEVISUALIZER_H_

#include <Graphics/Visualizers/EntityComponentVisualizer.h>
#include <Graphics/Transformers/BaseTransform.h>
#include <battle/BattleCharacterComponent.h>
#include <Graphics/Sprites/AnimatedSprite.h>
#include <Graphics/Shapes/Shapes.h>
namespace Game
{
	namespace Graphics
	{
		const std::string BattleOverviewStatusVisualizerIndex = "CharacterBattleStatusVisualizer";

		class CharacterBattleStatusVisualizer : public EntityVisualizer, public virtual ::Graphics::SpriteInterface
		{
		public:
			CharacterBattleStatusVisualizer(Engine* eng, Character::BaseCharacter& character);

			virtual void BindOnCharacter();
			virtual void UnBindOnCharacter();

		protected:
			virtual void HandleStatChange(Character::StatsManager& mng, const Character::Stat stat, const int oldVal, const int newVal);
			virtual void HandleStatusEffectChange(StatusEffects::StatusEffectsManager* mng, const std::string& seName, const bool removed);
			Character::BaseCharacter& VisualizingCharacter;
		private:
			
		};

		class HPBarFill : public ::Graphics::SpriteInterface, public ::Graphics::Updater
		{
		public:
			HPBarFill(boost::shared_ptr<sf::Texture> hpBarTexture, const sf::Vector2f& barSize, const float barRatio, const float circleRadius, const float circleDegrees, const float startAngle, const float thickness = 7.f, bool circleLeft = false) 
				: CirclePortion(hpBarTexture, circleRadius, circleDegrees, startAngle, thickness, !circleLeft), BarPortion(barSize), BarRatio(barRatio), CircleRatio(1 - barRatio), Transitioning(false), TargetRatio(1.f),
				CurrentRatio(1.f), TransitionRate(0.f), TargetTime(0), LastUpdate(0), BarScaleRate(0.f), BarMoveRate(0.f), ClearingVertexFromMax(true), DrawBar(true), DrawCircle(true), CircleFull(false)
			{
				BarPortion.setTexture(hpBarTexture.get());
				CirclePortion.setPosition(barSize.x, -circleRadius);
				LastClearedVertex = CirclePortion.GetVertexArray().getVertexCount() - 1;
				auto& curCen = BarPortion.getOrigin();
				auto sc = BarPortion.getScale();
				DefaultScale.x = BarPortion.getSize().x / hpBarTexture->getSize().x;
				DefaultScale.y = BarPortion.getSize().y / hpBarTexture->getSize().y;
				BarPortion.setOrigin(BarPortion.getSize().x, BarPortion.getSize().y);
				BarPortion.setPosition(BarPortion.getSize().x, BarPortion.getPosition().y + BarPortion.getSize().y);
			}

			virtual void Draw(sf::RenderTarget &window) 
			{
				sf::RenderStates st;
				st.transform = GetTransform();
				if (DrawBar)
					window.draw(BarPortion, st);
				if (DrawCircle)
					window.draw(CirclePortion, st);

			}
			virtual void Draw(sf::RenderTarget &window, sf::RenderStates states) 
			{
				states.transform *= GetTransform();
				if (DrawBar)
					window.draw(BarPortion, states);
				if (DrawCircle)
					window.draw(CirclePortion, states);
			}

			virtual void Update(const sf::Uint32 time, const float TimeScale = 1.f)
			{
				if (Transitioning)
				{
					sf::Uint32 Elpased = time - LastUpdate;
					if (time < LastUpdate)
						Elpased = 0;
					if (Elpased > 0)
					{
						CurrentRatio += TransitionRate * static_cast<float>(Elpased);
					}
					if (time > TargetTime)
					{
						Transitioning = false;
						CurrentRatio = TargetRatio;
					}
					SetTargetRatio(CurrentRatio);
				}
				LastUpdate = time;
			}
			virtual void SetTargetRatio(const float ratio)
			{
				DrawBar = ratio > CircleRatio;
				DrawCircle = ratio > 0.f;
				
				if (ratio < CircleRatio && CircleRatio > 0.f)
				{
					float circleRatio = ratio / CircleRatio;
					unsigned int TargetVertex = static_cast<unsigned int>(static_cast<float>(CirclePortion.GetVertexArray().getVertexCount() * circleRatio));
					if (TargetVertex != LastClearedVertex)
					{
						if (TargetVertex < LastClearedVertex)
						{
							for (unsigned int i = LastClearedVertex; i >= TargetVertex && i >= 0; --i)
							{
								CirclePortion.GetVertexArray()[i].color.a = 0;
							}
						}
						else
						{
							for (unsigned int i = LastClearedVertex; i <= TargetVertex && i < (CirclePortion.GetVertexArray().getVertexCount()); ++i)// += 2)
							{
								CirclePortion.GetVertexArray()[i].color.a = 255;
							}
						}
					}
					LastClearedVertex = TargetVertex;
				}
				else if (ratio >= CircleRatio)
				{
					if (LastClearedVertex < CirclePortion.GetVertexArray().getVertexCount() - 1)
					{
						for (unsigned int i = LastClearedVertex;  i < (CirclePortion.GetVertexArray().getVertexCount()); ++i)// += 2)
						{
							CirclePortion.GetVertexArray()[i].color.a = 255;
						}
						LastClearedVertex = CirclePortion.GetVertexArray().getVertexCount() - 1;
					}
					
					float EffBarRatio = (ratio - CircleRatio) / BarRatio;
					BarPortion.setScale(EffBarRatio, BarPortion.getScale().y );
					
				}
				CurrentRatio = ratio;
			}

			virtual void ScaleToTargetRatio(const float targetRatio, const sf::Uint32 time, const sf::Uint32 transitionTime, const sf::Uint32 delay = 0U)
			{
				TargetTime = time + transitionTime + delay;
				LastUpdate = time + delay;
				TargetRatio = targetRatio;
				if (transitionTime > 0)
					TransitionRate = (targetRatio - CurrentRatio) / static_cast<float>(transitionTime);
				Transitioning = true;
				
			}
			/*
			virtual void Rotate(const float angle, bool absolute = true)
			{
				SpriteInterface::Rotate(angle, absolute);
				LocalTransform.rotate(GetRotation(), BarPortion.getPosition());
			}

			virtual void SetPosition(const sf::Vector2f& pos)
			{
				SpriteInterface::SetPosition(pos);
				//LocalTransform.translate(GetPosition());
			}
			virtual void SetPosition(const float x, const float y)
			{
				SpriteInterface::SetPosition(x, y);
				//LocalTransform.translate(GetPosition());
			}

			virtual void IncrementPosition(const sf::Vector2f& incrpos)
			{
				SpriteInterface::IncrementPosition(incrpos);
				LocalTransform.translate(GetPosition());
			}
			virtual void IncrementPosition(const float xAdd, const float yAdd = 0)
			{
				SpriteInterface::IncrementPosition(xAdd, yAdd);
				LocalTransform.translate(GetPosition());
			}

			virtual void SetScale(const sf::Vector2f& scale)
			{
				SpriteInterface::SetScale(scale);
				LocalTransform.scale(GetScale());
			}
			virtual void SetScale(const float xScale, const float yScale)
			{
				SpriteInterface::SetScale(xScale, yScale);
				LocalTransform.scale(GetScale());
			}

			virtual void SetAlpha(const sf::Uint8 alpha)
			{
				SpriteInterface::SetAlpha(alpha);
				auto col = BarPortion.getFillColor();
				col.a = GetAlpha();
				BarPortion.setFillColor(col);
				
			}
			virtual void IncrementAlpha(const sf::Uint8 alphaAdd)
			{
				SpriteInterface::IncrementAlpha(alphaAdd);
				auto col = BarPortion.getFillColor();
				col.a = GetAlpha();
				BarPortion.setFillColor(col);
			}
			*/
		protected:
			bool Transitioning;
			float TargetRatio;
			float CurrentRatio;
			float TransitionRate;
			sf::Uint32 TargetTime;
			sf::Uint32 LastUpdate;
			//Bar Clearence
			float BarScaleRate;
			float BarMoveRate;
			//Circle Clearance
			unsigned int LastClearedVertex;
			bool ClearingVertexFromMax;
			bool CircleFull;
			bool DrawBar;
			bool DrawCircle;
			float BarRatio;
			float CircleRatio;
			sf::Vector2f CircleOffset;
			sf::Vector2f BarOffset;
			sf::Vector2f DefaultScale;
			::Graphics::HollowCircle CirclePortion;
			sf::RectangleShape BarPortion;
		};

		class HPBarSprite : public sf::Shape, public ::Graphics::Updater
		{
		public:
			HPBarSprite(boost::shared_ptr<sf::Texture> targetTexture, const sf::Vector2f& barSectionSize, const float circleRadius, const float circleDegrees, const float startAngle, const bool clockwise = true, const unsigned int circlePoints = 120, const float thickness = 6.f, const float barHPPortion = 0.6f);
		
			void MapTexture();
			void Update(const sf::Uint32 time, const float TimeScale = 1.0) override;
			void SetHPPositon(float ratio);
			void SlideToPosition(float ratio);

			//sf::Shape overrides
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

			unsigned int getPointCount(void) const;
			sf::Vector2f getPoint(unsigned int point) const;

			//HPBarSprite::
		protected:
			boost::shared_ptr<sf::Texture> TargetTexture;
			sf::RectangleShape BarPortionPath;
			bool BarCleared;
			unsigned int PreviouslyClearedCircleVertexes;
			float BarPortion;
			float CircleRadius;
			float CircleThickness;
			float ArcAngle;
			float StartAngle;
			float CurrentFillRatio;
			float RatioTransformRate;
			sf::Vector2f CirclePortionOffset;
			unsigned int PointCount;
			sf::Vector2f BarSize;
			sf::VertexArray CirclePortionPath;
		};

		const std::string SEVisIndex = "StatusEffectVis";
		class CurrentStatusEffectsVisualizer : public ::Graphics::SpriteInterface, public ::Graphics::Updater
		{
		public:
			CurrentStatusEffectsVisualizer(Engine* eng, Character::BaseCharacter& ch, bool growLeft = true);
			virtual void Draw(sf::RenderTarget& target);
			virtual void Draw(sf::RenderTarget& target, sf::RenderStates states);

			void Update(const sf::Uint32 time, const float TimeScale = 1.f);
			void AddStatusEffectIcon(const std::string& seName, sf::Vector2f slideInOffset, sf::Uint32 addTime = 0, sf::Uint8 startAlpha = 100, sf::Uint8 targetAlpha = 255, sf::Uint32 alphaTime = 200U);
			void RemoveStatusEffectIcon(const std::string& seName, sf::Vector2f slideOutOffset, sf::Uint32 RemoveTime = 0, sf::Uint8 startAlpha = 100, sf::Uint8 targetAlpha = 255, sf::Uint32 alphaTime = 200U);

			void Bind();
			void UnBind();
		protected:
			void HandleStatusEffectChange(StatusEffects::StatusEffectsManager* mng, const std::string& seName, const bool Removed);
			
		private:
			int GrowthAdder;
			bool GrowLeft;
			Character::BaseCharacter& VisCharacter;
			Engine* Eng;
			boost::unordered_set<std::string> SENames;
			std::deque<std::pair<std::string, boost::shared_ptr<::Graphics::AnimatedSprite> > > ActiveStatusEffects;
			std::vector<std::pair<std::string, boost::shared_ptr<::Graphics::AnimatedSprite> > > RemovedStatuses;
		};

		class StandardBattleStatusVisualizer : public CharacterBattleStatusVisualizer
		{
			
		public:
			StandardBattleStatusVisualizer(Engine* eng, Character::BaseCharacter& character);

			virtual void SetAlpha(const sf::Uint8 alpha);
			virtual void IncrementAlpha(const sf::Uint8 alphaAdd);

			virtual void BindOnCharacter();
			virtual void UnBindOnCharacter();

			void Draw(sf::RenderTarget &window) override;
			void Draw(sf::RenderTarget &window, sf::RenderStates states) override;

			void Update(const sf::Uint32 time, const float TimeScale = 1.f) override;

		protected:
			virtual void HandleStatChange(Character::StatsManager& mng, const Character::Stat stat, const int oldVal, const int newVal);
			virtual void HandleStatusEffectChange(StatusEffects::StatusEffectsManager* mng, const std::string& seName, const bool removed);

			CurrentStatusEffectsVisualizer SEVisualizer;

			::Graphics::AnimatedSprite BackFrame;
			::Graphics::AnimatedSprite MPBar;
			::Graphics::AnimatedSprite SPBar;
			::Graphics::AnimatedSprite CharacterPortrait;
			HPBarFill HPBar;
			sf::Vector2f DefaultBarScale;
			sf::Transform LocalTransform;
			//HPBarSprite HPBar;

		};
	}
}

#endif