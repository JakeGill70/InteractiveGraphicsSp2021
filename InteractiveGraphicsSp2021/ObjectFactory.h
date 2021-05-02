#pragma once
#ifndef OBJECT_FACTORY
#define OBJECT_FACTORY

#include "GraphicsStructures.h"
#include "AbstractTexture.h"

class GraphicsObject;

class ObjectFactory
{
public:
   static GraphicsObject* PlainCuboid(float width, float height, float depth, RGB color);
   static GraphicsObject* PCNTCuboid(float width, float height, float depth, RGBA color, AbstractTexture* texture);
};

#endif

