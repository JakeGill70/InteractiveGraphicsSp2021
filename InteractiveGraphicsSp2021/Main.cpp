#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#include <Windows.h>
#include "GraphicsEnvironment.h"
#include "GLFWGraphicsWindow.h"
#include "SceneReader.h"
#include "TextFileReader.h"
#include "OGLGraphicsScene.h"
#include "OGLGraphicsSystem.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPWSTR    lpCmdLine,
   _In_ int       nCmdShow)
{
   GLFWGraphicsWindow* window = 
      new GLFWGraphicsWindow(800, 600, "Lec Week 13 - Interactive Graphics");

   OGLGraphicsSystem* graphicsSystem = new OGLGraphicsSystem();

   OGLGraphicsScene* scene = 
      new OGLGraphicsScene(
         window,
         new SceneReader("Scene3.txt"), 
         new TextFileReader());

   GraphicsEnvironment environment(window, graphicsSystem, scene);
   environment.Initialize();
   environment.Run();
   return 0;
}