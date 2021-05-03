#pragma once
#ifndef BASE_CAMERA
#define BASE_CAMERA

#include "BaseObject.h"
#include <glm\glm.hpp>
#include "ReferenceFrame.h"
#include "ViewingFrustum.h"

class AbstractCameraAnimation;

class BaseCamera :
    public BaseObject
{
protected:
   glm::mat4 _projection, _view;
   float _aspectRatio;
   AbstractCameraAnimation* _animation;

public:
   float fieldOfView, nearPlane, farPlane;
   ReferenceFrame frame;
   glm::vec3 target;
   ViewingFrustum* viewingFrustrum;

public:
   BaseCamera() : 
      _projection(1.0f), _view(1.0f), _aspectRatio(1.0f), fieldOfView(60.0f),
      nearPlane(0.1f), farPlane(50.0f),
      target({ 0.0f, 0.0f, 0.0f }),
      frame(), _animation(nullptr)
   {
       viewingFrustrum = new ViewingFrustum(1, 1, 3, 3, 3);
   }

   inline void SetAspectRatio(float aspectRatio) {
      _aspectRatio = aspectRatio;
   }

   void SetAnimation(AbstractCameraAnimation* animation);
   AbstractCameraAnimation* GetAnimation();

   virtual inline const glm::mat4& GetProjection() const { return _projection; }
   virtual inline const glm::mat4& GetView() const { return _view; }

   virtual void Update(double elapsedSeconds);
   virtual void UpdateProjection(float aspectRatio);
   virtual void UpdateView();

   virtual void SetupLookingForward();

   virtual void SetupViewingFrustum(float depth);
   virtual void OrientViewingFrustum();
};

#endif

