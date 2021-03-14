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
   else if (_state == "reading shaders") {
      ProcessShaderLine(line);
   }
   else if (_state == "reading objects") {
      ProcessObjectLine(line);
   }
   else if (_state == "reading mesh data") {
      ProcessMeshDataLine(line);
   }
   else if (_state == "reading vertex data") {
      ProcessVertexDataLine(line);
   }
   else if (_state == "reading index data") {
      ProcessIndexDataLine(line);
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

void SceneReader::ProcessObjectLine(const string& line)
{
   if (line == "<endObjects>") {
      _state = "end";
      return;
   }
   vector<string> tokens;
   Split(line, ',', tokens);
   if (tokens.size() != 2) {
      _errorOccurred = true;
      _log << "This line is badly formatted: " << line << std::endl;
      return;
   }
   for (size_t i = 0; i < tokens.size(); i++) {
      Trim(tokens[i]);
   }
   // vertex type, object name, shader name, primitive type
   ObjectData data;
   data.name = tokens[0];
   data.shaderName = tokens[1];
   _objectData[data.name] = data;
   _currentObjectName = data.name;
   _state = "reading mesh data";
}

void SceneReader::ProcessMeshDataLine(const string& line)
{
   if (line == "<endMesh>") {
      _state = "reading objects";
      _currentMeshIndex = 0;
      return;
   }
   vector<string> tokens;
   Split(line, ',', tokens);
   if (tokens.size() == 2) tokens.push_back("not indexed");
   if (tokens.size() != 3) {
      _errorOccurred = true;
      _log << "This line is badly formatted: " << line << std::endl;
      return;
   }
   MeshData data;
   data.vertexType = tokens[0];
   data.primitiveType = tokens[1];
   data.isIndexed = (tokens[2] == "indexed");
   _objectData[_currentObjectName].meshData.push_back(data);
   _state = "reading vertex data";
}

void SceneReader::ProcessVertexDataLine(const string& line)
{
   if (line == "<endVertexData>") {
      _state = "reading index data";
      return;
   }
   vector<string> tokens;
   Split(line, ',', tokens);
   for (size_t i = 0; i < tokens.size(); i++) {
      Trim(tokens[i]);
      MeshData& meshData = _objectData[_currentObjectName].meshData[_currentMeshIndex];
      meshData.vertexData.push_back(std::stof(tokens[i]));
   }
}

void SceneReader::ProcessIndexDataLine(const string& line)
{
   if (line == "<endIndexData>") {
      _state = "reading mesh data";
      _currentMeshIndex++;
      return;
   }
   vector<string> tokens;
   Split(line, ',', tokens);
   for (size_t i = 0; i < tokens.size(); i++) {
      Trim(tokens[i]);
      MeshData& meshData = _objectData[_currentObjectName].meshData[_currentMeshIndex];
      meshData.indexData.push_back(std::stoi(tokens[i]));
   }
}

void SceneReader::Close()
{
   _fin.close();
}




