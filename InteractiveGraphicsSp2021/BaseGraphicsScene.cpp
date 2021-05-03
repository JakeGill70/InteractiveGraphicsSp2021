#include "BaseGraphicsScene.h"
#include "AbstractKeyBinding.h"
#include "ObjectFactory.h"
#include "FollowAnimation.h"

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
   _currentCamera->SetupViewingFrustum(2);
   _currentCamera->OrientViewingFrustum();

   if (_inputSystem->GetKeyState("F2") == KeyState::Pressed) {
       string objectName;
       _frustumViewState = (_frustumViewState + 1) % 3;
       if (_frustumViewState == 0) {
            // Hide frustums
           for (std::map<string, GraphicsObject*>::iterator it = _objects.begin(); it != _objects.end(); ++it)
           {
               objectName = it->first;
               if (objectName.find("dbg_frustum::") == 0) {
                   it->second->isVisible = false;
               }
           }
       }
       else if (_frustumViewState == 1) {
           // Show frustums
           // Play follow animation
           for (std::map<string, GraphicsObject*>::iterator it = _objects.begin(); it != _objects.end(); ++it)
           {
               objectName = it->first;
               if (objectName.find("dbg_frustum::") == 0) {
                   it->second->isVisible = true;
                   ((FollowAnimation*)(it->second->GetAnimation()))->setFollowing(true);
               }
           }
       }
       else if (_frustumViewState == 2) {
           // Show frustums
           // Stop follow animation
           for (std::map<string, GraphicsObject*>::iterator it = _objects.begin(); it != _objects.end(); ++it)
           {
               objectName = it->first;
               if (objectName.find("dbg_frustum::") == 0) {
                   it->second->isVisible = true;
                   ((FollowAnimation*)(it->second->GetAnimation()))->setFollowing(false);
               }
           }
       }
   }

   for (auto iterator = _objects.begin(); iterator != _objects.end(); iterator++) {
       GraphicsObject* obj = iterator->second;
       obj->Update(elapsedSeconds);
       if (_currentCamera->viewingFrustrum->hasSphereInside(obj->boundingSphere)) {
           obj->GetMesh(0)->material.ambientIntensity = 1;

       }
       else {
           obj->GetMesh(0)->material.ambientIntensity = 0.01;
       }
       if (iterator->first == "axis") {
           obj->isVisible = true;
       }
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
