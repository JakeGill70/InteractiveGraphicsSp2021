#pragma once
#ifndef OGL_VERTEX_MESH
#define OGL_VERTEX_MESH

#include "AbstractVertexMesh.hpp"

template <class T>
class OGLVertexMesh :
    public AbstractVertexMesh<T>
{
protected:
   GLuint _vboId;
   GLuint _eboId;

   struct VertexAttribute {
      int index;
      int count;
      size_t bytesToNext;
      size_t offsetToFirst;
   } _positionAttribute, _colorAttribute, _textureAttribute;

public:
   OGLVertexMesh() : _vboId(0), _eboId(0) {
      this->_primitive = GL_TRIANGLES;
      this->_positionAttribute = { 0, 3, 0, 0 };
      this->_colorAttribute = { 1, 3, 0, 0 };
      this->_textureAttribute = { 2, 2, 0, 0 };
   }

   void Render() {}

   inline size_t GetBufferId() {
      return this->_vboId;
   }

   inline void SetBufferId(size_t bufferId) {
      this->_vboId = (GLuint)bufferId;
   }

   inline size_t GetIndexedBufferId() {
      return this->_eboId;
   }

   inline void SetIndexedBufferId(size_t bufferId) {
      this->_eboId = (GLuint)bufferId;
   }

   inline void SetPositionAttribute(VertexAttribute pa) {
      this->_positionAttribute = pa;
   }

   inline void SetColorAttribute(VertexAttribute ca) {
      this->_colorAttribute = ca;
   }

   inline void SetTextureAttribute(VertexAttribute ta) {
      this->_textureAttribute = ta;
   }

   void SetupBufferInterpretation();

   void SendToGPU();
};

template <class T>
void OGLVertexMesh<T>::SetupBufferInterpretation()
{
   // Positions
   glEnableVertexAttribArray(this->_positionAttribute.index);
   glVertexAttribPointer(
      this->_positionAttribute.index,
      (GLint)this->_positionAttribute.count,
      GL_FLOAT,
      GL_FALSE,
      (GLsizei)this->_positionAttribute.bytesToNext,
      (void*)this->_positionAttribute.offsetToFirst
   );
   // Colors
   glEnableVertexAttribArray(this->_colorAttribute.index);
   glVertexAttribPointer(
      this->_colorAttribute.index,
      (GLint)this->_colorAttribute.count,
      GL_FLOAT,
      GL_FALSE,
      (GLsizei)this->_colorAttribute.bytesToNext,
      (void*)this->_colorAttribute.offsetToFirst
   );
   // Textures
   glEnableVertexAttribArray(this->_textureAttribute.index);
   glVertexAttribPointer(
      this->_textureAttribute.index,
      (GLint)this->_textureAttribute.count,
      GL_FLOAT,
      GL_FALSE,
      (GLsizei)this->_textureAttribute.bytesToNext,
      (void*)this->_textureAttribute.offsetToFirst
   );
}

template <class T>
void OGLVertexMesh<T>::SendToGPU()
{
   // Bind the object to the binding target
   glBindBuffer(GL_ARRAY_BUFFER, this->_vboId);
   // Allocate memory in the GPU for the buffer bound to the binding target and then
   // copy the data
   glBufferData(GL_ARRAY_BUFFER,
      this->_vertices.size() * sizeof(T),
      &this->_vertices[0],
      GL_STATIC_DRAW);
   if (this->IsIndexed()) {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_eboId);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER,
         this->_indices.size() * sizeof(unsigned short),
         &this->_indices[0],
         GL_STATIC_DRAW);
   }
   if (this->IsTextured()) {
      this->_texture->SendToGPU();
   }
   // Good practice to cleanup by unbinding 
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0);
}

#endif

