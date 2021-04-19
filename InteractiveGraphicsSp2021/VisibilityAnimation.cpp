#include "VisibilityAnimation.h"

#include "ReferenceFrame.h"
#include "AbstractInputSystem.h"
#include "GraphicsObject.h"

VisibilityAnimation::VisibilityAnimation(AbstractInputSystem* inputSystem) {
	_isShowing = false;
    _inputSystem = inputSystem;
}

void VisibilityAnimation::Update(double elapsedSeconds)
{
    CheckInputSystem();
    _object->isVisible = _isShowing;
}

void VisibilityAnimation::CheckInputSystem()
{
    KeyState keyState = _inputSystem->GetKeyState("1");
    if (keyState == KeyState::Pressed) {
        _isShowing = !_isShowing;
    }
}