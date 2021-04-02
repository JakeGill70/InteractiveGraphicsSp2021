#include "SimpleMovingCameraAnimation.h"
#include "ReferenceFrame.h"
#include "BaseCamera.h"
#include "AbstractInputSystem.h"

SimpleMovingCameraAnimation::SimpleMovingCameraAnimation()
{
	_state = SimpleMovingState::Not_Moving;
	_speed = 20.0f;
	_turnSpeed = 180.0f;
}

inline SimpleMovingState SimpleMovingCameraAnimation::GetState()
{
	return _state;
}

inline void SimpleMovingCameraAnimation::SetState(SimpleMovingState state)
{
	_state = state;
}

// Update(double elapsedSeconds)
// ...

void SimpleMovingCameraAnimation::Update(double elapsedSeconds)
{
	CheckInputSystem();
	ReferenceFrame& frame = _camera->frame;
	glm::vec3 moveDelta(1);
	switch (_state) {
	case SimpleMovingState::Not_Moving:
		break;
	case SimpleMovingState::Moving_Forward: {
		glm::vec3 forward = -frame.GetZAxis(); // Forward is -ve Z
		moveDelta = forward * (_speed * (float)elapsedSeconds);
		frame.TranslateWorld(moveDelta);
		break;
	}
	case SimpleMovingState::Moving_Backward: {
		glm::vec3 backward = frame.GetZAxis();
		moveDelta = backward * (_speed * (float)elapsedSeconds);
		frame.TranslateWorld(moveDelta);
		break;
	}
	case SimpleMovingState::Moving_Left:
		glm::vec3 left = -frame.GetXAxis(); // Left is -ve X
		moveDelta = left * (_speed * (float)elapsedSeconds);
		frame.TranslateWorld(moveDelta);
		break;
	case SimpleMovingState::Moving_Right:
		glm::vec3 right = frame.GetXAxis();
		moveDelta = right * (_speed * (float)elapsedSeconds);
		frame.TranslateWorld(moveDelta);
		break;
	case SimpleMovingState::Turning_Left:
		frame.RotateLocal(_turnSpeed * (float)elapsedSeconds, frame.GetYAxis());
		break;
	case SimpleMovingState::Turning_Right:
		frame.RotateLocal(_turnSpeed * -(float)elapsedSeconds, frame.GetYAxis());
		break;
	}
	_camera->SetupLookingForward();
	_camera->UpdateView();
}

void SimpleMovingCameraAnimation::CheckInputSystem()
{
	_state = SimpleMovingState::Not_Moving;
	KeyState keyState = _inputSystem->GetKeyState("W");
	if (keyState == KeyState::Pressed) {
		_state = SimpleMovingState::Moving_Forward;
		return;
	}
	keyState = _inputSystem->GetKeyState("S");
	if (keyState == KeyState::Pressed) {
		_state = SimpleMovingState::Moving_Backward;
		return;
	}
	keyState = _inputSystem->GetKeyState("A");
	if (keyState == KeyState::Pressed) {
		_state = SimpleMovingState::Moving_Left;
		return;
	}
	keyState = _inputSystem->GetKeyState("D");
	if (keyState == KeyState::Pressed) {
		_state = SimpleMovingState::Moving_Right;
		return;
	}
	keyState = _inputSystem->GetKeyState("LEFT");
	if (keyState == KeyState::Pressed) {
		_state = SimpleMovingState::Turning_Left;
		return;
	}
	keyState = _inputSystem->GetKeyState("RIGHT");
	if (keyState == KeyState::Pressed) {
		_state = SimpleMovingState::Turning_Right;
		return;
	}
}
