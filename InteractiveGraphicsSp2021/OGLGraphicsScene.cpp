#include "OGLGraphicsScene.h"
#include "OGLShader.h"
#include "GraphicsStructures.h"
#include "OGLGraphicsObject.hpp"

OGLGraphicsScene::OGLGraphicsScene(SceneReader* sceneReader) {
	_sceneReader = sceneReader;
}

OGLGraphicsScene::~OGLGraphicsScene() {
	delete _sceneReader;
}


bool OGLGraphicsScene::Create() {
	/*======================================\\
	||            Read Scene Data           ||
	\\=====================================*/
	_sceneReader->Open();
	_sceneReader->Read();
	if (_sceneReader->HasError()) {
		return false;
	}
	_sceneReader->Close();

	/*======================================\\
	||            Create Cameras            ||
	\\=====================================*/
	for (int i = 0; i < _sceneReader->GetCameraData().size(); i++) {
		auto camData = _sceneReader->GetCameraData()[i];
		BaseCamera* cam = new BaseCamera();
		cam->frame.SetPosition(camData.position.x, camData.position.y, camData.position.z);
		cam->farPlane = camData.farPlane;
		cam->nearPlane = camData.nearPlane;
		cam->fieldOfView = camData.fov;
		cam->UpdateView();
		addCamera(camData.name, cam);
	}


	/*======================================\\
	||            Create Shaders            ||
	\\=====================================*/
	if (!ReadShaderData()) { 
		return false; 
	}

	/*======================================\\
	||            Create Objects            ||
	\\=====================================*/

	//========== Triangle ==========

	OGLGraphicsObject<VertexPC>* triangle = new OGLGraphicsObject<VertexPC>();
	AddGraphicsObject("trianlge", triangle, "defaultShader");
	triangle->AddVertex({ 0,  0.5f, 0, 1, 0, 0 });
	triangle->AddVertex({ -0.5f, -0.5f, 0, 0, 0, 1 });
	triangle->AddVertex({ 0.5f, -0.5f, 0, 0, 1, 0 });
	triangle->SendToGPU();

	//========== Cube ==========

	OGLGraphicsObject<VertexPC>* cube = new OGLGraphicsObject<VertexPC>();
	AddGraphicsObject("cube", cube, "simple3DShader");
	// Red vertices
	VertexPC V1 = { -0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f };
	VertexPC V2 = { -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f };
	VertexPC V3 = { 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f };
	VertexPC V4 = { 0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f };
	// Mixed color vertices
	VertexPC V5 = { 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f };
	VertexPC V6 = { 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f };
	VertexPC V7 = { -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f };
	VertexPC V8 = { -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f };
	// Face 1
	cube->AddVertex(V1);
	cube->AddVertex(V2);
	cube->AddVertex(V3);
	cube->AddVertex(V1);
	cube->AddVertex(V3);
	cube->AddVertex(V4);
	// Face 2
	cube->AddVertex(V4);
	cube->AddVertex(V3);
	cube->AddVertex(V6);
	cube->AddVertex(V4);
	cube->AddVertex(V6);
	cube->AddVertex(V5);
	// Face 3
	cube->AddVertex(V5);
	cube->AddVertex(V6);
	cube->AddVertex(V7);
	cube->AddVertex(V5);
	cube->AddVertex(V7);
	cube->AddVertex(V8);
	// Face 4
	cube->AddVertex(V8);
	cube->AddVertex(V7);
	cube->AddVertex(V2);
	cube->AddVertex(V8);
	cube->AddVertex(V2);
	cube->AddVertex(V1);
	// Face 5
	cube->AddVertex(V6);
	cube->AddVertex(V3);
	cube->AddVertex(V2);
	cube->AddVertex(V6);
	cube->AddVertex(V2);
	cube->AddVertex(V7);
	// Face 6
	cube->AddVertex(V8);
	cube->AddVertex(V1);
	cube->AddVertex(V4);
	cube->AddVertex(V8);
	cube->AddVertex(V4);
	cube->AddVertex(V5);
	cube->SendToGPU();

	return true;
}

bool OGLGraphicsScene::ReadShaderData() {
	auto shaderDataSet = _sceneReader->GetShaderData();
	for (int i = 0; i < shaderDataSet.size(); i++) {
		ShaderData shaderData = shaderDataSet[i];

		OGLShader* shader = new OGLShader();

		// Get vertex shader data
		if (shaderData.vertexShader_filepath.compare("default") != 0) {
			_textFileReader->SetFilePath(shaderData.vertexShader_filepath);
			_textFileReader->Open();
			_textFileReader->Read();
			_textFileReader->Close();
			if (_textFileReader->HasError()) {
				return false;
			}
			shader->SetVertexSource(_textFileReader->GetContents());
		}

		// Get fragment shader data
		if (shaderData.fragmentShader_filepath.compare("default") != 0) {
			_textFileReader->SetFilePath(shaderData.fragmentShader_filepath);
			_textFileReader->Open();
			_textFileReader->Read();
			_textFileReader->Close();
			if (_textFileReader->HasError()) {
				return false;
			}
			shader->SetFragmentSource(_textFileReader->GetContents());
		}

		// Attempt to create the shader
		try
		{
			shader->Create();
			shader->SetPositionAttribute({ 0,  3, sizeof(VertexPC), 0 });
			shader->SetColorAttribute({ 1, 3, sizeof(VertexPC), sizeof(GLfloat) * 3 });
			AddShader(shaderData.name, shader);
		}
		catch (const std::exception&)
		{
			_log << "Could not create shader '" << shaderData.name << "'." << std::endl;
			return false;
		}

		// Get camera data
		try
		{
			if (shaderData.cameraName.compare("none") != 0) {
				_shaders[shaderData.name]->SetCamera(_cameras[shaderData.cameraName]);
			}
		}
		catch (const std::exception&)
		{
			_log << "Could not add camera '" << shaderData.cameraName << "' to shader '" << shaderData.name << "'." << std::endl;
			return false;
		}
	}
	return true;
}