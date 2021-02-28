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

struct CameraData{
   string name;
   Vector3D position;
   float fov, nearPlane, farPlane;
};

class SceneReader :
    public AbstractReader
{
protected:
   string _filePath;
   ifstream _fin;
   bool _errorOccurred;
   vector<CameraData> _cameraData;
   string _state;

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

protected:
   virtual void ReadCameraData();
   virtual void ProcessLine(const string& line);
   virtual void ProcessCameraLine(const string& line);
};

#endif

