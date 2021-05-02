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
   OGLGraphicsScene(GraphicsWindow* window, SceneReader* sceneReader, TextFileReader* textFileReader)
      : BaseGraphicsScene(window), _sceneReader(sceneReader)
   {
      _textFileReader = textFileReader;
   }
   ~OGLGraphicsScene();

   bool Create();

protected:
   bool LoadScene();
   bool ReadCameraData();
   bool ReadShaderData();
   bool ReadLightData();
   bool ReadTextureData();
   bool ReadObjectData();
   void CreateFactoriedMesh(FactoriedMeshData& factoriedMeshData, AbstractMesh*& mesh);
   void CreateMesh(MeshData& meshData, AbstractMesh*& mesh);
   AbstractMesh* CreatePCMesh(MeshData& meshData);
   bool ReadPCMeshData(OGLVertexMesh<VertexPC>* mesh, MeshData& meshData);
   AbstractMesh* CreatePCTMesh(MeshData& meshData);
   bool ReadPCTMeshData(OGLVertexMesh<VertexPCT>* mesh, MeshData& meshData);
   AbstractMesh* CreateFactoriedPCMesh(FactoriedMeshData& meshData);
   AbstractMesh* CreateFactoriedPCTMesh(FactoriedMeshData& meshData);
   AbstractMesh* CreateFactoriedPCNTMesh(FactoriedMeshData& meshData);

   void CreatePCNTFlatMesh(FactoriedMeshData& meshData, OGLVertexMesh<VertexPCNT>*& mesh);
   void CreatePCCuboidMesh(FactoriedMeshData& meshData, OGLVertexMesh<VertexPC>*& mesh);
   void CreatePCNTCuboidMesh(FactoriedMeshData& meshData, OGLVertexMesh<VertexPCNT>*& mesh);

   void MakeRandomBoxes(int count, glm::vec3 range, glm::vec3 centerPoint);
};

#endif

