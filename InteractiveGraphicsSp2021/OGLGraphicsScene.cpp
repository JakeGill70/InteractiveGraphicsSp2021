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

   //OGLGraphicsObject<VertexPC>* triangle = new OGLGraphicsObject<VertexPC>();
   //AddGraphicsObject("triangle", triangle, "defaultShader");
   //triangle->AddVertexData({  0.0f,  0.5f, 0, 1, 0, 0 });
   //triangle->AddVertexData({ -0.5f, -0.5f, 0, 0, 0, 1 });
   //triangle->AddVertexData({  0.5f, -0.5f, 0, 0, 1, 0 });
   //triangle->SendToGPU();

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
   cube->AddVertexData(V1);
   cube->AddVertexData(V2);
   cube->AddVertexData(V3);
   cube->AddVertexData(V1);
   cube->AddVertexData(V3);
   cube->AddVertexData(V4);
   
   // Face 2
   cube->AddVertexData(V4);
   cube->AddVertexData(V3);
   cube->AddVertexData(V6);
   cube->AddVertexData(V4);
   cube->AddVertexData(V6);
   cube->AddVertexData(V5);
   
   // Face 3
   cube->AddVertexData(V5);
   cube->AddVertexData(V6);
   cube->AddVertexData(V7);
   cube->AddVertexData(V5);
   cube->AddVertexData(V7);
   cube->AddVertexData(V8);
   
   // Face 4
   cube->AddVertexData(V8);
   cube->AddVertexData(V7);
   cube->AddVertexData(V2);
   cube->AddVertexData(V8);
   cube->AddVertexData(V2);
   cube->AddVertexData(V1);
   
   // Face 5
   cube->AddVertexData(V6);
   cube->AddVertexData(V3);
   cube->AddVertexData(V2);
   cube->AddVertexData(V6);
   cube->AddVertexData(V2);
   cube->AddVertexData(V7);
   
   // Face 6
   cube->AddVertexData(V8);
   cube->AddVertexData(V1);
   cube->AddVertexData(V4);
   cube->AddVertexData(V8);
   cube->AddVertexData(V4);
   cube->AddVertexData(V5);
   cube->frame.TranslateLocal(glm::vec3(-2, 0, 0));
   cube->SendToGPU();

   OGLGraphicsObject<VertexPC>* indexedCube = new OGLGraphicsObject<VertexPC>();
   AddGraphicsObject("indexedCube", indexedCube, "simple3DShader", true);
   // Yellow vertices
   indexedCube->AddVertexData({ -0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 0.0f }); // 0
   indexedCube->AddVertexData({ -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f }); // 1
   indexedCube->AddVertexData({  0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f }); // 2
   indexedCube->AddVertexData({  0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 0.0f }); // 3
   // Mixed color vertices
   indexedCube->AddVertexData({  0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f }); // 4
   indexedCube->AddVertexData({  0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f }); // 5
   indexedCube->AddVertexData({ -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f }); // 6
   indexedCube->AddVertexData({ -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f }); // 7
   unsigned short indices[] = {
      0, 1, 2, 0, 2, 3, // Front face
      3, 2, 5, 3, 5, 4, // Right face
      4, 5, 6, 4, 6, 7, // Back face
      7, 6, 1, 7, 1, 0, // Left face
      5, 2, 1, 5, 1, 6, // Bottom face
      7, 0, 3, 7, 3, 4  // Top face
   };
   indexedCube->SetIndices(indices, sizeof(indices) / sizeof(unsigned short));
   indexedCube->frame.TranslateLocal(glm::vec3(2, 0, 0));
   indexedCube->SendToGPU();

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

