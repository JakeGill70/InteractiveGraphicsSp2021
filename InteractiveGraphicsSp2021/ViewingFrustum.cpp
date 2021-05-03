#include "ViewingFrustum.h"

ViewingFrustum::ViewingFrustum(float fw, float fh, float bw, float bh, float depth)
{
	Set(fw, fh, bw, bh, depth);
	Create();
}

void ViewingFrustum::Set(float fw, float fh, float bw, float bh, float depth) {
	frontWidth = fw;
	frontHeight = fh;
	backWidth = bw;
	backHeight = bh;
	this->depth = depth;
}

void ViewingFrustum::Create() {
	float halfFrontWidth = frontWidth / 2;
	float halfFrontHeight = frontHeight / 2;
	float halfBackWidth = backWidth / 2;
	float halfBackHeight = backHeight / 2;

	glm::vec3 ulf = { halfFrontWidth, halfFrontHeight, 0 };
	glm::vec3 llf = { halfFrontWidth, -halfFrontHeight, 0 };
	glm::vec3 lrf = { -halfFrontWidth, -halfFrontHeight, 0 };
	glm::vec3 urf = { -halfFrontWidth,  halfFrontHeight, 0 };
	glm::vec3 ulb = { halfBackWidth,  halfBackHeight, depth };
	glm::vec3 llb = { halfBackWidth, -halfBackHeight, depth };
	glm::vec3 lrb = { -halfBackWidth, -halfBackHeight, depth };
	glm::vec3 urb = { -halfBackWidth,  halfBackHeight, depth };

	// Transform each point to the camera�s 
	// orientation
	glm::vec3 F1 = frame.Transform(ulf);
	glm::vec3 F2 = frame.Transform(llf);
	glm::vec3 F3 = frame.Transform(lrf);
	glm::vec3 F4 = frame.Transform(urf);

	glm::vec3 B1 = frame.Transform(ulb);
	glm::vec3 B2 = frame.Transform(llb);
	glm::vec3 B3 = frame.Transform(lrb);
	glm::vec3 B4 = frame.Transform(urb);

	planes[0].Set(frame.GetZAxis(), F3); // Front
	planes[1].Set(-frame.GetZAxis(), B2); // Back
	planes[2].Set(F1, F2, B2); // Left
	planes[3].Set(B4, B3, F3); // Right
	planes[4].Set(F1, B1, B4); // Top
	planes[5].Set(B2, F2, F3); // Bottom
}

bool ViewingFrustum::hasSphereInside(BoundingSphere sphere)
{
	for (int i = 0; i < 5; i++)
	{
		if (!planes[i].IsSphereInFront(sphere)) {
			return false;
		}
	}
	return true;
}

bool ViewingFrustum::hasPointInside(glm::vec3 point)
{
	for (int i = 0; i < 5; i++)
	{
		if (!planes[i].IsPointInFront(point)) {
			return false;
		}
	}
	return true;
}

