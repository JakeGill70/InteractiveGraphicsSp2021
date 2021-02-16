#pragma once
#ifndef ABSTRACT_RENDERER
#define ABSTRACT_RENDERER

class AbstractGraphicsObject;

class AbstractRenderer
{
protected:
   size_t _shaderProgram;

public:
   AbstractRenderer() : _shaderProgram(0) {}
   ~AbstractRenderer() {}

   void SetShaderProgram(size_t shaderProgram) {
      _shaderProgram = shaderProgram;
   }

   virtual inline void Select() = 0;
   virtual void Render(AbstractGraphicsObject* object) = 0;
   virtual size_t GenerateBuffer() = 0;
};

#endif

