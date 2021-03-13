#include "OGLTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

OGLTexture::OGLTexture() :
   AbstractTexture(), _id(0)
{
   _wrapS = _wrapT = GL_REPEAT;
   _minFilter = _magFilter = GL_NEAREST;
}

OGLTexture::~OGLTexture()
{
}

void OGLTexture::LoadFromFile(const string& filename)
{
   // https://github.com/nothings/stb
   int width, height, nrChannels;
   stbi_set_flip_vertically_on_load(true);
   _textureData = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
   if (_textureData) {
      _width = width;
      _height = height;
      _loadedFromFile = true;
   }
   else {
      _log << "Could not load texture: " << filename;
   }
}

void OGLTexture::LoadFromArray(unsigned char* data, unsigned int size, int width, int height)
{
   _width = width;
   _height = height;
   _textureData = new unsigned char[size];
   for (unsigned int i = 0; i < size; i++) {
      _textureData[i] = data[i];
   }
   _loadedFromFile = false;
}

void OGLTexture::Select()
{
   glBindTexture(GL_TEXTURE_2D, _id);
}

void OGLTexture::Setup()
{
   if (_textureData != nullptr) {
      glGenTextures(1, &_id);
      glBindTexture(GL_TEXTURE_2D, _id);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrapS);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrapT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minFilter);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _magFilter);
      glGenerateMipmap(GL_TEXTURE_2D);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _textureData);
      if (_loadedFromFile) {
         stbi_image_free(_textureData);
      }
      else {
         delete[] _textureData;
      }
      _textureData = nullptr;
   }
}

