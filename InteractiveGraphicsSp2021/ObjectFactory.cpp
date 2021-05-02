#include "ObjectFactory.h"
#include "GraphicsObject.h"
#include "OGLVertexMesh.hpp"
#include "MeshFactory.hpp"

GraphicsObject* ObjectFactory::PlainCuboid(float width, float height, float depth, RGB color)
{
   MeshFactory<VertexPC, RGB> meshFactoryPCRGB;
   OGLVertexMesh<VertexPC>* cuboidMesh = (OGLVertexMesh<VertexPC>*)
      meshFactoryPCRGB.CuboidMesh(width, height, depth, color);
   cuboidMesh->SetUpAttributes("PC");
   GraphicsObject* cuboid = new GraphicsObject();
   cuboid->AddMesh(cuboidMesh);
   return cuboid;
}

GraphicsObject* ObjectFactory::PCNTCuboid(float width, float height, float depth, RGBA color, AbstractTexture* texture)
{
    MeshFactory<VertexPCNT, RGBA> meshFactory;
    OGLVertexMesh<VertexPCNT>* cuboidMesh = (OGLVertexMesh<VertexPCNT>*)
        meshFactory.NormalizedTexturedCuboidMesh(width, height, depth, color, 1, 1);
    cuboidMesh->SetUpAttributes("PCNT");
    cuboidMesh->SetTexture(texture);
    GraphicsObject* cuboid = new GraphicsObject();
    cuboid->AddMesh(cuboidMesh);
    return cuboid;
}