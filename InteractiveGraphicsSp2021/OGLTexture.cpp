#include "OGLTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

OGLTexture::OGLTexture() :
   AbstractTexture(), _id(0)
{
   _wrapS = _wrapT = GL_REPEAT;
   _minFilter = _magFilter = GL_LINEAR;
   glGenTextures(1, &_id);
}

OGLTexture::~OGLTexture()
{
   if(_textureData) delete[] _textureData;
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
      _numberOfChannels = nrChannels;
      _loadedFromFile = true;
   }
   else {
      _log << "Could not load texture: " << filename;
   }
}

void OGLTexture::LoadFromArray(unsigned char* data, unsigned int numberOfElements,
   int width, int height, int numberOfChannels)
{
   _width = width;
   _height = height;
   _numberOfChannels = numberOfChannels;
   _textureData = new unsigned char[numberOfElements];
   for (unsigned int i = 0; i < numberOfElements; i++) {
      _textureData[i] = data[i];
   }
   _loadedFromFile = false;
}

void OGLTexture::Select()
{
   glBindTexture(GL_TEXTURE_2D, _id);
}

void OGLTexture::SendToGPU()
{
   if (_textureData != nullptr) {
      ApplyFilters();
      glBindTexture(GL_TEXTURE_2D, _id);
      GLenum internalTextureFormat = GL_SRGB, sourceFormat = GL_RGB;
      if (_numberOfChannels == 4) {
         internalTextureFormat = GL_SRGB_ALPHA;
         sourceFormat = GL_RGBA;
      }
      // Send the texture data
      glTexImage2D(GL_TEXTURE_2D, 
         0, internalTextureFormat, _width, _height, 
         0, sourceFormat, GL_UNSIGNED_BYTE, _textureData);
      glGenerateMipmap(GL_TEXTURE_2D);
      // We don't need the texture data anymore
      if (_loadedFromFile) {
         stbi_image_free(_textureData);
      }
      else {
         delete[] _textureData;
      }
      _textureData = nullptr;
   }
}

void OGLTexture::ApplyFilters()
{
   glBindTexture(GL_TEXTURE_2D, _id);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrapS);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrapT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minFilter);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _magFilter);
}

