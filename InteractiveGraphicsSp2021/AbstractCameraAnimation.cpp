#include "AbstractCameraAnimation.h"
#include "BaseCamera.h"
#include "AbstractInputSystem.h"
#include "AbstractKeyBinding.h"

void AbstractCameraAnimation::SetCamera(BaseCamera* camera)
{
   _camera = camera;
}

BaseCamera* AbstractCameraAnimation::GetCamera()
{
   return _camera;
}

void AbstractCameraAnimation::SetInputSystem(AbstractInputSystem* inputSystem)
{
   _inputSystem = inputSystem;
}

AbstractInputSystem* AbstractCameraAnimation::GetInputSystem()
{
   return _inputSystem;
}

void AbstractCameraAnimation::SetKeyBindings(AbstractKeyBinding* keyBinding)
{
   _keyBinding = keyBinding;
   _keyBinding->SetBindings();
}

