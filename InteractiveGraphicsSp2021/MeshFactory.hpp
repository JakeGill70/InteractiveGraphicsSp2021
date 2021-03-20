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
   V vA = { -halfWidth, halfHeight, halfDepth, color};
   V vB = { -halfWidth, -halfHeight, halfDepth, color};
   V vC = { halfWidth, -halfHeight, halfDepth, color};
   V vD = { halfWidth, halfHeight, halfDepth, color};
   // -Z
   V vE = { halfWidth, halfHeight, -halfDepth, color };
   V vF = { halfWidth, -halfHeight, -halfDepth, color };
   V vG = { -halfWidth, -halfHeight, -halfDepth, color };
   V vH = { -halfWidth, halfHeight, -halfDepth, color };

   // Looking from the front

   // Front face
   vA.tex = { 0, repeatT };
   vB.tex = { 0, 0 };
   vC.tex = { repeatS, 0 };
   vD.tex = { repeatS, repeatT };
   mesh->AddVertexData(vA);
   mesh->AddVertexData(vB);
   mesh->AddVertexData(vC);
   mesh->AddVertexData(vA);
   mesh->AddVertexData(vC);
   mesh->AddVertexData(vD);
   // Right face
   vD.tex = { 0, repeatT };
   vC.tex = { 0, 0 };
   vF.tex = { repeatS, 0 };
   vE.tex = { repeatS, repeatT };
   mesh->AddVertexData(vD);
   mesh->AddVertexData(vC);
   mesh->AddVertexData(vF);
   mesh->AddVertexData(vD);
   mesh->AddVertexData(vF);
   mesh->AddVertexData(vE);
   // Back face
   vE.tex = { 0, repeatT };
   vF.tex = { 0, 0 };
   vG.tex = { repeatS, 0 };
   vH.tex = { repeatS, repeatT };
   mesh->AddVertexData(vE);
   mesh->AddVertexData(vF);
   mesh->AddVertexData(vG);
   mesh->AddVertexData(vE);
   mesh->AddVertexData(vG);
   mesh->AddVertexData(vH);
   // Left face
   vH.tex = { 0, repeatT };
   vG.tex = { 0, 0 };
   vB.tex = { repeatS, 0 };
   vA.tex = { repeatS, repeatT };
   mesh->AddVertexData(vH);
   mesh->AddVertexData(vG);
   mesh->AddVertexData(vB);
   mesh->AddVertexData(vH);
   mesh->AddVertexData(vB);
   mesh->AddVertexData(vA);
   // Top face
   vH.tex = { 0, repeatT };
   vA.tex = { 0, 0 };
   vD.tex = { repeatS, 0 };
   vE.tex = { repeatS, repeatT };
   mesh->AddVertexData(vH);
   mesh->AddVertexData(vA);
   mesh->AddVertexData(vD);
   mesh->AddVertexData(vH);
   mesh->AddVertexData(vD);
   mesh->AddVertexData(vE);
   // Bottom face
   vB.tex = { 0, repeatT };
   vG.tex = { 0, 0 };
   vF.tex = { repeatS, 0 };
   vC.tex = { repeatS, repeatT };
   mesh->AddVertexData(vB);
   mesh->AddVertexData(vG);
   mesh->AddVertexData(vF);
   mesh->AddVertexData(vB);
   mesh->AddVertexData(vF);
   mesh->AddVertexData(vC);
   mesh->SetPositionAttribute({ 0,  3, sizeof(V), 0 });
   mesh->SetColorAttribute({ 1, 4, sizeof(V), sizeof(GLfloat) * 3 });
   mesh->SetTextureAttribute({ 2, 2, sizeof(V), sizeof(GLfloat) * 7 });
   return mesh;
}

#endif

