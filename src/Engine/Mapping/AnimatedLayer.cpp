#include "AnimatedLayer.h"

namespace Mapping
{
	AnimatedLayer::AnimatedLayer()
	{
	}
	AnimatedLayer::AnimatedLayer(std::string &Name, int Width, int Height, int TileWidth, int TileHeight, std::vector<std::string> &decodedStrings, float fps_) 
		//: name(Name), width(Width), height(Height), tileWidth(TileWidth), tileHeight(TileHeight), IsAnimated(decodedStrings.size() > 1), maxIndex(Width * Height), fps(fps_), fpsms(1000.0f / fps_), SetIndex(0), lastUpdate(0), 
		//maxIndex(Width * Height)
	{
		this->name = Name;
		this->width = Width;
		this->height = Height;
		this->tileWidth = TileWidth;
		this->tileHeight = TileHeight;
		this->IsAnimated = decodedStrings.size() > 1;
		this->maxIndex = Width * Height;
		this->fps =fps_;
		this->fpsms = 1000.0f / fps_;
		this->SetIndex = 0;
		this->lastUpdate = 0;
		//fps(fps_), fpsms(1000.0f / fps_), SetIndex(0), lastUpdate(0), 
		for (auto dstring = decodedStrings.begin(); dstring != decodedStrings.end(); ++dstring)
		{
			LayerSet.push_back(Layer::GenerateDataFromDecodedString(*dstring, width, height));
		}
	}
	AnimatedLayer::~AnimatedLayer()
	{
		while (!LayerSet.empty())
		{
			auto lptr = LayerSet.back();
			if (lptr != nullptr)
				delete lptr;
			LayerSet.pop_back();
		}
	}

	/*inline unsigned int AnimatedLayer::At(int index)
	{
		if (index >= maxIndex)
			return 0;
		return LayerSet[SetIndex][index];
	}
	inline unsigned int AnimatedLayer::At(int x, int y)
	{
		return At(y * width + x);
	}*/

	float AnimatedLayer::GetFPS() const
	{
		return fps;
	}
	void AnimatedLayer::SetFPS(const float fps_)
	{
		fps = fps_;
		fpsms = 1000.0f / fps;
	}
	const std::vector<unsigned int*>& AnimatedLayer::GetAnimationSet() const
	{
		return LayerSet;
	}

	void AnimatedLayer::AddLayer(std::string& decodedString)
	{
		LayerSet.push_back(Layer::GenerateDataFromDecodedString(decodedString, width, height));
	}

	void AnimatedLayer::Update(sf::Uint32 time, float timeScale)
	{
		sf::Uint32 elapsed = lastUpdate - time;
		if (elapsed > fpsms)
		{
			if (LayerSet.size() > 0)
			{
				SetIndex = (SetIndex + 1) % LayerSet.size();
				layerData = LayerSet[SetIndex];
			}
			lastUpdate = time;
		}
	}
}

