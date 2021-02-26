#include "OGLGraphicsScene.h"
#include "OGLShader.h"
#include "OGLGraphicsObject.hpp"

void OGLGraphicsScene::Create()
{
   OGLShader* shader = new OGLShader();
   shader->Create();
   shader->SetPositionAttribute({ 0,  3, sizeof(VertexPC), 0 });
   shader->SetColorAttribute({ 1, 3, sizeof(VertexPC), sizeof(GLfloat) * 3 });
   AddShader("defaultShader", shader);

   OGLShader* simple3DShader = new OGLShader();
   simple3DShader->SetVertexSource(
      "#version 400\n"\
      "layout(location = 0) in vec3 position;\n"\
      "layout(location = 1) in vec3 vertexColor;\n"\
      "out vec4 fragColor;\n"\
      "uniform mat4 world;\n"\
      "uniform mat4 view;\n"\
      "uniform mat4 projection;\n"\
      "void main()\n"\
      "{\n"\
      "   gl_Position = projection * view * world * vec4(position, 1.0);\n"\
      "   fragColor = vec4(vertexColor, 1.0);\n"\
      "}\n"
   );
   simple3DShader->Create();
   simple3DShader->SetPositionAttribute({ 0,  3, sizeof(VertexPC), 0 });
   simple3DShader->SetColorAttribute({ 1, 3, sizeof(VertexPC), sizeof(GLfloat) * 3 });
   AddShader("simple3DShader", simple3DShader);


   //OGLGraphicsObject<VertexPC>* triangle = new OGLGraphicsObject<VertexPC>();
   //triangle.AddVertex({ 0,  0.5f, 0, 1, 0, 0 });
   //triangle.AddVertex({ -0.5f, -0.5f, 0, 0, 0, 1 });
   //triangle.AddVertex({ 0.5f, -0.5f, 0, 0, 1, 0 });
   //triangle.SendToGPU();
}
