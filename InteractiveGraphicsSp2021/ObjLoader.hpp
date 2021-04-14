#pragma once
#ifndef OBJ_READER
#define OBJ_READER


#include "BaseObject.h"
#include "OGLVertexMesh.hpp"
#include "AbstractReader.h"
#include <fstream>

class ObjReader :
	public AbstractReader
{
protected:
	string _filePath;
	ifstream _fin;
	bool _errorOccurred;
	std::vector< unsigned int > _vertexIndices, _uvIndices, _normalIndices;
	std::vector< glm::vec3 > _temp_vertices;
	std::vector< glm::vec2 > _temp_uvs;
	std::vector< glm::vec3 > _temp_normals;
public:
	ObjReader(string filePath) : _filePath(filePath), _errorOccurred(false)	{}
	void Open();
	void Read();
	void Close();
	bool HasError() { return _errorOccurred; }
	virtual OGLVertexMesh<VertexPCNT>* LoadOBJ();
protected:
	virtual void ProcessLine(string line);
};

#endif