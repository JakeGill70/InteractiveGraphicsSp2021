#pragma once
#ifndef ABSTRACT_GRAPHICS_OBJECT
#define ABSTRACT_GRAPHICS_OBJECT

#include "BaseObject.h"
#include "ReferenceFrame.h"
#include "AbstractTexture.h"
#include "BoundingSphere.h"
class AbstractAnimation;
#include "AbstractMesh.h"
#include <vector>
using std::vector;

class GraphicsObject : 
   public BaseObject
{
protected:

   AbstractAnimation* _animation;
   vector<AbstractMesh*> _meshes;

public:
   ReferenceFrame frame;
   bool isVisible;
   BoundingSphere boundingSphere;
   bool isStaticObject;

public:
   GraphicsObject() : _animation(nullptr), isVisible(true), isStaticObject(false){}

   virtual ~GraphicsObject();

   virtual inline AbstractMesh* GetMesh(int index)
   {
      return _meshes[index];
   }

   virtual inline vector<AbstractMesh*>& GetMeshes() {
      return _meshes;
   }

   inline void AddMesh(AbstractMesh* mesh)
   {
      _meshes.push_back(mesh);
   }

   virtual inline void SetAnimation(AbstractAnimation* animation);

   virtual inline AbstractAnimation* GetAnimation();

   virtual void Update(double elapsedSeconds);

   virtual void SendToGPU();
};
#endif
