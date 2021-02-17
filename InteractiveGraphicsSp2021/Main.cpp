#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#include <Windows.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include "GraphicsStructures.h"
#include "OGLGraphicsObject.hpp"
#include "SimpleOGLRenderer.h"

void OnWindowResize_Callback(GLFWwindow* window, int width, int height)
{
   glViewport(0, 0, width, height);
}

GLuint CompileShader(GLenum type, const GLchar* source)
{
   GLint length = (GLint)(sizeof(GLchar) * strlen(source));
   GLuint shader = glCreateShader(type);
   glShaderSource(shader, 1, (const GLchar**)&source, &length);
   glCompileShader(shader);
   GLint shaderOk = 0;
   glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderOk);
   if (!shaderOk) {
      glDeleteShader(shader);
      shader = 0;
   }
   return shader;
}

GLuint LinkShader(GLuint vertexShader, GLuint fragmentShader)
{
   GLuint program = glCreateProgram();
   glAttachShader(program, vertexShader);
   glAttachShader(program, fragmentShader);
   glLinkProgram(program);
   GLint programOk = 0;
   glGetProgramiv(program, GL_LINK_STATUS, &programOk);
   if (!programOk) {
      glDeleteShader(program);
      program = 0;
   }
   return program;
}

bool CreateShaderProgram(GLuint& shaderProgram)
{
   const GLchar* vertexSource =
      "#version 400\n"\
      "layout(location = 0) in vec3 position;\n"\
      "layout(location = 1) in vec3 vertexColor;\n"\
      "out vec4 fragColor;\n"\
      "void main()\n"\
      "{\n"\
      "   gl_Position = vec4(position, 1.0);\n" \
      "   fragColor = vec4(vertexColor, 1.0);\n" \
      "}\n";
   GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
   if (vertexShader == 0) return false;

   const GLchar* fragmentSource =
      "#version 400\n"\
      "in vec4 fragColor;\n"\
      "out vec4 color;\n"\
      "void main()\n"\
      "{\n"\
      "   color = fragColor;\n"\
      "}\n";
   GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
   if (fragmentShader == 0) return false;

   shaderProgram = LinkShader(vertexShader, fragmentShader);
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);
   return true;
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

   GLuint shaderProgram;
   bool isCreated = CreateShaderProgram(shaderProgram);
   if (!isCreated) {
      std::cout << "Failed to create the shader program" << std::endl;
      return -1;
   }

   SimpleOGLRenderer simpleRenderer;
   simpleRenderer.SetShaderProgram(shaderProgram);
   simpleRenderer.SetPositionAttribute({ 0,  3, sizeof(VertexPC), 0 });
   simpleRenderer.SetColorAttribute({ 1, 3, sizeof(VertexPC), sizeof(GLfloat) * 3 });
   OGLGraphicsObject<VertexPC> triangle(&simpleRenderer);
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