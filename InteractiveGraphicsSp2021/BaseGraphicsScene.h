#pragma once
#ifndef BASE_GRAPHICS_SCENE
#define BASE_GRAPHICS_SCENE

#include "BaseObject.h"
#include <map>
using std::map;
#include "AbstractShader.h"
#include "AbstractGraphicsObject.h"
#include "BaseCamera.h"
#include "TextFileReader.h"

class BaseGraphicsScene :
    public BaseObject
{
protected:
   map<string, AbstractShader*> _shaders;
   map<string, AbstractGraphicsObject*> _objects;
   map<string, BaseCamera*> _cameras;
   BaseCamera* _currentCamera;
   TextFileReader* _textFileReader;

public:
   BaseGraphicsScene() : _currentCamera(nullptr), _textFileReader(nullptr) {}
   virtual ~BaseGraphicsScene();

   virtual void AddShader(const string& name, AbstractShader* shader) {
      _shaders[name] = shader;
   }

   virtual void AddGraphicsObject(
      const string& name, AbstractGraphicsObject* object, 
      const string& shaderName, bool isIndexed=false)
   {
      _objects[name] = object;
      _shaders[shaderName]->AddObjectToRender(name, object, isIndexed);
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

   virtual void Render();
};

#endif

