#pragma once
#ifndef SCENE_READER
#define SCENE_READER

#include "AbstractReader.h"
#include <string>
using std::string;
#include <fstream>
#include "GraphicsStructures.h"
using std::ifstream;
#include <vector>
using std::vector;
#include <unordered_map>
using std::unordered_map;
#include "OGLVertexMesh.hpp"

struct CameraData{
   string name;
   Vector3D position;
   float fov, nearPlane, farPlane;
};

struct LightData {
   string type;
   Light light;
};

struct ShaderData {
   string name;
   string vertexShaderFilePath;
   string fragmentShaderFilePath;
   string cameraName;
};

struct MeshData {
   string vertexType;
   string primitiveType;
   string textureName;
   bool isIndexed;
   vector<float> vertexData;
   vector<unsigned short> indexData;
   Material material;
};

struct FactoriedMeshData {
   string vertexType;
   string colorType;
   string meshType;
   string whichPlane;
   string textureName;
   vector<float> params;
   bool hasMaterial;
   Material material;
};

struct ObjFileMeshData {
    string textureName;
    bool hasMaterial;
    Material material;
    OGLVertexMesh<VertexPCNT>* meshPtr;
};

struct ObjectData {
   string name;
   string shaderName;
   vector<MeshData> meshData;
   vector<FactoriedMeshData> factoriedMeshData;
   vector<ObjFileMeshData> objMeshData;
};

// texture name, width, height, number of channels, wrap s, wrap t, min filter, max filter
struct TextureData {
   string name;
   int width, height, numberOfChannels;
   string wrapS, wrapT, minFilter, maxFilter;
   vector<unsigned char> arrayData;
   string filePath;
};

class SceneReader :
    public AbstractReader
{
protected:
   string _filePath;
   ifstream _fin;
   bool _errorOccurred;
   vector<CameraData> _cameraData;
   vector<ShaderData> _shaderData;
   vector<LightData> _lightData;
   unordered_map<string, ObjectData> _objectData;
   unordered_map<string, TextureData> _textureData;
   string _currentName;
   string _state;
   int _currentMeshIndex;

public:
   SceneReader(string filePath) : _filePath(filePath), _errorOccurred(false), 
      _currentName(""), _currentMeshIndex(0), _state("reading cameras")
   {}
   void Open();
   void Read();
   void Close();
   bool HasError() { return _errorOccurred; }

   vector<CameraData>& GetCameraData() {
      return _cameraData;
   }

   vector<ShaderData>& GetShaderData() {
      return _shaderData;
   }

   vector<LightData>& GetLightData() {
      return _lightData;
   }

   unordered_map<string, ObjectData>& GetObjectData() {
      return _objectData;
   }

   unordered_map<string, TextureData>& GetTextureData() {
      return _textureData;
   }

protected:
   virtual void ProcessLine(const string& line);
   virtual void ProcessCameraLine(const string& line);
   virtual void ProcessShaderLine(const string& line);
   virtual void ProcessLightLine(const string& line);
   virtual void ProcessObjectLine(const string& line);
   virtual void ProcessMeshDataLine(const string& line);
   virtual void ProcessFactoriedMeshDataLine(const string& line);
   virtual void ProcessVertexDataLine(const string& line);
   virtual void ProcessIndexDataLine(const string& line);
   virtual void ProcessTextureLine(const string& line);
   virtual void ProcessTextureArrayLine(const string& line);
   virtual void ProcessTextureFileLine(const string& line);
   virtual void ProcessObjFileLine(const string& line);
};

#endif

