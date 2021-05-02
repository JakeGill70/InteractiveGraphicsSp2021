#include "GeometricPlane.h"

GeometricPlane::GeometricPlane()
{
}

GeometricPlane::GeometricPlane(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
	Set(p1, p2, p3);
}

GeometricPlane::GeometricPlane(glm::vec3 normal, glm::vec3 p) {
	Set(normal, p);
}

GeometricPlane::GeometricPlane(glm::vec3 normal, float d) {
	this->normal = normal;
	this->distance = d;
}

void GeometricPlane::Set(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
	glm::vec3 v1 = p2 - p1;
	glm::vec3 v2 = p3 - p1;
	normal = glm::normalize(v1 * v2);
	distance = -glm::dot(p1, normal);
}

void GeometricPlane::Set(glm::vec3 normal, glm::vec3 p) {
	this->normal = glm::normalize(normal);
	distance = -glm::dot(p, this->normal);
}