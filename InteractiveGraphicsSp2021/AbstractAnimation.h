#pragma once
#ifndef ABSTRACT_ANIMATION
#define ABSTRACT_ANIMATION

#include "BaseObject.h"
class AbstractGraphicsObject;

class AbstractAnimation :
    public BaseObject
{
protected:
   AbstractGraphicsObject* _object;

public:
   AbstractAnimation() : _object(nullptr) {}
   virtual ~AbstractAnimation() {}

   void SetObject(AbstractGraphicsObject* object);

   virtual void Update(double elapsedSeconds) {}
};

#endif

