#pragma once

class CMaterial
{
	glm::vec3 _ambient;
	glm::vec3 _diffuse;
	glm::vec3 _specular;
public:
	CMaterial();
	void SetAmbDiffSpec(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	CMaterial* operator=(CMaterial material);

	glm::vec3 GetAmbient();
	glm::vec3 GetDiffuse();
	glm::vec3 GetSpecular();
};