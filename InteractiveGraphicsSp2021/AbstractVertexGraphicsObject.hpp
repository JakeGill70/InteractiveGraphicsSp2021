#pragma once
#ifndef ABSTRACT_VERTEX_OBJECT
#define ABSTRACT_VERTEX_OBJECT

#include "AbstractGraphicsObject.h"
#include <vector>
using std::vector;
#include "GraphicsStructures.h"
#include "AbstractRenderer.h"

template <class T>
class AbstractVertexObject :
   public AbstractGraphicsObject
{
protected:
   vector<T> _vertices;
   AbstractRenderer* _renderer;

public:
   AbstractVertexObject(AbstractRenderer* renderer) {
      this->_renderer = renderer;
   }

   virtual ~AbstractVertexObject() {}

   void AddVertex(const T& vertex);

   inline size_t GetNumberOfElements() {
      return this->_vertices.size();
   }

   virtual void Render();
};

template<class T>
void AbstractVertexObject<T>::AddVertex(const T& vertex)
{
   this->_vertices.push_back(vertex);
}

template <class T>
void AbstractVertexObject<T>::Render()
{
   AbstractVertexObject<T>* self = this;
   this->_renderer->Render(self);
}

#endif

