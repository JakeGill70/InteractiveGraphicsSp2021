#pragma once
#ifndef ABSTRACT_GRAPHICS_OBJECT
#define ABSTRACT_GRAPHICS_OBJECT
#include <vector>
#include "GraphicsStructures.h"
using std::vector;
#include "AbstractRenderer.hpp"

template <class T>
class AbstractGraphicsObject
{
protected:
   vector<T> _vertices;
   AbstractRenderer<T>* _renderer;

public:
   AbstractGraphicsObject(AbstractRenderer<T>* renderer);

   virtual ~AbstractGraphicsObject();

   void AddVertex(const T& vertex);

   size_t GetNumberOfVertices();

   virtual void Render();
   virtual void SendToGPU() = 0;
   virtual size_t GetBufferId() = 0;
};

template<class T>
AbstractGraphicsObject<T>::AbstractGraphicsObject(AbstractRenderer<T>* renderer)
{
   this->_renderer = renderer;
}

template<class T>
AbstractGraphicsObject<T>::~AbstractGraphicsObject()
{
}

template<class T>
void AbstractGraphicsObject<T>::AddVertex(const T& vertex)
{
   this->_vertices.push_back(vertex);
}

template<class T>
size_t AbstractGraphicsObject<T>::GetNumberOfVertices()
{
   return this->_vertices.size();
}

template <class T>
void AbstractGraphicsObject<T>::Render()
{
   AbstractGraphicsObject<T>* self = this;
   this->_renderer->Render(self);
}

#endif

