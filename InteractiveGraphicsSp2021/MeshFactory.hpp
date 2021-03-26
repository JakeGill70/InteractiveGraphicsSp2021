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

   AbstractVertexMesh<V>* CuboidMesh(float width, float height, float depth, C color);

   AbstractVertexMesh<V>* TexturedCuboidMesh(
       float width, float height, float depth, C color, float repeatS, float repeatT);

   AbstractVertexMesh<V>* NormalizedTexturedCuboidMesh(
       float width, float height, float depth, C color, float repeatS, float repeatT);

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

template <class V, class C>
AbstractVertexMesh<V>* MeshFactory<V, C>::CuboidMesh(
    float width, float height, float depth, C color)
{
    float halfWidth = width / 2;
    float halfHeight = height / 2;
    float halfDepth = depth / 2;
    OGLVertexMesh<V>* mesh = new OGLVertexMesh<V>();
    // +Z
    V vA = { -halfWidth, halfHeight, halfDepth, color };
    V vB = { -halfWidth, -halfHeight, halfDepth, color };
    V vC = { halfWidth, -halfHeight, halfDepth, color };
    V vD = { halfWidth, halfHeight, halfDepth, color };
    // -Z
    V vE = { halfWidth, halfHeight, -halfDepth, color };
    V vF = { halfWidth, -halfHeight, -halfDepth, color };
    V vG = { -halfWidth, -halfHeight, -halfDepth, color };
    V vH = { -halfWidth, halfHeight, -halfDepth, color };

    // Looking from the front

    // Front face
    mesh->AddVertexData(vA);
    mesh->AddVertexData(vB);
    mesh->AddVertexData(vC);
    mesh->AddVertexData(vA);
    mesh->AddVertexData(vC);
    mesh->AddVertexData(vD);
    // Right face
    mesh->AddVertexData(vD);
    mesh->AddVertexData(vC);
    mesh->AddVertexData(vF);
    mesh->AddVertexData(vD);
    mesh->AddVertexData(vF);
    mesh->AddVertexData(vE);
    // Back face
    mesh->AddVertexData(vE);
    mesh->AddVertexData(vF);
    mesh->AddVertexData(vG);
    mesh->AddVertexData(vE);
    mesh->AddVertexData(vG);
    mesh->AddVertexData(vH);
    // Left face
    mesh->AddVertexData(vH);
    mesh->AddVertexData(vG);
    mesh->AddVertexData(vB);
    mesh->AddVertexData(vH);
    mesh->AddVertexData(vB);
    mesh->AddVertexData(vA);
    // Top face
    mesh->AddVertexData(vH);
    mesh->AddVertexData(vA);
    mesh->AddVertexData(vD);
    mesh->AddVertexData(vH);
    mesh->AddVertexData(vD);
    mesh->AddVertexData(vE);
    // Bottom face
    mesh->AddVertexData(vB);
    mesh->AddVertexData(vG);
    mesh->AddVertexData(vF);
    mesh->AddVertexData(vB);
    mesh->AddVertexData(vF);
    mesh->AddVertexData(vC);
    return mesh;
}

template <class V, class C>
AbstractVertexMesh<V>* MeshFactory<V, C>::TexturedCuboidMesh(
    float width, float height, float depth, C color, float repeatS, float repeatT)
{
    OGLVertexMesh<V>* mesh = dynamic_cast<OGLVertexMesh<V>*>
        (CuboidMesh(width, depth, height, color));

    int numberOfVertices = (int)mesh->GetNumberOfVertices();
    for (int i = 0; i < numberOfVertices; i += 6)
    {
        mesh->GetVertex(i).tex = { 0, repeatT };
        mesh->GetVertex(i + 1).tex = { 0, 0 };
        mesh->GetVertex(i + 2).tex = { repeatS, 0 };
        mesh->GetVertex(i + 3).tex = { 0, repeatT };
        mesh->GetVertex(i + 4).tex = { repeatS, 0 };
        mesh->GetVertex(i + 5).tex = { repeatS, repeatT };
    }
    return mesh;
}

template <class V, class C>
AbstractVertexMesh<V>* MeshFactory<V, C>::NormalizedTexturedCuboidMesh(
    float width, float height, float depth, C color, float repeatS, float repeatT)
{
    OGLVertexMesh<V>* mesh = dynamic_cast<OGLVertexMesh<V>*>
        (TexturedCuboidMesh(width, depth, height, color, repeatS, repeatT));

    // Assumes the cuboid mesh is created in the following order:
    // front, right, back, left, top, bottom
    // with 6 vertices for each face
    Vector3D normals[6] = {
       { 0, 0, 1 }, { 1, 0, 0 }, { 0, 0, -1 },
       { -1, 0, 0 }, { 0, 1, 0 }, { 0, -1, 0 }
    };
    int ni = 0;
    int numberOfVertices = (int)mesh->GetNumberOfVertices();
    for (int i = 0; i < numberOfVertices; i += 6)
    {
        mesh->GetVertex(i).normal = normals[ni];
        mesh->GetVertex(i + 1).normal = normals[ni];
        mesh->GetVertex(i + 2).normal = normals[ni];
        mesh->GetVertex(i + 3).normal = normals[ni];
        mesh->GetVertex(i + 4).normal = normals[ni];
        mesh->GetVertex(i + 5).normal = normals[ni];
        ni++;
    }

    return mesh;
}


#endif

