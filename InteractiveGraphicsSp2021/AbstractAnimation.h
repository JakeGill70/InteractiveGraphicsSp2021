#pragma once
#ifndef ABSTRACT_ANIMATION
#define ABSTRACT_ANIMATION

#include "BaseObject.h"
class GraphicsObject;

class AbstractAnimation :
    public BaseObject
{
protected:
   GraphicsObject* _object;

public:
   AbstractAnimation() : _object(nullptr) {}
   virtual ~AbstractAnimation() {}

   void SetObject(GraphicsObject* object);

   virtual void Update(double elapsedSeconds) {}
};

#endif

