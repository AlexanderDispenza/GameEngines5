#include "Model.h"

Model::Model(const std::string& objFilePath, const std::string& mtlFilePath, GLuint shaderProgram_) : subMeshes(std::vector<Mesh*>()), 
modelInstances(std::vector<glm::mat4>())
{
	modelInstances.reserve(5);
	subMeshes.reserve(10);
	shaderProgram = shaderProgram_;
	
	obj = new LoadObjModel();
	obj->LoadModel(objFilePath, mtlFilePath);
	this->LoadModel();
}

Model::~Model()
{
	if (subMeshes.size() > 0) 
	{
		for (auto m : subMeshes) 
		{
			delete m;
			m = nullptr;
		}
		subMeshes.clear();
	}

	if (modelInstances.size() > 0)
	{
		modelInstances.clear();
	}
}

void Model::Render(Camera* camera_)
{
	for (auto m : subMeshes)
	{
		m->Render(camera_, modelInstances);
	}
}

void Model::AddMesh(Mesh* mesh_)
{
	subMeshes.push_back(mesh_);
}

int Model::CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	modelInstances.push_back(GetTransform(position_, angle_, rotation_, scale_));

	return modelInstances.size() - 1; 
}

void Model::UpdateInstance(int index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	modelInstances[index_] = GetTransform(position_, angle_, rotation_, scale_);
}

BoundingBox Model::GetBoundingBox()
{
	return box;
}

glm::mat4 Model::GetTransform(int index_) const
{
	return modelInstances[index_];
}

GLuint Model::GetShaderProgram() const
{
	return shaderProgram;
}

glm::mat4 Model::GetTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const
{
	glm::mat4 model;
	model = glm::translate(model, position_);
	model = glm::rotate(model, angle_, position_);
	model = glm::scale(model, scale_);

	return model;
}

void Model::LoadModel()
{
	for (int i = 0; i < obj->GetSubMeshes().size(); i++) 
	{
		subMeshes.push_back(new Mesh(obj->GetSubMeshes()[i], shaderProgram));
	}

	box = obj->GetBoundingBox();

	delete obj;
	obj = nullptr;
}


