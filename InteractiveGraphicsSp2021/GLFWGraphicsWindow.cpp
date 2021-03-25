
#include "GLFWGraphicsWindow.h"

void OnWindowResize_Callback(GLFWwindow* window, int width, int height)
{
   glViewport(0, 0, width, height);
}

GLFWGraphicsWindow::GLFWGraphicsWindow(int width, int height, const std::string& title)
   : GraphicsWindow(width, height, title), _window(nullptr)
{
}

void GLFWGraphicsWindow::Initialize()
{
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

bool GLFWGraphicsWindow::Create()
{
   _window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
   if (_window == nullptr) {
      _log << "Failed to create GLFW window" << std::endl;
      return false;
   }

   glfwMakeContextCurrent(_window);

   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      _log << "Failed to initialize GLAD" << std::endl;
      return false;
   }

   glfwSetFramebufferSizeCallback(_window, OnWindowResize_Callback);
   return true;
}

void GLFWGraphicsWindow::Terminate()
{
   glfwTerminate();
}

void GLFWGraphicsWindow::Show()
{
   switch (_showState) {
   case WindowShowState::Normal:
      glfwShowWindow(_window);
      break;
   case WindowShowState::Maximized:
      glfwMaximizeWindow(_window);
      break;
   default:
      glfwShowWindow(_window);
      break;
   }
}

bool GLFWGraphicsWindow::IsTimeToClose()
{
   return glfwWindowShouldClose(_window);
}

void GLFWGraphicsWindow::GetWindowSize(int& width, int& height)
{
   glfwGetWindowSize(_window, &width, &height);
}

void GLFWGraphicsWindow::ProcessUserInput()
{
   if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(_window, true);
   }
}

void GLFWGraphicsWindow::SwapBuffer()
{
   glfwSwapBuffers(_window);
}

void GLFWGraphicsWindow::PollEvents()
{
   glfwPollEvents();
}

void GLFWGraphicsWindow::Clear()
{
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
