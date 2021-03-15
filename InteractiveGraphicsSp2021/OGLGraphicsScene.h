#pragma once
#ifndef OGL_GRAPHICS_SCENE
#define OGL_GRAPHICS_SCENE

#include "BaseGraphicsScene.h"
#include "SceneReader.h"
#include "OGLGraphicsObject.hpp"

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
   bool ReadPCObjectData(OGLGraphicsObject<VertexPC>* object, vector<float>& vertexData, vector<unsigned short>& indexData, bool isIndexed);
};

#endif

