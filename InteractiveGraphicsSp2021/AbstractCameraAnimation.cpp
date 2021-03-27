#include "AbstractCameraAnimation.h"
#include "BaseCamera.h"
#include "AbstractInputSystem.h"

inline void AbstractCameraAnimation::SetCamera(BaseCamera* camera)
{
   _camera = camera;
}

inline BaseCamera* AbstractCameraAnimation::GetCamera()
{
   return _camera;
}

inline void AbstractCameraAnimation::SetInputSystem(AbstractInputSystem* inputSystem)
{
   _inputSystem = inputSystem;
}

inline AbstractInputSystem* AbstractCameraAnimation::GetInputSystem()
{
   return _inputSystem;
}
