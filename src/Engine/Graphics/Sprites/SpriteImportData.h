#pragma once
#ifndef _SPRITEIMPORTDATA_H_
#define _SPRITEIMPORTDATA_H_

#include <Graphics/Sprites/AnimatedSprite.h>
#include <boost/unordered_map.hpp>
namespace Graphics
{
	class SpriteImportData
	{
	public:
		SpriteImportData(const std::string& dataIndex = "BadIndex");
	
		const std::string& GetSpriteDataIndex() const;

		void AddFrameSet(const std::string& frameset, const float frameSetDuration, const std::vector<std::pair<float, sf::IntRect>> FrameSet);

		void AddFrame(const std::string& frameSet, const float relativeDuration, const sf::IntRect& frame);

		void ApplyThisData(AnimatedSprite& sprite) const;

		static void ApplySpriteDataToSprite(const SpriteImportData& data, AnimatedSprite& sprite);
		virtual ~SpriteImportData();
	private:
		//<FrameSetIndex <FrameSetDuration<FrameSet<FrameDuration, FrameRect>>>>
		boost::unordered_map<std::string, std::pair<float, std::vector<std::pair<float, sf::IntRect>>>> StoredFrames;
		std::string SpriteDataIndex;
	};
}

#endif