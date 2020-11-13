#include "OpenGLMesh.h"

OpenGLMesh::OpenGLMesh(SubMesh subMesh_, GLuint shaderProgram_)
{
	VAO = 0;
	VBO = 0;

	modelLocation = 0;
	viewLocation = 0;
	projectionLocation = 0;
	subMesh = subMesh_;
	shaderProgram = shaderProgram_;

	GenerateBuffers();
}

OpenGLMesh::~OpenGLMesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (subMesh.vertextList.size() > 0)
	{
		subMesh.vertextList.clear();
	}

	if (subMesh.meshIndices.size() > 0)
	{
		subMesh.meshIndices.clear();
	}

}

void OpenGLMesh::Render(Camera* camera_, std::vector<glm::mat4> instances_)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);

	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

	// light uniform stuff
	glUniform3f(viewPosition, camera_->GetPosition().x, camera_->GetPosition().y, camera_->GetPosition().z);
	glUniform3f(lightColour, camera_->GetLightSources()[0]->GetLightColour().x,
		camera_->GetLightSources()[0]->GetLightColour().y, camera_->GetLightSources()[0]->GetLightColour().z);
	glUniform3f(lightPosition, camera_->GetLightSources()[0]->GetPosition().x,
		camera_->GetLightSources()[0]->GetPosition().y, camera_->GetLightSources()[0]->GetPosition().z);

	////////////// Material uniform
	glUniform1f(diffuseMapLocation, subMesh.material.diffuseMap);
	glUniform1f(shininessLocation, subMesh.material.shininess);
	glUniform1f(transperencyLocation, subMesh.material.transparency);
	glUniform3f(ambientLocation, subMesh.material.ambient.x, subMesh.material.ambient.y, subMesh.material.ambient.z);
	glUniform3f(diffuseLocation, subMesh.material.diffuse.x, subMesh.material.diffuse.y, subMesh.material.diffuse.z);
	glUniform3f(specularLocation, subMesh.material.specular.x, subMesh.material.specular.y, subMesh.material.specular.z);


	glBindVertexArray(VAO);
	for (int i = 0; i < instances_.size(); i++)
	{
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertextList.size());
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void OpenGLMesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertextList.size() * sizeof(Vertex), &subMesh.vertextList[0], GL_STATIC_DRAW);

	// Vertex Pos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	// Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

	//Colour
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLocation = glGetUniformLocation(shaderProgram, "model");
	viewLocation = glGetUniformLocation(shaderProgram, "view");
	projectionLocation = glGetUniformLocation(shaderProgram, "projection");
	diffuseMapLocation = glGetUniformLocation(shaderProgram, "material.diffuseMap");


	// Light 
	viewPosition = glGetUniformLocation(shaderProgram, "cameraPosition");
	lightPosition = glGetUniformLocation(shaderProgram, "light.lightPos");
	lightAmbient = glGetUniformLocation(shaderProgram, "light.ambientValue");
	lightDiffuse = glGetUniformLocation(shaderProgram, "light.diffuseValue");
	lightColour = glGetUniformLocation(shaderProgram, "light.lightColour");

	//Material

	diffuseMapLocation = glGetUniformLocation(shaderProgram, "material.diffuseMap");
	shininessLocation = glGetUniformLocation(shaderProgram, "material.shininess");
	transperencyLocation = glGetUniformLocation(shaderProgram, "material.transparency");
	ambientLocation = glGetUniformLocation(shaderProgram, "material.ambient");
	diffuseLocation = glGetUniformLocation(shaderProgram, "material.diffuse");
	specularLocation = glGetUniformLocation(shaderProgram, "material.specular");
}
