#include "BaseGraphicsScene.h"

BaseGraphicsScene::~BaseGraphicsScene()
{
   for (auto iterator = _shaders.begin(); iterator != _shaders.end(); iterator++) {
      delete iterator->second;
   }
   _shaders.clear();

   for (auto iterator = _objects.begin(); iterator != _objects.end(); iterator++) {
      delete iterator->second;
   }
   _objects.clear();

   for (auto iterator = _cameras.begin(); iterator != _cameras.end(); iterator++) {
      delete iterator->second;
   }
   _cameras.clear();
}

void BaseGraphicsScene::UpdateCameraProjection(float aspectRatio)
{
   for (auto iterator = _cameras.begin(); iterator != _cameras.end(); iterator++) {
      iterator->second->UpdateProjection(aspectRatio);
   }
}

void BaseGraphicsScene::Render()
{
   for (auto iterator = _shaders.begin(); iterator != _shaders.end(); iterator++) {
      iterator->second->RenderObjects();
   }
}
