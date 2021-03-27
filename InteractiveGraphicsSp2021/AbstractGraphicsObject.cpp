#include "GraphicsObject.h"
#include "AbstractAnimation.h"
#include "AbstractMesh.h"

GraphicsObject::~GraphicsObject()
{
   if (_animation) delete _animation;
   for (auto it = _meshes.begin(); it != _meshes.end(); it++) {
      delete *it;
   }
   _meshes.clear();
}

inline void GraphicsObject::SetAnimation(AbstractAnimation* animation)
{
   _animation = animation;
   _animation->SetObject(this);
}

void GraphicsObject::Update(double elapsedSeconds)
{
   if (_animation == nullptr) return;
   _animation->Update(elapsedSeconds);
}

void GraphicsObject::SendToGPU()
{
   AbstractMesh* mesh;
   for (auto it = this->_meshes.begin(); it != this->_meshes.end(); it++) {
      mesh = *it;
      mesh->SendToGPU();
   }
}
