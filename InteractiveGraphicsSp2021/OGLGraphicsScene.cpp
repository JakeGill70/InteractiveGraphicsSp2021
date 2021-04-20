#include "OGLGraphicsScene.h"
#include "OGLShader.h"
#include "TextFileReader.h"
#include "RotateAnimation.h"
#include "OGLTexture.h"
#include "OGLVertexMesh.hpp"
#include "MeshFactory.hpp"
#include "GLFWInputSystem.h"
#include "GLFWGraphicsWindow.h"
#include "SimpleMovingCameraAnimation.h"
#include "ObjectFactory.h"
#include "VisibilityAnimation.h"

OGLGraphicsScene::~OGLGraphicsScene()
{
   delete _sceneReader; 
}

int getRandomNumber(int min, int max) {
    return ((rand() % (max - min)) + min);
}

void OGLGraphicsScene::MakeObjectsVisisble(string objNamePrefix, bool visibility) {
    string objectName;
    for (std::map<string, GraphicsObject*>::iterator it = _objects.begin(); it != _objects.end(); ++it)
    {
        objectName = it->first;
        if (objectName.find(objNamePrefix) == 0) {
            it->second->isVisible = visibility;
        }
    }
}

void OGLGraphicsScene::MakeRandomLight(glm::vec3 minVals, glm::vec3 maxVals) {
    // Make color
    glm::vec3 color = { getRandomNumber(1,100) / 100.0f, getRandomNumber(1,100) / 100.0f, getRandomNumber(1,100) / 100.0f };
    float colorMax = std::fmax(color.r, std::fmax(color.g, color.b));
    color = { color.r / colorMax, color.g / colorMax, color.b / colorMax };
    
    // Make position
    glm::vec3 pos = { getRandomNumber(minVals.x, maxVals.x), getRandomNumber(minVals.y, maxVals.y), getRandomNumber(minVals.z, maxVals.z) };
    
    // Make intensity
    float intensity = 2.0f;// (float)getRandomNumber(4, 15) / 10.0f;

    // Make light
    localLights[_numberOfLights].color = color;
    localLights[_numberOfLights].position = pos;
    localLights[_numberOfLights].intensity = intensity;
    localLights[_numberOfLights].attenuationCoefficient = 0.5f;
    _numberOfLights++;

    // Make Gizmo object
    GraphicsObject* object;
    stringstream ss;
    string objName;

    object = ObjectFactory::PlainCuboid(0.5f, 0.5f, 0.5f, {color.r, color.g, color.b});
    ss << "l::" << "randomLight:" << _numberOfLights;
    objName = ss.str();
    AddGraphicsObject(objName, object, "simple3DShader");
    _objects[objName]->frame.TranslateWorld(pos);
    _objects[objName]->SendToGPU();
}

void OGLGraphicsScene::CreateRandomCurve(string objName, string texName, glm::vec3 offset) {
    glm::vec3 spoints[4][4]{};
    /*spoints[0][0] = { -10,  2, -10 };
    spoints[0][1] = { -7,  6, -10 };
    spoints[0][2] = { 3, -6, -10 };
    spoints[0][3] = { 10,  4, -10 };

    spoints[1][0] = { -10,  0, -5 };
    spoints[1][1] = { -7,  6, -5 };
    spoints[1][2] = { 3, -6, -5 };
    spoints[1][3] = { 10,  -6, -5 };

    spoints[2][0] = { -10,  4, 0 };
    spoints[2][1] = { -7,  6, 0 };
    spoints[2][2] = { 3, -6, 0 };
    spoints[2][3] = { 10,  2, 0 };

    spoints[3][0] = { -10,  -4, 5 };
    spoints[3][1] = { -7,  6, 5 };
    spoints[3][2] = { 3, -6, 5 };
    spoints[3][3] = { 10,  -4, 5 };*/

    int z;
    for (int row = 0; row < 4; row++) {
        z = getRandomNumber(-10, 10);
        spoints[row][0] = { getRandomNumber(-10,10), getRandomNumber(-5,5), z };
        spoints[row][1] = { getRandomNumber(-10,10), getRandomNumber(-5,5), z };
        spoints[row][2] = { getRandomNumber(-10,10), getRandomNumber(-5,5), z };
        spoints[row][3] = { getRandomNumber(-10,10), getRandomNumber(-5,5), z };
    }

    MeshFactory<VertexPCNT, RGBA> meshFactoryPCNTRGBA;

    OGLVertexMesh<VertexPCNT>* patch_Mesh = (OGLVertexMesh<VertexPCNT>*)
        meshFactoryPCNTRGBA.CubicBezierPatchPCNTRandomY(spoints, -5, 5, { 1, 1, 1 }, 40, 40, 20);
    patch_Mesh->SetTexture(_textures[texName]);
    GraphicsObject* patch_Object = new GraphicsObject();
    patch_Object->AddMesh(patch_Mesh);
    patch_Object->frame.TranslateWorld(offset);
    AddGraphicsObject(objName, patch_Object, "lightingShader");
    _objects[objName]->SendToGPU();

    stringstream ss;
    GraphicsObject* object;
    VisibilityAnimation* anim;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            RGB color = { 1, 1, 1 };
            if (row == col) {
                color = { 1, 0, 0 };
            }
            object = ObjectFactory::PlainCuboid(0.2f, 0.2f, 0.2f, color);
            ss << "p::" << objName << ":" << row << ":" << col;
            AddGraphicsObject(ss.str(), object, "simple3DShader");
            anim = new VisibilityAnimation(_inputSystem);
            _objects[ss.str()]->SetAnimation(anim);
            _objects[ss.str()]->frame.TranslateWorld(spoints[row][col] + offset);
            _objects[ss.str()]->SendToGPU();
        }
    }
}

