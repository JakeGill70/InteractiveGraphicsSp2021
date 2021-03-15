#pragma once
#ifndef ABSTRACT_GRAPHICS_OBJECT
#define ABSTRACT_GRAPHICS_OBJECT

#include "BaseObject.h"
#include "ReferenceFrame.h"

class AbstractAnimation;

class AbstractGraphicsObject : 
   public BaseObject
{
protected:
   unsigned int _primitive;
   AbstractAnimation* _animation;

public:
   ReferenceFrame frame;

public:
   AbstractGraphicsObject() : _primitive(0), _animation(nullptr) {}
   virtual ~AbstractGraphicsObject() {
       if (_animation) {
           delete _animation;
       }
   }

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
   virtual void Update(double elapsedSeconds);
   virtual void SetAnimation(AbstractAnimation* animation);
};
#endif
