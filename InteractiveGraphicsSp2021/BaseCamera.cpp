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

void BaseCamera::SetupViewingFrustum(float depth) {
    float fov_radians = this->fieldOfView * 0.0174533f; // Magic number ~= PI/180, used to 

    float frontHeight = tan(fov_radians / 2) * nearPlane * 2;
    float backHeight = tan(fov_radians / 2) * depth * 2;
    float frontWidth = _aspectRatio * frontHeight;
    float backWidth = _aspectRatio * backHeight;

    viewingFrustrum->Set(frontWidth, frontHeight, backWidth, backHeight, depth);
}

void BaseCamera::OrientViewingFrustum() {
    viewingFrustrum->frame = frame;
    viewingFrustrum->frame.RotateLocal(180, { 0,1,0 });
    viewingFrustrum->Create();
}
