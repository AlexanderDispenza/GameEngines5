#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glm/gtc/matrix_transform.hpp>

class LightSource
{
public:

	LightSource(glm::vec3 position_, float ambientValue_, float diffuseValue_, glm::vec3 lightColour_);
	~LightSource();

	glm::vec3 GetPosition() const;
	float GetAmbientValue() const;
	float GetDiffuseValue() const;
	glm::vec3 GetLightColour() const;
	
	void SetPosition(glm::vec3 position_);
	void SetAmbientValue(float ambientValue_);
	void SetDiffuseValue(float diffuseValue_);
	void SetLightColour(glm::vec3 lightColour_);

private:

	glm::vec3 position;
	float ambientValue;
	float diffuseValue;
	glm::vec3 lightColour;

};
#endif

