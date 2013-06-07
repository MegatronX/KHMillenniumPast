#pragma once
#include <vector>
#include <string>
#include <boost\unordered_set.hpp>
#include <boost\shared_ptr.hpp>

namespace Mapping
{
	typedef std::pair<std::string, std::string> LayerProperty;

	class Layer
	{
	public:
		Layer(void);
		Layer(std::string &Name, int Width, int Height, int TileWidth, int TileHeight, std::string &decodedString);
		Layer(std::string &Name, int Width, int Height, int TileWidth, int TileHeight, std::string &b64String, bool DecodedFromBase64);
		virtual ~Layer(void);

		std::string GetName();

		int GetWidth();
		int GetHeight();
		int GetTileWidth();
		int GetTileHeight();
		int GetLayerNum();
		int GetDrawOrder();
		float GetOpacity();
		void SetLayerNum(int value);
		void SetDrawOrder(int value);
		void SetOpacity(float value);

		bool GetIsAnimated() const;

		void AddCollisionLayerName(std::string &name);

		unsigned int At(int index);
		unsigned int At(int x, int y);

		bool IsActive();

		void AddExtendedProperty(std::string &name, std::string &value);
		void SetExtendedProperties(std::vector<LayerProperty> &properties);
		static unsigned int* GenerateDataFromDecodedString(std::string &decodedstring, int width, int height);
		static unsigned int* GenerateDataFromBase64String(std::string &base64string, int width, int height);
	protected:
		bool IsAnimated;
		bool active;
		unsigned int* layerData;
		int width, height; //in Tiles
		int tileWidth, tileHeight;
		int maxIndex;
		int layerNum;
		int drawOrder;
		float opacity;
		std::string name;
		std::vector<LayerProperty> extendedProperties;
		std::vector<std::string> collisionLayerNames;
	private:

	};

	class CollisionLayer : public Layer
	{
	public:
		CollisionLayer(void);
		CollisionLayer(std::string &name, int width, int height, int tilewidth, int tileheight, std::string &decodedstring, boost::unordered_set<int> &activeLayerSet);
		CollisionLayer(std::string &name, int width, int height, int tilewidth, int tileheight, std::string &decodedstring, boost::unordered_set<std::string> &activeLayerSet);
		bool ActiveOnLayer(int layer);
		bool ActiveOnLayer(std::string &layerName);
		void AddAsActiveLayer(int layer);
		void AddAsActiveLayer(std::string layerName);
	private:
		boost::unordered_set<std::string> enforcedOn; 
		boost::unordered_set<int> activeOnLayers;


	};

	typedef boost::shared_ptr<Layer> layer_ptr;
	typedef boost::shared_ptr<CollisionLayer> col_layer_ptr;


}
