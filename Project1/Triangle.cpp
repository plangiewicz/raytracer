#include "stdafx.h"



CTriangle::CTriangle()
{
}


CTriangle::CTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, CMaterial material, float shininess, int idCount)
{
	_vertex.push_back(a);
	_vertex.push_back(b);
	_vertex.push_back(c);

	A = &_vertex[0].Vertice;
	B = &_vertex[1].Vertice;
	C = &_vertex[2].Vertice;

	Material = material;
	Material.SetAmbDiffSpec(material.GetAmbient(), material.GetDiffuse(), material.GetSpecular());
	Shininess = shininess;

	PrimId = idCount;
}

CTriangle::~CTriangle()
{
}

glm::vec3 iloczynWektorowy(glm::vec3 u, glm::vec3 v)
{
	glm::vec3 w;
	w.x = u.y * v.z - v.y * u.z;
	w.y = u.z * v.x - v.z * u.x;
	w.z = u.x * v.y - v.x * u.y;
	return w;
}
#define vector(a,b,c) \
	(a)[0] = (b)[0] - (c)[0];	\
	(a)[1] = (b)[1] - (c)[1];	\
	(a)[2] = (b)[2] - (c)[2];
#define crossProduct(a,b,c) \
	(a)[0] = (b)[1] * (c)[2] - (c)[1] * (b)[2]; \
	(a)[1] = (b)[2] * (c)[0] - (c)[2] * (b)[0]; \
	(a)[2] = (b)[0] * (c)[1] - (c)[0] * (b)[1];

Intersection CTriangle::HitTest(Ray ray)
{
	Intersection ret;
	ret.uvwt = { 0,0,0,0 };
	ret.shape = nullptr;
	

	glm::vec3 u1 = *B - *A;
	glm::vec3 v1 = *C - *A;

	//vector(u1, *B, *A);
	//vector(v1, *C, *A);

	Normal = iloczynWektorowy(u1, v1);
	Normal = glm::normalize(Normal);
	ret.normal = Normal;

	glm::vec3 w = iloczynWektorowy(ray.d, v1);
	//crossProduct(w, ray.d, v1);

	float uw = glm::dot(u1, w);

	if (uw > -0.00001 && uw < 0.00001) return ret;

	float f = 1 / uw;
	glm::vec3 s = ray.o - *A;
	//vector(s, ray.o, *A);
	float u = f * glm::dot(s, w);

	if (u < 0.0 || u > 1.0) return ret;

	glm::vec3 q = iloczynWektorowy(s, u1);
	//crossProduct(q, s, u1);
	float v = f * glm::dot(ray.d, q);

	if (v < 0.0 || u + v > 1.0) return ret;

	float t = f * glm::dot(v1, q);

	if (t > 0.00001) {
		ret.uvwt = { ray.o + ray.d * t, t };
		ret.shape = make_shared<CTriangle>(*this);
	}


	return ret;
}
