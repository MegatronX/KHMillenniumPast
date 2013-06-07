#pragma once
#ifndef _PATHPOSITIONTRANSFORMER_H_
#define _PATHPOSITIONTRANSFORMER_H_

#include "ElementTransformer.h"
#include "ElementTransformInterface.h"
#include <Math/MathFormula.h>
#include <boost/lexical_cast.hpp>
#include <Rocket/Controls.h>
#include <Rocket/Core.h>
#include <sfml/System.hpp>

namespace Graphics
{
	namespace GameRocket
	{
		class PathPositionTransformer : ElementTransformationInterface
		{
		public:
			PathPositionTransformer(ElementTransformer* transform, const std::string& pathFormula, const sf::Uint32 currentTime, sf::Uint32 endTime, bool IsXPath = true)
				: ElementTransformationInterface(transform, currentTime, endTime), PathInX(IsXPath), PathInY(!IsXPath), (IsXPath ? PathFormulaX(pathFormula) : PathFormulaY(pathFormula))
			{

			}
			virtual void ReInitialize(const sf::Uint32 currentTime, const sf::Uint32 EndTime_, ElementTransformer* holder) override
			{
				ElementTransformationInterface::ReInitialize(currentTime, EndTime_, holder);
				if (!Finished)
				{
				}

			}
			void FullReInitialize(sf::Vector2f TargetOffset, const sf::Uint32 currentTime, const sf::Uint32 EndTime_, ElementTransformer* holder)
			{
				
			}
			virtual void Update(ElementTransformer* eletarget, const sf::Uint32 time) override
			{
				if (!Finished)
				{
					if (PathInX)
					{
						auto left = eletarget->GetTarget()->GetProperty(Rocket::Core::String("left"));
					}
					if (PathInY)
					{

					}
					ElementTransformationInterface::Update(eletarget, time);
				}
			}

			MathFormula& GetXFormula()
			{
				return PathFormulaX;
			}

			MathFormula& GetYFormula()
			{
				return PathFormulaY;
			}
			bool GetPathInX()
			{
				return PathInX;
			}
			bool GetPathInY()
			{
				return PathInY;
			}
		private:
			MathFormula PathFormulaX;
			bool PathInX;
			MathFormula PathFormulaY;
			bool PathInY;
		};
	}
}

#endif