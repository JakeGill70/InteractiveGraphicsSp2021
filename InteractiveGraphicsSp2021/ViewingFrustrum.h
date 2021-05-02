#pragma once
#ifndef VIEWING_FRUSTRUM
#define VIEWING_FRUSTRUM

#include "BaseObject.h"
#include "ReferenceFrame.h"
#include "GeometricPlane.h"

class ViewingFrustrum :
	public BaseObject
{
protected:
	int frontWidth, frontHeight;
	int backWidth, backHeight;
	int depth;
	GeometricPlane planes[6];
public:
	ReferenceFrame frame;
	ViewingFrustrum(float fw, float fh, float bw, float bh, float depth);
	void Set(float fw, float fh, float bw, float bh, float depth);
	void Create();
	bool hasSphereInside(BoundingSphere sphere);
	bool hasPointInside(glm::vec3 point);
};

#endif // !VIEWING_FRUSTRUM
