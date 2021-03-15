#include "AbstractGraphicsObject.h"
#include "AbstractAnimation.h"

void AbstractGraphicsObject::Update(double elapsedSeconds) {
    if (_animation) {
        _animation->Update(elapsedSeconds);
    }
}

void AbstractGraphicsObject::SetAnimation(AbstractAnimation* animation) {
    _animation = animation;
    _animation->SetObject(this);
}