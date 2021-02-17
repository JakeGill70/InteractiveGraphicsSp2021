#pragma once
#ifndef ABSTRACT_RENDERER
#define ABSTRACT_RENDERER

class AbstractGraphicsObject;

class AbstractRenderer
{
protected:
   unsigned int _shaderProgram;

public:
   AbstractRenderer() : _shaderProgram(0) {}
   ~AbstractRenderer() {}

   inline void SetShaderProgram(unsigned int shaderProgram){
      _shaderProgram = shaderProgram;
   }

   virtual inline void Select() = 0;
   virtual void Render(AbstractGraphicsObject* object) = 0;
   virtual size_t GenerateBuffer() = 0;

 private:
   virtual void SetUpBufferInterpretation() = 0;
};

#endif

