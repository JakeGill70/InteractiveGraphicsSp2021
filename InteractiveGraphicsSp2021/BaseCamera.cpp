#include "BaseCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "AbstractCameraAnimation.h"

void BaseCamera::SetAnimation(AbstractCameraAnimation* animation)
{
   _animation = animation;
   _animation->SetCamera(this);
}

AbstractCameraAnimation* BaseCamera::GetAnimation()
{
   return _animation;
}

void BaseCamera::Update(double elapsedSeconds)
{
   if (_animation) _animation->Update(elapsedSeconds);
}

void BaseCamera::UpdateProjection(float aspectRatio)
{
   _aspectRatio = aspectRatio;
   _projection = glm::perspective(
      glm::radians(fieldOfView),
      _aspectRatio,
      nearPlane,
      farPlane
   );
}

void BaseCamera::UpdateView()
{
   glm::vec3 position = frame.GetPosition();
   _view = glm::lookAt(
      position,
      target,
      frame.GetYAxis()
   );
}

void BaseCamera::SetupLookingForward()
{
   glm::vec3 position = frame.GetPosition();
   glm::vec3 forward = frame.orientation[2];
   forward = -forward;
   target = position + forward;
}
