#pragma once
#ifndef GRAPHICS_WINDOW
#define GRAPHICS_WINDOW

#include "BaseObject.h"
#include <string>

enum class WindowShowState {
   Normal, Maximized
};

class GraphicsWindow : public BaseObject
{
protected:
   int _width, _height;
   std::string _title;
   WindowShowState _showState;

public:
   GraphicsWindow(int width, int height, const std::string& title);

   inline void SetShowState(WindowShowState showState) {
      _showState = showState;
   }

   virtual void Initialize() = 0;
   virtual bool Create() = 0;
   virtual void Terminate() = 0;
   virtual void Show() = 0;
   virtual bool IsTimeToClose() = 0;
   virtual void GetWindowSize(int& width, int& height) = 0;
   virtual void ProcessUserInput() = 0;
   virtual void SwapBuffer() = 0;
   virtual void PollEvents() = 0;
   virtual void Clear() = 0;
};

#endif

