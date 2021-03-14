#pragma once
#ifndef OGL_TEXTURE
#define OGL_TEXTURE

#include "AbstractTexture.h"
#include <glad\glad.h>

class OGLTexture :
   public AbstractTexture
{
protected:
   GLuint _id;
   GLint _wrapS, _wrapT;
   GLint _minFilter, _magFilter;

public:
   OGLTexture();
   virtual ~OGLTexture();

   inline void SetWrapS(GLint wrapS) { _wrapS = wrapS; }
   inline void SetWrapT(GLint wrapT) { _wrapT = wrapT; }
   inline void SetMinFilter(GLint minFilter) { _minFilter = minFilter; }
   inline void SetMagFilter(GLint magFilter) { _magFilter = magFilter; }
   void ApplyFilters();

   void LoadFromFile(const string& filename);
   void LoadFromArray(unsigned char* data, unsigned int numberOfElements, 
      int width, int height, int numberOfChannels=3);
   void Select();
   void SendToGPU();
};

#endif
