#include "stdafx.h"



CMaterial::CMaterial()
{
}

void CMaterial::SetAmbDiffSpec(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	_ambient = ambient; _diffuse = diffuse; _specular = specular;
}

CMaterial * CMaterial::operator=(CMaterial material)
{
	CMaterial *temp = new CMaterial();
	temp->SetAmbDiffSpec(material._ambient, material._diffuse, material._specular);
	return temp;
}

glm::vec3 CMaterial::GetAmbient()
{
	return _ambient;
}

glm::vec3 CMaterial::GetDiffuse()
{
	return _diffuse;
}

glm::vec3 CMaterial::GetSpecular()
{
	return _specular;
}

