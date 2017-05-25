#pragma once


class CLight
{
	glm::vec3 _position;
	float _luminance;
	CMaterial _sMaterial;
public:
	CLight(glm::vec3 position, float luminance, CMaterial sMaterial);
	void HitTest(Ray ray, Intersection* intersection, std::vector<CShape *> *Objects, int main);
};