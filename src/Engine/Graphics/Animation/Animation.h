#pragma once


namespace Graphics
{
	template <class Animated>
	class Animation
	{
		virtual void operator() (Animated& animated, float progress) const = 0;
	};
}