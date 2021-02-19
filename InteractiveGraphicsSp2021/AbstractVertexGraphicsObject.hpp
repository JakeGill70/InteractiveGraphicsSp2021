#pragma once
#ifndef ABSTRACT_VERTEX_GRAPHICS_OBJECT
#define ABSTRACT_VERTEX_GRAPHICS_OBJECT

#include "AbstractGraphicsObject.h"
#include <vector>
using std::vector;
#include "GraphicsStructures.h"
#include "AbstractShader.h"

template <class T>
class AbstractVertexGraphicsObject :
   public AbstractGraphicsObject
{
protected:
   vector<T> _vertices;
   AbstractShader* _renderer;

public:
   AbstractVertexGraphicsObject(AbstractShader* renderer) {
      this->_renderer = renderer;
   }

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
   this->_renderer->Render(this);
}

#endif

