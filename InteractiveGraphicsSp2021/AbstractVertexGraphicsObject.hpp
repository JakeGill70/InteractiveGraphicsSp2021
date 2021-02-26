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

public:
   AbstractVertexGraphicsObject() {}

   virtual ~AbstractVertexGraphicsObject() {}

   void AddVertex(const T& vertex);

   inline size_t GetNumberOfElements() {
      return this->_vertices.size();
   }

   virtual void Render();
};

template<class T>
void AbstractVertexGraphicsObject<T>::AddVertex(const T& vertex)
{
   this->_vertices.push_back(vertex);
}

template <class T>
void AbstractVertexGraphicsObject<T>::Render()
{
   //this->_shader->Render(this);
}

#endif

