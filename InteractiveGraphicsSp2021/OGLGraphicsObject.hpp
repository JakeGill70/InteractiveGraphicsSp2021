#pragma once
#ifndef OGL_GRAPHICS_OBJECT
#define OGL_GRAPHICS_OBJECT

#include "AbstractVertexGraphicsObject.hpp"
#include "AbstractRenderer.h"

template <class T>
class OGLGraphicsObject :
    public AbstractVertexGraphicsObject<T>
{
private:
   GLuint _vboId;

public:
   OGLGraphicsObject(AbstractRenderer* renderer);

   inline size_t GetBufferId() {
      return this->_vboId;
   }

   void SendToGPU();
};

template<class T>
OGLGraphicsObject<T>::OGLGraphicsObject(AbstractRenderer* renderer) : AbstractVertexGraphicsObject<T>(renderer)
{
   this->_vboId = (GLuint)this->_renderer->GenerateBuffer();
}

template <class T>
void OGLGraphicsObject<T>::SendToGPU()
{
   this->_renderer->Select();
   // Bind the object to the binding target
   glBindBuffer(GL_ARRAY_BUFFER, _vboId);
   // Allocate memory in the GPU for the buffer bound to the binding target and then
   // copy the data
   glBufferData(GL_ARRAY_BUFFER, this->_vertices.size() * sizeof(T), &this->_vertices[0], GL_STATIC_DRAW);

   // Good practice to cleanup by unbinding 
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0);
}

#endif

