#include "RotateAnimation.h"
#include "ReferenceFrame.h"
#include "GraphicsObject.h"

void RotateAnimation::Update(double elapsedSeconds) {
   if (_object == nullptr) return;
   float degreesToRotate = _degreesPerSecond * (float)elapsedSeconds;
   _object->frame.RotateLocal(degreesToRotate, _axis);
}
