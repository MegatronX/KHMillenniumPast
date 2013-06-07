#pragma once

#include <string>
#include <vector>
#include <sfml\Graphics.hpp>
#include <boost\shared_ptr.hpp>

namespace Mapping
{
	class TileSet
	{
	public:
		TileSet(void);
		TileSet(std::string &name, int firstGID);
		TileSet(std::string &name, int firstGID, int tileWidth, int tileHeight, boost::shared_ptr<sf::Texture> refImage);
		TileSet(std::string &name, int firstGID, int tileWidth, int tileHeight, sf::Texture &sourceImage);

		virtual int GetFirstGID();
		virtual int GetEndGID();
		sf::Sprite& GetTile(int index);
		std::string GetName();

		const sf::Texture& GetTexture();
		void SetTexture(sf::Texture& image);

		void SetTexture(boost::shared_ptr<sf::Texture>& tex);

		void Add(sf::Sprite &sprite);

		bool IsAnimated() const;

		virtual ~TileSet(void);
	protected:
		sf::Texture referenceTexture;
		bool useImagePtr;
		boost::shared_ptr<sf::Texture> BaseTexture;
		std::string name;
		std::vector<sf::Sprite> tilesprites;
		std::vector<sf::Sprite>* activetiles;
		std::vector<sf::IntRect> tilerects;
		int firstGID;
		int endGID;
		int tileWidth, tileHeight;
		bool Animated;
	private:

	};

	typedef boost::shared_ptr<TileSet> tileset_ptr;

}