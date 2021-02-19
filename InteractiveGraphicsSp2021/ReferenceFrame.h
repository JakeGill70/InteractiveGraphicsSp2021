#pragma once
#ifndef REFERENCE_FRAME
#define REFERENCE_FRAME

#include <glm\glm.hpp>

#include "BaseObject.h"

class ReferenceFrame :
    public BaseObject
{
public:
   glm::mat4 orientation;

public:
   ReferenceFrame() : orientation(1.0f) {}
   ~ReferenceFrame() {}

   inline void SetPosition(float x, float y, float z) {
      orientation[3] = glm::vec4(x, y, z, 1.0f);
   }

   inline void SetPosition(const glm::vec3& pos) {
      orientation[3] = glm::vec4(pos, 1.0f);
   }

   inline glm::vec3 GetPosition() const { return glm::vec3(orientation[3]); }
   inline glm::vec3 GetXAxis() const { return glm::vec3(orientation[0]); }
   inline glm::vec3 GetYAxis() const { return glm::vec3(orientation[1]); }
   inline glm::vec3 GetZAxis() const { return glm::vec3(orientation[2]); }
};

#endif

