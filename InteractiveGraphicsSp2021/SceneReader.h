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
#include <map>

struct CameraData{
   string name;
   Vector3D position;
   float fov, nearPlane, farPlane;
};

struct ShaderData {
   string name;
   string vertexShaderFilePath;
   string fragmentShaderFilePath;
   string cameraName;
};

struct ObjectData {
    string vertexType;
    string name;
    string shaderName;
    string primitiveType;
    vector<float> vertexData;
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
   std::map<string, ObjectData> _objectData;
   string _state;
   string _currentObjectName;

public:
   SceneReader(string filePath) : _filePath(filePath), _errorOccurred(false), _state("reading cameras")
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

   std::map<string, ObjectData>& GetObjectData() {
       return _objectData;
   }


protected:
   virtual void ProcessLine(const string& line);
   virtual void ProcessCameraLine(const string& line);
   virtual void ProcessShaderLine(const string& line);
   virtual void ProcessObjectLine(const string& line);
   virtual void ProcessVertexDataLine(const string& line);
};

#endif

