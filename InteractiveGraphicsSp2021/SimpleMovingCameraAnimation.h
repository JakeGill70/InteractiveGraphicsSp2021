#pragma once
#ifndef SIMPLE_MOVING_CAMERA_ANIMATION
#define SIMPLE_MOVING_CAMERA_ANIMATION

#include "AbstractCameraAnimation.h"

class AbstractKeyBinding;

enum class SimpleMovingState {
   Not_Moving, Moving_Forward, Moving_Backward, Moving_Left, Moving_Right,
   Turning_Left, Turning_Right
};

class SimpleMovingCameraAnimation :
    public AbstractCameraAnimation
{
protected:
   SimpleMovingState _state;
   float _speed, _turnSpeed;

public:
   SimpleMovingCameraAnimation(
      BaseCamera* camera,
      AbstractInputSystem* inputSystem,
      AbstractKeyBinding* keyBinding);

   inline SimpleMovingState GetState();
   inline void SetState(SimpleMovingState state);

   void Update(double elapsedSeconds);

   void CheckInputSystem();
};

#endif

