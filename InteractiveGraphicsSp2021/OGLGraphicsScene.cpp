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


   OGLGraphicsObject<VertexPC>* triangle = new OGLGraphicsObject<VertexPC>();
   AddGraphicsObject("triangle", triangle, "defaultShader");
   triangle->AddVertex({  0.0f,  0.5f, 0, 1, 0, 0 });
   triangle->AddVertex({ -0.5f, -0.5f, 0, 0, 0, 1 });
   triangle->AddVertex({  0.5f, -0.5f, 0, 0, 1, 0 });
   triangle->SendToGPU();

   OGLGraphicsObject<VertexPC>* cube = new OGLGraphicsObject<VertexPC>();
   AddGraphicsObject("cube", cube, "simple3DShader");
   // Red vertices
   VertexPC V1 = { -0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f };
   VertexPC V2 = { -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f };
   VertexPC V3 = { 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f };
   VertexPC V4 = { 0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f };
   // Mixed color vertices
   VertexPC V5 = { 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f };
   VertexPC V6 = { 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f };
   VertexPC V7 = { -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f };
   VertexPC V8 = { -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f };
   // Face 1
   cube->AddVertex(V1);
   cube->AddVertex(V2);
   cube->AddVertex(V3);
   cube->AddVertex(V1);
   cube->AddVertex(V3);
   cube->AddVertex(V4);
   // Face 2
   cube->AddVertex(V4);
   cube->AddVertex(V3);
   cube->AddVertex(V6);
   cube->AddVertex(V4);
   cube->AddVertex(V6);
   cube->AddVertex(V5);
   // Face 3
   cube->AddVertex(V5);
   cube->AddVertex(V6);
   cube->AddVertex(V7);
   cube->AddVertex(V5);
   cube->AddVertex(V7);
   cube->AddVertex(V8);
   // Face 4
   cube->AddVertex(V8);
   cube->AddVertex(V7);
   cube->AddVertex(V2);
   cube->AddVertex(V8);
   cube->AddVertex(V2);
   cube->AddVertex(V1);
   // Face 5
   cube->AddVertex(V6);
   cube->AddVertex(V3);
   cube->AddVertex(V2);
   cube->AddVertex(V6);
   cube->AddVertex(V2);
   cube->AddVertex(V7);
   // Face 6
   cube->AddVertex(V8);
   cube->AddVertex(V1);
   cube->AddVertex(V4);
   cube->AddVertex(V8);
   cube->AddVertex(V4);
   cube->AddVertex(V5);
   cube->SendToGPU();

   BaseCamera* camera = new BaseCamera();
   camera->frame.SetPosition(3, 3, 3);
   camera->UpdateView();
   AddCamera("camera", camera);

   _shaders["simple3DShader"]->SetCamera(camera);
}
