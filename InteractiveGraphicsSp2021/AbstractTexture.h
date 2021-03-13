#pragma once

#ifndef ABSTRACT_TEXTURE
#define ABSTRACT_TEXTURE
#include "BaseObject.h"

class AbstractTexture : public BaseObject
{
protected:
   int _width, _height;
   unsigned char* _textureData;
   bool _loadedFromFile;

public:
   AbstractTexture() : _width(0), _height(0), _textureData(nullptr), _loadedFromFile(false) {}
   virtual ~AbstractTexture() {}

   virtual void LoadFromFile(const string& filename) = 0;
   virtual void LoadFromArray(unsigned char* textureData, unsigned int size, int width, int height) = 0;
   virtual void Select() = 0;
   virtual void Setup() = 0;
};

#endif
