#pragma once
#ifndef GLFW_KEY_BINDINGS
#define GLFW_KEY_BINDINGS

#include "AbstractKeyBinding.h"
#include <GLFW/glfw3.h>

class GLFWKeyBinding : public AbstractKeyBinding
{
public:
   GLFWKeyBinding(AbstractInputSystem* inputSystem)
      : AbstractKeyBinding(inputSystem) {}

   void SetBindings() {
      _inputSystem->RegisterKey("W", GLFW_KEY_W);
      _inputSystem->RegisterKey("S", GLFW_KEY_S);
      _inputSystem->RegisterKey("A", GLFW_KEY_A);
      _inputSystem->RegisterKey("D", GLFW_KEY_D);
      _inputSystem->RegisterKey("LEFT", GLFW_KEY_LEFT);
      _inputSystem->RegisterKey("RIGHT", GLFW_KEY_RIGHT);
   }
};

#endif