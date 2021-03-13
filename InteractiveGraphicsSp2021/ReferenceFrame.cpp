#include "ReferenceFrame.h"
#include <glm/ext/matrix_transform.hpp>

void ReferenceFrame::TranslateLocal(const glm::vec3& vector)
{
   orientation = glm::translate(orientation, vector);
}

void ReferenceFrame::RotateLocal(float degrees, const glm::vec3& axis)
{
   orientation = glm::rotate(orientation, glm::radians(degrees), axis);
}

void ReferenceFrame::RotateWorld(float degrees, const glm::vec3& axis)
{
   glm::mat4 mat(1.0f);
   mat = glm::rotate(mat, glm::radians(degrees), axis);
   orientation = mat * orientation;
}

void ReferenceFrame::TranslateWorld(const glm::vec3& vector)
{
   glm::mat4 mat(1.0f);
   mat[3] = glm::vec4(vector, 1.0f);
   orientation = mat * orientation;
}
