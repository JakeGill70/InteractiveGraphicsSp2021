#pragma once
#ifndef OGL_GRAPHICS_SCENE
#define OGL_GRAPHICS_SCENE

#include "BaseGraphicsScene.h"
#include "SceneReader.h"
#include "TextFileReader.h"
#include <vector>
using std::vector;
#include "OGLVertexMesh.hpp"

class OGLGraphicsScene :
    public BaseGraphicsScene
{
private:
   SceneReader* _sceneReader;

public:
   OGLGraphicsScene(SceneReader* sceneReader, TextFileReader* textFileReader)
      : _sceneReader(sceneReader)
   {
      _textFileReader = textFileReader;
   }
   ~OGLGraphicsScene();

   bool Create();

protected:
   bool LoadScene();
   bool ReadCameraData();
   bool ReadShaderData();
   bool ReadTextureData();
   bool ReadObjectData();
   AbstractMesh* CreatePCMesh(MeshData& meshData);
   bool ReadPCMeshData(OGLVertexMesh<VertexPC>* mesh, MeshData& meshData);
   AbstractMesh* CreatePCTMesh(MeshData& meshData);
   bool ReadPCTMeshData(OGLVertexMesh<VertexPCT>* mesh, MeshData& meshData);
   AbstractMesh* CreateFactoriedPCTMesh(FactoriedMeshData& meshData);

};

#endif

