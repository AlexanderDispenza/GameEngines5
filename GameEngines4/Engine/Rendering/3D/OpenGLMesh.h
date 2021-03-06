#ifndef OPENGLMESH_H
#define OPENGLMESH_H

#include "Mesh.h"

class OpenGLMesh : public Mesh
{
public:

	OpenGLMesh(SubMesh subMesh_, GLuint shaderProgram_);
	virtual ~OpenGLMesh();


	void Render(Camera* camera_, std::vector<glm::mat4> instances_) override;

private:

	void GenerateBuffers();

	SubMesh subMesh;
	GLuint VAO, VBO;
	GLuint shaderProgram;
	GLuint modelLocation, viewLocation, projectionLocation;

	GLuint viewPosition, lightPosition, lightAmbient, lightDiffuse, lightColour;

	GLuint diffuseMapLocation, shininessLocation, transperencyLocation, ambientLocation, diffuseLocation, specularLocation;
};

#endif

