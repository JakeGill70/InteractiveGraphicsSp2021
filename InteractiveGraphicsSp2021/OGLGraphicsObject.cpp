#include "OGLGraphicsObject.h"

void OGLGraphicsObject::SendToGPU()
{
   _renderer->Select();
   // Bind the object to the binding target
   glBindBuffer(GL_ARRAY_BUFFER, _vboId);
   // Allocate memory in the GPU for the buffer bound to the binding target and then
   // copy the data
   glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);
   // Good practice to cleanup by unbinding 
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0);
}
