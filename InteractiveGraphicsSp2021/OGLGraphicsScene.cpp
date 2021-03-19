#include "OGLGraphicsScene.h"
#include "OGLShader.h"
#include "TextFileReader.h"
#include "RotateAnimation.h"
#include "OGLTexture.h"
#include "OGLVertexMesh.hpp"
#include "MeshFactory.hpp"

OGLGraphicsScene::~OGLGraphicsScene()
{
   delete _sceneReader;
}

bool OGLGraphicsScene::Create()
{
   if (!LoadScene()) return false;
   ReadCameraData();
   if (!ReadShaderData()) return false;
   if (!ReadTextureData()) return false;
   if (!ReadObjectData()) return false;

    _objects["cube"]->frame.TranslateLocal(glm::vec3(-2, 0.5f, 0));
    _objects["indexedCube"]->frame.TranslateLocal(glm::vec3(2, 0.5f, 0));
    _objects["purpleRectangle"]->frame.TranslateLocal(glm::vec3(0, 0, 2.0f));

    RotateAnimation* defaultRot = new RotateAnimation();
    RotateAnimation* otherRot = new RotateAnimation(glm::vec3(0, 0, 1), 180.0f);
    _objects["cube"]->SetAnimation(defaultRot);
    _objects["indexedCube"]->SetAnimation(otherRot);

    GraphicsObject* wall = new GraphicsObject();
    wall->AddMesh(new OGLVertexMesh<VertexPCT>());
    wall->AddMesh(new OGLVertexMesh<VertexPCT>());
    OGLVertexMesh<VertexPCT>* mesh = (OGLVertexMesh<VertexPCT>*)wall->GetMesh(0);
    mesh->SetPositionAttribute({ 0,  3, sizeof(VertexPCT), 0 });
    mesh->SetColorAttribute({ 1, 4, sizeof(VertexPCT), sizeof(GLfloat) * 3 });
    mesh->SetTextureAttribute({ 2, 2, sizeof(VertexPCT), sizeof(GLfloat) * 7 });
    //                     x,  y, z, r, g, b, a, s, t
    mesh->AddVertexData({ -2,  1, 0, 1, 1, 1, 1, 0, 1 });
    mesh->AddVertexData({ -2, -1, 0, 1, 1, 1, 1, 0, 0 });
    mesh->AddVertexData({  0, -1, 0, 1, 1, 1, 1, 1, 0 });
    mesh->AddVertexData({  0,  1, 0, 1, 1, 1, 1, 1, 1 });
    unsigned short indices1[] = { 0, 1, 2, 0, 2, 3 };
    mesh->SetIndices(indices1, 6);
    mesh->SetTexture(_textures["customTexture"]);

    mesh = (OGLVertexMesh<VertexPCT>*)wall->GetMesh(1);
    mesh->SetPositionAttribute({ 0,  3, sizeof(VertexPCT), 0 });
    mesh->SetColorAttribute({ 1, 4, sizeof(VertexPCT), sizeof(GLfloat) * 3 });
    mesh->SetTextureAttribute({ 2, 2, sizeof(VertexPCT), sizeof(GLfloat) * 7 });
    mesh->AddVertexData({ 0,  1, 0, 1, 1, 1, 1, 0, 1 });
    mesh->AddVertexData({ 0, -1, 0, 1, 1, 1, 1, 0, 0 });
    mesh->AddVertexData({ 2, -1, 0, 1, 1, 1, 1, 1, 0 });
    mesh->AddVertexData({ 2,  1, 0, 1, 1, 1, 1, 1, 1 });
    unsigned short indices2[] = { 0, 1, 2, 0, 2, 3 };
    mesh->SetIndices(indices2, 6);
    mesh->SetTexture(_textures["brickwallTexture"]);

    wall->frame.TranslateLocal(glm::vec3(0, 1.0f, -2.0f));
    AddGraphicsObject("wall", wall, "simpleTextureShader");
    _objects["wall"]->SendToGPU();

    MeshFactory<VertexPCT, RGBA> pctFactory;
    mesh = (OGLVertexMesh<VertexPCT>*)
       pctFactory.FlatTexturedSurfaceXZ(-5, -5, 5, 5, { 1, 1, 1, 1 }, 5, 5);
    mesh->SetPositionAttribute({ 0,  3, sizeof(VertexPCT), 0 });
    mesh->SetColorAttribute({ 1, 4, sizeof(VertexPCT), sizeof(GLfloat) * 3 });
    mesh->SetTextureAttribute({ 2, 2, sizeof(VertexPCT), sizeof(GLfloat) * 7 });
    mesh->SetTexture(_textures["smileyTexture"]);
    GraphicsObject* floor = new GraphicsObject();
    floor->AddMesh(mesh);
    AddGraphicsObject("floor", floor, "simpleTextureShader");
    _objects["floor"]->SendToGPU();

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
      AddShader(shaderData[i].name, shader);
      if (shaderData[i].cameraName != "none") {
         _shaders[shaderData[i].name]->SetCamera(_cameras[shaderData[i].cameraName]);
      }
   }

   return true;
}

