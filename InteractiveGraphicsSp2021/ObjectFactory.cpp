#include "ObjectFactory.h"
#include "GraphicsObject.h"
#include "OGLVertexMesh.hpp"
#include "MeshFactory.hpp"
#include "GraphicsStructures.h"

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

GraphicsObject* ObjectFactory::FrustumModel(std::vector<glm::vec3> corners, RGB frontColor, RGB backColor)
{
    VertexPC ulf = { corners[0].x, corners[0].y, corners[0].z, frontColor };
    VertexPC llf = { corners[1].x, corners[1].y, corners[1].z, frontColor };
    VertexPC lrf = { corners[2].x, corners[2].y, corners[2].z, frontColor };
    VertexPC urf = { corners[3].x, corners[3].y, corners[3].z, frontColor };
    VertexPC ulb = { corners[4].x, corners[4].y, corners[4].z, backColor };
    VertexPC llb = { corners[5].x, corners[5].y, corners[5].z, backColor };
    VertexPC lrb = { corners[6].x, corners[6].y, corners[6].z, backColor };
    VertexPC urb = { corners[7].x, corners[7].y, corners[7].z, backColor };

    OGLVertexMesh<VertexPC>* mesh = new OGLVertexMesh<VertexPC>();
    mesh->SetPrimitive(GL_LINES);

    // upper left front corner
    mesh->AddVertexData(ulf);
    mesh->AddVertexData(urf);
    mesh->AddVertexData(ulf);
    mesh->AddVertexData(llf);
    // lower right front corner
    mesh->AddVertexData(lrf);
    mesh->AddVertexData(urf);
    mesh->AddVertexData(lrf);
    mesh->AddVertexData(llf);
    // upper left back corner
    mesh->AddVertexData(ulb);
    mesh->AddVertexData(urb);
    mesh->AddVertexData(ulb);
    mesh->AddVertexData(llb);
    // lower right back corner
    mesh->AddVertexData(lrb);
    mesh->AddVertexData(urb);
    mesh->AddVertexData(lrb);
    mesh->AddVertexData(llb);
    // Upper left edge
    mesh->AddVertexData(ulf);
    mesh->AddVertexData(ulb);
    // Lower left edge
    mesh->AddVertexData(llf);
    mesh->AddVertexData(llb);
    // Upper right edge
    mesh->AddVertexData(urf);
    mesh->AddVertexData(urb);
    // Lower right edge
    mesh->AddVertexData(lrf);
    mesh->AddVertexData(lrb);

    
    mesh->SetUpAttributes("PC");

    GraphicsObject* obj = new GraphicsObject();
    obj->AddMesh(mesh);
    return obj;
}
