#pragma once
#ifndef ABSTRACT_GRAPHICS_OBJECT
#define ABSTRACT_GRAPHICS_OBJECT

#include "BaseObject.h"
#include "ReferenceFrame.h"

class AbstractGraphicsObject : 
   public BaseObject
{
public:
   ReferenceFrame frame;

public:
   AbstractGraphicsObject() {}
   virtual ~AbstractGraphicsObject() {}

   virtual void Render() = 0;
   virtual void SendToGPU() = 0;
   virtual size_t GetBufferId() = 0;
   virtual size_t GetNumberOfElements() = 0;
};
#endif
