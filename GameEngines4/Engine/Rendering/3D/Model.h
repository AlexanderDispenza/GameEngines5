#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "../3D/LoadObjModel.h"
#include "../../Math/BoundingBox.h"

class Model
{
public:
	Model(const std::string& objFilePath, const std::string& mtlFilePath, GLuint shaderProgram_);
	
	~Model();

	void Render(Camera* camera_);
	void AddMesh(Mesh* mesh_);

	int CreateInstance(glm::vec3 position_, float angle_, 
		glm::vec3 rotation_, glm::vec3 scale_);
	
	void UpdateInstance(int index_, glm::vec3 position_, 
		float angle_, glm::vec3 rotation_, glm::vec3 scale_);

	BoundingBox GetBoundingBox();
	glm::mat4 GetTransform(int index_) const;
	GLuint GetShaderProgram() const;
	
private:
	
	std::vector<Mesh*> subMeshes;
	GLuint shaderProgram;
	//***recomended for Frustum cullings for Bounding box change to bounding boxes instead of mat4s***
	std::vector<glm::mat4> modelInstances;
	LoadObjModel* obj;
	BoundingBox box;

	glm::mat4 GetTransform(glm::vec3 position_,
		float angle_, glm::vec3 rotation_, glm::vec3 scale_) const;

	void LoadModel();


};
#endif

