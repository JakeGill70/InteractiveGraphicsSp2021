#pragma once
#ifndef GLFW_GRAPHICS_WINDOW
#define GLFW_GRAPHICS_WINDOW
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "GraphicsWindow.h"

class GLFWGraphicsWindow :
    public GraphicsWindow
{
protected:
   GLFWwindow* _window;

public:
   GLFWGraphicsWindow(int width, int height, const std::string& title);
   void Initialize();
   bool Create();
   void Terminate();
   void Show();
   bool IsTimeToClose();
   void GetWindowSize(int& width, int& height);
   void ProcessUserInput();
   void SwapBuffer();
   void PollEvents();
   void Clear();
};

#endif

