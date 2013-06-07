#pragma once
#ifndef _ANIMATEDTILESET_H_
#define _ANIMATEDTILESET_H_
#include "TileSet.h"
namespace Mapping
{
	class AnimatedTileSet : public TileSet
	{
	public:
		AnimatedTileSet(std::string &name, int firstGID, int tileWidth, int tileHeight, std::vector<boost::shared_ptr<sf::Texture> >& cycleSet, float fps, int StartingIndex);
		//virtual int GetEndGID() override;
		//virtual sf::Sprite& GetTile(int index) override;
		virtual void Update(const sf::Uint32 time, const float TimeScale = 1.0f);
		float GetFPS() const;
		void SetFPS(const float newfps);

	protected:
		std::vector<boost::shared_ptr<sf::Texture> > CyclingSet;
		int ActiveIndex;
		float fps;
		float fpsms;
		sf::Uint32 lastUpdate;

		std::vector<std::vector<sf::Sprite> > SpriteSet;
	private:

	};

	typedef boost::shared_ptr<AnimatedTileSet> anim_tile_ptr;
}


#endif