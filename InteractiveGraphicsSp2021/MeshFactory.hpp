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
   AbstractVertexMesh<V>* FlatTexturedMeshXZ(
      float sx, float sz, float ex, float ez, C color, float repeatS, float repeatT);
   AbstractVertexMesh<V>* CuboidMeshPCT(
      float width, float height, float depth, C color, float repeatS, float repeatT);
};

template <class V, class C>
AbstractVertexMesh<V>* MeshFactory<V,C>::FlatTexturedMeshXZ(
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

template <class V, class C>
AbstractVertexMesh<V>* MeshFactory<V, C>::CuboidMeshPCT(
   float width, float height, float depth, C color, float repeatS, float repeatT)
{
   float halfWidth = width / 2;
   float halfHeight = height / 2;
   float halfDepth = depth / 2;
   OGLVertexMesh<V>* mesh = new OGLVertexMesh<V>();
   // +Z
   V A = { -halfWidth, halfHeight, halfDepth, color};
   V B = { -halfWidth, -halfHeight, halfDepth, color};
   V C = { halfWidth, halfHeight, halfDepth, color};
   V D = { halfWidth, -halfHeight, halfDepth, color};
   // -Z
   V E = { halfWidth, halfHeight, -halfDepth, color };
   V F = { halfWidth, -halfHeight, -halfDepth, color };
   V G = { -halfWidth, halfHeight, -halfDepth, color };
   V H = { -halfWidth, -halfHeight, -halfDepth, color };

   // Looking from the front

   // Front face
   A.tex = { 0, repeatT };
   B.tex = { 0, 0 };
   C.tex = { repeatS, 0 };
   D.tex = { repeatS, repeatT };
   mesh->AddVertexData(A);
   mesh->AddVertexData(B);
   mesh->AddVertexData(C);
   mesh->AddVertexData(A);
   mesh->AddVertexData(C);
   mesh->AddVertexData(D);
   // Right face
   D.tex = { 0, repeatT };
   C.tex = { 0, 0 };
   F.tex = { repeatS, 0 };
   E.tex = { repeatS, repeatT };
   mesh->AddVertexData(D);
   mesh->AddVertexData(C);
   mesh->AddVertexData(F);
   mesh->AddVertexData(D);
   mesh->AddVertexData(F);
   mesh->AddVertexData(E);
   // Back face
   E.tex = { 0, repeatT };
   F.tex = { 0, 0 };
   G.tex = { repeatS, 0 };
   H.tex = { repeatS, repeatT };
   mesh->AddVertexData(E);
   mesh->AddVertexData(F);
   mesh->AddVertexData(G);
   mesh->AddVertexData(E);
   mesh->AddVertexData(G);
   mesh->AddVertexData(H);
   // Left face
   H.tex = { 0, repeatT };
   G.tex = { 0, 0 };
   B.tex = { repeatS, 0 };
   A.tex = { repeatS, repeatT };
   mesh->AddVertexData(H);
   mesh->AddVertexData(G);
   mesh->AddVertexData(B);
   mesh->AddVertexData(H);
   mesh->AddVertexData(B);
   mesh->AddVertexData(A);
   // Top face
   H.tex = { 0, repeatT };
   A.tex = { 0, 0 };
   D.tex = { repeatS, 0 };
   E.tex = { repeatS, repeatT };
   mesh->AddVertexData(H);
   mesh->AddVertexData(A);
   mesh->AddVertexData(D);
   mesh->AddVertexData(H);
   mesh->AddVertexData(D);
   mesh->AddVertexData(E);
   // Bottom face
   B.tex = { 0, repeatT };
   G.tex = { 0, 0 };
   F.tex = { repeatS, 0 };
   C.tex = { repeatS, repeatT };
   mesh->AddVertexData(B);
   mesh->AddVertexData(G);
   mesh->AddVertexData(F);
   mesh->AddVertexData(B);
   mesh->AddVertexData(F);
   mesh->AddVertexData(C);
}

#endif

