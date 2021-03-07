#pragma once
#ifndef ABSTRACT_RENDERER
#define ABSTRACT_RENDERER

#include "BaseObject.h"
#include <glm\glm.hpp>
#include <string>
#include <map>
#include "BaseCamera.h"
#include "AbstractGraphicsObject.h"

using std::string;
using std::map;

//class AbstractGraphicsObject;

class AbstractShader :
   public BaseObject
{
protected:
   unsigned int _shaderProgram;
   map<string, AbstractGraphicsObject*> _objectsToRender;
   BaseCamera* _camera;
   virtual void SendGPUData() = 0;
   virtual void RenderObjects() = 0;

public:
   AbstractShader() : _shaderProgram(0) {
       _camera = nullptr;
   }
   ~AbstractShader() {}

   inline void SetShaderProgram(unsigned int shaderProgram){
      _shaderProgram = shaderProgram;
   }

   inline void SetCamera(BaseCamera* cam) {
       _camera = cam;
   }

   inline void AddObjectToRender(const string& objectName, AbstractGraphicsObject* object) {
       _objectsToRender[objectName] = object;
       object->SetBufferId(GenerateBuffer());
   }

   virtual inline void Select() = 0;
   virtual inline void SelectProgram() = 0;
   virtual void Render(AbstractGraphicsObject* object) = 0;
   virtual size_t GenerateBuffer() = 0;
   virtual bool Create() = 0;
   virtual void SendMatrixToGPU(const string& name, const glm::mat4& matrix) = 0;

 private:
   virtual void SetUpBufferInterpretation() = 0;
};

#endif

