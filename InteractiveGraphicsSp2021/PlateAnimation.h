#pragma once
#ifndef PLATE_ANIMATION
#define PLATE_ANMATION
#include "AbstractAnimation.h"
#include <glm\glm.hpp>

class PlateAnimation :
	public AbstractAnimation
{
protected:
    float _degreesPerSecond;
    float _degreesRotated;
    float _raiseHeight;
    float _lateralMovement;
    float _waitTime;
    string _state;

public:
    PlateAnimation() : _degreesPerSecond(90.0f), _raiseHeight(0), _lateralMovement(0), _waitTime(1), _state("First Raise"), _degreesRotated(0) {}

    void Update(double elapsedSeconds);

};

#endif

