#pragma once
#ifndef GLFW_INPUT_SYSTEM
#define GLFW_INPUT_SYSTEM

#include "AbstractInputSystem.h"
#include <GLFW/glfw3.h>

class GLFWInputSystem :
    public AbstractInputSystem
{
protected:
   GLFWwindow* _window;

public:
   GLFWInputSystem(GLFWwindow* window) : _window(window) {}
   KeyState GetKeyState(const std::string& key);
};

#endif

