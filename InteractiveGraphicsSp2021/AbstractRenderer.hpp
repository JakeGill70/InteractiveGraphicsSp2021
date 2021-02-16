#pragma once
#ifndef ABSTRACT_RENDERER
#define ABSTRACT_RENDERER

template <class T>
class AbstractGraphicsObject;

template <class T>
class AbstractRenderer
{
protected:
   unsigned int _shaderProgram;

public:
   AbstractRenderer() : _shaderProgram(0) {}
   ~AbstractRenderer() {}

   void SetShaderProgram(unsigned int shaderProgram);

   virtual inline void Select() = 0;
   virtual void Render(AbstractGraphicsObject<T>* object) = 0;
   virtual size_t GenerateBuffer() = 0;
};

template <class T>
void AbstractRenderer<T>::SetShaderProgram(unsigned int shaderProgram) {
   _shaderProgram = shaderProgram;
}

#endif

