#pragma once
#ifndef OGL_GRAPHICS_SCENE
#define OGL_GRAPHICS_SCENE

#include "BaseGraphicsScene.h"
#include "SceneReader.h"

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

};

#endif

