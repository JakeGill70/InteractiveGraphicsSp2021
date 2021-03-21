#pragma once
#ifndef ABSTRACT_VERTEX_GRAPHICS_OBJECT
#define ABSTRACT_VERTEX_GRAPHICS_OBJECT

#include "AbstractMesh.h"
#include <vector>
using std::vector;
#include "GraphicsStructures.h"

template <class T>
class AbstractVertexMesh :
   public AbstractMesh
{
protected:
   vector<T> _vertices;
   vector<unsigned short> _indices;

public:
   AbstractVertexMesh() {}

   virtual ~AbstractVertexMesh() {}

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

   T& GetVertex(int index) {
      return _vertices[index];
   }

   virtual void Render() = 0;
};

template<class T>
void AbstractVertexMesh<T>::AddVertexData(const T& vertex)
{
   this->_vertices.push_back(vertex);
}

template <class T>
void AbstractVertexMesh<T>::SetIndices(unsigned short indices[], int count)
{
   for (int i = 0; i < count; i++) {
      this->_indices.push_back(indices[i]);
   }
}

#endif

