#include "GLFWInputSystem.h"

KeyState GLFWInputSystem::GetKeyState(const std::string& key)
{
   KeyState keyState = KeyState::Not_Pressed;
   int glfwKey = _keyBindings[key];
   if (glfwGetKey(_window, glfwKey) == GLFW_PRESS) {
      keyState = KeyState::Pressed;
   }
   return keyState;
}
