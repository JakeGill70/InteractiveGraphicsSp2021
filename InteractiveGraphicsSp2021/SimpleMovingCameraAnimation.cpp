#include "SimpleMovingCameraAnimation.h"
#include "ReferenceFrame.h"
#include "BaseCamera.h"

SimpleMovingCameraAnimation::SimpleMovingCameraAnimation()
{
   _state = SimpleMovingState::Not_Moving;
   _speed = 20.0f;
}

inline SimpleMovingState SimpleMovingCameraAnimation::GetState()
{
   return _state;
}

inline void SimpleMovingCameraAnimation::SetState(SimpleMovingState state)
{
   _state = state;
}

void SimpleMovingCameraAnimation::Update(float elapsedSeconds)
{
   ReferenceFrame& frame = _camera->frame;
   switch (_state) {
   case SimpleMovingState::Not_Moving:
      break;
   case SimpleMovingState::Moving_Forward: {
      glm::vec3 forward = -frame.GetZAxis(); // Forward is -ve Z
      glm::vec3 moveDelta = forward * (_speed * elapsedSeconds);
      frame.TranslateWorld(moveDelta);
      break;
   }
   case SimpleMovingState::Moving_Backward:
      break;
   case SimpleMovingState::Moving_Left:
      break;
   case SimpleMovingState::Moving_Right:
      break;
   }
}
