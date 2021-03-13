#pragma once
#ifndef GRAPHICS_STRUCTURES
#define GRAPHICS_STRUCTURES
#include <glad/glad.h>

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

#endif
