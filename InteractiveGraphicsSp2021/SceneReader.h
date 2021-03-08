#pragma once

#ifndef SCENE_READER
#define SCENE_READER

#include "GraphicsStructures.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

struct CameraData {
	string name;
	Vector3D position;
	float fov;
	float nearPlane;
	float farPlane;
};

struct ShaderData {
	string name;
	string vertexShader_filepath;
	string fragmentShader_filepath;
	string cameraName;
};

#include "AbstractReader.h"
class SceneReader :
	public AbstractReader
{
protected:
	string _filePath;
	ifstream _fin;
	bool _errorOccurred;
	vector<CameraData> _cameraData;
	vector<ShaderData> _shaderData;
	string _state;

	void ProcessLine(const string& line);
	void ProcessCameraLine(const string& line);
	virtual void ProcessShaderLine(const string& line);

public:
	SceneReader(const string& filePath);

	void Open();
	void Read();
	void Close();
	bool HasError();

	void SetFilePath(const string& path);

	vector<CameraData>& GetCameraData();
	vector<ShaderData>& GetShaderData();
};

#endif // !SCENE_READER
