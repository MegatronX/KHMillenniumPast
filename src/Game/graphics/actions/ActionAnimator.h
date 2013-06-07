#pragma once

#ifndef _ACTIONANIMATOR_H_
#define _ACTIONANIMATOR_H_
#include <Graphics/actions/ActionAnimation.h>
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include <deque>
namespace Game
{
	namespace Graphics
	{
		class ActionAnimator
		{
		public:
		protected:
			boost::unordered_map<std::string, boost::shared_ptr<ActionAnimation> > ActiveAnimations;
			std::deque<std::pair<std::string, boost::shared_ptr<ActionAnimation> > QueuedAnimations;
		private:
		};
	}
}

#endif