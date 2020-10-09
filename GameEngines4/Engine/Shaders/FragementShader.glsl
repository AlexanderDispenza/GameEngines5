#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;
in vec3 FragPosition;

out vec4 fragColour;

struct Light
{
	vec3 lightPos;
	float ambientValue;
	float diffuseValue;
	vec3 lightColour;
};

struct Material 
{
	sampler2D diffuseMap; // new mtl

	float shininess; // Ns
	float transparency; //d

	vec3 ambient; // Ka
	vec3 diffuse; // Kd
	vec3 specular; // Ks
};

uniform vec3 cameraPosition;
uniform Light light;
uniform Material material;

void main()
{
	//Ambient 
	vec3 ambientValue = light.ambientValue * material.ambient * texture(material.diffuseMap, TexCoords).rgb * light.lightColour;

	//Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.lightPos - FragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuseValue = (diff * material.diffuse) * texture(material.diffuseMap, TexCoords).rgb * light.lightColour; 

	//Specular
	vec3 viewDir = normalize(cameraPosition - FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);	
	vec3 specular = (spec * material.specular) * light.lightColour;

	vec3 resualt = ambientValue + diffuseValue + specular;

	fragColour = vec4(resualt, material.transparency);
}