bool OGLGraphicsScene::Create()
{
   if (!LoadScene()) return false;
   ReadCameraData();
   if (!ReadShaderData()) return false;
   if (!ReadLightData()) return false;
   if (!ReadTextureData()) return false;
   if (!ReadObjectData()) return false;

   _currentCamera = _cameras["camera"];
   _currentCamera->frame.SetPosition(0, 1, 15);
   _currentCamera->SetupLookingForward();
   _currentCamera->UpdateView();

   GLFWGraphicsWindow* window = (GLFWGraphicsWindow*)_window;
   _inputSystem = new GLFWInputSystem(window->GetGLFWWindow());
   _inputSystem->RegisterKey("W", GLFW_KEY_W);
   _inputSystem->RegisterKey("S", GLFW_KEY_S);
   _inputSystem->RegisterKey("A", GLFW_KEY_A);
   _inputSystem->RegisterKey("D", GLFW_KEY_D);
   _inputSystem->RegisterKey("LEFT", GLFW_KEY_LEFT);
   _inputSystem->RegisterKey("RIGHT", GLFW_KEY_RIGHT);
   _inputSystem->RegisterKey("1", GLFW_KEY_1);

   SimpleMovingCameraAnimation* cameraAnimation = new SimpleMovingCameraAnimation();
   cameraAnimation->SetInputSystem(_inputSystem);
   _currentCamera->SetAnimation(cameraAnimation);

   localLights[_numberOfLights].color = { 0, 1, 0 };
   localLights[_numberOfLights].position = { -10, 1, -10 };
   localLights[_numberOfLights].intensity = 0.5f;
   localLights[_numberOfLights].attenuationCoefficient = 0.5f;
   _numberOfLights++;

   CreateRandomCurve("patch1", "worldTexture", {-30,0,0});
   CreateRandomCurve("patch2", "crateTexture", { -10,0,0 });
   CreateRandomCurve("patch3", "woodFloorTexture", { 10,0,0 });
   CreateRandomCurve("patch4", "brickwallTexture", { 30,0,0 });

   // Patch 1 lights
   MakeRandomLight({ -30, -5, -5 }, { -20, 5, 5 });
   MakeRandomLight({ -30, -5, -5 }, { -20, 5, 5 });
   MakeRandomLight({ -30, -5, -5 }, { -20, 5, 5 });

   // Patch 2 lights
   MakeRandomLight({ -10, -5, -5 }, { 0, 5, 5 });
   MakeRandomLight({ -10, -5, -5 }, { 0, 5, 5 });
   MakeRandomLight({ -10, -5, -5 }, { 0, 5, 5 });

   // Patch 3 lights
   MakeRandomLight({ 10, -5, -5 }, { 20, 5, 5 });
   MakeRandomLight({ 10, -5, -5 }, { 20, 5, 5 });
   MakeRandomLight({ 10, -5, -5 }, { 20, 5, 5 });

   // Patch 4 lights
   MakeRandomLight({ 20, -5, -5 }, { 30, 5, 5 });
   MakeRandomLight({ 20, -5, -5 }, { 30, 5, 5 });
   MakeRandomLight({ 20, -5, -5 }, { 30, 5, 5 });

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

bool OGLGraphicsScene::ReadLightData()
{
   vector<LightData>& allLightData = _sceneReader->GetLightData();
   LightData data;
   int li = 0;
   for (size_t i = 0; i < allLightData.size(); i++) {
      data = allLightData[i];
      if (data.type == "local") {
         localLights[li++] = data.light;
      }
      else {
         globalLight = data.light;
      }
   }
   _numberOfLights = li;

   return true;
}

bool OGLGraphicsScene::ReadTextureData()
{
   OGLTexture* texture;
   TextureData data;
   size_t numberOfElements;
   unsigned char* array;
   unordered_map<string, TextureData>& textureData = _sceneReader->GetTextureData();
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
   unordered_map<string, ObjectData>& objectData = _sceneReader->GetObjectData();
   for (auto it = objectData.begin(); it != objectData.end(); it++) {
      object = new GraphicsObject();
      data = it->second;
      for (auto mit = data.meshData.begin(); mit != data.meshData.end(); mit++) {
         meshData = *mit;
         CreateMesh(meshData, mesh);
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
         CreateFactoriedMesh(factoriedMeshData, mesh);
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

void OGLGraphicsScene::CreateMesh(MeshData& meshData, AbstractMesh*& mesh)
{
   if (meshData.vertexType == "PC") {
      mesh = CreatePCMesh(meshData);
   }
   else if (meshData.vertexType == "PCT") {
      mesh = CreatePCTMesh(meshData);
   }
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
   mesh->SetUpAttributes("PC");
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
   mesh->SetUpAttributes("PCT");
   return mesh;
}

void OGLGraphicsScene::CreateFactoriedMesh(FactoriedMeshData& factoriedMeshData, AbstractMesh*& mesh)
{
   if (factoriedMeshData.vertexType == "PC") {
      mesh = CreateFactoriedPCMesh(factoriedMeshData);
   } 
   else if (factoriedMeshData.vertexType == "PCT") {
      mesh = CreateFactoriedPCTMesh(factoriedMeshData);
   }
   else if (factoriedMeshData.vertexType == "PCNT") {
      mesh = CreateFactoriedPCNTMesh(factoriedMeshData);
   }
}

AbstractMesh* OGLGraphicsScene::CreateFactoriedPCMesh(FactoriedMeshData& meshData)
{
   OGLVertexMesh<VertexPC>* mesh = nullptr;
   if (meshData.meshType == "cuboid") {
      CreatePCCuboidMesh(meshData, mesh);
   }
   if (mesh) {
      mesh->SetUpAttributes("PC");
   }
   return mesh;
}

AbstractMesh* OGLGraphicsScene::CreateFactoriedPCTMesh(FactoriedMeshData& meshData)
{
   MeshFactory<VertexPCT, RGBA> pctFactory;
   OGLVertexMesh<VertexPCT>* mesh = nullptr;
   if (meshData.meshType == "flat") {
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
      mesh->SetUpAttributes("PCT");
   }
   return mesh;
}

AbstractMesh* OGLGraphicsScene::CreateFactoriedPCNTMesh(FactoriedMeshData& meshData)
{
   OGLVertexMesh<VertexPCNT>* mesh = nullptr;
   if (meshData.meshType == "flat") {
      CreatePCNTFlatMesh(meshData, mesh);
   }
   else if (meshData.meshType == "cuboid") {
      CreatePCNTCuboidMesh(meshData, mesh);
   }
   if (mesh) {
      if(meshData.hasMaterial) mesh->material = meshData.material;
      mesh->SetTexture(_textures[meshData.textureName]);
      mesh->SetUpAttributes("PCNT");
   }
   return mesh;
}

void OGLGraphicsScene::CreatePCNTFlatMesh(
   FactoriedMeshData& meshData, OGLVertexMesh<VertexPCNT>*& mesh)
{
   MeshFactory<VertexPCNT, RGBA> pcntFactory;
   if (meshData.whichPlane == "XZ") {
      mesh = (OGLVertexMesh<VertexPCNT>*)
         pcntFactory.NormalizedIndexedFlatTexturedMeshXZ(
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

void OGLGraphicsScene::CreatePCCuboidMesh(
   FactoriedMeshData& meshData, OGLVertexMesh<VertexPC>*& mesh)
{
   MeshFactory<VertexPC, RGB> pcntFactory;
   mesh = (OGLVertexMesh<VertexPC>*)
      pcntFactory.CuboidMesh(
         meshData.params[0], // width
         meshData.params[1], // height
         meshData.params[2], // depth
         {
            meshData.params[3], // r
            meshData.params[4], // g
            meshData.params[5], // b
         }
      );
}

void OGLGraphicsScene::CreatePCNTCuboidMesh(
   FactoriedMeshData& meshData, OGLVertexMesh<VertexPCNT>*& mesh)
{
   MeshFactory<VertexPCNT, RGBA> pcntFactory;
   mesh = (OGLVertexMesh<VertexPCNT>*)
      pcntFactory.NormalizedTexturedCuboidMesh(
         meshData.params[0], // width
         meshData.params[1], // height
         meshData.params[2], // depth
         {
            meshData.params[3], // r
            meshData.params[4], // g
            meshData.params[5], // b
            meshData.params[6]  // a
         },
         meshData.params[7], // repeatS
         meshData.params[8]  // repeatT
      );
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

