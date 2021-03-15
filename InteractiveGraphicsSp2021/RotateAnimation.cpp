#include "RotateAnimation.h"
#include "AbstractGraphicsObject.h"

RotateAnimation::RotateAnimation(){
	setAxis(glm::vec3(0.0f, 1.0f, 0.0f));
	_degreesPerSecond = 90.0f;
}

RotateAnimation::RotateAnimation(glm::vec3 axis, float degreesPerSecond) {
	setAxis(axis);
	_degreesPerSecond = degreesPerSecond;
}

void RotateAnimation::setAxis(glm::vec3 axis) {
	_axis = axis;
}

void RotateAnimation::Update(double elapsedSeconds) {
	if (_object == nullptr) {
		return;
	}
	double degreesToRotate = _degreesPerSecond * elapsedSeconds;
	_object->frame.RotateLocal(degreesToRotate, _axis);
}