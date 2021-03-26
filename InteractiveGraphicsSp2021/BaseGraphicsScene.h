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
   Light globalLight;

public:
   BaseGraphicsScene() : _currentCamera(nullptr), _textFileReader(nullptr), globalLight() {
       globalLight.position.x = 100;
       globalLight.position.y = 100;
       globalLight.position.z = 0;
       globalLight.color.r = 255;
       globalLight.color.g = 255;
       globalLight.color.b = 255;
       globalLight.intensity = 0.25f;
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

