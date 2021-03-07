#pragma once
#ifndef ABSTRACT_ANIMATION
#define ABSTRACT_ANIMATION

#include "BaseObject.h"
#include "AbstractGraphicsObject.h"

class AbstractAnimation :
    public BaseObject
{
protected:
   AbstractGraphicsObject* _object;

public:
   AbstractAnimation() : _object(nullptr) {}
   virtual ~AbstractAnimation() {}

   inline void SetObject(AbstractGraphicsObject* object) {
      _object = object;
   }

   virtual void Update(double elapsedSeconds) {}
};

#endif

