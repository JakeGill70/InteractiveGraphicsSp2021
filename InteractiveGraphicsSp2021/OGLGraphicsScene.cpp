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

   _objects["axis"]->frame.TranslateLocal(glm::vec3(0, 0.1f, 0));

   /*MeshFactory<VertexPCT, RGBA> meshFactory;
   OGLVertexMesh<VertexPCT>* mesh = (OGLVertexMesh<VertexPCT>*)
       meshFactory.TexturedCuboidMesh(4, 4, 4, { 1, 1, 1, 1 }, 2, 2);
   mesh->SetUpAttributes("PCT");
   mesh->SetTexture(_textures["smileyTexture"]);
   GraphicsObject* c1 = new GraphicsObject();
   c1->AddMesh(mesh);
   AddGraphicsObject("smileyCube", c1, "diffuseShader");
   c1->SendToGPU();

   RotateAnimation* defaultRot = new RotateAnimation();
   _objects["smileyCube"]->SetAnimation(defaultRot);

   _objects["smileyCube"]->frame.TranslateWorld(glm::vec3(-4, 0, 0));*/

   globalLight.intensity = 0.25f; // Brighten the cube a bit

   MeshFactory<VertexPCNT, RGBA> meshFactory2;
   OGLVertexMesh<VertexPCNT>* mesh2 = (OGLVertexMesh<VertexPCNT>*)
       meshFactory2.NormalizedTexturedCuboidMesh(4, 4, 4, { 1, 1, 1, 1 }, 1, 1);
   mesh2->SetUpAttributes("PCNT");
   mesh2->SetTexture(_textures["smileyTexture"]);
   GraphicsObject* c2 = new GraphicsObject();
   c2->AddMesh(mesh2);
   AddGraphicsObject("smileyCube2", c2, "diffuseShader");
   c2->SendToGPU();

   RotateAnimation* defaultRot2 = new RotateAnimation();
   _objects["smileyCube2"]->SetAnimation(defaultRot2);
   _objects["smileyCube2"]->frame.TranslateWorld(glm::vec3(4, 0, 0));

   OGLVertexMesh<VertexPCNT>* mesh = (OGLVertexMesh<VertexPCNT>*)
       meshFactory2.NormalizedTexturedCuboidMesh(4, 4, 4, { 1, 1, 1, 1 }, 2, 2);
   mesh->SetUpAttributes("PCNT");
   mesh->SetTexture(_textures["smileyTexture"]);
   GraphicsObject* c1 = new GraphicsObject();
   c1->AddMesh(mesh);
   AddGraphicsObject("smileyCube", c1, "diffuseShader");
   c1->SendToGPU();

   RotateAnimation* defaultRot = new RotateAnimation();
   _objects["smileyCube"]->SetAnimation(defaultRot);

   _objects["smileyCube"]->frame.TranslateWorld(glm::vec3(-4, 0, 0));

   OGLVertexMesh<VertexPCNT>* mesh3 = (OGLVertexMesh<VertexPCNT>*)
       meshFactory2.NormalizedIndexedFlatTexturedMeshXZ(-20, -20, 40, 40, { 1,1,1,1 }, 20, 20);
   mesh3->SetUpAttributes("PCNT");
   mesh3->SetTexture(_textures["woodFloorTexture"]);
   GraphicsObject* c3 = new GraphicsObject();
   c3->AddMesh(mesh3);
   AddGraphicsObject("floor", c3, "diffuseShader");
   c3->SendToGPU();


   _objects["smileyCube"]->frame.TranslateWorld(glm::vec3(0, 2, 0));
   _objects["smileyCube2"]->frame.TranslateWorld(glm::vec3(0, 2, 0));

   _cameras["camera"]->frame.TranslateWorld(glm::vec3(0, 2, 8));
   _cameras["camera"]->UpdateView();

   localLight.color = { 1, 1, 1 }; // White light
   localLight.intensity = 0.5f; // Medium intensity
   localLight.position = { 0, 0.5f, 2.0f }; // Close to the floor

   MeshFactory<VertexPC, RGB> meshFactory3;
   OGLVertexMesh<VertexPC>* mesh4 = (OGLVertexMesh<VertexPC>*)
       meshFactory3.CuboidMesh(0.25f, 0.25f, 0.25f, { 1,1,1 });
   mesh4->SetUpAttributes("PC");
   GraphicsObject* c4 = new GraphicsObject();
   c4->AddMesh(mesh4);
   AddGraphicsObject("localLight", c4, "simple3DShader");
   c4->SendToGPU();
   _objects["localLight"]->frame.TranslateWorld(localLight.position);

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
   FactoriedMeshData factoriedMeshData;
   map<string, ObjectData>& objectData = _sceneReader->GetObjectData();
   for (auto it = objectData.begin(); it != objectData.end(); it++) {
      object = new GraphicsObject();
      data = it->second;
      for (auto mit = data.meshData.begin(); mit != data.meshData.end(); mit++) {
         meshData = *mit;
         if (meshData.vertexType == "PC") {
            mesh = CreatePCMesh(meshData);
         }
         else if (meshData.vertexType == "PCT") {
            mesh = CreatePCTMesh(meshData);
         }
         if (mesh) {
            object->AddMesh(mesh);
         }
         else {
            _log << "Could not create mesh for " << data.name << std::endl;
            delete object;
            return false;
         }
      }
      for (auto mit = data.factoriedMeshData.begin(); mit != data.factoriedMeshData.end(); mit++) {
         factoriedMeshData = *mit;
         if (factoriedMeshData.vertexType == "PCT") {
            mesh = CreateFactoriedPCTMesh(factoriedMeshData);
         }
         if (mesh) {
            object->AddMesh(mesh);
         }
         else {
            _log << "Could not create factoried mesh for " << data.name << std::endl;
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
   if (!ReadPCMeshData((OGLVertexMesh<VertexPC>*)mesh, meshData)) {
      delete mesh;
      return nullptr;
   }
   mesh->SetPositionAttribute({ 0,  3, sizeof(VertexPC), 0 });
   mesh->SetColorAttribute({ 1, 3, sizeof(VertexPC), sizeof(GLfloat) * 3 });
   return mesh;
}

AbstractMesh* OGLGraphicsScene::CreatePCTMesh(MeshData& meshData)
{
   OGLVertexMesh<VertexPCT>* mesh = new OGLVertexMesh<VertexPCT>();
   if (meshData.primitiveType == "lines") {
      mesh->SetPrimitive(GL_LINES);
   }
   if (!ReadPCTMeshData((OGLVertexMesh<VertexPCT>*)mesh, meshData)) {
      delete mesh;
      return nullptr;
   }
   mesh->SetTexture(_textures[meshData.textureName]);
   mesh->SetPositionAttribute({ 0,  3, sizeof(VertexPCT), 0 });
   mesh->SetColorAttribute({ 1, 4, sizeof(VertexPCT), sizeof(GLfloat) * 3 });
   mesh->SetTextureAttribute({ 2, 2, sizeof(VertexPCT), sizeof(GLfloat) * 7 });
   return mesh;
}

AbstractMesh* OGLGraphicsScene::CreateFactoriedPCTMesh(FactoriedMeshData& meshData)
{
   MeshFactory<VertexPCT, RGBA> pctFactory;
   OGLVertexMesh<VertexPCT>* mesh = nullptr;
   if (meshData.meshType == "flat textured") {
      if (meshData.whichPlane == "XZ") {
         mesh = (OGLVertexMesh<VertexPCT>*)
            pctFactory.IndexedFlatTexturedMeshXZ(
               meshData.params[0], // sx
               meshData.params[1], // sz
               meshData.params[2], // ex
               meshData.params[3], // ez
               {
                  meshData.params[4], // r
                  meshData.params[5], // g
                  meshData.params[6], // b
                  meshData.params[7]  // a
               },
               meshData.params[8], // repeatS
               meshData.params[9]  // repeatT
            );
      }
   }
   if (mesh) {
      mesh->SetTexture(_textures[meshData.textureName]);
      mesh->SetPositionAttribute({ 0,  3, sizeof(VertexPCT), 0 });
      mesh->SetColorAttribute({ 1, 4, sizeof(VertexPCT), sizeof(GLfloat) * 3 });
      mesh->SetTextureAttribute({ 2, 2, sizeof(VertexPCT), sizeof(GLfloat) * 7 });
   }
   return mesh;
}

bool OGLGraphicsScene::ReadPCMeshData(OGLVertexMesh<VertexPC>* mesh, MeshData& meshData)
{
   size_t numberOfVertices = meshData.vertexData.size();
   size_t numberOfIndices = meshData.indexData.size();
   size_t numbersLeftToRead = numberOfVertices;
   const int SIZE = 6;
   float x, y, z, r, g, b;
   vector<VertexPC> vertices;
   for (size_t i = 0; i < numberOfVertices;) {
      if (numbersLeftToRead < SIZE) {
         _log << "Incorrect number of vertices for the mesh (expected 6 for VertexPC).";
         return false;
      }
      x = meshData.vertexData[i++];
      y = meshData.vertexData[i++];
      z = meshData.vertexData[i++];
      r = meshData.vertexData[i++];
      g = meshData.vertexData[i++];
      b = meshData.vertexData[i++];
      if (numberOfIndices > 0) {
         if (meshData.isIndexed) {
            mesh->AddVertexData({ x,  y, z, r, g, b });
         }
         else {
            vertices.push_back({ x,  y, z, r, g, b });
         }
      }
      else { // No index data
         mesh->AddVertexData({ x,  y, z, r, g, b });
      }
      numbersLeftToRead -= SIZE;
   }

   VertexPC v;
   for (size_t i = 0; i < numberOfIndices; i++) {
      if (meshData.isIndexed) {
         mesh->AddIndex(meshData.indexData[i]);
      }
      else {
         v = vertices[meshData.indexData[i]];
         mesh->AddVertexData({ v.position, v.color });
      }
   }
   return true;
}

bool OGLGraphicsScene::ReadPCTMeshData(OGLVertexMesh<VertexPCT>* mesh, MeshData& meshData)
{
   size_t numberOfVertices = meshData.vertexData.size();
   size_t numberOfIndices = meshData.indexData.size();
   size_t numbersLeftToRead = numberOfVertices;
   float x, y, z, r, g, b, a, s, t;
   vector<VertexPCT> vertices;
   const int SIZE = 9;
   for (size_t i = 0; i < numberOfVertices;) {
      if (numbersLeftToRead < SIZE) {
         _log << "Incorrect number of vertices for the mesh (expected 8 for VertexPCT).";
         return false;
      }
      x = meshData.vertexData[i++];
      y = meshData.vertexData[i++];
      z = meshData.vertexData[i++];
      r = meshData.vertexData[i++];
      g = meshData.vertexData[i++];
      b = meshData.vertexData[i++];
      a = meshData.vertexData[i++];
      s = meshData.vertexData[i++];
      t = meshData.vertexData[i++];
      if (numberOfIndices > 0) {
         if (meshData.isIndexed) {
            mesh->AddVertexData({ x,  y, z, r, g, b, a, s, t });
         }
         else {
            vertices.push_back({ x,  y, z, r, g, b, a, s, t });
         }
      }
      else { // No index data
         mesh->AddVertexData({ x,  y, z, r, g, b, a, s, t });
      }
      numbersLeftToRead -= SIZE;
   }

   VertexPCT v;
   for (size_t i = 0; i < numberOfIndices; i++) {
      if (meshData.isIndexed) {
         mesh->AddIndex(meshData.indexData[i]);
      }
      else {
         v = vertices[meshData.indexData[i]];
         mesh->AddVertexData({ v.position, v.color });
      }
   }
   return true;
}

