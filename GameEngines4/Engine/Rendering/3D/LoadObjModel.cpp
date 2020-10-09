#include "LoadObjModel.h"

LoadObjModel::LoadObjModel()
{
	
	currentMaterial = Material();

	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	
	meshVertices.reserve(200);
	subMeshes.reserve(10);
}

LoadObjModel::~LoadObjModel()
{
	OnDestroy();
}

void LoadObjModel::LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_)
{
	LoadMaterialLibrary(mtlFilePath_);
	LoadModel(objFilePath_);
}

void LoadObjModel::LoadModel(const std::string& filePath_)
{
	std::ifstream file(filePath_.c_str(), std::ios::in);
	
	if (!file)
	{
		Debugger::Error("Could not open .obj file " + filePath_, " LoadObjModel.cpp ", __LINE__);
		return;
	}

	std::string line;
	
	while (std::getline(file, line)) 
	{
		// Vertex Data
		if (line.substr(0, 2) == "v ")
		{
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;

			// Setting min bound box
			if (box.minVert.x > x)
			{
				box.minVert.x = x;
			}
			if (box.minVert.y > y)
			{
				box.minVert.y = y;
				
			}
			if (box.minVert.z > z)
			{
				box.minVert.z = z;
			}
			// Setting the max bound box
			if (box.maxVert.x < x)
			{
				box.maxVert.x = x;
			}
			if (box.maxVert.y < y)
			{
				box.maxVert.y = y;
			}
			if (box.maxVert.z < z)
			{
				box.maxVert.z = z;
			}

			vertices.push_back(glm::vec3(x, y, z));

		}
		// Normal Data
		else if (line.substr(0, 3) == "vn ")
		{
			std::stringstream vn(line.substr(2));
			float x, y, z;
			vn >> x >> y >> z;

			normals.push_back(glm::vec3(x, y, z));
			
		}
		// Texture Data
		else if (line.substr(0, 3) == "vt ")
		{
			std::stringstream vt(line.substr(2));
			float x, y;
			vt >> x >> y;

			textureCoords.push_back(glm::vec2(x, y));

		}
		// Face Data
		else if (line.substr(0, 2) == "f ")
		{
			if (line.find("/"))
			{
				std::replace(line.begin(), line.end(), '/', ' ');

				std::stringstream f(line.substr(2));

				int fVertexPos[3];
				int fTexturePos[3];
				int fNormalPos[3];

				f >> fVertexPos[0]>> fTexturePos[0] >> fNormalPos[0] >>
					fVertexPos[1] >> fTexturePos[1] >> fNormalPos[1] >> 
					fVertexPos[2] >> fTexturePos[2] >> fNormalPos[2];

				indices.push_back(fVertexPos[0]);
				indices.push_back(fVertexPos[1]);
				indices.push_back(fVertexPos[2]);
				
				textureIndices.push_back(fTexturePos[0]);
				textureIndices.push_back(fTexturePos[1]);
				textureIndices.push_back(fTexturePos[2]);

				normalIndices.push_back(fNormalPos[0]);
				normalIndices.push_back(fNormalPos[1]);
				normalIndices.push_back(fNormalPos[2]);
			}
			
		}
		// Create new SubMesh 
		else if (line.substr(0, 7) == "usemtl ") 
		{
			if (indices.size() > 0) 
			{
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}
	PostProcessing();
}

std::vector<Vertex> LoadObjModel::GetVertex()
{
	return meshVertices;
}

std::vector<int> LoadObjModel::GetIndices()
{
	return indices;
}

std::vector<SubMesh> LoadObjModel::GetSubMeshes()
{
	return subMeshes;
}

void LoadObjModel::OnDestroy()
{
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();
}

BoundingBox LoadObjModel::GetBoundingBox()
{
	return box;
}

void LoadObjModel::PostProcessing()
{
	for (int i = 0; i < indices.size(); i++)
	{
		Vertex vert;
		vert.position = vertices[indices[i] - 1];
		vert.normal = normals[normalIndices[i] - 1];
		vert.texCoords = textureCoords[textureIndices[i] - 1];
	
		meshVertices.push_back(vert);
	}
	SubMesh subMesh;

	subMesh.vertextList = meshVertices;
	subMesh.meshIndices = indices;
	subMesh.material = currentMaterial;

	subMeshes.push_back(subMesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentMaterial = Material();
}

void LoadObjModel::LoadMaterial(const std::string& matName_)
{
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);
}

void LoadObjModel::LoadMaterialLibrary(const std::string& matFilePath_)
{
	MaterialLoader::LoadMaterial(matFilePath_);
}
