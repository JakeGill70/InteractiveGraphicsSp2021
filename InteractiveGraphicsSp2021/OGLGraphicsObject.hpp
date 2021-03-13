#pragma once
#ifndef OGL_GRAPHICS_OBJECT
#define OGL_GRAPHICS_OBJECT

#include "AbstractVertexGraphicsObject.hpp"
#include "AbstractShader.h"

template <class T>
class OGLGraphicsObject :
    public AbstractVertexGraphicsObject<T>
{
protected:
   GLuint _vboId;
   GLuint _eboId;

public:
   OGLGraphicsObject();

   inline size_t GetBufferId() {
      return this->_vboId;
   }

   void SetBufferId(size_t bufferId) {
      this->_vboId = (GLuint)bufferId;
   }

   inline size_t GetIndexedBufferId() {
      return this->_eboId;
   }

   inline void SetIndexedBufferId(size_t bufferId) {
      this->_eboId = (GLuint)bufferId;
   }

   void SendToGPU();
};

template<class T>
OGLGraphicsObject<T>::OGLGraphicsObject() : _vboId(0), _eboId(0)
{
   this->_primitive = GL_TRIANGLES;
}

template <class T>
void OGLGraphicsObject<T>::SendToGPU()
{
   // Bind the object to the binding target
   glBindBuffer(GL_ARRAY_BUFFER, _vboId);
   // Allocate memory in the GPU for the buffer bound to the binding target and then
   // copy the data
   glBufferData(GL_ARRAY_BUFFER, 
      this->_vertices.size() * sizeof(T), 
      &this->_vertices[0], 
      GL_STATIC_DRAW);

   if (this->IsIndexed()) {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _eboId);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER,
         this->_indices.size() * sizeof(unsigned short),
         &this->_indices[0],
         GL_STATIC_DRAW);
      
   }
   // Good practice to cleanup by unbinding 
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0);
}

#endif

