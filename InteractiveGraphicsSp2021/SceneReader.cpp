#include "SceneReader.h"

SceneReader::SceneReader(const string& filePath) {
	SetFilePath(filePath);
	_errorOccurred = false;
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

		}
	}
}

void SceneReader::Close() {
	_fin.close();
}

std::vector<CameraData>& SceneReader::GetCameraData() {
	return _cameraData;
}
