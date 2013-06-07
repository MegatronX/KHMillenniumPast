#include "Layer.h"
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <utilities\base64.h>

namespace Mapping
{
	Layer::Layer(void)
	{
	}

	Layer::Layer(std::string &Name, int Width, int Height, int TileWidth, int TileHeight, std::string &decodedString)
		: name(Name), width(Width), height(Height), tileWidth(TileWidth), tileHeight(TileHeight), IsAnimated(false), maxIndex(Width * Height)
	{
		layerData = Layer::GenerateDataFromDecodedString(decodedString, width, height);
	}

	Layer::Layer(std::string &Name, int Width, int Height, int TileWidth, int TileHeight, std::string &b64String, bool DecodedFromBase64)
		: name(Name), width(Width), height(Height), tileWidth(TileWidth), tileHeight(TileHeight), IsAnimated(false), maxIndex(Width * Height)
	{
		if (DecodedFromBase64)
			layerData = Layer::GenerateDataFromDecodedString(b64String, width, height);
		else
			layerData = Layer::GenerateDataFromBase64String(b64String, width, height);
	}

	unsigned int Layer::At(int index)
	{
		if (index >= maxIndex)
			return 0;
		return layerData[index];
	}

	unsigned int Layer::At(int x, int y)
	{
		//int index = y * width + x;
		return At(y * width + x);
		//return layerData[index];
	}

	void Layer::AddExtendedProperty(std::string &name, std::string &value)
	{
		extendedProperties.push_back(LayerProperty(name, value));
	}

	void Layer::SetExtendedProperties(std::vector<LayerProperty> &properties)
	{

	}

	int Layer::GetDrawOrder()
	{
		return drawOrder;
	}

	int Layer::GetHeight()
	{
		return height;
	}
	int Layer::GetWidth()
	{
		return width;
	}

	int Layer::GetLayerNum()
	{
		return layerNum;
	}

	int Layer::GetTileHeight()
	{
		return tileHeight;
	}

	int Layer::GetTileWidth()
	{
		return tileWidth;
	}

	std::string Layer::GetName()
	{
		return name;
	}

	float Layer::GetOpacity()
	{
		return opacity;
	}

	bool Layer::GetIsAnimated() const
	{
		return IsAnimated;
	}

	bool Layer::IsActive()
	{
		return active;
	}

	void Layer::SetDrawOrder(int value)
	{
		drawOrder = value;
	}

	void Layer::SetLayerNum(int value)
	{
		layerNum = value;
	}

	void Layer::SetOpacity(float value)
	{
		opacity = value;
	}

	void Layer::AddCollisionLayerName(std::string &name)
	{
		collisionLayerNames.push_back(name);
	}

	unsigned int* Layer::GenerateDataFromDecodedString(std::string &decodedstring, int width, int height)
	{
		unsigned int* data = new unsigned int[width * height];
		int index = 0;
		for (int i = 0; i < width * height; ++i)
		{
			/*unsigned char x1 = decodedstring[index];
			unsigned char x2 = decodedstring[index + 1];
			unsigned char x3 = decodedstring[index + 2];
			unsigned char x4 = decodedstring[index + 3];*/
			data[i] = (unsigned char)decodedstring[index] | 
				(unsigned char)decodedstring[index + 1] << 8 | 
				(unsigned char)decodedstring[index + 2] << 16 | 
				(unsigned char)decodedstring[index + 3] << 24;
			index += 4;
			//if (data[i] < 0)
			//	data[i] = -data[i];
		}
		/*std::vector<unsigned int> dataDump;
		dataDump.reserve(width * height);
		for (int i = 0; i < width * height; ++i)
		{
		dataDump.push_back(data[i]);
		}*/
		return data;
	}

	unsigned int* Layer::GenerateDataFromBase64String(std::string &base64string, int width, int height)
	{
		return (unsigned int*)Base64TMXDecode(base64string, width * height);
	}

	Layer::~Layer(void)
	{
		if (layerData != nullptr)
		{
			delete[] layerData;
			layerData = nullptr;
		}
	}

	//Collision Layer

	CollisionLayer::CollisionLayer(std::string &name, int width, int height, int tilewidth, int tileheight, std::string &decodedstring, boost::unordered_set<int> &activeLayerSet)
		: Layer(name, width, height, tilewidth, tileheight, decodedstring)
	{
		activeOnLayers = activeLayerSet;
	}

	CollisionLayer::CollisionLayer(std::string &name, int width, int height, int tilewidth, int tileheight, std::string &decodedstring, boost::unordered_set<std::string> &activeLayerSet)
		: Layer(name, width, height, tilewidth, tileheight, decodedstring)
	{
		using boost::lexical_cast;
		using boost::bad_lexical_cast;
		enforcedOn = activeLayerSet;
		for (auto enforceVal = enforcedOn.begin(); enforceVal != enforcedOn.end(); ++enforceVal)
		{
			try
			{
				activeOnLayers.insert(lexical_cast<int>(*enforceVal));
			}
			catch (bad_lexical_cast ex)
			{
				std::cerr << "Bad Layer Int Cast " << ex.what() << std::endl;
			}
		}
	}


	bool CollisionLayer::ActiveOnLayer(int layer)
	{
		return activeOnLayers.find(layer) != activeOnLayers.end();
	}

	bool CollisionLayer::ActiveOnLayer(std::string &layer)
	{
		return enforcedOn.find(layer) != enforcedOn.end();
	}

	void CollisionLayer::AddAsActiveLayer(int layer)
	{
		activeOnLayers.insert(layer);
	}
	void CollisionLayer::AddAsActiveLayer(std::string layerName)
	{
		enforcedOn.insert(layerName);
	}
}