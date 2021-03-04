#pragma once
#ifndef ABSTRACT_VERTEX_GRAPHICS_OBJECT
#define ABSTRACT_VERTEX_GRAPHICS_OBJECT

#include "AbstractGraphicsObject.h"
#include <vector>
using std::vector;
#include "GraphicsStructures.h"


template <class T>
class AbstractVertexGraphicsObject :
   public AbstractGraphicsObject
{
protected:
   vector<T> _vertices;
   vector<unsigned short> _indices;

public:
   AbstractVertexGraphicsObject() {}

   virtual ~AbstractVertexGraphicsObject() {}

   void AddVertexData(const T& vertex);

   void AddIndex(unsigned int index) {
      this->_indices.push_back(index);
   }

   void SetIndices(unsigned short indices[], int count);

   inline bool IsIndexed() const {
      return this->_indices.size() > 0;
   }

   size_t GetNumberOfElements() {
      size_t numberOfElements = this->_vertices.size();
      if (IsIndexed()) numberOfElements = this->_indices.size();
      return numberOfElements;
   }

   virtual void Render();
};

template<class T>
void AbstractVertexGraphicsObject<T>::AddVertexData(const T& vertex)
{
   this->_vertices.push_back(vertex);
}

template <class T>
void AbstractVertexGraphicsObject<T>::Render()
{
   //this->_shader->Render(this);
}

template <class T>
void AbstractVertexGraphicsObject<T>::SetIndices(unsigned short indices[], int count)
{
   for (int i = 0; i < count; i++) {
      this->_indices.push_back(indices[i]);
   }
}

#endif

