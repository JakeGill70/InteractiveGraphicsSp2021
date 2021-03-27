#pragma once
#ifndef ABSTRACT_CAMERA_ANIMATION
#define ABSTRACT_CAMERA_ANIMATION

#include "BaseObject.h"
class BaseCamera;
class AbstractInputSystem;

class AbstractCameraAnimation : public BaseObject
{
protected:
   BaseCamera* _camera;
   AbstractInputSystem* _inputSystem;

public:
   virtual void Update(float elapsedSeconds) = 0;

   inline void SetCamera(BaseCamera* camera);
   inline BaseCamera* GetCamera();

   inline void SetInputSystem(AbstractInputSystem* inputSystem);
   inline AbstractInputSystem* GetInputSystem();
};

#endif

