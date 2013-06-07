#include <SFML/Graphics/Image.hpp>
#include <functional>

// Function that maps every pixel of dest to source, according to the transform
// transform: Takes pixel coordinates, returns texture coordinate vector with components in [0.f, 1.f]
void ApplyTransform(const sf::Image& source, sf::Image& dest, std::function<sf::Vector2f(unsigned int, unsigned int)> transform)
{
	for (unsigned int x = 0; x < dest.getSize().x; ++x)
	{
		for (unsigned int y = 0; y < dest.getSize().y; ++y)
		{
			sf::Vector2f texCoords = transform(x, y);

			// Invalid texture coordinates lead to transparent pixels
			sf::Color color(0, 0, 0, 0);
			if (texCoords != sf::Vector2f(-1.f, -1.f))
			{
				color = source.getPixel(
					static_cast<unsigned int>(source.getSize().x * texCoords.x), 
					static_cast<unsigned int>(source.getSize().y * texCoords.y));
			}

			dest.setPixel(x, y, color);
		}
	}
}
/*
#include <Thor/Vectors/PolarVector.hpp>

// Functor to transform every point in a circle sector piece to a square with width 1
struct CircleSectorPiece
{
// center: Center position of the circle
// r1:     Small radius, > 0
// r2:     Big radius, > r1
// phi1:   Begin angle, in [-180, 180[
// phi2:   End angle, in ]phi1, 180]
CircleSectorPiece(sf::Vector2f center, float r1, float r2, float phi1, float phi2)
: center(center)
, r1(r1)
, r2(r2)
, phi1(phi1)
, phi2(phi2)
{
}

sf::Vector2f operator() (unsigned int x, unsigned int y)
{
const sf::Vector2f pixelCoords(sf::Vector2i(x, y));

// Transform difference between current pixel and circle center to polar coordinates
const thor::PolarVector2f vec = pixelCoords - center;

// The actual transform, if point is inside the circle sector piece
if (vec.r > r1 && vec.r < r2 && vec.phi > phi1 && vec.phi < phi2)
{
return sf::Vector2f(
(vec.phi - phi1) / (phi2 - phi1),
1.f - (vec.r   - r1)   / (r2   - r1));
}

// Point is outside, return invalid texture coordinate
else
{
return sf::Vector2f(-1.f, -1.f);
}
};

sf::Vector2f center;
float r1;
float r2;
float phi1;
float phi2;
};
*/