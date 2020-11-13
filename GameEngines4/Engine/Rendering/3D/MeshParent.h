#ifndef MESHPARENT_H
#define MESHPARENT_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"
#include "../../Graphics/MaterialHandler.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 colour;
};

struct SubMesh
{
	std::vector<Vertex> vertextList;
	std::vector<int> meshIndices;
	Material material;
};

class MeshParent 
{
public:

	MeshParent() {}
	virtual ~MeshParent() {}

	virtual void Render(Camera* camera_, std::vector<glm::mat4> instances_) = 0;

	virtual void OnDestroy() = 0;
};

#endif
