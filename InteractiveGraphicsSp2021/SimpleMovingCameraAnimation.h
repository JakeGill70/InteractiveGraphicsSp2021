#pragma once
#ifndef SIMPLE_MOVING_CAMERA_ANIMATION
#define SIMPLE_MOVING_CAMERA_ANIMATION

#include "AbstractCameraAnimation.h"

enum class SimpleMovingState {
   Not_Moving, Moving_Forward, Moving_Backward, Moving_Left, Moving_Right
};

class SimpleMovingCameraAnimation :
    public AbstractCameraAnimation
{
protected:
   SimpleMovingState _state;
   float _speed;

public:
   SimpleMovingCameraAnimation();

   inline SimpleMovingState GetState();
   inline void SetState(SimpleMovingState state);

   void Update(float elapsedSeconds);
};

#endif

