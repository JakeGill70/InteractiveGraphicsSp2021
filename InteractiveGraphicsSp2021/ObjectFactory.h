#pragma once
#ifndef OBJECT_FACTORY
#define OBJECT_FACTORY

#include "GraphicsStructures.h"
#include "AbstractTexture.h"
#include <vector>

class GraphicsObject;

class ObjectFactory
{
public:
   static GraphicsObject* PlainCuboid(float width, float height, float depth, RGB color);
   static GraphicsObject* PCNTCuboid(float width, float height, float depth, RGBA color, AbstractTexture* texture);
   static GraphicsObject* FrustumModel(std::vector<glm::vec3> corners, RGB frontColor, RGB backColor);
};

#endif

