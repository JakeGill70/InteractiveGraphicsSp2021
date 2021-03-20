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
   } _positionAttribute, _colorAttribute, _textureAttribute, _normalAttribute;

public:
   OGLVertexMesh() : _vboId(0), _eboId(0) {
      this->_primitive = GL_TRIANGLES;
      this->_positionAttribute = { 0, 3, 0, 0 };
      this->_colorAttribute = { 1, 3, 0, 0 };
      this->_textureAttribute = { 2, 2, 0, 0 };
      this->_normalAttribute = { 0, 0, 0, 0 };
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
      this->_hasPosition = true;
   }

   inline void SetColorAttribute(VertexAttribute ca) {
      this->_colorAttribute = ca;
      this->_hasColor = true;
   }

   inline void SetTextureAttribute(VertexAttribute ta) {
      this->_textureAttribute = ta;
      this->_hasTexture = true;
   }

   inline void SetNormalAttribute(VertexAttribute na) {
      this->_normalAttribute = na;
      this->_hasNormal = true;
   }

   void SetUpBufferInterpretation();

   void SendToGPU();

protected:
   void SetUpBufferInterpretation(const VertexAttribute& attr);
};

template <class T>
void OGLVertexMesh<T>::SetUpBufferInterpretation()
{
   if (this->_hasPosition) this->SetUpBufferInterpretation(this->_positionAttribute);
   if (this->_hasColor) this->SetUpBufferInterpretation(this->_colorAttribute);
   if (this->_hasTexture) this->SetUpBufferInterpretation(this->_textureAttribute);
   if (this->_hasNormal) this->SetUpBufferInterpretation(this->_normalAttribute);
}

template <class T>
void OGLVertexMesh<T>::SetUpBufferInterpretation(const VertexAttribute& attr)
{
   glEnableVertexAttribArray(attr.index);
   glVertexAttribPointer(
      attr.index,
      (GLint)attr.count,
      GL_FLOAT,
      GL_FALSE,
      (GLsizei)attr.bytesToNext,
      (void*)attr.offsetToFirst
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

