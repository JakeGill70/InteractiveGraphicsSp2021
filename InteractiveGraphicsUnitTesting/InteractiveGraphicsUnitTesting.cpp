#include "pch.h"
#include "CppUnitTest.h"
#include "../InteractiveGraphicsSp2021/BaseObject.cpp"
#include "../InteractiveGraphicsSp2021/AbstractReader.cpp"
#include "../InteractiveGraphicsSp2021/TextFileReader.cpp"
#include "../InteractiveGraphicsSp2021/SceneReader.cpp"
#include <fstream>
using std::ofstream;
#include <string>
using std::wstring;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace InteractiveGraphicsUnitTesting
{
   TEST_CLASS(ATextFileReader)
   {
   public:

      TEST_METHOD(ShouldHaveAnErrorIfTheFileWasNotFound)
      {
         TextFileReader sut("NoSuchFile.txt");
         sut.Open();
         Assert::IsTrue(sut.HasError());
      }

      TEST_METHOD(ShouldReportTheContentsOfAnExistingFile)
      {
         ofstream fout("TestFile.txt");
         fout << "Content Line 1" << std::endl
            << "Content Line 2" << std::endl;
         fout.close();

         TextFileReader sut("TestFile.txt");
         sut.Open();
         Assert::IsFalse(sut.HasError());
         sut.Read();
         string expected("Content Line 1\nContent Line 2\n");
         Assert::AreEqual(expected, sut.GetContents());

         std::remove("TestFile.txt");
      }
   };

   TEST_CLASS(ASceneReader)
   {
   public:

      TEST_METHOD(ShouldHaveAnErrorIfTheFileWasNotFound)
      {
         SceneReader sut("NoSuchFile.txt");
         sut.Open();
         Assert::IsTrue(sut.HasError());
      }

      TEST_METHOD(ShouldReportTheSingleCameraData)
      {
         ofstream fout("TestFile.txt");
         fout << "# camera name, pos x, pos y, pos z, fov, near plane, far plane" << std::endl;
         fout << "camera,1,2,3,60,0.1f,50" << std::endl;
         fout << "<endCameras>" << std::endl;
         fout.close();

         SceneReader sut("TestFile.txt");
         sut.Open();
         Assert::IsFalse(sut.HasError());
         sut.Read();
         vector<CameraData>& data = sut.GetCameraData();
         Assert::AreEqual(1, (int)data.size());
         string expected("camera");
         Assert::AreEqual(expected, data[0].name);
         Assert::AreEqual(1.0f, data[0].position.x);
         Assert::AreEqual(2.0f, data[0].position.y);
         Assert::AreEqual(3.0f, data[0].position.z);
         Assert::AreEqual(60.0f, data[0].fov);
         Assert::AreEqual(0.1f, data[0].nearPlane);
         Assert::AreEqual(50.0f, data[0].farPlane);

         std::remove("TestFile.txt");
      }

      TEST_METHOD(ShouldReportMultipleCameraData)
      {
         ofstream fout("TestFile.txt");
         fout << "# camera name, pos x, pos y, pos z, fov, near plane, far plane" << std::endl;
         fout << "camera,1,2,3,60,0.1f,50" << std::endl;
         fout << "camera2,1,2,3,60,0.1f,50" << std::endl;
         fout << "camera3,1,2,3,60,0.1f,50" << std::endl;
         fout << "<endCameras>" << std::endl;
         fout.close();

         SceneReader sut("TestFile.txt");
         sut.Open();
         Assert::IsFalse(sut.HasError());
         sut.Read();
         vector<CameraData>& data = sut.GetCameraData();
         Assert::AreEqual(3, (int)data.size());

         std::remove("TestFile.txt");
      }

      TEST_METHOD(ShouldReportTheSingleShaderData)
      {
         ofstream fout("TestFile.txt");
         fout << "# camera name, pos x, pos y, pos z, fov, near plane, far plane" << std::endl;
         fout << "camera,1,2,3,60,0.1f,50" << std::endl;
         fout << "<endCameras>" << std::endl;
         fout << "defaultShader,  default,default,none" << std::endl;
         fout << "<endShaders>" << std::endl;
         fout.close();

         SceneReader sut("TestFile.txt");
         sut.Open();
         Assert::IsFalse(sut.HasError());
         sut.Read();
         vector<ShaderData>& data = sut.GetShaderData();
         Assert::AreEqual(1, (int)data.size());
         string expected("defaultShader");
         Assert::AreEqual(expected, data[0].name);
         expected = "default";
         Assert::AreEqual(expected, data[0].vertexShaderFilePath);
         expected = "default";
         Assert::AreEqual(expected, data[0].fragmentShaderFilePath);
         expected = "none";
         Assert::AreEqual(expected, data[0].cameraName);

         std::remove("TestFile.txt");
      }

      TEST_METHOD(ShouldReportMultipleShaderData)
      {
         ofstream fout("TestFile.txt");
         fout << "# camera name, pos x, pos y, pos z, fov, near plane, far plane" << std::endl;
         fout << "camera,1,2,3,60,0.1f,50" << std::endl;
         fout << "<endCameras>" << std::endl;
         fout << "defaultShader,  default,default,none" << std::endl;
         fout << "simple3DShader,simple3Dvertex.glsl,default,camera" << std::endl;
         fout << "<endShaders>" << std::endl;
         fout.close();

         SceneReader sut("TestFile.txt");
         sut.Open();
         Assert::IsFalse(sut.HasError());
         sut.Read();
         vector<ShaderData>& data = sut.GetShaderData();
         Assert::AreEqual(2, (int)data.size());

         std::remove("TestFile.txt");
      }

      TEST_METHOD(ShouldReportOneArrayTexture)
      {
         ofstream fout("TestFile.txt");
         fout << "# camera name, pos x, pos y, pos z, fov, near plane, far plane" << std::endl;
         fout << "camera,1,2,3,60,0.1f,50" << std::endl;
         fout << "<endCameras>" << std::endl;
         fout << "defaultShader,  default,default,none" << std::endl;
         fout << "simple3DShader,simple3Dvertex.glsl,default,camera" << std::endl;
         fout << "<endShaders>" << std::endl;
         fout << "# texture name, width, height, number of channels, wrap s, wrap t, min filter, max filter" << std::endl;
         fout << "customTexture, repeat, repeat, nearest, nearest, 4, 4, 4" << std::endl;
         fout << "<array>" << std::endl;
         fout << "255,255,255,255,0,0,255,255,0,0,255,255,255,255,255,255" << std::endl;
         fout << "<endTexture>" << std::endl;
         fout << "<endTextures>" << std::endl;
         fout.close();

         SceneReader sut("TestFile.txt");
         sut.Open();
         Assert::IsFalse(sut.HasError());
         sut.Read();
         unordered_map<string, TextureData>& data = sut.GetTextureData();
         Assert::AreEqual(1, (int)data.size());
         TextureData texData = data.begin()->second;
         Assert::AreEqual(16, (int)texData.arrayData.size());

         std::remove("TestFile.txt");
      }

      TEST_METHOD(ShouldReportTwoArrayTextures)
      {
         ofstream fout("TestFile.txt");
         fout << "# camera name, pos x, pos y, pos z, fov, near plane, far plane" << std::endl;
         fout << "camera,1,2,3,60,0.1f,50" << std::endl;
         fout << "<endCameras>" << std::endl;
         fout << "defaultShader,  default,default,none" << std::endl;
         fout << "simple3DShader,simple3Dvertex.glsl,default,camera" << std::endl;
         fout << "<endShaders>" << std::endl;

         fout << "# texture name, width, height, number of channels, wrap s, wrap t, min filter, max filter" << std::endl;
         fout << "customTexture, repeat, repeat, nearest, nearest, 4, 4, 4" << std::endl;
         fout << "<array>" << std::endl;
         fout << "255,255,255,255,0,0,255,255,0,0,255,255,255,255,255,255" << std::endl;
         fout << "<endTexture>" << std::endl;

         fout << "customTexture2, repeat, repeat, nearest, nearest, 4, 4, 4" << std::endl;
         fout << "<array>" << std::endl;
         fout << "255,255,255,255,0,0,255,255,0,0,255,255,255,255,255" << std::endl;
         fout << "<endTexture>" << std::endl;
         fout << "<endTextures>" << std::endl;
         fout.close();

         SceneReader sut("TestFile.txt");
         sut.Open();
         Assert::IsFalse(sut.HasError());
         sut.Read();
         unordered_map<string, TextureData>& data = sut.GetTextureData();
         Assert::AreEqual(2, (int)data.size());

         TextureData texData = data["customTexture"];
         Assert::AreEqual(16, (int)texData.arrayData.size());
         texData = data["customTexture2"];
         Assert::AreEqual(15, (int)texData.arrayData.size());

         std::remove("TestFile.txt");
      }

      TEST_METHOD(ShouldReportTwoArrayTexturesOneFromFile)
      {
         ofstream fout("TestFile.txt");
         fout << "# camera name, pos x, pos y, pos z, fov, near plane, far plane" << std::endl;
         fout << "camera,1,2,3,60,0.1f,50" << std::endl;
         fout << "<endCameras>" << std::endl;
         fout << "defaultShader,  default,default,none" << std::endl;
         fout << "simple3DShader,simple3Dvertex.glsl,default,camera" << std::endl;
         fout << "<endShaders>" << std::endl;

         fout << "# texture name, width, height, number of channels, wrap s, wrap t, min filter, max filter" << std::endl;
         fout << "customTexture, repeat, repeat, nearest, nearest, 4, 4, 4" << std::endl;
         fout << "<array>" << std::endl;
         fout << "255,255,255,255,0,0,255,255,0,0,255,255,255,255,255,255" << std::endl;
         fout << "<endTexture>" << std::endl;

         fout << "someTexture" << std::endl;
         fout << "<file>" << std::endl;
         fout << "somefile.jpg" << std::endl;
         fout << "<endTexture>" << std::endl;
         fout << "<endTextures>" << std::endl;
         fout.close();

         SceneReader sut("TestFile.txt");
         sut.Open();
         Assert::IsFalse(sut.HasError());
         sut.Read();
         Assert::IsFalse(sut.HasError());
         unordered_map<string, TextureData>& data = sut.GetTextureData();
         Assert::AreEqual(2, (int)data.size());
         TextureData texData = data["customTexture"];
         Assert::AreEqual(16, (int)texData.arrayData.size());
         texData = data["someTexture"];
         Assert::AreEqual("somefile.jpg", texData.filePath.c_str());

         std::remove("TestFile.txt");
      }

      TEST_METHOD(CanReadATexturedObject)
      {
         ofstream fout("TestFile.txt");
          fout << "camera,1,2,3,60,0.1f,50" << std::endl;
         fout << "<endCameras>" << std::endl;
         fout << "defaultShader,  default,default,none" << std::endl;
         fout << "simple3DShader,simple3Dvertex.glsl,default,camera" << std::endl;
         fout << "simpleTextureShader, PCT3DVertexShader.glsl, TexFragmentShader.glsl, camera" << std::endl;
         fout << "<endShaders>" << std::endl;
         fout << "customTexture, repeat, repeat, nearest, nearest, 4, 4, 4" << std::endl;
         fout << "<array>" << std::endl;
         fout << "255,255,255,255,0,0,255,255,0,0,255,255,255,255,255,255" << std::endl;
         fout << "<endTexture>" << std::endl;
         fout << "someTexture" << std::endl;
         fout << "<file>" << std::endl;
         fout << "somefile.jpg" << std::endl;
         fout << "<endTexture>" << std::endl;
         fout << "<endTextures>" << std::endl;

         fout << "wall,simpleTextureShader" << std::endl;

         fout << "PCT,triangles,indexed,someTexture" << std::endl;
         fout << "-2,  1, 0, 1, 1, 1, 1, 0, 1" << std::endl;
         fout << "-2, -1, 0, 1, 1, 1, 1, 0, 0" << std::endl;
         fout << " 0, -1, 0, 1, 1, 1, 1, 1, 0" << std::endl;
         fout << " 0,  1, 0, 1, 1, 1, 1, 1, 1" << std::endl;
         fout << "<endVertexData>" << std::endl;
         fout << " 0, 1, 2, 0, 2, 3" << std::endl;
         fout << "<endIndexData>" << std::endl;
         fout << "<endMesh>" << std::endl;

         fout << "PCT,triangles,indexed,someTexture" << std::endl;
         fout << " 0,  1, 0, 1, 1, 1, 1, 0, 1" << std::endl;
         fout << " 0, -1, 0, 1, 1, 1, 1, 0, 0" << std::endl;
         fout << " 2, -1, 0, 1, 1, 1, 1, 1, 0" << std::endl;
         fout << " 2,  1, 0, 1, 1, 1, 1, 1, 1" << std::endl;
         fout << "<endVertexData>" << std::endl;
         fout << " 0, 1, 2, 0, 2, 3" << std::endl;
         fout << "<endIndexData>" << std::endl;
         fout << "<endMesh>" << std::endl;
         fout << "<endObject>" << std::endl;

         fout << "<endObjects>" << std::endl;
         fout.close();

         SceneReader sut("TestFile.txt");
         sut.Open();
         Assert::IsFalse(sut.HasError(), sut.WidenString(sut.GetLog()).c_str());

         sut.Read();
         Assert::IsFalse(sut.HasError(), sut.WidenString(sut.GetLog()).c_str());

         unordered_map<string, ObjectData>& data = sut.GetObjectData();
         Assert::AreEqual(1, (int)data.size());

         ObjectData objectData = data["wall"];
         Assert::AreEqual(2, (int)objectData.meshData.size());

         MeshData meshData = objectData.meshData[0];
         string expected = "PCT";
         Assert::AreEqual(expected, meshData.vertexType);

         expected = "triangles";
         Assert::AreEqual(expected, meshData.primitiveType);

         Assert::IsTrue(meshData.isIndexed);

         expected = "someTexture";
         Assert::AreEqual(expected, meshData.textureName);

         std::remove("TestFile.txt");
      }

      TEST_METHOD(CanReadATexturedFactoriedObject)
      {
         ofstream fout("TestFile.txt");
         fout << "camera,1,2,3,60,0.1f,50" << std::endl;
         fout << "<endCameras>" << std::endl;
         fout << "defaultShader,  default,default,none" << std::endl;
         fout << "simple3DShader,simple3Dvertex.glsl,default,camera" << std::endl;
         fout << "simpleTextureShader, PCT3DVertexShader.glsl, TexFragmentShader.glsl, camera" << std::endl;
         fout << "<endShaders>" << std::endl;
         fout << "customTexture, repeat, repeat, nearest, nearest, 4, 4, 4" << std::endl;
         fout << "<array>" << std::endl;
         fout << "255,255,255,255,0,0,255,255,0,0,255,255,255,255,255,255" << std::endl;
         fout << "<endTexture>" << std::endl;
         fout << "someTexture" << std::endl;
         fout << "<file>" << std::endl;
         fout << "somefile.jpg" << std::endl;
         fout << "<endTexture>" << std::endl;
         fout << "<endTextures>" << std::endl;

         fout << "wall,simpleTextureShader" << std::endl;

         fout << "PCT,triangles,indexed,someTexture" << std::endl;
         fout << "-2,  1, 0, 1, 1, 1, 1, 0, 1" << std::endl;
         fout << "-2, -1, 0, 1, 1, 1, 1, 0, 0" << std::endl;
         fout << " 0, -1, 0, 1, 1, 1, 1, 1, 0" << std::endl;
         fout << " 0,  1, 0, 1, 1, 1, 1, 1, 1" << std::endl;
         fout << "<endVertexData>" << std::endl;
         fout << " 0, 1, 2, 0, 2, 3" << std::endl;
         fout << "<endIndexData>" << std::endl;
         fout << "<endMesh>" << std::endl;

         fout << "PCT,triangles,indexed,someTexture" << std::endl;
         fout << " 0,  1, 0, 1, 1, 1, 1, 0, 1" << std::endl;
         fout << " 0, -1, 0, 1, 1, 1, 1, 0, 0" << std::endl;
         fout << " 2, -1, 0, 1, 1, 1, 1, 1, 0" << std::endl;
         fout << " 2,  1, 0, 1, 1, 1, 1, 1, 1" << std::endl;
         fout << "<endVertexData>" << std::endl;
         fout << " 0, 1, 2, 0, 2, 3" << std::endl;
         fout << "<endIndexData>" << std::endl;
         fout << "<endMesh>" << std::endl;
         fout << "<endObject>" << std::endl;

         fout << "object,someShader" << std::endl;
         fout << "<factoried mesh>" << std::endl;
         fout << "PCT, RGBA, flat, XZ, someTexture, 5, -5, 5, 5, 1, 1, 1, 1, 5, 5" << std::endl;
         fout << "<endMesh>" << std::endl;
         fout << "<endObject>" << std::endl;

         fout << "<endObjects>" << std::endl;
         fout.close();

         SceneReader sut("TestFile.txt");
         sut.Open();
         Assert::IsFalse(sut.HasError(), sut.WidenString(sut.GetLog()).c_str());

         sut.Read();
         Assert::IsFalse(sut.HasError(), sut.WidenString(sut.GetLog()).c_str());

         unordered_map<string, ObjectData>& data = sut.GetObjectData();
         Assert::AreEqual(2, (int)data.size());

         ObjectData objectData = data["object"];
         Assert::AreEqual(1, (int)objectData.factoriedMeshData.size());

         string expectedStr = "PCT";
         Assert::AreEqual(expectedStr, objectData.factoriedMeshData[0].vertexType);

         expectedStr = "flat";
         Assert::AreEqual(expectedStr, objectData.factoriedMeshData[0].meshType);

         expectedStr = "XZ";
         Assert::AreEqual(expectedStr, objectData.factoriedMeshData[0].whichPlane);

         expectedStr = "someTexture";
         Assert::AreEqual(expectedStr, objectData.factoriedMeshData[0].textureName);

         size_t expectedInt = 10;
         Assert::AreEqual(expectedInt, objectData.factoriedMeshData[0].params.size());

         std::remove("TestFile.txt");
      } // TEST_METHOD(CanReadATexturedFactoriedObject)

      TEST_METHOD(CanReadASceneFile)
      {
         ofstream fout("TestFile.txt");
         fout << "camera,1,2,3,60,0.1f,50" << std::endl;
         fout << "<endCameras>" << std::endl;

         fout << "defaultShader,  default,default,none" << std::endl;
         fout << "simple3DShader,simple3Dvertex.glsl,default,camera" << std::endl;
         fout << "simpleTextureShader, PCT3DVertexShader.glsl, TexFragmentShader.glsl, camera" << std::endl;
         fout << "<endShaders>" << std::endl;

         fout << "global, 101, 102, 103, 0.1, 0.2, 0.3, 0.4, 0.5" << std::endl;
         fout << "local, 0, 0.5f, 2.0f, 1, 1, 1, 0.5f, 1" << std::endl;
         fout << "local, 0, 0.5f, 2.0f, 1, 1, 1, 0.5f, 1" << std::endl;
         fout << "<endLights>" << std::endl;

         fout << "customTexture, repeat, repeat, nearest, nearest, 4, 4, 4" << std::endl;
         fout << "<array>" << std::endl;
         fout << "255,255,255,255,0,0,255,255,0,0,255,255,255,255,255,255" << std::endl;
         fout << "<endTexture>" << std::endl;
         fout << "someTexture" << std::endl;
         fout << "<file>" << std::endl;
         fout << "somefile.jpg" << std::endl;
         fout << "<endTexture>" << std::endl;
         fout << "<endTextures>" << std::endl;

         fout << "wall,simpleTextureShader" << std::endl;

         fout << "PCT,triangles,indexed,someTexture" << std::endl;
         fout << "-2,  1, 0, 1, 1, 1, 1, 0, 1" << std::endl;
         fout << "-2, -1, 0, 1, 1, 1, 1, 0, 0" << std::endl;
         fout << " 0, -1, 0, 1, 1, 1, 1, 1, 0" << std::endl;
         fout << " 0,  1, 0, 1, 1, 1, 1, 1, 1" << std::endl;
         fout << "<endVertexData>" << std::endl;
         fout << " 0, 1, 2, 0, 2, 3" << std::endl;
         fout << "<endIndexData>" << std::endl;
         fout << "<endMesh>" << std::endl;

         fout << "PCT,triangles,indexed,someTexture" << std::endl;
         fout << " 0,  1, 0, 1, 1, 1, 1, 0, 1" << std::endl;
         fout << " 0, -1, 0, 1, 1, 1, 1, 0, 0" << std::endl;
         fout << " 2, -1, 0, 1, 1, 1, 1, 1, 0" << std::endl;
         fout << " 2,  1, 0, 1, 1, 1, 1, 1, 1" << std::endl;
         fout << "<endVertexData>" << std::endl;
         fout << " 0, 1, 2, 0, 2, 3" << std::endl;
         fout << "<endIndexData>" << std::endl;
         fout << "<endMesh>" << std::endl;
         fout << "<endObject>" << std::endl;

         fout << "object,someShader" << std::endl;
         fout << "<factoried mesh>" << std::endl;
         fout << "PCT, RGBA, flat, XZ, someTexture, 5, -5, 5, 5, 1, 1, 1, 1, 5, 5" << std::endl;
         fout << "<endMesh>" << std::endl;
         fout << "<endObject>" << std::endl;

         fout << "object2,someShader2" << std::endl;
         fout << "<factoried mesh>" << std::endl;
         fout << "PCNT, RGBA, cuboid, someTexture2, 4, 4, 4, 1, 1, 1, 1, 1, 1" << std::endl;
         fout << "material, 0.1, 0.2, 0.3" << std::endl;
         fout << "<endMesh>" << std::endl;
         fout << "<endObject>" << std::endl;

         fout << "<endObjects>" << std::endl;
         fout.close();

         size_t expectedInt;
         float expectedFloat;
         string expectedStr;

         SceneReader sut("TestFile.txt");
         sut.Open();
         Assert::IsFalse(sut.HasError(), sut.WidenString(sut.GetLog()).c_str());

         sut.Read();
         Assert::IsFalse(sut.HasError(), sut.WidenString(sut.GetLog()).c_str());

         // LIGHTS

         vector<LightData>& allLights = sut.GetLightData();

         expectedInt = 3;
         Assert::AreEqual(expectedInt, allLights.size());

         LightData lightData;
         // "global, 101, 102, 103, 0.1, 0.2, 0.3, 0.4, 0.5"
         lightData = allLights[0];
         expectedStr = "global";
         Assert::AreEqual(expectedStr, lightData.type);

         // OBJECTS

         unordered_map<string, ObjectData>& allObjects = sut.GetObjectData();

         expectedInt = 3;
         Assert::AreEqual(expectedInt, allObjects.size());

         ObjectData objectData = allObjects["object"];
         Assert::AreEqual(1, (int)objectData.factoriedMeshData.size());

         expectedStr = "PCT";
         Assert::AreEqual(expectedStr, objectData.factoriedMeshData[0].vertexType);

         expectedStr = "flat";
         Assert::AreEqual(expectedStr, objectData.factoriedMeshData[0].meshType);

         expectedStr = "XZ";
         Assert::AreEqual(expectedStr, objectData.factoriedMeshData[0].whichPlane);

         expectedStr = "someTexture";
         Assert::AreEqual(expectedStr, objectData.factoriedMeshData[0].textureName);

         expectedInt = 10;
         Assert::AreEqual(expectedInt, objectData.factoriedMeshData[0].params.size());

         objectData = allObjects["object2"];

         expectedInt = 1;
         Assert::AreEqual(expectedInt, objectData.factoriedMeshData.size());

         expectedStr = "PCNT";
         Assert::AreEqual(expectedStr, objectData.factoriedMeshData[0].vertexType);

         expectedStr = "RGBA";
         Assert::AreEqual(expectedStr, objectData.factoriedMeshData[0].colorType);

         expectedStr = "cuboid";
         Assert::AreEqual(expectedStr, objectData.factoriedMeshData[0].meshType);

         expectedStr = "someTexture2";
         Assert::AreEqual(expectedStr, objectData.factoriedMeshData[0].textureName);

         expectedInt = 9;
         Assert::AreEqual(expectedInt, objectData.factoriedMeshData[0].params.size());

         expectedFloat = 0.1f;
         Assert::AreEqual(expectedFloat, objectData.factoriedMeshData[0].material.ambientIntensity);

         expectedFloat = 0.2f;
         Assert::AreEqual(expectedFloat, objectData.factoriedMeshData[0].material.specularIntensity);

         expectedFloat = 0.3f;
         Assert::AreEqual(expectedFloat, objectData.factoriedMeshData[0].material.shininess);

         std::remove("TestFile.txt");
      } // TEST_METHOD(CanReadATexturedFactoriedCuboidPCNTRGBA)


   };
}
