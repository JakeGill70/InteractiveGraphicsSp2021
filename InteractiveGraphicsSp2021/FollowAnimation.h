#pragma once
#ifndef FOLLOW_ANIMATION
#define FOLLOE_ANIMATION

#include "AbstractAnimation.h"
#include "ReferenceFrame.h"

class FollowAnimation :
	public AbstractAnimation
{
protected:
	ReferenceFrame* _leader;
	bool _isFollowing;

public:
	FollowAnimation() : _leader(nullptr), _isFollowing(false) {};
	FollowAnimation(ReferenceFrame* leader) : _leader(leader), _isFollowing(true) {};

	void Update(double elapsedSeconds);

	inline void setFollowing(bool f) { _isFollowing = f; }
};


#endif // !FOLLOW_ANIMATION
