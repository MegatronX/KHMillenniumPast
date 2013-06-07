#pragma once
#ifndef _SHAPES_H_
#define _SHAPES_H_

#include <sfml/Graphics.hpp>
#include <thor/Math.hpp>
#include <thor/Vectors.hpp>
#include <thor/Shapes.hpp>
#include <boost/shared_ptr.hpp>
namespace Graphics
{
	//Image Pathers

	/*template <class Shape>
	void addPoint(sf::Shape& shape, sf::Vector2f point)
	{
		const unsigned int size = shape.getPointCount();

		shape.setPointCount(size + 1);
		shape.setPoint(size, point);
	}*/

	class CircularPath : public sf::Shape
	{
	public:
		CircularPath(const float innerRadius, const float thickness, const float arcDegrees, float startingAngle, const unsigned int points, bool clockWise) 
			: InnerRadius(innerRadius), Thickness(thickness), PointCount(points), ArcDegrees(arcDegrees), StartingAngle(startingAngle), EndingAngle(static_cast<int>(startingAngle + (clockWise ? arcDegrees : -arcDegrees)) % 360),
			Path(sf::TrianglesStrip)
		{
			if (points > 0 && ArcDegrees > 0.f)
			{

				ArcDegrees = std::fmod(ArcDegrees, 360.f);

				// nbTotalPoints = the points that would be there at a full circle; nbActualPoints = the actual points
				const unsigned int nbTotalPoints = (PointCount / ArcDegrees) * 360.f;
				const unsigned int nbActualPoints = static_cast<unsigned int>(ArcDegrees / 360.f * nbTotalPoints);

				// Add center point, unless the pie is full
				//if (filledAngle != 0.f)
				//addPoint(shape, sf::Vector2f(0.f, 0.f));

				thor::PolarVector2f vector(innerRadius, StartingAngle);
				thor::PolarVector2f vectorOut(innerRadius + Thickness, StartingAngle);
				float incrementer = (360.f / nbTotalPoints) * (clockWise ? 1 : -1);
				for (unsigned int i = 0; i <= nbActualPoints; ++i)
				{
					vector.phi = incrementer * i;
					vectorOut.phi = incrementer * i;
					Path.append(sf::Vertex(vector));//, sf::Color::Black));
					Path.append(sf::Vertex(vectorOut));//, sf::Color::Black));
					//addPoint(*this, vector);
				}

				/*float degreesPerPoint = arcDegrees / static_cast<float>(points) * (clockWise ? 1 : -1);
				thor::PolarVector2f vec(InnerRadius, StartingAngle);
				thor::PolarVector2f outVec(InnerRadius + Thickness, StartingAngle);
				//Path.resize(points);
				for (int i = 0; i < points; ++i)
				{
					vec.phi += degreesPerPoint * i;
					outVec.phi += degreesPerPoint * i;
					sf::Vector2f innerPoint = vec;
					innerPoint += Center;
					sf::Vector2f outerPoint = outVec;
					outerPoint += Center;
					Path.append(sf::Vertex(innerPoint, sf::Color::Black));
					Path.append(sf::Vertex(outerPoint, sf::Color::Black));
				}*/
			}
			
			
			//arcDegrees/static_cast<float>(points);
		}

		void MapTexture()
		{
			auto texture = getTexture();
			if (texture != nullptr && Path.getVertexCount() > 0)
			{
				auto size = texture->getSize();
				float xInc = size.x / static_cast<float>(Path.getVertexCount());
				for (int i = 0; i < Path.getVertexCount(); i += 2)
				{
					float mappedX = xInc * static_cast<float>(i);
					Path[i].texCoords.x = mappedX;
					Path[i].texCoords.y = 0;
					Path[i + 1].texCoords.x = mappedX;
					Path[i + 1].texCoords.y = size.y;
				}
			}
		}

		void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			states.transform *= getTransform();

			// Render the inside
			//if (m_fillColor.a > 0)
			{
				states.texture = getTexture();//m_texture;
				//states.texture = nullptr;
				target.draw(Path, states);
			}

			// Render the outline
			//if ((m_outlineColor.a > 0) && (m_outlineThickness > 0))
			{
			//	states.texture = NULL;
			//	target.draw(m_outlineVertices, states);
			}
		}

		unsigned int getPointCount(void) const
		{
			return PointCount;
		}

		sf::Vector2f getPoint(unsigned int point) const
		{
			return Path[point].position;
		}

	protected:
		float Thickness;
		float InnerRadius;
		float ArcDegrees;
		float StartingAngle;
		float EndingAngle;
		unsigned int PointCount;
		sf::VertexArray Path;
	};

	class HollowCircle : public sf::Shape
	{
	public:
		HollowCircle(const float circleRadius, const float circleDegrees, const float startAngle, const bool clockwise = true, const unsigned int circlePoints = 120, const float thickness = 6.f);
		HollowCircle(boost::shared_ptr<sf::Texture> targetTexture, const float circleRadius, const float circleDegrees, const float startAngle, const float thickness = 6.f, const bool clockwise = true, const unsigned int circlePoints = 120);
		void MapTexture();

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		unsigned int getPointCount(void) const;
		sf::Vector2f getPoint(unsigned int point) const;

		sf::VertexArray& GetVertexArray();
	private:
		float CircleRadius;
		float ArcAngle;
		float StartAngle;
		float CircleThickness;
		boost::shared_ptr<sf::Texture> TargetTexture;
		unsigned int PointCount;

		sf::VertexArray PathPoints;
	};


	//thor::ConcaveShape EmptyCircle(float radius, float filledAngle, float startAngle, const sf::Color& fillColor, float Thickness = 0.f, const unsigned int pointCount = 100);
}

#endif