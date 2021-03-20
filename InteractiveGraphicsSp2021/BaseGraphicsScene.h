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

public:
   Light globalLight;

public:
   BaseGraphicsScene() : _currentCamera(nullptr), _textFileReader(nullptr) {
      globalLight.position = { 100.0f, 100.0f, 0 };
      globalLight.color = { 1, 1, 1 };
      globalLight.intensity = 0.25;
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

   virtual bool Create() { return true; }

   virtual void Update(double elapsedSeconds);

   virtual void Render();
};

#endif

