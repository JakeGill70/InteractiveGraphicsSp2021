#pragma once
#ifndef OGL_GRAPHICS_OBJECT
#define OGL_GRAPHICS_OBJECT

#include "AbstractGraphicsObject.h"
#include "AbstractRenderer.h"

class OGLGraphicsObject :
    public AbstractGraphicsObject
{
private:
   GLuint _vboId;

public:
   OGLGraphicsObject(AbstractRenderer* renderer) : AbstractGraphicsObject(renderer)
   {
      _vboId = (GLuint)renderer->GenerateBuffer();
   }

   inline size_t GetBufferId()
   {
      return _vboId;
   }

   void SendToGPU();
};

#endif

