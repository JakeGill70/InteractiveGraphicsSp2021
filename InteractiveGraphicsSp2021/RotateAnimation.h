#pragma once
#ifndef ROTATE_ANIMATION
#define ROTATE_ANMATION

#include "AbstractAnimation.h"
#include <glm\glm.hpp>


class RotateAnimation :
    public AbstractAnimation
{
protected:
   glm::vec3 _axis;
   float _degreesPerSecond;

public:
   RotateAnimation() : _axis({ 0, 1, 0 }), _degreesPerSecond(90.0f) {}
   RotateAnimation(glm::vec3 axis, float degreesPerSecond) 
      : _axis(axis), _degreesPerSecond(degreesPerSecond) {}

   void Update(double elapsedSeconds);

};

#endif

