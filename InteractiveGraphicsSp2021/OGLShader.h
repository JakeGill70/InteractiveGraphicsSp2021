#pragma once
#ifndef OGL_SHADER
#define OGL_SHADER

#include <string>
using std::string;
#include "AbstractShader.h"
#include <glad/glad.h>

class BaseCamera;

class OGLShader :
    public AbstractShader
{
private:
   GLuint _vaoId;

   string _vertexSource;
   string _fragmentSource;

public:
   OGLShader();

   ~OGLShader(){
      glDeleteVertexArrays(1, &_vaoId);
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

   inline void SetFragmentSource(string source) {
      _fragmentSource = source;
   }

   size_t GenerateBuffer();

   void RenderObjects();
   void Render(GraphicsObject* object);
   bool Create();
   void SendMatrixToGPU(const string& name, const glm::mat4& matrix);

protected:
   void SetDefaultSource();
   GLuint Compile(GLenum type, const GLchar* source);
   GLuint Link(GLuint vertexShader, GLuint fragmentShader);
   void LogError(GLuint shader, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog);
   void SendGPUData();
};




#endif

