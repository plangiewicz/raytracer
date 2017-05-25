#include "stdafx.h"



CSfera::CSfera()
{
}

CSfera::CSfera(bool light, float radius, glm::vec3 center, CMaterial material, float shininess, int idCount)
{
	this->BLight = light;
	_radius = radius;
	_center = center;
	Material = material;
	Material.SetAmbDiffSpec(material.GetAmbient(), material.GetDiffuse(), material.GetSpecular());
	Shininess = shininess;
	PrimId = idCount;
	typ = "sfera";
}

CSfera::~CSfera()
{
}



Intersection CSfera::HitTest(Ray ray)
{

	Intersection ret;
	ret.uvwt = { 0,0,0,0 };
	ret.shape = nullptr;

	float a = glm::pow(glm::length(ray.d), 2);
	float b = 2 * glm::dot(ray.d, (ray.o - _center));
	float c = glm::pow(glm::length((ray.o - _center)), 2) - glm::pow(_radius, 2);

	float delta = glm::pow(b, 2) - (4 * a * c);

	float x1;
	float x2;

	float epsilon = 0.0001;

	if (delta < 0) return ret;
	if (delta < epsilon)
	{
		x1 = (-b / 2 * a);
		ret.shadow = true;
	}
	else
	{
		x1 = (-b - glm::sqrt(delta)) / (2 * a);
		x2 = (-b + glm::sqrt(delta)) / (2 * a);
		x1 = glm::min(x1, x2);
		ret.shadow = true;
	}
	if (x1 < 0.0f)
	{
		return ret;
	}

	ret.uvwt = { 0,0,0, x1 };
	glm::vec3 p = { ray.o + ray.d * x1 };
	ret.normal = glm::normalize(p -_center);
	Normal = ret.normal;
	
	ret.shape = make_shared<CSfera>(*this);

	ret.shape->E = 0;
	ret.Ambient = { 0.0f, 0.0f, 0.0f};
	ret.Diffuse = { 0.0f, 0.0f, 0.0f};
	ret.Specular = { 0.0f, 0.0f, 0.0f};

	float PI = glm::pi<float>();
	ret.uvwt.s = 0.5 + (glm::atan(2 * p.z, 2 * p.x) / (2 * PI));
	ret.uvwt.t = 0.5 + (glm::asin(p.y) / PI);
	if (p.y > 1)
		ret.uvwt.t = 0.5 + (1.57 / PI);

	return ret;
}
