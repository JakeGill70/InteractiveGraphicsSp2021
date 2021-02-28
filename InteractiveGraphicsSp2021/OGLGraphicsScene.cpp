#include "OGLGraphicsScene.h"
#include "OGLShader.h"
#include "OGLGraphicsObject.hpp"
#include "TextFileReader.h"

OGLGraphicsScene::~OGLGraphicsScene()
{
   delete _sceneReader;
}

bool OGLGraphicsScene::Create()
{
   _sceneReader->Open();
   _sceneReader->Read();
   if (_sceneReader->HasError()) {
      return false;
   }
   _sceneReader->Close();

   vector<CameraData>& cameraData = _sceneReader->GetCameraData();
   BaseCamera* camera = new BaseCamera();
   camera->frame.SetPosition(
      cameraData[0].position.x, cameraData[0].position.y, cameraData[0].position.z);
   camera->fieldOfView = cameraData[0].fov;
   camera->nearPlane = cameraData[0].nearPlane;
   camera->farPlane = cameraData[0].farPlane;
   camera->UpdateView();
   AddCamera(cameraData[0].name, camera);

   if (!ReadShaderData()) return false;

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
  
   return true;
}

bool OGLGraphicsScene::ReadShaderData()
{
   vector<ShaderData>& shaderData = _sceneReader->GetShaderData();
   for (size_t i = 0; i < shaderData.size(); i++) {
      OGLShader* shader = new OGLShader();
      if (shaderData[i].vertexShaderFilePath != "default") {
         _textFileReader->SetFilePath(shaderData[i].vertexShaderFilePath);
         _textFileReader->Open();
         _textFileReader->Read();
         _textFileReader->Close();
         if (_textFileReader->HasError()) {
            return false;
         }
         shader->SetVertexSource(_textFileReader->GetContents());
      }
      if (shaderData[i].fragmentShaderFilePath != "default") {
         _textFileReader->SetFilePath(shaderData[i].fragmentShaderFilePath);
         _textFileReader->Open();
         _textFileReader->Read();
         _textFileReader->Close();
         if (_textFileReader->HasError()) {
            return false;
         }
         shader->SetFragmentSource(_textFileReader->GetContents());
      }
      if (!shader->Create()) {
         return false;
      }
      shader->SetPositionAttribute({ 0,  3, sizeof(VertexPC), 0 });
      shader->SetColorAttribute({ 1, 3, sizeof(VertexPC), sizeof(GLfloat) * 3 });
      AddShader(shaderData[i].name, shader);
      if (shaderData[i].cameraName != "none") {
         _shaders[shaderData[i].name]->SetCamera(_cameras[shaderData[i].cameraName]);
      }
   }

   return true;
}

