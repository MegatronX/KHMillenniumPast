#pragma once
#ifndef _IANIMATED_DRAW_H_
#define _IANIMATED_DRAW_H_
#include <sfml\Graphics.hpp>
#include <sfml\System.hpp>
#include <graphics/DrawInterface.h>
#include <Graphics/Updater.h>
namespace Graphics
{
	class AnimatedDraw : public virtual DrawInterface, public Updater
	{
	public:
		AnimatedDraw(bool paused = false, int drawPriority = 0) : DrawInterface(drawPriority), Paused(paused)
		{
		}
		virtual void SetPause(const bool value)
		{
			Paused = value;
		}
		virtual bool GetPause() const
		{
			return Paused;
		}
		/*virtual RawClonePtr RawClone() const override
		{
			return new AnimatedDraw(*this);
		}*/

		virtual ~AnimatedDraw()
		{

		}
	protected:
		bool Paused;
	private:
	};
}


#endif