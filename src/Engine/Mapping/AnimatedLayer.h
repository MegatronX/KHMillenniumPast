#pragma once
#ifndef _ANIMATEDLAYER_H_
#define _ANIMATEDLAYER_H_
#include "Layer.h"
#include <sfml/System.hpp>

namespace Mapping
{
	class AnimatedLayer : public Layer
	{
	public:
		AnimatedLayer();
		AnimatedLayer(std::string &Name, int Width, int Height, int TileWidth, int TileHeight, std::vector<std::string> &decodedStrings, float fps);
		virtual ~AnimatedLayer();

		//virtual unsigned int At(int index) override;
		//virtual unsigned int At(int x, int y) override;

		float GetFPS() const;
		void SetFPS(const float fps);

		const std::vector<unsigned int*>& GetAnimationSet() const;

		void AddLayer(std::string& decodedString);

		virtual void Update(const sf::Uint32 time, const float TimeScale = 1.0f);
	protected:
		std::vector<unsigned int*> LayerSet;
		float fps;
		int fpsms;
		int SetIndex;
		sf::Uint32 lastUpdate;
	private:

	};

	typedef boost::shared_ptr<AnimatedLayer> anim_layer_ptr;
}




#endif