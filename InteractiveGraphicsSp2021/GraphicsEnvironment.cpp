#include <Windows.h>
#include "GraphicsEnvironment.h"
#include "TextFileReader.h"
#include "BaseGraphicsScene.h"
#include "OGLGraphicsScene.h"
#include "GraphicsWindow.h"
#include "GraphicsSystem.h"
#include <string>
using std::string;
using std::wstring;

GraphicsEnvironment::GraphicsEnvironment(
   GraphicsWindow* window, GraphicsSystem* graphicsSystem, BaseGraphicsScene* scene)
   : _window(window), _graphicsSystem(graphicsSystem), _scene(scene)
{
}

GraphicsEnvironment::~GraphicsEnvironment()
{
   delete _window;
   delete _graphicsSystem;
   delete _scene;
}

void GraphicsEnvironment::ReportMessage(const string& message) const
{
   // Quick way to convert from string to wstring
   wstring errorString(message.begin(), message.end());
   MessageBox(
      NULL,
      errorString.c_str(),
      L"An Error Occurred",
      MB_OK);
}

void GraphicsEnvironment::Initialize()
{
   _window->Initialize();

   if (!_window->Create()) {
      ReportMessage(_window->GetLog());
      _window->Terminate();
      return;
   }

   if (!_scene->Create()) {
      ReportMessage(_scene->GetLog());
      _window->Terminate();
      return;
   }

   _graphicsSystem->Initialize();
}

void GraphicsEnvironment::Run()
{
   int width, height;
   _window->Show();
   _timer.StartTiming();
   while (!_window->IsTimeToClose()) {
      _window->GetWindowSize(width, height);
      _scene->UpdateCameraProjection(width / (float)height);
      _window->ProcessUserInput();

      _window->Clear();
      _scene->Update(_timer.GetElapsedTimeInSeconds());
      _scene->Render();

      _window->SwapBuffer();
      _window->PollEvents();
   }

   _window->Terminate();
}
