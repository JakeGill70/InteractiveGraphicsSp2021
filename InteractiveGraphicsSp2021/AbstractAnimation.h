#pragma once
#ifndef ABSTRACT_ANIMATION
#define ABSTRACT_ANIMATION

#include "BaseObject.h"

class AbstractGraphicsObject;

class AbstractAnimation :
	public BaseObject
{
protected:
	AbstractGraphicsObject* _object;
public:
	void SetObject(AbstractGraphicsObject* obj);
	virtual void Update(double elapsedSeconds)=0;
};

#endif // !ABSTRACT_ANIMATION
