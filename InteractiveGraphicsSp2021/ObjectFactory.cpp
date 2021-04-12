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
