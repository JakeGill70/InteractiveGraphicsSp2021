#pragma once
#ifndef OBJECT_FACTORY
#define OBJECT_FACTORY

#include "GraphicsStructures.h"

class GraphicsObject;

class ObjectFactory
{
public:
   static GraphicsObject* PlainCuboid(float width, float height, float depth, RGB color);
};

#endif

