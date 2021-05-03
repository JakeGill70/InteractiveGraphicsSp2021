#pragma once
#ifndef VIEWING_FRUSTRUM
#define VIEWING_FRUSTRUM

#include "BaseObject.h"
#include "ReferenceFrame.h"
#include "GeometricPlane.h"
#include <vector>

class ViewingFrustum :
	public BaseObject
{
protected:
	float frontWidth, frontHeight;
	float backWidth, backHeight;
	float depth;
	GeometricPlane planes[6];
public:
	ReferenceFrame frame;
	ViewingFrustum(float fw, float fh, float bw, float bh, float depth);
	void Set(float fw, float fh, float bw, float bh, float depth);
	void Create();
	bool hasSphereInside(BoundingSphere sphere);
	bool hasPointInside(glm::vec3 point);
};

#endif // !VIEWING_FRUSTRUM
