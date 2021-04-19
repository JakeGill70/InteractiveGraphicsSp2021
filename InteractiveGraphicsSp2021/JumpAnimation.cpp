#include "JumpAnimation.h"
#include "ReferenceFrame.h"
#include "GraphicsObject.h"

JumpAnimation::JumpAnimation(float spd, AbstractInputSystem* inSys) {
	setSpeed(spd);
	SetInputSystem(inSys);
	_state = "falling";
}

void JumpAnimation::Update(double elapsedSeconds)
{
	if (_object == nullptr) return;
	CheckInputSystem();

	if (_state == "falling") {
		if (_object->frame.GetPosition().y > 0) {
			_object->frame.TranslateLocal({ 0,(float)elapsedSeconds * -_speed,0 });
		}
	}
	else if (_state == "jumping") {
		glm::vec3 pos = _object->frame.GetPosition();
		_object->frame.TranslateLocal({ 0,(float)elapsedSeconds * _speed,0 });
	}
}

void JumpAnimation::CheckInputSystem()
{
	_state = "falling";
	KeyState keyState = _inputSystem->GetKeyState("SPACE");
	if (keyState == KeyState::Pressed) {
		_state = "jumping";
		return;
	}
	
}
