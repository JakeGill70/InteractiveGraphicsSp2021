#include "FollowAnimation.h"
#include "ReferenceFrame.h"
#include "GraphicsObject.h"

void FollowAnimation::Update(double elapsedSeconds)
{
	if (_object == nullptr || _leader == nullptr || !_isFollowing) return;

	_object->frame.SetPosition(_leader->GetPosition());
	_object->frame.orientation = _leader->orientation;
	_object->frame.RotateLocal(180, { 0,1,0 });
}
