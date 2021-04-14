#pragma once
#ifndef SINE_WAVE_MOVEMENT_ANIMATION
#define SINE_WAVE_MOVEMENT_ANIMATION

#include "AbstractAnimation.h"
#include <glm\glm.hpp>

class SineWaveMovementAnimation :
	public AbstractAnimation
{
protected:
    glm::vec3 _lateralMovement;
    float _verticalMovementSpeed;
    float _height;
    glm::vec3 _startPosition;
    float _runTime;
    float _currTime;
    string _state;

public:
    SineWaveMovementAnimation(glm::vec3 latMovement, float runTime, glm::vec3 position);

    void Update(double elapsedSeconds);

    void SetLatMovement(glm::vec3 dir){ _lateralMovement = dir; }
    void SetVertMoveSpeed(float spd) { _verticalMovementSpeed = spd; }
    void SetHeight(float h) { _height = h; }
    void SetStartPos(glm::vec3 pos) { _startPosition = pos; }
    void setRunTime(float sec) { _runTime = sec; }
    
};

#endif // !SINE_WAVE_MOVEMENT_ANIMATION
