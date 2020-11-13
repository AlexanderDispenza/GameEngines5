#ifndef OPENGLPARTICLE_H
#define OPENGLPARTICLE_H
#define GLM_SWIZZLE

#include "particle.h"

class OpenGLParticle : public Particle
{
public:

	OpenGLParticle(GLuint shaderProgram_, GLuint textureID_);
	virtual ~OpenGLParticle();


private:

	void GenerateBuffers();

	GLuint VAO, VBO;
	GLuint textureID;

	GLuint shaderProgram;
	GLuint modelLocation, viewLocation, projectionLocation;
	GLuint colourLocation, textureLocation;

	std::vector<vertexData> particles;

	glm::mat4 GetTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)const;

	void Render(Camera* camera_);
};
#endif

