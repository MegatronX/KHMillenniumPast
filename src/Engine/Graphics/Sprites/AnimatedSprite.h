#pragma once
#ifndef _ANIMATEDSPRITE__H_
#define _ANIMATEDSPRITE__H_

#include <graphics/Sprites/AnimatedSpriteInterface.h>
#include <sfml/Graphics.hpp>
#include <graphics/Animation/Animator.hpp>

//#include <Graphics/Sprites/AnimatedSpriteInterface.h>
#include <Graphics/Transformers/BaseTransform.h>
//#include <graphics/Animation/Animation.h>
//#include <graphics/Animation/FrameAnimation.h>
namespace Content
{

}
namespace Graphics
{
	class SpriteImportData;
	class AnimatedSprite : public AnimatedSpriteInterface
	{
	public:
		AnimatedSprite();

		AnimatedSprite(boost::shared_ptr<sf::Texture> tx, bool Center = false);

		//AnimatedSprite(boost::shared_ptr<sf::Texture> tx, Content::SpriteLoadImport& spriteImportData, bool Center = false);

		AnimatedSprite(boost::shared_ptr<sf::Texture> tx, const ::Graphics::SpriteImportData& data, bool Center = false);

		virtual void SetTexture(boost::shared_ptr<sf::Texture> txt);

		virtual void Update(const sf::Uint32 time, const float TimeScale = 1.0) override;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual void Draw(sf::RenderTarget &window, sf::RenderStates states) override;

		virtual void Draw(sf::RenderTarget& window) override;

		Animator<sf::Sprite, std::string>& GetAnimator();

//		virtual AnimatedDraw::RawClonePtr RawClone() const;

		sf::Sprite& GetBaseSprite();
	protected:
		std::vector<boost::shared_ptr<sf::Texture> > Textures;
		Animator<sf::Sprite, std::string> Anim;
		sf::Uint32 Lastupdate;
		sf::Sprite BaseSprite;
	private:
	};
	/*class AnimatedSprite : public sf::Sprite, public AnimatedDraw
	{
	public:
		AnimatedSprite();
		AnimatedSprite(const boost::shared_ptr<sf::Texture> texture);
		AnimatedSprite(const boost::shared_ptr<sf::Texture> texture, Animator* anim);
		//AnimatedSprite(SpriteLoadDescription& loadDescript);
		void Draw(sf::RenderWindow &window, sf::Shader &shader) override;
		void Draw(sf::RenderWindow &window) override;

		void Update(const sf::Uint32 time, const float TimeScale = 1.0) override;

		Animator* GetAnimator();
	protected:
	private:
		Animator* animator;

		boost::shared_ptr<sf::Texture> localTexture;
	};

	typedef boost::shared_ptr<AnimatedSprite> animspr_ptr;*/
}

#endif