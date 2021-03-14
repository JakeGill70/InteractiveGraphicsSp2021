#pragma once
#ifndef OGL_GRAPHICS_SCENE
#define OGL_GRAPHICS_SCENE

#include "BaseGraphicsScene.h"
#include "SceneReader.h"
#include <vector>
using std::vector;
#include "OGLVertexMesh.hpp"

class OGLGraphicsScene :
    public BaseGraphicsScene
{
private:
   SceneReader* _sceneReader;

public:
   OGLGraphicsScene(SceneReader* sceneReader) : _sceneReader(sceneReader)
   {}
   ~OGLGraphicsScene();

   bool Create();

protected:
   bool LoadScene();
   bool ReadCameraData();
   bool ReadShaderData();
   bool ReadObjectData();
   AbstractMesh* CreatePCMesh(MeshData& meshData);
   bool ReadPCMeshData(
      OGLVertexMesh<VertexPC>* mesh, 
      vector<float>& vertexData,
      vector<unsigned short>& indexData,
      bool isIndexed);

};

#endif

