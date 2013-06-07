#include "OpenGLHelpers.h"
#include <SFML/OpenGL.hpp>

namespace Graphics
{
	inline void SetupOpenGL2DView(const sf::View& view)
	{
		sf::Vector2f size(view.getSize());
		sf::Vector2f center(view.getCenter());
		sf::Vector2f position = center - size * 0.5f;

		// Edit the OpenGL projection matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Setup translation (according to left-upper corner) and scale
		glOrtho(0., size.x, size.y, 0., -1., 1.);
		glTranslatef(-position.x, -position.y, 0.f);

		// Setup rotation 
		glTranslatef(center.x, center.y, 0.f);
		glRotatef(view.getRotation(), 0.f, 0.f, -1.f);
		glTranslatef(-center.x, -center.y, 0.f);
	}
	void PushOpenGLStates(sf::RenderWindow& target)
	{
		// Switch to manual OpenGL handling, save SFML's state
		//target.SaveGLStates();
		target.setActive();

		// Switch blend mode, depending on glow effect	
		//if (mGlow)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		//else
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		// Store attributes and assign them
		glPushAttrib(GL_DEPTH_BITS | GL_TEXTURE_BIT);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);

		// Bind texture - instead of glBindTexture(GL_TEXTURE_2D, id)

		// Initialize projection matrix (2D view)
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		SetupOpenGL2DView(target.getView());

		// Initialize modelview matrix
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
	}
	void PopOpenGLStates(sf::RenderWindow& target)
	{
		// Restore projection matrix
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

		// Restore modelview matrix
		glMatrixMode(GL_MODELVIEW); 
		glPopMatrix();

		// Restore attributes
		glPopAttrib();

		// Switch back, restore SFML's OpenGL state
		//target.RestoreGLStates();
	}
}