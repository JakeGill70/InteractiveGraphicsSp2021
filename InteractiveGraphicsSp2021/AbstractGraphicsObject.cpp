#include "AbstractGraphicsObject.h"
#include "AbstractAnimation.h"

AbstractGraphicsObject::~AbstractGraphicsObject()
{
   if (_animation) delete _animation;
}

inline void AbstractGraphicsObject::SetAnimation(AbstractAnimation* animation)
{
   _animation = animation;
   _animation->SetObject(this);
}

void AbstractGraphicsObject::Update(double elapsedSeconds)
{
   if (_animation == nullptr) return;
   _animation->Update(elapsedSeconds);
}
