#pragma once
#ifndef GRAPHICS_SYSTEM
#define GRAPHICS_SYSTEM

#include "BaseObject.h"

class GraphicsSystem :
    public BaseObject
{
public:
   virtual void Initialize() = 0;
};

#endif

