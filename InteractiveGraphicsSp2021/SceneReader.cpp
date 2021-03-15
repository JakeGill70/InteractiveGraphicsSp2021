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
   if (line.substr(0, 1) == "#") 
       return;
   if (_state == "reading cameras") {
      ProcessCameraLine(line);
   }
   else if (_state == "reading shaders") {
      ProcessShaderLine(line);
   }
   else if (_state == "reading objects") {
       ProcessObjectLine(line);
   }
   else if (_state == "reading objects") {
       ProcessVertexDataLine(line);
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
      return;
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

void SceneReader::ProcessShaderLine(const string& line)
{
   if (line == "<endShaders>") {
      _state = "reading objects";
      return;
   }
   vector<string> tokens;
   Split(line, ',', tokens);
   if (tokens.size() != 4) {
      _errorOccurred = true;
      _log << "This line is badly formatted: " << line << std::endl;
      return;
   }
   for (size_t i = 0; i < tokens.size(); i++) {
      Trim(tokens[i]);
   }
   // shader name, file path of vertex shader, file path of fragment shader, camera name
   ShaderData data;
   data.name = tokens[0];
   data.vertexShaderFilePath = tokens[1];
   data.fragmentShaderFilePath = tokens[2];
   data.cameraName = tokens[3];
   _shaderData.push_back(data);
}

void SceneReader::ProcessObjectLine(const string& line) {
    if (line == "<endObjects>") {
        _state = "end";
        return;
    }
    vector<string> tokens;
    Split(line, ',', tokens);
    if (tokens.size() != 4) {
        _errorOccurred = true;
        _log << "This line is badly formatted: " << line << std::endl;
        return;
    }
    for (size_t i = 0; i < tokens.size(); i++) {
        Trim(tokens[i]);
    }
    // vertex type, object name, shader name, primitive type
    ObjectData data;
    data.vertexType = tokens[0];
    data.name = tokens[1];
    data.shaderName = tokens[2];
    data.primitiveType = tokens[3];
    _objectData[data.name] = data;
    _currentObjectName = data.name;
    _state = "reading vertex data";
}

void SceneReader::ProcessVertexDataLine(const string& line) {
    if (line == "<endVertexData>") {
        _state = "reading objects";
        return;
    }
    vector<string> tokens;
    Split(line, ',', tokens);
    if (tokens.size() != 4) {
        _errorOccurred = true;
        _log << "This line is badly formatted: " << line << std::endl;
        return;
    }
    for (size_t i = 0; i < tokens.size(); i++) {
        Trim(tokens[i]);
        float number = std::stof(tokens[i]);
        _objectData[_currentObjectName].vertexData.push_back(number);
    }
}

void SceneReader::Close()
{
   _fin.close();
}




