#include "ObjLoader.hpp"

/*
Implementation informed by this tutorial:
http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
*/

void ObjReader::Open()
{
	_fin.open(_filePath.c_str());
	if (_fin.fail()) {
		_errorOccurred = true;
		char buffer[256];
		strerror_s(buffer, 256, errno);
		Log(buffer);
	}
}

void ObjReader::Read()
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

void ObjReader::ProcessLine(string line) {
	//char lineHeader[128];
	//// read the first word of the line
	//int res = fscanf_s(file, "%s", lineHeader);

	string lineHeader = line.substr(0, line.find(" "));

	vector<string> tokens;
	Split(line, ',', tokens);

	// Load vertices
	if (lineHeader == "v") {
		glm::vec3 vertex;
		sscanf_s(line.c_str(), "v %f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
		_temp_vertices.push_back(vertex);
	}
	// Load texture coordinate
	else if (lineHeader == "vt") {
		glm::vec2 uv;
		sscanf_s(line.c_str(), "vt %f %f\n", &uv.x, &uv.y);
		_temp_uvs.push_back(uv);
	}
	// Load vertex normals
	else if (lineHeader == "vn") {
		glm::vec3 normal;
		sscanf_s(line.c_str(), "vn %f %f %f\n", &normal.x, &normal.y, &normal.z);
		_temp_normals.push_back(normal);
	}
	// Load faces
	else if (lineHeader == "f") {
		std::string vertex1, vertex2, vertex3;
		unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
		int matches = sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
		if (matches != 9) {
			_errorOccurred = true;
			_log << "This file can't be read by this simple parser because of this line:: " << line << " :: Try exporting with other options." << std::endl;
			return;
		}
		_vertexIndices.push_back(vertexIndex[0]);
		_vertexIndices.push_back(vertexIndex[1]);
		_vertexIndices.push_back(vertexIndex[2]);
		_uvIndices.push_back(uvIndex[0]);
		_uvIndices.push_back(uvIndex[1]);
		_uvIndices.push_back(uvIndex[2]);
		_normalIndices.push_back(normalIndex[0]);
		_normalIndices.push_back(normalIndex[1]);
		_normalIndices.push_back(normalIndex[2]);
	}
}


OGLVertexMesh<VertexPCNT>* ObjReader::LoadOBJ() {
	if (_errorOccurred) return nullptr;

	// Process the data
	OGLVertexMesh<VertexPCNT>* mesh = new OGLVertexMesh<VertexPCNT>();
	/*
	// Process vertex coords
	for (int i = 0; i < _temp_vertices.size(); i++)
	{
		mesh->AddVertexData({ _temp_vertices[i].x, _temp_vertices[i].y, _temp_vertices[i].z, {1.0f,1.0f,1.0f,1.0f} });
	}
	int vertexIndex, texIndex, normIndex;
	// Process Indices
	for (int i = 0; i < _vertexIndices.size(); i++)
	{
		// Subtract 1 because the file format's indices start at 1, but C++ starts at 0
		vertexIndex = _vertexIndices[i] - 1;
		mesh->AddIndex(vertexIndex);
	}
	// Process Normals & Texture Data
	for (int i = 0; i < _vertexIndices.size(); i++)
	{
		// Subtract 1 because the file format's indices start at 1, but C++ starts at 0
		vertexIndex = _vertexIndices[i] - 1;
		texIndex = _uvIndices[i] - 1;
		normIndex = _normalIndices[i] - 1;
		mesh->SetUpAttributes("PCNT");
		mesh->GetVertex(vertexIndex).tex = { 0.5, 0.5 };
		mesh->GetVertex(vertexIndex).normal = { 0.3, 0.3, 0.3 };
		mesh->GetVertex(vertexIndex).tex = { _temp_uvs[texIndex].s, _temp_uvs[texIndex].t};
		mesh->GetVertex(vertexIndex).normal = { _temp_normals[normIndex].x, _temp_normals[normIndex].y, _temp_normals[normIndex].z };
	}

	*/
	int vertexIndex, texIndex, normIndex;
	VertexPCNT vtd;
	for (int i = 0; i < _vertexIndices.size(); i++)
	{
		// Subtract 1 because the file format's indices start at 1, but C++ starts at 0
		vertexIndex = _vertexIndices[i] - 1;
		texIndex = _uvIndices[i] - 1;
		normIndex = _normalIndices[i] - 1;

		/*
		struct VertexPCNT {
			Vector3D position;
			RGBA color;
			Vector3D normal;
			TexCoord tex;
		*/

		vtd = {
			_temp_vertices[vertexIndex].x, _temp_vertices[vertexIndex].y, _temp_vertices[vertexIndex].z,
			{1.0f,1.0f,1.0f,1.0f},
			_temp_normals[normIndex].x, _temp_normals[normIndex].y, _temp_normals[normIndex].z,
			_temp_uvs[texIndex].x, _temp_uvs[texIndex].y
		};

		mesh->AddVertexData(vtd);
		

	}

	mesh->SetUpAttributes("PCNT");

	return mesh;
}

void ObjReader::Close()
{
	_fin.close();
}