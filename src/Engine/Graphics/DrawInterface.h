#pragma once
#ifndef _DRAWINTERFACE_H_
#define _DRAWINTERFACE_H_
#include <sfml/Graphics.hpp>
#include <sfml/Window.hpp>
#include <Utilities/Cloneable.h>
namespace Graphics
{
	class DrawInterface : /*public Cloneable<DrawInterface>, */public sf::Drawable
	{
	public:
		DrawInterface(const int drawPriority = 0, const bool drawing = true) : DrawPriority(drawPriority), Drawing(drawing)
		{

		}
		bool IsDrawing() const
		{
			return Drawing;
		}
		void SetDrawing(const bool value)
		{
			Drawing = value;
		}

		int GetDrawPriority() const
		{
			return DrawPriority;
		}
		void SetDrawPriority(const int priority)
		{
			DrawPriority = priority;
		}
		/*RawClonePtr RawClone() const override
		{
			return new DrawInterface(*this);
		}
		*/
		//sf::Drawable overrides

		virtual void Draw(sf::RenderTarget& target)
		{
			draw(target, sf::Transform());
		}

		virtual void Draw(sf::RenderTarget & target, sf::RenderStates states)
		{
			draw(target, states);
		}

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{

		}

		/*virtual void Draw(sf::RenderWindow &window) { }
		virtual void Draw(sf::RenderWindow &window, sf::Shader &shader) {}*/
		
		virtual ~DrawInterface()
		{

		}

	protected:
		bool Drawing;
		int DrawPriority;
	private:

	};
	class DrawXInterface : public Cloneable<DrawXInterface>
	{
	public:
		DrawXInterface(int drawPriority = 0, bool drawing = true) : DrawPriority(drawPriority), Drawing(drawing)
		{

		}
		bool IsDrawing() const
		{
			return Drawing;
		}
		void SetDrawing(const bool value)
		{
			Drawing = value;
		}
		virtual void Draw(sf::RenderWindow &window) { }
		virtual void Draw(sf::RenderWindow &window, sf::Shader &shader) {}
		int GetDrawPriority() const
		{
			return DrawPriority;
		}
		void SetDrawPriority(const int priority)
		{
			DrawPriority = priority;
		}
		RawClonePtr RawClone() const override
		{
			return new DrawXInterface(*this);
		}
		virtual ~DrawXInterface()
		{

		}
	protected:
		bool Drawing;
		int DrawPriority;
	private:
		
	};
}

#endif