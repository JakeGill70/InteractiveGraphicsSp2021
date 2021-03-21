#pragma once
#ifndef OGL_SHADER
#define OGL_SHADER

#include <string>
using std::string;
#include "AbstractShader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

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
   void SendFloatToGPU(const string& name, float data) const
   {
      unsigned int location = glGetUniformLocation(_shaderProgram, name.c_str());
      glUniform1f(location, data);
   }

   void SendVec3ToGPU(const string& name, const glm::vec3& vector) const
   {
      unsigned int location = glGetUniformLocation(_shaderProgram, name.c_str());
      glUniform3fv(location, 1, glm::value_ptr(vector));
   }

   void SendGlobalLightToGPU(const Light& globalLight) const
   {
      SendVec3ToGPU("globalLightPosition", globalLight.position);
      SendVec3ToGPU("globalLightColor", globalLight.color);
      SendFloatToGPU("globalLightIntensity", globalLight.intensity);
   }

   void SendLocalLightToGPU(const Light& localLight) const
   {
      SendVec3ToGPU("localLightPosition", localLight.position);
      SendVec3ToGPU("localLightColor", localLight.color);
      SendFloatToGPU("localLightIntensity", localLight.intensity);
   }

protected:
   void SetDefaultSource();
   GLuint Compile(GLenum type, const GLchar* source);
   GLuint Link(GLuint vertexShader, GLuint fragmentShader);
   void LogError(GLuint shader, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog);
   void SendGPUData();
};




#endif

