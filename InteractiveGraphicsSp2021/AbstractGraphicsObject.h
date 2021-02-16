#pragma once
#ifndef ABSTRACT_GRAPHICS_OBJECT
#define ABSTRACT_GRAPHICS_OBJECT
#include <vector>
#include "GraphicsStructures.h"
using std::vector;

class AbstractRenderer;

class AbstractGraphicsObject
{
protected:
   vector<Vertex> _vertices;
   AbstractRenderer* _renderer;

public:
   AbstractGraphicsObject(AbstractRenderer* renderer) : _renderer(renderer)
   {}

   virtual ~AbstractGraphicsObject() {}

   void AddVertex(const Vertex& vertex) {
      _vertices.push_back(vertex);
   }

   size_t GetNumberOfVertices() {
      return _vertices.size();
   }

   virtual void Render();
   virtual void SendToGPU() = 0;
   virtual size_t GetBufferId() = 0;
};

#endif

