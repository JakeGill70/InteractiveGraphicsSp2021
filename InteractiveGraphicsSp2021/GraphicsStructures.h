#pragma once
#ifndef GRAPHICS_STRUCTURES
#define GRAPHICS_STRUCTURES
#include <glad/glad.h>
#include <glm\glm.hpp>

struct Vector3D {
   GLfloat x, y, z;
};

struct RGB {
   GLfloat red, green, blue;
};

struct VertexPC {
   Vector3D position;
   RGB color;
};

struct RGBA {
   GLfloat red, green, blue, alpha;
};

struct TexCoord {
   GLfloat S, T;
};

struct VertexPCT {
   Vector3D position;
   RGBA color;
   TexCoord tex;
};

struct VertexPCNT {
   Vector3D position;
   RGBA color;
   Vector3D normal;
   TexCoord tex;
};

struct Material {
   float ambientIntensity;
};

struct Light {
   glm::vec3 position;
   glm::vec3 color;
   float intensity;
   float attenuationCoefficient;
};

#endif
