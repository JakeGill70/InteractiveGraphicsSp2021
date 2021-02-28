#include "SceneReader.h"

void SceneReader::Open()
{
   _fin.open(_filePath.c_str());
   if (_fin.fail()) {
      _errorOccurred = true;
      char buffer[256];
      strerror_s(buffer, 256, errno);
      Log(buffer);
   }
}

void SceneReader::Read()
{
   if (_errorOccurred) return;
   string line;
   while (!_fin.eof()) {
      getline(_fin, line);
      Trim(line);
      if (line != "") {
         ProcessLine(line);
      }
   }
}

void SceneReader::ProcessLine(const string& line)
{
   if (line.substr(0, 1) == "#") return;
   if (_state == "reading cameras") {
      ProcessCameraLine(line);
   }
}

void SceneReader::ProcessCameraLine(const string& line)
{
   if (line == "<endCameras>") {
      _state = "reading shaders";
      return;
   }
   vector<string> tokens;
   Split(line, ',', tokens);
   if (tokens.size() != 7) {
      _errorOccurred = true;
      _log << "This line is badly formatted: " << line << std::endl;
   }
   // camera name, camera position, the field of view, the near plane, and the far plane
   CameraData data;
   data.name = tokens[0];
   data.position = {
      std::stof(tokens[1]),
      std::stof(tokens[2]),
      std::stof(tokens[3])
   };
   data.fov = std::stof(tokens[4]);
   data.nearPlane = std::stof(tokens[5]);
   data.farPlane = std::stof(tokens[6]);
   _cameraData.push_back(data);
}

void SceneReader::Close()
{
   _fin.close();
}

void SceneReader::ReadCameraData()
{
}



