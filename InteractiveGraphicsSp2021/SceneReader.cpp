#include "SceneReader.h"

SceneReader::SceneReader(const string& filePath) {
	SetFilePath(filePath);
	_errorOccurred = false;
	_state = "reading cameras";
}

void SceneReader::SetFilePath(const string& path) {
	_filePath = path;
}

bool SceneReader::HasError() {
	return _errorOccurred;
}

void SceneReader::Open() {
	_fin.open(_filePath);
	if (_fin.fail()) {
		_errorOccurred = true;

		char buffer[256];
		strerror_s(buffer, 256, errno);
		Log(buffer);
	}
}

void SceneReader::Read() {
	if (HasError()) {
		return;
	}

	string line;
	while (!_fin.eof()) {
		std::getline(_fin, line);
		Trim(line);
		if (!line.empty()) {
			ProcessLine(line);
		}
	}
}

void SceneReader::Close() {
	_fin.close();
}

vector<CameraData>& SceneReader::GetCameraData() {
	return _cameraData;
}

vector<ShaderData>& SceneReader::GetShaderData() {
	return _shaderData;
}

void SceneReader::ProcessLine(const string& line) {
	if (line.substr(0, 1).compare("#") == 0) {
		// Ignore comments
		return;
	}

	if (_state.compare("reading cameras") == 0) {
		ProcessCameraLine(line);
	}
	else if (_state.compare("reading shaders") == 0) {
		ProcessShaderLine(line);
	}
}

void SceneReader::ProcessCameraLine(const string& line) {
	if (line.compare("<endCameras>") == 0) {
		_state = "reading shaders";
		return;
	}
	//Split the line on �, � into tokens
	vector<string> tokens;
	Split(line, ',', tokens);
	//If the number of tokens is not 7
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

void SceneReader::ProcessShaderLine(const string& line) {
	if (line.compare("<endShaders>") == 0) {
		_state = "reading objects";
		return;
	}
	//Split the line on �, � into tokens
	vector<string> tokens;
	Split(line, ',', tokens);
	//If the number of tokens is not 7
	if (tokens.size() != 4) {
		_errorOccurred = true;
		_log << "This line is badly formatted: " << line << std::endl;
		return;
	}

	for (int i = 0; i < tokens.size(); i++)
	{
		Trim(tokens[i]);
	}

	ShaderData data;
	data.name = tokens[0];
	data.vertexShader_filepath = tokens[1];
	data.fragmentShader_filepath = tokens[2];
	data.cameraName = tokens[3];
	_shaderData.push_back(data);
}