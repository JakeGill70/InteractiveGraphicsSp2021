#pragma once
#ifndef ABSTRACT_TIMER
#define ABSTRACT_TIMER

#include "BaseObject.h"
class AbstractTimer :
	public BaseObject
{
public:
	AbstractTimer() {}   
	virtual ~AbstractTimer() {}   
	virtual void StartTiming() = 0;   
	virtual double GetElapsedTimeInSeconds() = 0;
};

#endif // !ABSTRACT_TIMER

