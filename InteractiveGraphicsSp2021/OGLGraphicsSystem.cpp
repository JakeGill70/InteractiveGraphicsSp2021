#include "OGLGraphicsSystem.h"
#include <glad/glad.h>

void OGLGraphicsSystem::Initialize()
{
   // Cull back faces and use counter-clockwise winding of front faces
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);
   glFrontFace(GL_CCW);

   //Enable depth testing
   glEnable(GL_DEPTH_TEST);
   glDepthMask(GL_TRUE);
   glDepthFunc(GL_LEQUAL);
   glDepthRange(0.0f, 1.0f);
}
