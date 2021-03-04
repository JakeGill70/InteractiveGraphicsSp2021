#pragma once
#ifndef ABSTRACT_GRAPHICS_OBJECT
#define ABSTRACT_GRAPHICS_OBJECT

#include "BaseObject.h"
#include "ReferenceFrame.h"

class AbstractGraphicsObject : 
   public BaseObject
{
protected:
   unsigned int _primitive;

public:
   ReferenceFrame frame;

public:
   AbstractGraphicsObject() : _primitive(0) {}
   virtual ~AbstractGraphicsObject() {}

   virtual inline void SetPrimitive(unsigned int primitive) {
      _primitive = primitive;
   }

   virtual inline unsigned int GetPrimitive() const {
      return _primitive;
   }

   inline virtual bool IsIndexed() const {
      return false;
   }

   virtual void Render() = 0;
   virtual void SendToGPU() = 0;
   virtual size_t GetBufferId() = 0;
   virtual void SetBufferId(size_t bufferId) = 0;
   virtual size_t GetNumberOfElements() = 0;
   virtual size_t GetIndexedBufferId() = 0;
   virtual void SetIndexedBufferId(size_t bufferId) = 0;
};
#endif
