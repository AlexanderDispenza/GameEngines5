#include "LightSource.h"

LightSource::LightSource(glm::vec3 position_, float ambientValue_, float diffuseValue_, glm::vec3 lightColour_)
{
	position = position_;
	ambientValue = ambientValue_;
	diffuseValue = diffuseValue_;
	lightColour = lightColour_;
}

LightSource::~LightSource()
{
}

glm::vec3 LightSource::GetPosition() const
{
	return position;
}

void LightSource::SetPosition(glm::vec3 position_)
{
	position = position_;
}

float LightSource::GetAmbientValue() const
{
	return ambientValue;
}

void LightSource::SetAmbientValue(float ambientValue_)
{
	ambientValue = ambientValue_;
}

float LightSource::GetDiffuseValue() const
{
	return diffuseValue;
}

void LightSource::SetDiffuseValue(float diffuseValue_)
{
	diffuseValue = diffuseValue_;
}

glm::vec3 LightSource::GetLightColour() const
{
	return lightColour;
}

void LightSource::SetLightColour(glm::vec3 lightColour_)
{
	lightColour = lightColour_;
}


