#include "OGLShader.h"
#include "GraphicsObject.h"
#include <glm/gtc/type_ptr.hpp>
#include "BaseCamera.h"
#include "AbstractTexture.h"
#include "AbstractMesh.h"

OGLShader::OGLShader() : AbstractShader(), _vaoId(0)
{

   glGenVertexArrays(1, &_vaoId);
   SetDefaultSource();
}

size_t OGLShader::GenerateBuffer()
{
   glBindVertexArray(_vaoId);
   GLuint buffer;
   glGenBuffers(1, &buffer);
   return buffer;
}

void OGLShader::SendGPUData()
{
   if (_camera != nullptr) {
      SendMatrixToGPU("view", _camera->GetView());
      SendMatrixToGPU("projection", _camera->GetProjection());
   }
}

void OGLShader::RenderObjects()
{
   SelectProgram();
   SendGPUData();
   for (auto iterator = _objectsToRender.begin(); 
      iterator != _objectsToRender.end(); 
      iterator++) {
      GraphicsObject* object = iterator->second;
      SelectProgram();
      SendMatrixToGPU("world", object->frame.orientation);
      Render(object);
   }
}

void OGLShader::Render(GraphicsObject* object)
{
   glBindVertexArray(_vaoId);
   glUseProgram((GLuint)_shaderProgram);
   vector<AbstractMesh*> meshes = object->GetMeshes();
   AbstractMesh* mesh;
   GLuint vbo;
   for (auto it = meshes.begin(); it != meshes.end(); it++) {
      mesh = *it;
      SendFloatToGPU("materialAmbientIntensity", mesh->material.ambientIntensity);
      vbo = (GLuint)mesh->GetBufferId();
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      if (mesh->IsTextured()) {
         mesh->GetTexture()->Select();
      }
      mesh->SetUpBufferInterpretation();
      if (!mesh->IsIndexed()) {
         glDrawArrays(mesh->GetPrimitive(), 0, (GLsizei)mesh->GetNumberOfElements());
      }
      else {
         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (GLuint)mesh->GetIndexedBufferId());
         glDrawElements(mesh->GetPrimitive(), (GLsizei)mesh->GetNumberOfElements(),
            GL_UNSIGNED_SHORT, 0);
      }
   }

   glDisableVertexAttribArray(0);
   glDisableVertexAttribArray(1);
   glUseProgram(0);
   glBindVertexArray(0);
}

void OGLShader::SetDefaultSource()
{
   _vertexSource =
      "#version 400\n"\
      "layout(location = 0) in vec3 position;\n"\
      "layout(location = 1) in vec3 vertexColor;\n"\
      "out vec4 fragColor;\n"\
      "void main()\n"\
      "{\n"\
      "   gl_Position = vec4(position, 1.0);\n" \
      "   fragColor = vec4(vertexColor, 1.0);\n" \
      "}\n";

   _fragmentSource =
      "#version 400\n"\
      "in vec4 fragColor;\n"\
      "out vec4 color;\n"\
      "void main()\n"\
      "{\n"\
      "   color = fragColor;\n"\
      "}\n";
}



bool OGLShader::Create()
{
   GLuint vertexShader =
      Compile(GL_VERTEX_SHADER, _vertexSource.c_str());
   if (vertexShader == 0) return false;
   GLuint fragmentShader =
      Compile(GL_FRAGMENT_SHADER, _fragmentSource.c_str());
   if (fragmentShader == 0) return false;
   _shaderProgram = Link(vertexShader, fragmentShader);
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);
   if (_shaderProgram == 0) return false;
   return true;
}

void OGLShader::SendMatrixToGPU(const string& name, const glm::mat4& matrix)
{
   unsigned int uniformLocation = glGetUniformLocation(_shaderProgram, name.c_str());
   glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

GLuint OGLShader::Compile(GLenum type, const GLchar* source)
{
   GLint length = (GLint)(sizeof(GLchar) * strlen(source));
   GLuint shader = glCreateShader(type);
   glShaderSource(shader, 1, (const GLchar**)&source, &length);
   glCompileShader(shader);
   GLint shaderOk = 0;
   glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderOk);
   if (!shaderOk) {
      LogError(shader, glGetShaderiv, glGetShaderInfoLog);
      glDeleteShader(shader);
      shader = 0;
   }
   return shader;
}

GLuint OGLShader::Link(GLuint vertexShader, GLuint fragmentShader)
{
   GLuint program = glCreateProgram();
   glAttachShader(program, vertexShader);
   glAttachShader(program, fragmentShader);
   glLinkProgram(program);
   GLint programOk = 0;
   glGetProgramiv(program, GL_LINK_STATUS, &programOk);
   if (!programOk) {
      LogError(program, glGetProgramiv, glGetProgramInfoLog);
      glDeleteShader(program);
      program = 0;
   }
   return program;
}

void OGLShader::LogError(GLuint shader, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog)
{
   GLint logLength;
   glGet__iv(shader, GL_INFO_LOG_LENGTH, &logLength);
   char* info = (char*)malloc(logLength);
   glGet__InfoLog(shader, logLength, NULL, info);
   Log(info);
   free(info);
}

void OGLShader::SendFloatToGPU(const string& name, float data) const
{
    unsigned int location = glGetUniformLocation(_shaderProgram, name.c_str());
    glUniform1f(location, data);
}
