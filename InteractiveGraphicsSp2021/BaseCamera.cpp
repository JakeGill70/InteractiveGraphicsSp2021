#include "BaseCamera.h"
#include <glm/gtc/matrix_transform.hpp>

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
