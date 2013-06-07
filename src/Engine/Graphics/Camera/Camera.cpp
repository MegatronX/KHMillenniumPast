#include "Camera.h"
#include <gl/glew.h>
namespace Graphics
{
	Camera::Camera()
		:   myFOV(70),
		myNearValue(1),
		myFarValue(1000),
		myAspectRatio(4.f / 3.f),
		myTarget()
	{

	}

	void    Camera::SetPosition(const sf::Vector3f& position)
	{
		myPosition = position;
	}

	const sf::Vector3f& Camera::GetPosition() const
	{
		return myPosition;
	}

	void    Camera::Move(const sf::Vector3f& move)
	{
		myPosition += move;
	}

	void    Camera::SetRotation(const sf::Vector3f& rotation)
	{
		myRotation = rotation;
	}

	const sf::Vector3f& Camera::GetRotation() const
	{
		return myRotation;
	}

	void    Camera::Rotate(const sf::Vector3f& rotate)
	{
		myRotation += rotate;
	}
	void    Camera::SetFOV(float fov)
	{
		myFOV = fov;
	}

	float   Camera::GetFOV() const
	{
		return myFOV;
	}

	void    Camera::SetNearValue(float nearValue)
	{
		myNearValue = nearValue;
	}

	float   Camera::GetNearValue() const
	{
		return myNearValue;
	}

	void    Camera::SetFarValue(float farValue)
	{
		myFarValue = farValue;
	}

	float   Camera::GetFarValue() const
	{
		return myFarValue;
	}

	void    Camera::SetAspectRatio(float aspectRatio)
	{
		myAspectRatio = aspectRatio;
	}

	float   Camera::GetAspectRatio() const
	{
		return myAspectRatio;
	}

	void    Camera::SetTarget(const sf::Vector3f& target)
	{
		myTarget = target;
	}

	const sf::Vector3f& Camera::GetTarget() const
	{
		return myTarget;
	}

	void    Camera::Set()
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(myFOV, myAspectRatio, myNearValue, myFarValue);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef(myRotation.x, 1, 0, 0);
		glRotatef(myRotation.y, 0, 1, 0);
		glRotatef(myRotation.z, 0, 0, 1);
		glTranslatef(myPosition.x, myPosition.y, myPosition.z);
	}


}
