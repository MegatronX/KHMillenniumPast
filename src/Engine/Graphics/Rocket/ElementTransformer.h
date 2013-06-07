#pragma once
#ifndef _ROCKETELEMENTTRANSFORM_H_
#define _ROCKETELEMENTTRANSFORM_H_

#include <Rocket/Controls.h>
#include <Rocket/Core/Element.h>
#include <sfml/System.hpp>

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/unordered_map.hpp>
namespace Graphics
{
	namespace GameRocket
	{
		class ElementTransformationInterface;
		class ElementTransformer
		{
		public:
			ElementTransformer(Rocket::Core::Element* targetEle = nullptr);
			ElementTransformer(std::vector<ElementTransformationInterface*>& initialTransforms, Rocket::Core::Element* targetEle = nullptr);
			ElementTransformer(std::vector< boost::shared_ptr<ElementTransformationInterface> >& initialTransforms);
			Rocket::Core::Element* GetTarget() const;
			void SetTarget(Rocket::Core::Element* targetEle);
			void Update(const sf::Uint32 time);
			//void AddTransformation(ElementTransformationInterface* transform);
			void AddTransformation( boost::shared_ptr<ElementTransformationInterface> transform);
			//void AddTransformationWithPostTransform();
		private:
			std::vector< boost::shared_ptr<ElementTransformationInterface> > transformations;
			std::vector< boost::shared_ptr<ElementTransformationInterface> > readytransformations;
			bool Updating;
			//sf::Mutex UpdateLock;
			boost::unordered_map<ElementTransformationInterface*, std::vector<boost::shared_ptr<ElementTransformationInterface> > > postTransformations;
			Rocket::Core::Element* target;
		};
	}
}

#endif