#pragma once
#include "BaseGraphicsScene.h"
#include "SceneReader.h"
class OGLGraphicsScene :
	public BaseGraphicsScene
{
protected:
	SceneReader* _sceneReader;

	bool ReadShaderData();

public:
	OGLGraphicsScene(SceneReader* sceneReader);
	~OGLGraphicsScene();
	bool Create();
};

