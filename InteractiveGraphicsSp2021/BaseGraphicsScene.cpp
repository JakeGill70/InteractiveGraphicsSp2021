#include "BaseGraphicsScene.h"


BaseGraphicsScene::BaseGraphicsScene() {
	_currentCamera = nullptr;
}

BaseGraphicsScene::~BaseGraphicsScene() {
	clearMap(_shaders);
	clearMap(_objects);
	clearMap(_cameras);
	_currentCamera = nullptr;
}

void BaseGraphicsScene::Create() {};

void BaseGraphicsScene::AddShader(string name, AbstractShader* shader) {
	_shaders[name] = shader;
}

void  BaseGraphicsScene::AddGraphicsObject(string name, AbstractGraphicsObject* object, string shaderName) {
	_objects[name] = object;
	_shaders[shaderName]->AddObjectToRender(name, object);
}

void BaseGraphicsScene::addCamera(string name, BaseCamera* camera) {
	_cameras[name] = camera;
}

void BaseGraphicsScene::SetCurrentCamera(string cameraName) {
	_currentCamera = _cameras[cameraName];
}

void BaseGraphicsScene::Render() {
	for (auto iterator = _shaders.begin(); iterator != _shaders.end(); iterator++) {
		AbstractShader* shader = iterator->second;
		shader->RenderObjects();
	}
}

void BaseGraphicsScene::UpdateCameraProjection(float aspectRatio) {
	for (auto iterator = _cameras.begin(); iterator != _cameras.end(); iterator++) {
		BaseCamera* camera = iterator->second;
		camera->UpdateProjection(aspectRatio);
	}
}