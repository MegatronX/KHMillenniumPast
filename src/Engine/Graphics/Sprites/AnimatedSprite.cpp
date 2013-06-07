#include "AnimatedSprite.h"
#include <Graphics/Sprites/SpriteImportData.h>
namespace Graphics
{

	AnimatedSprite::AnimatedSprite()
	{

	}

	AnimatedSprite::AnimatedSprite(boost::shared_ptr<sf::Texture> tx, bool center) : BaseSprite(*tx)
	{
		Textures.push_back(tx);
	}

	/*AnimatedSprite::AnimatedSprite(boost::shared_ptr<sf::Texture> tx, Content::SpriteLoadImport& spriteImportData, bool Center) : BaseSprite(*tx)
	{
		Textures.push_back(tx);
		//spriteImportData.ApplyThisData(*this);
	}*/

	AnimatedSprite::AnimatedSprite(boost::shared_ptr<sf::Texture> tx, const SpriteImportData& data, bool Center) : BaseSprite(*tx)
	{
		Textures.push_back(tx);
		data.ApplyThisData(*this);
	}

	void AnimatedSprite::SetTexture(boost::shared_ptr<sf::Texture> txt)
	{
		if (Textures.size() > 0)
		{
			Textures[0] = txt;
		}
		else
		{
			Textures.push_back(txt);
		}
		BaseSprite.setTexture(*txt);
	}

	void AnimatedSprite::Update(const sf::Uint32 time, const float TimeScale)
	{
			Anim.update(time);
			Anim.animate(BaseSprite);
			AnimatedSpriteInterface::Update(time, TimeScale);
			Lastupdate = time;
	}

	void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		//states.transform *= GetTransformConst();
		target.draw(BaseSprite, states);
		//Sprite::draw(target, states);
	}
	void AnimatedSprite::Draw(sf::RenderTarget &window, sf::RenderStates states)
	{
		states.transform *= GetTransform();
		window.draw(BaseSprite, states);
		//BaseSprite.Draw(window, states);
		//S//prite::Draw(window, states);
	}

	void AnimatedSprite::Draw(sf::RenderTarget& window)
	{
		sf::RenderStates states;
		states.transform = GetTransform();
		window.draw(BaseSprite, states);
		//Sprite::Draw(window);
	}

	Animator<sf::Sprite, std::string>& AnimatedSprite::GetAnimator()
	{
		return Anim;
	}
	sf::Sprite& AnimatedSprite::GetBaseSprite()
	{
		return BaseSprite;
	}

	/*AnimatedDraw::RawClonePtr AnimatedSprite::RawClone() const
	{
		return new AnimatedSprite(*this);
	}*/
	/*AnimatedSprite::AnimatedSprite() : sf::Sprite()
	{

	}
	AnimatedSprite::AnimatedSprite(const boost::shared_ptr<sf::Texture> texture) : sf::Sprite(*texture), localTexture(texture)
	{

	}
	AnimatedSprite::AnimatedSprite(const boost::shared_ptr<sf::Texture> texture, Animator* anim) : sf::Sprite(*texture), localTexture(texture), animator(anim)
	{

	}
	void AnimatedSprite::Draw(sf::RenderWindow &window, sf::Shader &shader)
	{
		animator->Animate(*this);
		window.draw(*this);
	}
	void AnimatedSprite::Draw(sf::RenderWindow &window)
	{
		animator->Animate(*this);
		window.draw(*this);
	}

	void AnimatedSprite::Update(const sf::Uint32 time, const float TimeScale)
	{
		if (animator != nullptr)
			animator->Update(time * TimeScale);	
	}

	Animator* AnimatedSprite::GetAnimator()
	{
		return animator;
	}*/
}
