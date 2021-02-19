#pragma once
#ifndef OGL_SHADER
#define OGL_SHADER

#include <string>
using std::string;
#include "AbstractShader.h"
#include <glad/glad.h>

class OGLShader :
    public AbstractShader
{
private:
   GLuint _vaoId;
   struct VertexAttribute {
      int index;
      int count;
      size_t bytesToNext;
      size_t offsetToFirst;
   } _positionAttribute, _colorAttribute;
   string _vertexSource;
   string _fragmentSource;

public:
   OGLShader();

   ~OGLShader(){
      glDeleteVertexArrays(1, &_vaoId);
   }

   inline void SetPositionAttribute(VertexAttribute pa) {
      this->_positionAttribute = pa;
   }

   inline void SetColorAttribute(VertexAttribute ca) {
      this->_colorAttribute = ca;
   }

   inline void Select() {
      glBindVertexArray(_vaoId);
   }

   inline void SelectProgram() {
      glUseProgram(_shaderProgram);
   }

   inline void SetVertexSource(string source) {
      _vertexSource = source;
   }

   size_t GenerateBuffer();

   void Render(AbstractGraphicsObject* object);
   bool Create();
   void SendMatrixToGPU(const string& name, const glm::mat4& matrix);

protected:
   void SetDefaultSource();
   void SetUpBufferInterpretation();
   GLuint Compile(GLenum type, const GLchar* source);
   GLuint Link(GLuint vertexShader, GLuint fragmentShader);
   void LogError(GLuint shader, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog);
};




#endif

