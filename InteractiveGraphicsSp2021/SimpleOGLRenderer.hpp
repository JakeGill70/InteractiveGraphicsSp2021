#pragma once
#ifndef SIMPLE_OGL_RENDERER
#define SIMPLE_OGL_RENDERER

#include "AbstractRenderer.hpp"
#include <glad/glad.h>

template <class T>
class SimpleOGLRenderer :
    public AbstractRenderer<T>
{
private:
   GLuint _vaoId;
   struct VertexAttribute {
      int count;
      size_t bytesToNext;
      size_t offsetToFirst;
   } _positionAttribute, _colorAttribute;

public:
   SimpleOGLRenderer();

   ~SimpleOGLRenderer();

   void SetPositionAttribute(VertexAttribute pa);

   void SetColorAttribute(VertexAttribute ca);

   void Select();

   size_t GenerateBuffer();

   void Render(AbstractGraphicsObject<T>* object);

};

template <class T>
SimpleOGLRenderer<T>::SimpleOGLRenderer() : AbstractRenderer<T>(), _vaoId(0)
{
   _positionAttribute = { 3, 0, 0 };
   _colorAttribute = { 3, 0, 0 };
   glGenVertexArrays(1, &_vaoId);
}

template <class T>
SimpleOGLRenderer<T>::~SimpleOGLRenderer()
{
   glDeleteVertexArrays(1, &this->_vaoId);
}

template <class T>
void SimpleOGLRenderer<T>::SetPositionAttribute(VertexAttribute pa) {
   this->_positionAttribute = pa;
}

template <class T>
void SimpleOGLRenderer<T>::SetColorAttribute(VertexAttribute ca) {
   this->_colorAttribute = ca;
}

template <class T>
void SimpleOGLRenderer<T>::Select()
{
   glBindVertexArray(this->_vaoId);
}

template <class T>
size_t SimpleOGLRenderer<T>::GenerateBuffer()
{
   glBindVertexArray(this->_vaoId);
   GLuint vbo;
   glGenBuffers(1, &vbo);
   return vbo;
}

template <class T>
void SimpleOGLRenderer<T>::Render(AbstractGraphicsObject<T>* object)
{
   glBindVertexArray(_vaoId);
   glUseProgram((GLuint)this->_shaderProgram);
   glBindBuffer(GL_ARRAY_BUFFER, (GLuint)object->GetBufferId());
   // Positions
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(
      0,
      (GLint)_positionAttribute.count,
      GL_FLOAT,
      GL_FALSE,
      (GLsizei)_positionAttribute.bytesToNext,
      (void*)_positionAttribute.offsetToFirst
   );
   // Colors
   glEnableVertexAttribArray(1);
   glVertexAttribPointer(
      1,
      (GLint)_colorAttribute.count,
      GL_FLOAT,
      GL_FALSE,
      (GLsizei)_colorAttribute.bytesToNext,
      (void*)_colorAttribute.offsetToFirst
   );

   glDrawArrays(GL_TRIANGLES, 0, (GLsizei)object->GetNumberOfVertices());

   glDisableVertexAttribArray(0);
   glDisableVertexAttribArray(1);
   glUseProgram(0);
   glBindVertexArray(0);
}

#endif

