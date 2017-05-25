#pragma once

class Shape;

struct Ray
{
	glm::vec3 o;
	glm::vec3 d;
};
class CShape;

struct Intersection
{
	glm::vec4 uvwt;
	std::shared_ptr<CShape> shape;
	glm::vec3 normal;
	bool shadow = false;
	int PrimId;

	bool ret = false;
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
};


class CShape
{
public:
	std::string typ;
	int PrimId;
	virtual Intersection HitTest(Ray ray) = 0;
	bool BLight = false;
	float Shininess;
	glm::vec3 Normal;
	glm::vec3 Light;


	float E;

	CMaterial Material;
};

struct Texture
{
	Texture() { R = G = B = A = 0.0f; }
	float R;
	float G;
	float B;
	float A;
};




