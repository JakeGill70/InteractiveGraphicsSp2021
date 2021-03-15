#pragma once
#ifndef ROTATE_ANIMATION
#define ROTATE_ANIMATION

#include "AbstractAnimation.h";
#include <glm\glm.hpp>

class RotateAnimation :
	public AbstractAnimation
{
protected:
	glm::vec3 _axis;
	float _degreesPerSecond;
	void setAxis(glm::vec3 axis);
public:
	RotateAnimation();
	RotateAnimation(glm::vec3 axis, float degreesPerSecond);

	void Update(double elapsedSeconds);
};

#endif // !ROTATE_ANIMATION