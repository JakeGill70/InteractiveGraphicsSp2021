#pragma once
#ifndef ABSTRACT_RENDERER
#define ABSTRACT_RENDERER

#include "BaseObject.h"
#include <glm\glm.hpp>
#include <string>
using std::string;

class AbstractGraphicsObject;

class AbstractShader :
   public BaseObject
{
protected:
   unsigned int _shaderProgram;

public:
   AbstractShader() : _shaderProgram(0) {}
   ~AbstractShader() {}

   inline void SetShaderProgram(unsigned int shaderProgram){
      _shaderProgram = shaderProgram;
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

