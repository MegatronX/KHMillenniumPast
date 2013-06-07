#pragma once
#ifndef _OPENGLHELPERS_H_
#define _OPENGLHELPERS_H_

#include <SFML/Graphics.hpp>
namespace Graphics
{
	inline void SetupOpenGL2DView(const sf::View& view);
	void PushOpenGLStates(sf::RenderWindow& target);
	void PopOpenGLStates(sf::RenderWindow& target);
}

#endif