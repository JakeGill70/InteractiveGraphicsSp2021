#pragma once
#ifndef ABSTRACT_RENDERER
#define ABSTRACT_RENDERER

#include "BaseObject.h"

class AbstractGraphicsObject;

class AbstractShader :
   public BaseObject
{
protected:
   unsigned int _shaderProgram;

public:
   AbstractShader() : _shaderProgram(0) {}
   ~AbstractShader() {}

   inline void SetShaderProgram(unsigned int shaderProgram){
      _shaderProgram = shaderProgram;
   }

   virtual inline void Select() = 0;
   virtual void Render(AbstractGraphicsObject* object) = 0;
   virtual size_t GenerateBuffer() = 0;
   virtual bool Create() = 0;

 private:
   virtual void SetUpBufferInterpretation() = 0;
};

#endif

