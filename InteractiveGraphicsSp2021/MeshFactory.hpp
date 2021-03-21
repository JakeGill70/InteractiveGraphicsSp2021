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
   AbstractVertexMesh<V>* IndexedFlatTexturedMeshXZ(
      float sx, float sz, float width, float depth, C color, float repeatS, float repeatT);

   AbstractVertexMesh<V>* IndexedFlatMeshXZ(
      float sx, float sz, float width, float depth, C color);
};

template <class V, class C>
AbstractVertexMesh<V>* MeshFactory<V,C>::IndexedFlatTexturedMeshXZ(
   float sx, float sz, float width, float depth, C color, float repeatS, float repeatT)
{
   OGLVertexMesh<V>* mesh = 
      dynamic_cast<OGLVertexMesh<V>*>(IndexedFlatMeshXZ(sx, sz, width, depth, color));
   mesh->GetVertex(0).tex = { 0, repeatT };
   mesh->GetVertex(1).tex = { 0, 0 };
   mesh->GetVertex(2).tex = { repeatS, 0 };
   mesh->GetVertex(3).tex = { repeatS, repeatT };
   return mesh;
}

template <class V, class C>
AbstractVertexMesh<V>* MeshFactory<V, C>::IndexedFlatMeshXZ(
   float sx, float sz, float width, float depth, C color)
{
   float ex = sx + width;
   float ez = sz + depth;
   OGLVertexMesh<V>* mesh = new OGLVertexMesh<V>();
   mesh->AddVertexData({ sx, 0, sz, color});
   mesh->AddVertexData({ sx, 0, ez, color});
   mesh->AddVertexData({ ex, 0, ez, color});
   mesh->AddVertexData({ ex, 0, sz, color});
   unsigned short indices[] = { 0, 1, 2, 0, 2, 3 };
   mesh->SetIndices(indices, 6);
   return mesh;
}

#endif

