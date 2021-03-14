#pragma once
#ifndef ABSTRACT_MESH
#define ABSTRACT_MESH

#include "BaseObject.h"
#include "AbstractTexture.h"
class AbstractMesh :
   public BaseObject
{
protected:
   unsigned int _primitive;
   AbstractTexture* _texture;

public:
   AbstractMesh() : _texture(nullptr), _primitive(0) {}

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
   virtual void SetupBufferInterpretation() = 0;
   virtual void SendToGPU() = 0;
};

#endif
