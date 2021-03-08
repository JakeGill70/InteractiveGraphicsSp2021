#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#include <Windows.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include "GraphicsStructures.h"
#include "OGLGraphicsObject.hpp"
#include "OGLShader.h"
#include "BaseCamera.h"
#include "ReferenceFrame.h"
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "OGLGraphicsScene.h"

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

void ReportMessage(const string& message)
{
    // Quick way to convert from string to wstring
    std::wstring errorString(message.begin(), message.end());
    MessageBox(
        NULL,
        errorString.c_str(),
        L"An Error Occurred",
        MB_OK);
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

   GLFWwindow* window = glfwCreateWindow(800, 600, "Lab Week 7 - Interactive Graphics", NULL, NULL);
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

   auto textFileReader = new TextFileReader();
   OGLGraphicsScene scene;
   scene.SetTextFileReader(textFileReader);
   auto created = scene.Create();
   if (!created) {
       ReportMessage(scene.GetLog());
       glfwTerminate();
       return 0;
   }

   // Cull back faces and use counter-clockwise winding of front faces
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);
   glFrontFace(GL_CCW);

   // Enable depth testing
   //glEnable(GL_DEPTH_TEST);
   //glDepthMask(GL_TRUE);
   //glDepthFunc(GL_LEQUAL);
   //glDepthRange(0.0f, 1.0f);

   int width, height;
   glfwShowWindow(window);
   //glfwMaximizeWindow(window);
   while (!glfwWindowShouldClose(window)) {
      glfwGetWindowSize(window, &width, &height);
      scene.UpdateCameraProjection(width / (float)height);

      ProcessUserInput(window);

      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

      scene.Render();

      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   glfwTerminate();
   return 0;
}