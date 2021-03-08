#pragma once

#ifndef BASE_GRAPHICS_SCENE
#define BASE_GRAPHICS_SCENE

#include <string>
#include "BaseObject.h"
#include "AbstractShader.h"
#include <map>

using std::string;
using std::map;

//class AbstractGraphicsObject;

class BaseGraphicsScene :
	public BaseObject
{
protected:
	map<string, AbstractShader*> _shaders;
	map<string, AbstractGraphicsObject*> _objects;
	map<string, BaseCamera*> _cameras;
	BaseCamera* _currentCamera;

public:
	BaseGraphicsScene();
	~BaseGraphicsScene();

	virtual void Create();
	virtual void AddShader(string name, AbstractShader* shader);
	virtual void AddGraphicsObject(string name, AbstractGraphicsObject* object, string shaderName);
	virtual void addCamera(string name, BaseCamera* camera);
	virtual void SetCurrentCamera(string cameraName);
	virtual void Render();
	virtual void UpdateCameraProjection(float aspectRatio);

private:
	template<class T>
	inline void clearMap(map<string, T> m) {
		for (auto iterator = m.begin(); iterator != m.end(); iterator++) {
			delete iterator->second;
		}
		m.clear();
	}
};

#endif