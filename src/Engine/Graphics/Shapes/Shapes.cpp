#include "Shapes.h"

namespace Graphics
{
	using namespace thor;

	template <class Shape>
	void addPoint(Shape& shape, sf::Vector2f point)
	{
		const unsigned int size = shape.getPointCount();

		shape.setPointCount(size + 1);
		shape.setPoint(size, point);
	}

	thor::ConcaveShape EmptyCircle(float radius, float filledAngle, float startAngle, const sf::Color& fillColor, float Thickness, const unsigned int pointCount)
	{
		if (radius > 0.f)
		{
			assert(radius > 0.f);

			ConcaveShape shape;
			sf::Color f(fillColor);
			f.a = 0;
			shape.setFillColor(f);
			shape.setOutlineThickness(Thickness);
			shape.setOutlineColor(fillColor);

			filledAngle = std::fmod(filledAngle, 360.f);

			// nbTotalPoints = the points that would be there at a full circle; nbActualPoints = the actual points
			const unsigned int nbTotalPoints = (pointCount / filledAngle) * 360.f;
			const unsigned int nbActualPoints = static_cast<unsigned int>(filledAngle / 360.f * nbTotalPoints);

			// Add center point, unless the pie is full
			//if (filledAngle != 0.f)
				//addPoint(shape, sf::Vector2f(0.f, 0.f));

			PolarVector2f vector(radius, 0.f);
			for (unsigned int i = 0; i <= nbActualPoints; ++i)
			{
				vector.phi = 360.f * i / nbTotalPoints;

				addPoint(shape, vector);
			}
			return shape;
		}
	}


	HollowCircle::HollowCircle(const float circleRadius, const float circleDegrees, const float startAngle, const bool clockwise, const unsigned int circlePoints, const float thickness)
		: CircleRadius(circleRadius), ArcAngle(circleDegrees), StartAngle(startAngle), PointCount(circlePoints), CircleThickness(thickness), PathPoints(sf::TrianglesStrip)
	{
		ArcAngle = std::fmod(ArcAngle, 360);
		if (circlePoints > 0 && ArcAngle > 0)
		{
			const unsigned int nbTotalPoints = (static_cast<float>(PointCount) / ArcAngle) * 360.f;
			const unsigned int nbActualPoints = static_cast<unsigned int>(ArcAngle / 360.f * nbTotalPoints);

			// Add center point, unless the pie is full
			//if (filledAngle != 0.f)
			//addPoint(shape, sf::Vector2f(0.f, 0.f));

			thor::PolarVector2f vector;//(innerRadius, StartingAngle);
			thor::PolarVector2f vectorOut;//(innerRadius + Thickness, StartingAngle);

			vector.r = CircleRadius;
			vectorOut.r = CircleRadius + CircleThickness;
			vector.phi = vectorOut.phi = startAngle;
			float incrementer = (360.f / nbTotalPoints) * (clockwise ? 1 : -1);
			for (unsigned int i = 0; i <= nbActualPoints; ++i)
			{
				vector.phi += incrementer;
				vectorOut.phi += incrementer;
				PathPoints.append(sf::Vertex(vector));
				PathPoints.append(sf::Vertex(vectorOut));
			}
		}
		this->setTexture(nullptr);

		MapTexture();
		setFillColor(sf::Color::Black);
	}

	HollowCircle::HollowCircle(boost::shared_ptr<sf::Texture> tx, const float circleRadius, const float circleDegrees, const float startAngle, const float thickness, const bool clockwise, const unsigned int circlePoints)
		: TargetTexture(tx), CircleRadius(circleRadius), ArcAngle(circleDegrees), StartAngle(startAngle), PointCount(circlePoints), CircleThickness(thickness), PathPoints(sf::TrianglesStrip)
	{
		ArcAngle = std::fmod(ArcAngle, 360);
		if (circlePoints > 0 && ArcAngle > 0)
		{
			const unsigned int nbTotalPoints = (static_cast<float>(PointCount) / ArcAngle) * 360.f;
			const unsigned int nbActualPoints = static_cast<unsigned int>(ArcAngle / 360.f * nbTotalPoints);

			// Add center point, unless the pie is full
			//if (filledAngle != 0.f)
			//addPoint(shape, sf::Vector2f(0.f, 0.f));

			thor::PolarVector2f vector;//(innerRadius, StartingAngle);
			thor::PolarVector2f vectorOut;//(innerRadius + Thickness, StartingAngle);

			vector.r = CircleRadius;
			vectorOut.r = CircleRadius + CircleThickness;
			vector.phi = vectorOut.phi = startAngle;
			float incrementer = (360.f / nbTotalPoints) * (clockwise ? 1 : -1);
			for (unsigned int i = 0; i <= nbActualPoints; ++i)
			{
				vector.phi += incrementer;//incrementer * i + StartAngle;
				vectorOut.phi += incrementer;// * i + StartAngle;

				//sf::Vector2f effVector = vector;
				//std::cout << "Vector Phi: " << vector.phi << ", Vector R: " << vector.r << " | Effective Vector X: " << effVector.x << ", Y: " << effVector.y << "\n";
				PathPoints.append(sf::Vertex(vector));//, sf::Color::Black));
				PathPoints.append(sf::Vertex(vectorOut));//, sf::Color::Black));
				//addPoint(*this, vector);
			}
		}
		//BarPortionPath.setTexture(TargetTexture.get());
		this->setTexture(TargetTexture.get());

		MapTexture();
	}

	void HollowCircle::MapTexture()
	{
		auto texture = getTexture();
		if (texture != nullptr && PathPoints.getVertexCount() > 0)
		{
			auto size = texture->getSize();
			float xInc = size.x / static_cast<float>(PathPoints.getVertexCount());
			for (int i = 0; i < PathPoints.getVertexCount(); i += 2)
			{
				float mappedX = xInc * static_cast<float>(i);
				PathPoints[i].texCoords.x = mappedX;
				PathPoints[i].texCoords.y = 0;
				PathPoints[i + 1].texCoords.x = mappedX;
				PathPoints[i + 1].texCoords.y = size.y;
			}
		}
	}

	void HollowCircle::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = getTexture();

		target.draw(PathPoints, states);
	}

	unsigned int HollowCircle::getPointCount(void) const
	{
		return PathPoints.getVertexCount();
	}
	sf::Vector2f HollowCircle::getPoint(unsigned int point) const
	{
		return PathPoints[point].position;
	}

	sf::VertexArray& HollowCircle::GetVertexArray()
	{
		return PathPoints;
	}

}