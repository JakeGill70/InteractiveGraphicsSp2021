#pragma once
#ifndef ABSTRACT_RENDERER
#define ABSTRACT_RENDERER

#include "BaseObject.h"
#include <glm\glm.hpp>
#include <string>
using std::string;
#include <map>
using std::map;
#include "GraphicsObject.h"

class BaseCamera;

class AbstractShader :
   public BaseObject
{
protected:
   unsigned int _shaderProgram;
   map<string, GraphicsObject*> _objectsToRender;
   BaseCamera* _camera;

public:
   AbstractShader() : _shaderProgram(0), _camera(nullptr) {}
   ~AbstractShader() {}

   inline void SetShaderProgram(unsigned int shaderProgram){
      _shaderProgram = shaderProgram;
   }

   virtual void AddObjectToRender(const string& objectName, GraphicsObject* object);


   virtual inline void SetCamera(BaseCamera* camera) {
      _camera = camera;
   }

   virtual inline void Select() = 0;
   virtual inline void SelectProgram() = 0;
   virtual void RenderObjects() = 0;
   virtual void Render(GraphicsObject* object) = 0;
   virtual size_t GenerateBuffer() = 0;
   virtual bool Create() = 0;
   virtual void SendMatrixToGPU(const string& name, const glm::mat4& matrix) = 0;
   virtual void SendFloatToGPU(const string& name, float data) const = 0;
   virtual void SendVec3ToGPU(const string& name, const glm::vec3& vector) const = 0;
   virtual void SendGlobalLightToGPU(const Light& globalLight) const = 0;
   virtual void SendLocalLightToGPU(const Light& localLight) const = 0;

protected:
   virtual void SendGPUData() = 0;
};

#endif

