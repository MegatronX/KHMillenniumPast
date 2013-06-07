#pragma once
#ifndef _ANIMSPRITEINTER_H_
#define _ANIMSPRITEINTER_H_

#include <Graphics/Sprites/SpriteInterface.h>
#include <Graphics/AnimatedDraw.h>
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include <Graphics/Transformers/BaseTransform.h>
namespace Graphics
{
	class AnimatedSpriteInterface : public SpriteInterface, public virtual AnimatedDraw
	{
	public:
		AnimatedSpriteInterface(bool clearExpired = true);

		virtual void Update(const sf::Uint32 time, const float TimeScale = 1.f) override;
		virtual void AddTransform(const std::string& index, boost::shared_ptr<BaseTransform> transform, bool overwriteExisting = true);

		virtual bool RemoveTransform(const std::string index);

		virtual void ClearTransforms(const sf::Uint32 time, bool dispatchTranformFinishedEvents = true);

		virtual boost::unordered_map<std::string, boost::shared_ptr<BaseTransform> >& GetActiveTransforms();

		bool GetClearExpired();

		void SetClearExpired(const bool value = true);
	protected:
		bool ClearExpired;
		boost::unordered_map<std::string, boost::shared_ptr<BaseTransform> > ActiveTransforms;
		std::vector<boost::unordered_map<std::string, boost::shared_ptr<BaseTransform> >::iterator> RemovalList;
	private:
	};
}

#endif