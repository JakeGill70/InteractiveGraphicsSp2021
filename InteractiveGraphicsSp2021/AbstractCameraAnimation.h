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
   virtual void Update(double elapsedSeconds) = 0;

   void SetCamera(BaseCamera* camera);
   BaseCamera* GetCamera();

   void SetInputSystem(AbstractInputSystem* inputSystem);
   AbstractInputSystem* GetInputSystem();

   virtual void CheckInputSystem() {};
};

#endif

