#pragma once
#ifndef ABSTRACT_RENDERER
#define ABSTRACT_RENDERER

#include "BaseObject.h"
#include <glm\glm.hpp>
#include <string>
using std::string;
#include <map>
using std::map;
#include "AbstractGraphicsObject.h"

class BaseCamera;

class AbstractShader :
   public BaseObject
{
protected:
   unsigned int _shaderProgram;
   map<string, AbstractGraphicsObject*> _objectsToRender;
   BaseCamera* _camera;

public:
   AbstractShader() : _shaderProgram(0), _camera(nullptr) {}
   ~AbstractShader() {}

   inline void SetShaderProgram(unsigned int shaderProgram){
      _shaderProgram = shaderProgram;
   }

   virtual inline void AddObjectToRender(
      const string& objectName, AbstractGraphicsObject* object, bool isIndexed) {
      _objectsToRender[objectName] = object;
      _objectsToRender[objectName]->SetBufferId(GenerateBuffer());
      if (isIndexed) {
         _objectsToRender[objectName]->SetIndexedBufferId(GenerateBuffer());
      }
   }

   virtual inline void SetCamera(BaseCamera* camera) {
      _camera = camera;
   }

   virtual inline void Select() = 0;
   virtual inline void SelectProgram() = 0;
   virtual void RenderObjects() = 0;
   virtual void Render(AbstractGraphicsObject* object) = 0;
   virtual size_t GenerateBuffer() = 0;
   virtual bool Create() = 0;
   virtual void SendMatrixToGPU(const string& name, const glm::mat4& matrix) = 0;

protected:
   virtual void SendGPUData() = 0;

 private:
   virtual void SetUpBufferInterpretation() = 0;
};

#endif

