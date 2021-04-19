#pragma once
#ifndef VISIBILITY_ANIMATION
#define VISIBILITY_ANIMATION

#include "AbstractAnimation.h"
#include "AbstractInputSystem.h"

class VisibilityAnimation :
	public AbstractAnimation
{
protected:
	bool _isShowing;
	AbstractInputSystem* _inputSystem;

public:
	VisibilityAnimation(AbstractInputSystem* inputSystem);

	void Update(double elapsedSeconds);
	void CheckInputSystem();
};

#endif // !VISIBILITY_ANIMATION
