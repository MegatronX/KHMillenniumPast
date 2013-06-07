#pragma once
#ifndef _VIEWMANIPULATOR_H_
#define _VIEWMANIPULATOR_H_
#include <SFML/Graphics.hpp>
#include <Graphics/Updater.h>
namespace Graphics
{
	class ViewTransform
	{
	public:
		ViewTransform(sf::View* view) : TargetView(view)
		{

		}
		sf::View* GetView() const
		{
			return TargetView;
		}
		void SetView(sf::View* view)
		{
			TargetView = view;
		}
		virtual ~ViewTransform()
		{
		}
	protected:
		sf::View* TargetView;
	};
	class ViewPositionPan : ViewTransform
	{
	public:
		ViewPositionPan(sf::View* view, sf::Vector2f& StartPos) : ViewTransform(view)
		{

		}
	protected:
		sf::Vector2f RunningPos;
		sf::Vector2f EndPos;
		sf::Vector2f StartPos;
	};
	class ViewManipulator : public Updater
	{
	public:
		ViewManipulator();
		ViewManipulator(sf::View* targetView);
		virtual void Update(const sf::Uint32 time, const float TimeScale = 1.0) override;
		virtual ~ViewManipulator()
		{
		}
	protected:
		sf::View* TargetView;
	private:
	};
}

#endif