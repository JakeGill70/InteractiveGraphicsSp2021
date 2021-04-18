#pragma once
#ifndef ABSTRACT_CAMERA_ANIMATION
#define ABSTRACT_CAMERA_ANIMATION

#include "BaseObject.h"
class BaseCamera;
class AbstractInputSystem;
class AbstractKeyBinding;

class AbstractCameraAnimation : public BaseObject
{
protected:
   BaseCamera* _camera;
   AbstractInputSystem* _inputSystem;
   AbstractKeyBinding* _keyBinding;

public:
   AbstractCameraAnimation()
      : _camera(nullptr), _inputSystem(nullptr), _keyBinding(nullptr) {}

   AbstractCameraAnimation(
      BaseCamera* camera, AbstractInputSystem* inputSystem, AbstractKeyBinding* keyBinding)
      : _camera(camera), _inputSystem(inputSystem){
      SetKeyBindings(keyBinding);
   }

   virtual void Update(double elapsedSeconds) = 0;

   void SetCamera(BaseCamera* camera);
   BaseCamera* GetCamera();

   void SetInputSystem(AbstractInputSystem* inputSystem);
   AbstractInputSystem* GetInputSystem();

   virtual void SetKeyBindings(AbstractKeyBinding* keyBinding);
   virtual void CheckInputSystem() {};
};

#endif

