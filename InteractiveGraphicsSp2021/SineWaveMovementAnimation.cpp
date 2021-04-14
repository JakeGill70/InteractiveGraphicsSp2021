#include "SineWaveMovementAnimation.h"
#include "ReferenceFrame.h"
#include "GraphicsObject.h"

SineWaveMovementAnimation::SineWaveMovementAnimation(glm::vec3 latMovement, float runTime, glm::vec3 position) {
	SetLatMovement(latMovement);
	SetVertMoveSpeed(1);
	SetHeight(1);
	SetStartPos(position);
	setRunTime(runTime);
	_currTime = 0;
	_state = "reset";
}

void SineWaveMovementAnimation::Update(double elapsedSeconds) {
	if (_object == nullptr) return;
	if (_state == "reset") {
		_object->frame.SetPosition(_startPosition);
		_state = "move";
		_currTime = 0;
	}
	else if (_state == "move") {
		_object->frame.TranslateWorld(_lateralMovement * (float)elapsedSeconds);
		float sinWaveAmt = (float)sin(_currTime * _verticalMovementSpeed) * _height;
		glm::vec3 vertPos = { 0,1,0 };
		vertPos *= sinWaveAmt;
		glm::vec3 currPos = { _object->frame.GetPosition().x, _startPosition.y, _object->frame.GetPosition().z };
		vertPos = currPos + vertPos;
		_object->frame.SetPosition(vertPos);
		_currTime += (float)elapsedSeconds;
		if (_currTime > _runTime) {
			_state = "reset";
		}
	}
}