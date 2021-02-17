#include "SimpleOGLRenderer.h"
#include "AbstractGraphicsObject.h"

size_t SimpleOGLRenderer::GenerateBuffer()
{
   glBindVertexArray(_vaoId);
   GLuint vbo;
   glGenBuffers(1, &vbo);
   return vbo;
}

void SimpleOGLRenderer::Render(AbstractGraphicsObject* object)
{
   glBindVertexArray(_vaoId);
   glUseProgram((GLuint)this->_shaderProgram);
   glBindBuffer(GL_ARRAY_BUFFER, (GLuint)object->GetBufferId());
   // Positions
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(
      0,
      (GLint)_positionAttribute.count,
      GL_FLOAT,
      GL_FALSE,
      (GLsizei)_positionAttribute.bytesToNext,
      (void*)_positionAttribute.offsetToFirst
   );
   // Colors
   glEnableVertexAttribArray(1);
   glVertexAttribPointer(
      1,
      (GLint)_colorAttribute.count,
      GL_FLOAT,
      GL_FALSE,
      (GLsizei)_colorAttribute.bytesToNext,
      (void*)_colorAttribute.offsetToFirst
   );

   glDrawArrays(GL_TRIANGLES, 0, (GLsizei)object->GetNumberOfElements());

   glDisableVertexAttribArray(0);
   glDisableVertexAttribArray(1);
   glUseProgram(0);
   glBindVertexArray(0);
}