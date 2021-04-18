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

   for (auto iterator = _textures.begin(); iterator != _textures.end(); iterator++) {
      delete iterator->second;
   }
   _textures.clear();

   delete _textFileReader;
   if (_inputSystem) delete _inputSystem;
   if (_keyBinding) delete _keyBinding;
}

void BaseGraphicsScene::UpdateCameraProjection(float aspectRatio)
{
   for (auto iterator = _cameras.begin(); iterator != _cameras.end(); iterator++) {
      iterator->second->UpdateProjection(aspectRatio);
   }
}

void BaseGraphicsScene::Update(double elapsedSeconds)
{
   _currentCamera->Update(elapsedSeconds);
   for (auto iterator = _objects.begin(); iterator != _objects.end(); iterator++) {
      iterator->second->Update(elapsedSeconds);
   }
}

void BaseGraphicsScene::Render()
{
   AbstractShader* shader;
   for (auto iterator = _shaders.begin(); iterator != _shaders.end(); iterator++) {
      shader = iterator->second;
      shader->SelectProgram();
      shader->SendGlobalLightToGPU(globalLight);
      shader->SendLocalLightsToGPU(localLights, _numberOfLights);
      shader->SendVec3ToGPU("viewPosition", _currentCamera->frame.GetPosition());
      shader->RenderObjects();
   }
}

void BaseGraphicsScene::HideAllObjects()
{
   for (auto iterator = _objects.begin(); iterator != _objects.end(); iterator++) {
      iterator->second->isVisible = false;
   }
}
