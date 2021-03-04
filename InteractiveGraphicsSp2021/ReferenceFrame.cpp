#include "ReferenceFrame.h"
#include <glm/ext/matrix_transform.hpp>

void ReferenceFrame::TranslateLocal(const glm::vec3& vector)
{
   orientation = glm::translate(orientation, vector);
}
