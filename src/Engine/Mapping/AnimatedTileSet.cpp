#include "AnimatedTileSet.h"

namespace Mapping
{
	AnimatedTileSet::AnimatedTileSet(std::string &name, int firstGID, int tileWidth, int tileHeight, std::vector<boost::shared_ptr<sf::Texture> >& cycleSet, float fps_, int startingIndex)
		: CyclingSet(cycleSet), fps(fps_), fpsms(1000.0f / fps_), ActiveIndex(startingIndex), lastUpdate(0)
	{
		this->firstGID = firstGID;
		this->tileWidth = tileWidth;
		this->tileHeight = tileHeight;
		this->name = name;
		//referenceImage.SetSmooth(false);
		int index = 0;
		for (auto tileImage = cycleSet.begin(); tileImage != cycleSet.end(); ++tileImage, ++index)
		{
			SpriteSet.push_back(std::vector<sf::Sprite>());
			auto size = (*tileImage)->getSize();
			int XTiles = (int)(size.x) / tileWidth;
			int YTiles = (int)(size.y) / tileHeight;
			for (int y = 0; y < YTiles; ++y)
			{
				for (int x = 0; x < XTiles; ++x)
				{
					sf::Sprite sprite(*(*tileImage));
					sprite.setTextureRect(sf::IntRect(x * tileWidth, y * tileHeight, tileWidth, tileHeight));
					SpriteSet[index].push_back(sprite);
				}
			}
		}
		Animated = SpriteSet.size() > 1;
	}

	/*int AnimatedTileSet::GetEndGID()
	{
		return firstGID + SpriteSet[ActiveIndex].size() - 1;
	}*/

	/*sf::Sprite& AnimatedTileSet::GetTile(int index)
	{
		return SpriteSet[ActiveIndex][index];
		//return
	}*/

	void AnimatedTileSet::Update(sf::Uint32 time, float timeScale)
	{
		sf::Uint32 elapsed = time - lastUpdate;
		if (elapsed > fpsms)
		{
			ActiveIndex = (ActiveIndex + 1) % CyclingSet.size();
			activetiles = &(SpriteSet[ActiveIndex]);
			lastUpdate = time;
		}
	}

	float AnimatedTileSet::GetFPS() const
	{
		return fps;
	}
	void AnimatedTileSet::SetFPS(const float newfps)
	{
		fps = newfps;
		fpsms = 1000.0f / fps;
	}
}