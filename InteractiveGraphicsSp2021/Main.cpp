#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#include <Windows.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include "GraphicsStructures.h"
#include "OGLGraphicsObject.h"
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



void SetUpScene(Vertex vertexData[])
{
   vertexData[0].position.x = 0.0f;
   vertexData[0].position.y = 0.5f;
   vertexData[0].position.z = 0.0f;
   vertexData[0].color.red = 1.0f;
   vertexData[0].color.green = 0.0f;
   vertexData[0].color.blue = 0.0f;

   vertexData[1].position.x = -0.5f;
   vertexData[1].position.y = -0.5f;
   vertexData[1].position.z = 0.0f;
   vertexData[1].color.red = 0.0f;
   vertexData[1].color.green = 0.0f;
   vertexData[1].color.blue = 1.0f;

   vertexData[2].position.x = 0.5f;
   vertexData[2].position.y = -0.5f;
   vertexData[2].position.z = 0.0f;
   vertexData[2].color.red = 0.0f;
   vertexData[2].color.green = 1.0f;
   vertexData[2].color.blue = 0.0f;
}

GLuint CreateVBO(GLenum target, const void* bufferData, GLsizei bufferSize)
{
   GLuint vboHandle = 0;
   // Declare the buffer object and store a handle to the object
   glGenBuffers(1, &vboHandle);
   // Bind the object to the binding target
   glBindBuffer(target, vboHandle);
   // Allocate memory in the GPU for the buffer bound to the binding target and then
   // copy the data
   glBufferData(target, bufferSize, bufferData, GL_STATIC_DRAW);
   // Good practice to cleanup by unbinding 
   glBindBuffer(target, 0);
   return vboHandle;
}

void SendSceneDataToGPU(GLuint& vaoId, GLuint& vboId, Vertex triangleVertexData[], GLuint sizeInBytes)
{
   glGenVertexArrays(1, &vaoId);
   glBindVertexArray(vaoId);

   vboId = CreateVBO(
      GL_ARRAY_BUFFER, triangleVertexData, sizeInBytes);

   glBindVertexArray(0);
}

void ProcessUserInput(GLFWwindow* window)
{
   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
   }
}

void RenderScene(GLuint vaoId, GLuint vboId, GLuint shaderProgram)
{
   glBindVertexArray(vaoId);
   glUseProgram(shaderProgram);

   glBindBuffer(GL_ARRAY_BUFFER, vboId);
   // Positions
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(
      0,
      3,              // Each position has 3 components
      GL_FLOAT,       // Each component is a 32-bit floating point value
      GL_FALSE,
      sizeof(Vertex), // The number of bytes to the next position
      (void*)0        // Byte offset of the first position in the array
   );
   // Colors
   glEnableVertexAttribArray(1);
   glVertexAttribPointer(
      1,
      3,                           // Each color has 3 components
      GL_FLOAT,                    // Each component is a 32-bit floating point value
      GL_FALSE,
      sizeof(Vertex),              // The number of bytes to the next color
      (void*)(sizeof(GLfloat) * 3) // Byte offset of the first color in the array
   );
   glDrawArrays(GL_TRIANGLES, 0, 3);

   glDisableVertexAttribArray(0);
   glDisableVertexAttribArray(1);
   glUseProgram(0);
   glBindVertexArray(0);
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
   simpleRenderer.SetPositionAttribute({ 3, sizeof(Vertex), 0 });
   simpleRenderer.SetColorAttribute({ 3, sizeof(Vertex), sizeof(GLfloat) * 3 });
   OGLGraphicsObject triangle(&simpleRenderer);
   triangle.AddVertex({     0,  0.5f, 0, 1, 0, 0 });
   triangle.AddVertex({ -0.5f, -0.5f, 0, 0, 0, 1 });
   triangle.AddVertex({  0.5f, -0.5f, 0, 0, 1, 0 });
   triangle.SendToGPU();

   //Vertex triangleVertexData[3];
   //SetUpScene(triangleVertexData);

   //GLuint vaoId, vboId;
   //SendSceneDataToGPU(vaoId, vboId, triangleVertexData, sizeof(triangleVertexData));

   //glfwMaximizeWindow(window);
   glfwShowWindow(window);
   while (!glfwWindowShouldClose(window)) {
      ProcessUserInput(window);

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
      ///RenderScene(vaoId, vboId, shaderProgram);
      triangle.Render();

      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   //glDeleteVertexArrays(1, &vaoId);
   glfwTerminate();
   return 0;
}