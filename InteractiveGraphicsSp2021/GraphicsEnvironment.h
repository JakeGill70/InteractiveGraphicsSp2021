#pragma once
#ifndef GRAPHICS_ENVIRONMENT
#define GRAPHICS_ENVIRONMENT

#include "BaseObject.h"
#include "HighResolutionTimer.h"

class BaseGraphicsScene;
class GraphicsWindow;
class GraphicsSystem;

class GraphicsEnvironment :
    public BaseObject
{
protected:
   BaseGraphicsScene* _scene;
   HighResolutionTimer _timer;
   GraphicsWindow* _window;
   GraphicsSystem* _graphicsSystem;

public:
   GraphicsEnvironment(GraphicsWindow* window, GraphicsSystem* graphicsSystem, BaseGraphicsScene* scene);
   virtual ~GraphicsEnvironment();
   virtual void ReportMessage(const string& message) const;
   virtual void Initialize();
   virtual void Run();

};

#endif

