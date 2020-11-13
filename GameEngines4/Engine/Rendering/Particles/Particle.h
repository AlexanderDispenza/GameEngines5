#ifndef PARTICLE_H
#define PARTICLE_H
#define GLM_SWIZZLE

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <math.h>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"
#include <../../OpenGL/include/glm/glm.hpp>
#include "../../Graphics/MaterialHandler.h"


struct vertexData
{
	glm::vec3 position;
	
	glm::vec2 textureCoordinates;
};


//This class is similar to the Mesh class and SpriteSurface class
class Particle
{
public:

	Particle() {}
	virtual ~Particle() {}

	virtual void Render(Camera* camera_) = 0;

	float lifeTime;
	float size;
	float angle;


	glm::vec3 velocity;
	glm::vec4 colour;
	glm::vec3 position;
	glm::vec3 rotation;
};

#endif // !PARTICLE_H