/////////////////////////////////////////////////////////////////////////////////
//
// Thor C++ Library
// Copyright (c) 2011-2012 Jan Haller
// 
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////

/// @file
/// @brief Class thor::FrameAnimation

#ifndef _FRAMEANIMATION_HPP
#define _FRAMEANIMATION_HPP


#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <cassert>

namespace Graphics
{


namespace detail
{

	// Class that stores a single frame of FrameAnimation
	struct Frame
	{
		Frame(float duration, const sf::IntRect& subrect)
		: duration(duration)
		, subrect(subrect)
		{
		}

		mutable float			duration;
		sf::IntRect				subrect;
	};

} // namespace detail

// ---------------------------------------------------------------------------------------------------------------------------


/// @addtogroup Animation
/// @{

/// @brief Changes a sprite's subrect over time. 
/// @details This class stores multiple frames that represent the sub-rectangle of a texture. The resulting animation consists
///  of a sequence of frames that are drawn one after another.
class FrameAnimation
{
	// ---------------------------------------------------------------------------------------------------------------------------
	// Public member functions
	public:
		/// @brief Default constructor
		/// 
									FrameAnimation();

		/// @brief Adds a frame to the animation, changes only the sub-rect.
		/// @param relativeDuration Duration of the frame relative to the other durations.
		/// @param subrect %Rectangle of the sf::Texture that is used for the new frame.
		void						addFrame(float relativeDuration, const sf::IntRect& subrect);


		int							getFrameCount() const;
		/// @brief Animates the object.
		/// @param animated Object to animate.
		/// @param progress Value in [0,1] determining the progress of the animation.
		/// @tparam Animated Class with member function <i>void setTextureRect(sf::IntRect)</i>, for example sf::Sprite.
		template <class Animated>
		void						operator() (Animated& animated, float progress, bool flipped = false) const;
	

	// ---------------------------------------------------------------------------------------------------------------------------
	// Private member functions
	private:
		void						ensureNormalized() const;


	// ---------------------------------------------------------------------------------------------------------------------------
	// Private variables
	private:
		std::vector<detail::Frame>	mFrames;
		mutable bool				mNormalized;
};

/// @}

// ---------------------------------------------------------------------------------------------------------------------------


template <class Animated>
void FrameAnimation::operator() (Animated& target, float progress, bool flipped) const
{
	assert(!mFrames.empty());

	//assert(progress >= 0.f && progress <= 1.f);

	ensureNormalized();
	int i = 0;
	for (auto it = mFrames.begin(); it != mFrames.end(); ++it, ++i)
	{
		progress -= (*it).duration;
		if (progress < 0.f)
		{
			if (!flipped)
				target.setTextureRect(it->subrect);
			else
			{
				//Need to invert subrect
				target.setTextureRect(sf::IntRect(it->subrect.left + it->subrect.width, it->subrect.top, -it->subrect.width, it->subrect.height)); 
			}
			break;
		}
	}
}

} // namespace thor

#endif // THOR_FRAMEANIMATION_HPP
