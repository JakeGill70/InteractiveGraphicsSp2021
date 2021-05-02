#pragma once
#ifndef GEOMETRIC_PLANE
#define GEOMETRIC_PLANE

#include "BaseObject.h"
#include <glm/glm.hpp>
#include "BoundingSphere.h"

class GeometricPlane :
	public BaseObject
{
protected:
	glm::vec3 normal;
	float distance;
public:
	GeometricPlane();
	GeometricPlane(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
	GeometricPlane(glm::vec3 normal, glm::vec3 p);
	GeometricPlane(glm::vec3 normal, float d);
	void Set(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
	void Set(glm::vec3 normal, glm::vec3 p);
	bool IsPointInFront(glm::vec3 point);
	bool IsSphereInFront(BoundingSphere sphere);
};

#endif // !GEOMETRIC_PLANE
