#pragma once
#include "BaseGraphicsScene.h"
#include "SceneReader.h"
class OGLGraphicsScene :
	public BaseGraphicsScene
{
public:
	bool Create(SceneReader* sceneReader);
};

