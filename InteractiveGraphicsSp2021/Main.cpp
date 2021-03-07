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

   OGLShader shader;
   shader.Create();
   shader.SetPositionAttribute({ 0,  3, sizeof(VertexPC), 0 });
   shader.SetColorAttribute({ 1, 3, sizeof(VertexPC), sizeof(GLfloat) * 3 });
   OGLGraphicsObject<VertexPC> triangle(&shader);
   triangle.AddVertex({     0,  0.5f, 0, 1, 0, 0 });
   triangle.AddVertex({ -0.5f, -0.5f, 0, 0, 0, 1 });
   triangle.AddVertex({  0.5f, -0.5f, 0, 0, 1, 0 });
   triangle.SendToGPU();


   OGLShader simple3DShader;
   simple3DShader.SetVertexSource(
      "#version 400\n"\
      "layout(location = 0) in vec3 position;\n"\
      "layout(location = 1) in vec3 vertexColor;\n"\
      "out vec4 fragColor;\n"\
      "uniform mat4 world;\n"\
      "uniform mat4 view;\n"\
      "uniform mat4 projection;\n"\
      "void main()\n"\
      "{\n"\
      "   gl_Position = projection * view * world * vec4(position, 1.0);\n"\
      "   fragColor = vec4(vertexColor, 1.0);\n"\
      "}\n"
   );
   simple3DShader.Create();
   simple3DShader.SetPositionAttribute({ 0,  3, sizeof(VertexPC), 0 });
   simple3DShader.SetColorAttribute({ 1, 3, sizeof(VertexPC), sizeof(GLfloat) * 3 });

   OGLGraphicsObject<VertexPC> cube(&simple3DShader);
   // Red vertices
   VertexPC V1 = { -0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f };
   VertexPC V2 = { -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f };
   VertexPC V3 = {  0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f };
   VertexPC V4 = {  0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f };
   // Mixed color vertices
   VertexPC V5 = {  0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f };
   VertexPC V6 = {  0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f };
   VertexPC V7 = { -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f };
   VertexPC V8 = { -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f };
   // Face 1
   cube.AddVertex(V1);
   cube.AddVertex(V2);
   cube.AddVertex(V3);
   cube.AddVertex(V1);
   cube.AddVertex(V3);
   cube.AddVertex(V4);
   // Face 2
   cube.AddVertex(V4);
   cube.AddVertex(V3);
   cube.AddVertex(V6);
   cube.AddVertex(V4);
   cube.AddVertex(V6);
   cube.AddVertex(V5);
   // Face 3
   cube.AddVertex(V5);
   cube.AddVertex(V6);
   cube.AddVertex(V7);
   cube.AddVertex(V5);
   cube.AddVertex(V7);
   cube.AddVertex(V8);
   // Face 4
   cube.AddVertex(V8);
   cube.AddVertex(V7);
   cube.AddVertex(V2);
   cube.AddVertex(V8);
   cube.AddVertex(V2);
   cube.AddVertex(V1);
   // Face 5
   cube.AddVertex(V6);
   cube.AddVertex(V3);
   cube.AddVertex(V2);
   cube.AddVertex(V6);
   cube.AddVertex(V2);
   cube.AddVertex(V7);
   // Face 6
   cube.AddVertex(V8);
   cube.AddVertex(V1);
   cube.AddVertex(V4);
   cube.AddVertex(V8);
   cube.AddVertex(V4);
   cube.AddVertex(V5);
   cube.SendToGPU();

   BaseCamera camera;
   camera.frame.SetPosition(3, 3, 3);
   camera.UpdateView();

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
      camera.UpdateProjection(width / (float)height);

      simple3DShader.SelectProgram();
      simple3DShader.SendMatrixToGPU("view", camera.GetView());
      simple3DShader.SendMatrixToGPU("projection", camera.GetProjection());

      ProcessUserInput(window);

      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

      triangle.Render();

      cube.frame.orientation = glm::rotate(cube.frame.orientation, glm::radians(1.0f), glm::vec3( 0, 1, 0 ));
      simple3DShader.SelectProgram();
      simple3DShader.SendMatrixToGPU("world", cube.frame.orientation);
      cube.Render();

      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   glfwTerminate();
   return 0;
}