#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader()
{

}

void MaterialLoader::LoadMaterial(std::string filePath_)
{
	std::ifstream file(filePath_.c_str(), std::ios::in);
	if (!file)
	{
		Debugger::Error("Could not open .mtl file: " + filePath_, " MaterialLoader.cpp ", __LINE__);
		return;
	}
	
	Material m = Material();
	std::string matName = "";

	std::string line;
	
	while (std::getline(file, line))
	{
		if (line.substr(0, 7) == "newmtl ")
		{
			if (m.diffuseMap != 0)
			{
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
			m.name = matName;
		}

		// remove tabs from .mtl file
		if (line.find('\t Ns') || line.find('\t d') || line.find('\t Ka') || line.find('\t Ks'))
		{
			line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
		}

		//TODO: Read through the relevant lines/parse the ns, d, ka, kd, ks
		if (line.substr(0, 3) == "Ns ")
		{
			std::stringstream tempVal(line.substr(2));

			float tempShine;

			tempVal >> tempShine;

			m.shininess = tempShine;
		}
		else if (line.substr(0, 2) == "d ") 
		{
			std::stringstream tempVal(line.substr(2));

			float transperancy;

			tempVal >> transperancy;

			m.transparency = transperancy;
			
		}
		else if (line.substr(0, 3) == "Ka ")
		{
			std::stringstream tempVal(line.substr(2));

			float ambX, ambY, ambZ;

			tempVal >> ambX >> ambY >> ambZ;

			m.ambient.x = ambX;
			m.ambient.y = ambY;
			m.ambient.z = ambZ;

		}
		else if (line.substr(0, 3) == "Kd")
		{
			std::stringstream tempVal(line.substr(2));

			float diffX, diffY, diffZ;

			tempVal >> diffX >> diffY >> diffZ;

			m.diffuse.x = diffX;
			m.diffuse.y = diffY;
			m.diffuse.z = diffZ;
		}
		else if (line.substr(0, 3) == "Ks ")
		{
			std::stringstream tempVal(line.substr(2));

			float specX, specY, specZ;

			tempVal >> specX >> specY >> specZ;

			m.specular.x = specX;
			m.specular.y = specY;
			m.specular.z = specZ;
		}
	}

	if (m.diffuseMap != 0)
	{
		MaterialHandler::GetInstance()->AddMaterial(m);
	}
	file.close();
}

GLuint MaterialLoader::LoadTexture(std::string fileName_)
{
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	if (currentTexture == 0)
	{
		TextureHandler::GetInstance()->CreateTexture(fileName_, "./Resources/Textures/" + fileName_ + ".jpg");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}
	return currentTexture;
}
