#pragma once

#ifndef ABSTRACT_TEXTURE
#define ABSTRACT_TEXTURE
#include "BaseObject.h"

class AbstractTexture : public BaseObject
{
protected:
   int _width, _height, _numberOfChannels;
   unsigned char* _textureData;
   bool _loadedFromFile;

public:
   AbstractTexture() 
      : _width(0), _height(0), _numberOfChannels(0), 
        _textureData(nullptr), _loadedFromFile(false) {}
   virtual ~AbstractTexture() {}

   virtual void LoadFromFile(const string& filename) = 0;
   // We'll use numberOfChannels to differentiate between RGB and RGBA
   virtual void LoadFromArray(
      unsigned char* textureData, unsigned int numberOfElements, 
      int width, int height, int numberOfChannels=3) = 0;
   virtual void Select() = 0;
   virtual void SendToGPU() = 0;
};

#endif
