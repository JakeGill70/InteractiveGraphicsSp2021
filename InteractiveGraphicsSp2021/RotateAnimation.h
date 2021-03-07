#pragma once
#ifndef ROTATE_ANIMATION
#define ROTATE_ANMATION

#include "AbstractAnimation.h"
#include <glm\glm.hpp>
#include "ReferenceFrame.h"

class RotateAnimation :
    public AbstractAnimation
{
protected:
   glm::vec3 _axis;
   float _degreesPerSecond;

public:
   RotateAnimation() : _axis({ 0, 1, 0 }), _degreesPerSecond(90.0f) {}

   void Update(double elapsedSeconds) {
      if (_object == nullptr) return;
      float angleToRotate = _degreesPerSecond * (float)elapsedSeconds;
   }

};

#endif