bool OGLGraphicsScene::ReadTextureData()
{
   OGLTexture* texture;
   TextureData data;
   size_t numberOfElements;
   unsigned char* array;
   map<string, TextureData>& textureData = _sceneReader->GetTextureData();
   for (auto it = textureData.begin(); it != textureData.end(); it++) {
      data = it->second;
      texture = new OGLTexture();
      if (data.minFilter == "nearest") {
         texture->SetMinFilter(GL_NEAREST);
      }
      if (data.maxFilter == "nearest") {
         texture->SetMagFilter(GL_NEAREST);
      }
      numberOfElements = data.arrayData.size();
      if (numberOfElements > 0) {
         array = new unsigned char[numberOfElements];
         for (int i = 0; i < numberOfElements; i++) {
            array[i] = data.arrayData[i];
         }
         texture->LoadFromArray(
            array, (unsigned int)numberOfElements, 
            data.width, data.height, data.numberOfChannels);
      }
      else {
         texture->LoadFromFile(data.filePath);
      }
      AddTexture(data.name, texture);
   }
   return true;
}

bool OGLGraphicsScene::ReadObjectData()
{
   AbstractMesh* mesh = nullptr;
   GraphicsObject* object;
   ObjectData data;
   MeshData meshData;
   map<string, ObjectData>& objectData = _sceneReader->GetObjectData();
   for (auto it = objectData.begin(); it != objectData.end(); it++) {
      object = new GraphicsObject();
      data = it->second;
      for (auto mit = data.meshData.begin(); mit != data.meshData.end(); mit++) {
         meshData = *mit;
         if (meshData.vertexType == "PC") {
            mesh = CreatePCMesh(meshData);
         }
         if (mesh) {
            object->AddMesh(mesh);
         }
         else {
            _log << "Could not create " << data.name << std::endl;
            delete object;
            return false;
         }
      }
      AddGraphicsObject(data.name, object, data.shaderName);
      object->SendToGPU();
   }
   return true;
}

AbstractMesh* OGLGraphicsScene::CreatePCMesh(MeshData& meshData)
{
   OGLVertexMesh<VertexPC>* mesh = new OGLVertexMesh<VertexPC>();
   if (meshData.primitiveType == "lines") {
      mesh->SetPrimitive(GL_LINES);
   }
   if (!ReadPCMeshData(
      (OGLVertexMesh<VertexPC>*)mesh,
      meshData.vertexData, meshData.indexData, meshData.isIndexed)) {
      delete mesh;
      return nullptr;
   }
   mesh->SetPositionAttribute({ 0,  3, sizeof(VertexPC), 0 });
   mesh->SetColorAttribute({ 1, 3, sizeof(VertexPC), sizeof(GLfloat) * 3 });
   return mesh;
}

bool OGLGraphicsScene::ReadPCMeshData(
   OGLVertexMesh<VertexPC>* mesh,
   vector<float>& vertexData,
   vector<unsigned short>& indexData,
   bool isIndexed)
{
   size_t numbersLeftToRead = vertexData.size();
   float x, y, z, r, g, b;
   vector<VertexPC> vertices;
   for (size_t i = 0; i < vertexData.size();) {
      if (numbersLeftToRead < 6) {
         _log << "Incorrect number of vertices for the mesh.";
         return false;
      }
      x = vertexData[i++];
      y = vertexData[i++];
      z = vertexData[i++];
      r = vertexData[i++];
      g = vertexData[i++];
      b = vertexData[i++];
      if (indexData.size() > 0) {
         if (isIndexed) {
            mesh->AddVertexData({ x,  y, z, r, g, b });
         }
         else {
            vertices.push_back({ x,  y, z, r, g, b });
         }
      }
      else { // No index data
         mesh->AddVertexData({ x,  y, z, r, g, b });
      }
      numbersLeftToRead -= 6;
   }

   VertexPC v;
   for (size_t i = 0; i < indexData.size();i++) {
      if (isIndexed) {
         mesh->AddIndex(indexData[i]);
      }
      else {
         v = vertices[indexData[i]];
         mesh->AddVertexData({ v.position, v.color });
      }
   }
   return true;
}

