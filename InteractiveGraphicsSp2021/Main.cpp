#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#include <Windows.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include "GraphicsStructures.h"
#include "OGLGraphicsObject.hpp"
#include "OGLShader.h"

void OnWindowResize_Callback(GLFWwindow* window, int width, int height)
{
   glViewport(0, 0, width, height);
}

void ProcessUserInput(GLFWwindow* window)
{
   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
   }
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPWSTR    lpCmdLine,
   _In_ int       nCmdShow)
{
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   GLFWwindow* window = glfwCreateWindow(800, 600, "ETSU Computing Interactive Graphics", NULL, NULL);
   if (window == NULL) {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return -1;
   }
   glfwMakeContextCurrent(window);

   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to initialize GLAD" << std::endl;
      return -1;
   }

   glfwSetFramebufferSizeCallback(window, OnWindowResize_Callback);

   OGLShader shader;
   shader.Create();
   shader.SetPositionAttribute({ 0,  3, sizeof(VertexPC), 0 });
   shader.SetColorAttribute({ 1, 3, sizeof(VertexPC), sizeof(GLfloat) * 3 });
   OGLGraphicsObject<VertexPC> triangle(&shader);
   triangle.AddVertex({     0,  0.5f, 0, 1, 0, 0 });
   triangle.AddVertex({ -0.5f, -0.5f, 0, 0, 0, 1 });
   triangle.AddVertex({  0.5f, -0.5f, 0, 0, 1, 0 });
   triangle.SendToGPU();

   //glfwMaximizeWindow(window);
   glfwShowWindow(window);
   while (!glfwWindowShouldClose(window)) {
      ProcessUserInput(window);

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
      triangle.Render();

      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   glfwTerminate();
   return 0;
}