#pragma once
#ifndef BASE_GRAPHICS_SCENE
#define BASE_GRAPHICS_SCENE

#include "BaseObject.h"
#include <map>
using std::map;
#include "AbstractShader.h"
#include "GraphicsObject.h"
#include "BaseCamera.h"
#include "TextFileReader.h"
#include "GraphicsStructures.h"
#include "GraphicsWindow.h"
#include "AbstractInputSystem.h"

class AbstractKeyBinding;

class BaseGraphicsScene :
    public BaseObject
{
protected:
   map<string, AbstractShader*> _shaders;
   map<string, GraphicsObject*> _objects;
   map<string, BaseCamera*> _cameras;
   map<string, AbstractTexture*> _textures;
   BaseCamera* _currentCamera;
   TextFileReader* _textFileReader;
   int _numberOfLights;
   GraphicsWindow* _window;
   AbstractInputSystem* _inputSystem;
   AbstractKeyBinding* _keyBinding;

public:
   Light globalLight;
   static const int NumberOfLights = 10;
   Light localLights[BaseGraphicsScene::NumberOfLights];
 
public:
   BaseGraphicsScene(GraphicsWindow* window) 
      : _currentCamera(nullptr), _textFileReader(nullptr), 
      _window(window), _inputSystem(nullptr), _keyBinding(nullptr) {
      globalLight.position = { 100.0f, 100.0f, 0 };
      globalLight.color = { 1, 1, 1 };
      globalLight.intensity = 0.25;
      _numberOfLights = 1;
      for (int i = 0; i < BaseGraphicsScene::NumberOfLights; i++) {
         localLights[i].position = { 100.0f, 100.0f, 0 };
         localLights[i].color = { 1, 1, 1 };
         localLights[i].attenuationCoefficient = 0.2f;
      }
   }
   virtual ~BaseGraphicsScene();

   virtual void AddShader(const string& name, AbstractShader* shader) {
      _shaders[name] = shader;
   }

   virtual void AddTexture(const string& name, AbstractTexture* texture) {
      _textures[name] = texture;
   }

   virtual void AddGraphicsObject(
      const string& name, GraphicsObject* object, 
      const string& shaderName)
   {
      _objects[name] = object;
      _shaders[shaderName]->AddObjectToRender(name, object);
   }

   virtual void AddCamera(const string& name, BaseCamera* camera) {
      _cameras[name] = camera;
   }

   virtual void SetCurrentCamera(const string& cameraName) {
      _currentCamera = _cameras[cameraName];
   }

   virtual void UpdateCameraProjection(float aspectRatio);

   virtual inline void SetTextFileReader(TextFileReader* reader) {
      _textFileReader = reader;
   }

   virtual GraphicsWindow* GetWindow() {
      return _window;
   }

   virtual bool Create() { return true; }

   virtual void Update(double elapsedSeconds);

   virtual void Render();

   virtual void HideAllObjects();
};

#endif

