#include "SpriteImportData.h"
#include <Graphics/Sprites/AnimatedSprite.h>
#include <Graphics/Animation/FrameAnimation.hpp>
namespace Graphics
{

	SpriteImportData::SpriteImportData(const std::string& dataIndex) : SpriteDataIndex(dataIndex)
	{

	}

	const std::string& SpriteImportData::GetSpriteDataIndex() const
	{
		return SpriteDataIndex;
	}

	void SpriteImportData::AddFrameSet(const std::string& frameset, const float frameSetDuration, const std::vector<std::pair<float, sf::IntRect>> FrameSet)
	{
		StoredFrames[frameset] = std::pair<float, std::vector<std::pair<float, sf::IntRect>>>(frameSetDuration, FrameSet);
	}

	void SpriteImportData::AddFrame(const std::string& frameSet, const float relativeDuration, const sf::IntRect& frame)
	{
		auto fset = StoredFrames.find(frameSet);
		if (fset != StoredFrames.end())
		{
			fset->second.second.push_back(std::pair<float, sf::IntRect>(relativeDuration, frame));
		}
	}

	void SpriteImportData::ApplyThisData(AnimatedSprite& sprite) const
	{
		ApplySpriteDataToSprite(*this, sprite);
	}

	void SpriteImportData::ApplySpriteDataToSprite(const SpriteImportData& data, AnimatedSprite& sprite)
	{
		AnimatedSprite* AnimSpr = dynamic_cast<AnimatedSprite*>(&sprite);

		//Animated Load
		if (AnimSpr != nullptr)
		{
			auto & animator = AnimSpr->GetAnimator();
			for (auto frameSet = data.StoredFrames.begin(); frameSet != data.StoredFrames.end(); ++frameSet)
			{
				std::string animIdx = frameSet->first;
				sf::Time duration = sf::seconds(frameSet->second.first);
				::Graphics::FrameAnimation frameAnim;
				for (auto frame = frameSet->second.second.begin(); frame != frameSet->second.second.end(); ++frame)
				{
					frameAnim.addFrame(frame->first, frame->second);
				}
				if (!animIdx.empty())
				{
					animator.addFrameAnimation(animIdx, frameAnim, duration);
				}
			}
			
			//animator.
		}
		else
		{

		}
	}
	SpriteImportData::~SpriteImportData()
	{

	}
}
