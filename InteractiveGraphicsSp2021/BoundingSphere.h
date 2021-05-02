#pragma once
#ifndef BOUNDING_SPHERE
#define BOUNDING_SPHERE

#include "BaseObject.h"
#include <glm/glm.hpp>
class BoundingSphere :
	public BaseObject
{
public:
	glm::vec3 position;
	float radius;
};

#endif // !BOUNDING_SPHERE
