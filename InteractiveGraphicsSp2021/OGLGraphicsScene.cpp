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
   if (!LoadScene()) return false;
   ReadCameraData();
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
   cube->frame.TranslateLocal(glm::vec3(-1, 0.5f, 0));
   cube->SendToGPU();

   OGLGraphicsObject<VertexPC>* surface = new OGLGraphicsObject<VertexPC>();
   AddGraphicsObject("surface", surface, "simple3DShader");
   V1 = { -2.5f, 0, -2.5f, 0, 0.5f, 0 };
   V2 = { -2.5f, 0,  2.5f, 0, 0.5f, 0 };
   V3 = { 2.5f, 0,  2.5f, 0, 0.5f, 0 };
   V4 = { 2.5f, 0, -2.5f, 0, 0.5f, 0 };
   surface->AddVertexData(V1);
   surface->AddVertexData(V2);
   surface->AddVertexData(V3);
   surface->AddVertexData(V1);
   surface->AddVertexData(V3);
   surface->AddVertexData(V4);
   surface->SendToGPU();

   OGLGraphicsObject<VertexPC>* axis = new OGLGraphicsObject<VertexPC>();
   AddGraphicsObject("axis", axis, "simple3DShader");
   axis->SetPrimitive(GL_LINES);
   // Line along X
   axis->AddVertexData({ 0, 0, 0, 1, 0, 0 });
   axis->AddVertexData({ 2.0f, 0, 0, 1, 0, 0 });
   // Line along Y
   axis->AddVertexData({ 0,    0, 0, 0, 1, 0 });
   axis->AddVertexData({ 0, 2.0f, 0, 0, 1, 0 });
   // Line along Z
   axis->AddVertexData({ 0, 0,    0, 0, 0, 1 });
   axis->AddVertexData({ 0, 0, 2.0f, 0, 0, 1 });
   axis->SendToGPU();

   OGLGraphicsObject<VertexPC>* yelloCube = new OGLGraphicsObject<VertexPC>();
   AddGraphicsObject("yellowCube", yelloCube, "simple3DShader", true);
   // Yellow vertices
   yelloCube->AddVertexData({ -0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 0.0f }); // 0
   yelloCube->AddVertexData({ -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f }); // 1
   yelloCube->AddVertexData({  0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f }); // 2
   yelloCube->AddVertexData({  0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 0.0f }); // 3
   yelloCube->AddVertexData({  0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f }); // 4
   yelloCube->AddVertexData({  0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f }); // 5
   yelloCube->AddVertexData({ -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f }); // 6
   yelloCube->AddVertexData({ -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f }); // 7
   unsigned short yellowCubeIndices[] = {
      0, 1, 2, 0, 2, 3, // Front face
      3, 2, 5, 3, 5, 4, // Right face
      4, 5, 6, 4, 6, 7, // Back face
      7, 6, 1, 7, 1, 0, // Left face
      5, 2, 1, 5, 1, 6, // Bottom face
      7, 0, 3, 7, 3, 4  // Top face
   };
   yelloCube->SetIndices(yellowCubeIndices, sizeof(yellowCubeIndices) / sizeof(unsigned short));
   yelloCube->frame.TranslateLocal(glm::vec3(2, 0.5f, 0));
   yelloCube->SendToGPU();

   // Create Purple Cube
   OGLGraphicsObject<VertexPC>* purpleCube = new OGLGraphicsObject<VertexPC>();
   AddGraphicsObject("purpleCube", purpleCube, "simple3DShader", true);
   // Purple vertices
   purpleCube->AddVertexData({ -0.5f,  0.5f, 0.5f,  0.5f, 0.0f, 0.5f }); // 0
   purpleCube->AddVertexData({ -0.5f, -0.5f, 0.5f,  0.5f, 0.0f, 0.5f }); // 1
   purpleCube->AddVertexData({ 0.5f, -0.5f, 0.5f,  0.5f, 0.0f, 0.5f }); // 2
   purpleCube->AddVertexData({ 0.5f,  0.5f, 0.5f,  0.5f, 0.0f, 0.5f }); // 3
   purpleCube->AddVertexData({ 0.5f,  0.5f, -0.5f, 0.5f, 0.0f, 0.5f }); // 4
   purpleCube->AddVertexData({ 0.5f, -0.5f, -0.5f, 0.5f, 0.0f, 0.5f }); // 5
   purpleCube->AddVertexData({ -0.5f, -0.5f, -0.5f, 0.5f, 0.0f, 0.5f }); // 6
   purpleCube->AddVertexData({ -0.5f,  0.5f, -0.5f, 0.5f, 0.0f, 0.5f }); // 7

   unsigned short purpleCubeIndices[] = {
       0, 1, 2, 0, 2, 3, // Front face   
       3, 2, 5, 3, 5, 4, // Right face   
       4, 5, 6, 4, 6, 7, // Back face   
       7, 6, 1, 7, 1, 0, // Left face  
       5, 2, 1, 5, 1, 6, // Bottom face
       7, 0, 3, 7, 3, 4  // Top face
   };
   purpleCube->SetIndices(purpleCubeIndices, sizeof(purpleCubeIndices) / sizeof(unsigned short));
   // Position the purple cube to match the yellow cube
   purpleCube->frame.TranslateLocal(glm::vec3(0, 0, 2));
   purpleCube->SendToGPU();

   return true;
}

bool OGLGraphicsScene::LoadScene()
{
   _sceneReader->Open();
   _sceneReader->Read();
   if (_sceneReader->HasError()) {
      return false;
   }
   _sceneReader->Close();
   return true;
}

bool OGLGraphicsScene::ReadCameraData()
{
   vector<CameraData>& cameraData = _sceneReader->GetCameraData();
   for (size_t i = 0; i < cameraData.size(); i++) {
      BaseCamera* camera = new BaseCamera();
      camera->frame.SetPosition(
         cameraData[i].position.x, cameraData[i].position.y, cameraData[i].position.z);
      camera->fieldOfView = cameraData[i].fov;
      camera->nearPlane = cameraData[i].nearPlane;
      camera->farPlane = cameraData[i].farPlane;
      camera->UpdateView();
      AddCamera(cameraData[i].name, camera);
   }
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

