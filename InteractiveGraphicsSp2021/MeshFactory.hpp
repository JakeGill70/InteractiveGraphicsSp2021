#pragma once
#ifndef MESH_FACTORY
#define MESH_FACTORY

#include "BaseObject.h"
#include "AbstractVertexMesh.hpp"

template <class V, class C>
class MeshFactory :
    public BaseObject
{
public:
   AbstractVertexMesh<V>* FlatTexturedSurfaceXZ(
      float sx, float sz, float ex, float ez, C color, float repeatS, float repeatT);
};

template <class V, class C>
AbstractVertexMesh<V>* MeshFactory<V,C>::FlatTexturedSurfaceXZ(
   float sx, float sz, float ex, float ez, C color, float repeatS, float repeatT)
{
   OGLVertexMesh<V>* mesh = new OGLVertexMesh<V>();
   mesh->AddVertexData({ sx, 0, sz, color, 0, repeatT });
   mesh->AddVertexData({ sx, 0, ez, color, 0, 0 });
   mesh->AddVertexData({ ex, 0, ez, color, repeatS, 0 });
   mesh->AddVertexData({ ex, 0, sz, color, repeatS, repeatT });
   unsigned short indices[] = { 0, 1, 2, 0, 2, 3 };
   mesh->SetIndices(indices, 6);
   return mesh;
}


#endif

