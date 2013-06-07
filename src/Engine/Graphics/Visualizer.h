#pragma once
#ifndef _VISUALIZER_H_
#define _VISUALIZER_H_
#include <graphics/AnimatedDraw.h>
namespace Graphics
{
	template<class T>
	class Visualizer : public AnimatedDraw
	{
	public:
		Visualizer(T* visualizing) : Visualizing(visualizing)
		{

		}
		const T* GetVisualizing() const
		{
			return Visualizing;
		}
		virtual void SetVisualizing(T* newVis)
		{
			Visualizing = newVis;
		}
	protected:
		T* Visualizing;
	private:
		
	};
}

#endif