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
   if (!ReadObjectData()) return false;

   //OGLGraphicsObject<VertexPC>* triangle = new OGLGraphicsObject<VertexPC>();
   //AddGraphicsObject("triangle", triangle, "defaultShader");
   //triangle->AddVertexData({  0.0f,  0.5f, 0, 1, 0, 0 });
   //triangle->AddVertexData({ -0.5f, -0.5f, 0, 0, 0, 1 });
   //triangle->AddVertexData({  0.5f, -0.5f, 0, 0, 1, 0 });
   //triangle->SendToGPU();

    _objects["cube"]->frame.TranslateLocal(glm::vec3(-1, 0.5f, 0));

   OGLGraphicsObject<VertexPC>* indexedCube = new OGLGraphicsObject<VertexPC>();
   AddGraphicsObject("indexedCube", indexedCube, "simple3DShader", true);
   // Yellow vertices
   indexedCube->AddVertexData({ -0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 0.0f }); // 0
   indexedCube->AddVertexData({ -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f }); // 1
   indexedCube->AddVertexData({ 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f }); // 2
   indexedCube->AddVertexData({ 0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 0.0f }); // 3
   indexedCube->AddVertexData({ 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f }); // 4
   indexedCube->AddVertexData({ 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f }); // 5
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
   indexedCube->frame.TranslateLocal(glm::vec3(2, 0.5f, 0));
   indexedCube->SendToGPU();

   OGLGraphicsObject<VertexPC>* purpleRectangle = new OGLGraphicsObject<VertexPC>();
   AddGraphicsObject("redRectangle", purpleRectangle, "simple3DShader", true);
   purpleRectangle->AddVertexData({ -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f }); // 0
   purpleRectangle->AddVertexData({ -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f }); // 1
   purpleRectangle->AddVertexData({ 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f }); // 2
   purpleRectangle->AddVertexData({ 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f }); // 3
   unsigned short indices2[] = {
      0, 1, 2, 0, 2, 3
   };
   purpleRectangle->SetIndices(indices2, sizeof(indices2) / sizeof(unsigned short));
   purpleRectangle->frame.TranslateLocal(glm::vec3(0, 0, 2.0f));
   purpleRectangle->SendToGPU();

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

bool OGLGraphicsScene::ReadObjectData()
{
   AbstractGraphicsObject* object;
   ObjectData data;
   map<string, ObjectData>& objectData = _sceneReader->GetObjectData();
   for (auto it = objectData.begin(); it != objectData.end(); it++) {
      object = nullptr;
      data = it->second;
      if (data.vertexType == "PC") {
         object = new OGLGraphicsObject<VertexPC>();
      }
      if (object != nullptr) {
         if (data.primitiveType == "lines") {
            object->SetPrimitive(GL_LINES);
         }
         if (data.vertexType == "PC") {
            if (!ReadPCObjectData(
               (OGLGraphicsObject<VertexPC>*)object, data.vertexData, data.indexData)) {
               return false;
            }
            AddGraphicsObject(data.name, object, data.shaderName);
            object->SendToGPU();
         }
      }
   }
   return true;
}

bool OGLGraphicsScene::ReadPCObjectData(
   OGLGraphicsObject<VertexPC>* object,
   vector<float>& vertexData,
   vector<unsigned short>& indexData)
{
   size_t numbersLeftToRead = vertexData.size();
   float x, y, z, r, g, b;
   vector<VertexPC> vertices;
   for (size_t i = 0; i < vertexData.size();) {
      if (numbersLeftToRead < 6) {
         _log << "Incorrect number of vertices for the object.";
         return false;
      }
      x = vertexData[i++];
      y = vertexData[i++];
      z = vertexData[i++];
      r = vertexData[i++];
      g = vertexData[i++];
      b = vertexData[i++];
      if (indexData.size() > 0) {
         vertices.push_back({ x,  y, z, r, g, b });
      }
      else { // No index data
         object->AddVertexData({ x,  y, z, r, g, b });
      }
      numbersLeftToRead -= 6;
   }

   VertexPC v;
   for (size_t i = 0; i < indexData.size();i++) {
      v = vertices[indexData[i]];
      object->AddVertexData({ v.position, v.color });
   }
   return true;
}

