#pragma once
#ifndef ABSTRACT_MESH
#define ABSTRACT_MESH

#include "BaseObject.h"
#include "AbstractTexture.h"
#include "GraphicsStructures.h"
class AbstractMesh :
   public BaseObject
{
protected:
   unsigned int _primitive;
   AbstractTexture* _texture;
   bool _hasPosition, _hasColor, _hasTexture, _hasNormal;

public:
   Material material;

public:
   AbstractMesh() 
      : _texture(nullptr), _primitive(0) {
      _hasPosition = _hasColor = _hasTexture = _hasNormal = false;
      material.ambientIntensity = 0.01f;
      material.specularIntensity = 0.5f;
      material.shininess = 16;
   }

   virtual inline void SetPrimitive(unsigned int primitive) {
      _primitive = primitive;
   }

   virtual inline unsigned int GetPrimitive() const {
      return _primitive;
   }

   inline virtual void SetTexture(AbstractTexture* texture) {
      _texture = texture;
   }

   inline virtual AbstractTexture* GetTexture() {
      return _texture;
   }

   inline virtual bool IsTextured() const {
      return _texture != nullptr;
   }

   inline virtual bool IsIndexed() const = 0;
   virtual size_t GetNumberOfElements() = 0;
   virtual size_t GetBufferId() = 0;
   virtual void SetBufferId(size_t bufferId) = 0;
   virtual size_t GetIndexedBufferId() = 0;
   virtual void SetIndexedBufferId(size_t bufferId) = 0;
   virtual void SetUpBufferInterpretation() = 0;
   virtual void SendToGPU() = 0;
};

#endif
