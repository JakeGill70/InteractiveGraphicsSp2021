#pragma once
#ifndef JUMP_ANIMATION
#define JUMP_ANIMATION



#include "AbstractAnimation.h"
#include "AbstractInputSystem.h"
class JumpAnimation :
	public AbstractAnimation
{
protected:
    AbstractInputSystem* _inputSystem;
    float _speed;
    string _state;
public:

    JumpAnimation(float spd, AbstractInputSystem* inSys);

    void Update(double elapsedSeconds);

    void SetInputSystem(AbstractInputSystem* inputSystem) { _inputSystem = inputSystem; }

    void setSpeed(float spd) { _speed = spd; }

    void CheckInputSystem();
};

#endif // !JUMP_ANIMATION