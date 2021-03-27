#include "BaseCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "AbstractCameraAnimation.h"

inline void BaseCamera::SetAnimation(AbstractCameraAnimation* animation)
{
   _animation = animation;
   _animation->SetCamera(this);
}

inline AbstractCameraAnimation* BaseCamera::GetAnimation()
{
   return _animation;
}

void BaseCamera::Update(float elapsedSeconds, float aspectRatio)
{
   UpdateProjection(aspectRatio);
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
