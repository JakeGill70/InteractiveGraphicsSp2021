#pragma once
#ifndef SIMPLE_OGL_RENDERER
#define SIMPLE_OGL_RENDERER

#include "AbstractRenderer.h"
#include <glad/glad.h>

class SimpleOGLRenderer :
    public AbstractRenderer
{
private:
   GLuint _vaoId;
   struct VertexAttribute {
      int index;
      int count;
      size_t bytesToNext;
      size_t offsetToFirst;
   } _positionAttribute, _colorAttribute;

public:
   SimpleOGLRenderer() : AbstractRenderer(), _vaoId(0)
   {
      _positionAttribute = { 0, 3, 0, 0 };
      _colorAttribute = { 1, 3, 0, 0 };
      glGenVertexArrays(1, &_vaoId);
   }

   ~SimpleOGLRenderer(){
      glDeleteVertexArrays(1, &this->_vaoId);
   }

   inline void SetPositionAttribute(VertexAttribute pa) {
      this->_positionAttribute = pa;
   }

   inline void SetColorAttribute(VertexAttribute ca) {
      this->_colorAttribute = ca;
   }

   inline void Select() {
      glBindVertexArray(this->_vaoId);
   }

   size_t GenerateBuffer();

   void Render(AbstractGraphicsObject* object);

private:
   void SetUpBufferInterpretation();

};




#endif

