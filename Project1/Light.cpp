#include "stdafx.h"

CLight::CLight(glm::vec3 position, float luminance, CMaterial sMaterial)
{
	_position = position;
	_luminance = luminance;
	_sMaterial = sMaterial;
	_sMaterial.SetAmbDiffSpec(sMaterial.GetAmbient(), sMaterial.GetDiffuse(), sMaterial.GetSpecular());
}

void CLight::HitTest(Ray ray, Intersection * intersection, std::vector<CShape *> *Objects, int main)
{

	Ray testRay;

	testRay.o = (intersection->uvwt.w * ray.d + ray.o);
	testRay.d = glm::normalize(_position - testRay.o);
	//testRay.o -= (testRay.d * 0.0001f);
	

	//glm::vec3 r = glm::normalize(1.0f - 2.0f * glm::dot(intersection->normal, testRay.d) * intersection->normal);
	//glm::vec3 r = glm::normalize(testRay.d - 2.0f * glm::dot(intersection->normal, testRay.d) * intersection->normal);
	////glm::vec3 r = glm::normalize(2.0f * intersection->normal * glm::dot(-intersection->normal, testRay.d));
	////glm::vec3 v = glm::normalize(ray.o - testRay.o);
	//glm::vec3 v = glm::normalize(2.0f * glm::dot(-intersection->normal, ray.d) * intersection->normal);
	//glm::vec3 h = glm::normalize((testRay.d + v) / glm::abs(testRay.d + testRay.d));
	//glm::vec3 r = v + testRay.d;

	glm::vec3 r = glm::reflect(glm::normalize(testRay.d), intersection->normal);
	float rv = max(0.0f, glm::pow(glm::dot(-ray.d, r), intersection->shape->Shininess));

	//float rv = glm::pow(glm::dot(r, v), intersection->shape->Shininess);
	float ln = glm::dot(testRay.d, intersection->normal);
	//float nh = glm::pow(glm::dot(intersection->normal, h), intersection->shape->Shininess);

	intersection->Ambient += intersection->shape->Material.GetAmbient() * _sMaterial.GetAmbient();
	//intersection->Specular += intersection->shape->Material.GetSpecular() * _sMaterial.GetSpecular() * nh;

	float rr = glm::length(_position - testRay.o);
	float cosTheta = glm::max(0.0f, glm::dot(intersection->normal, testRay.d)) / (glm::length(intersection->normal) * glm::length(testRay.d));
	float energia = 1.0f;
	intersection->shape->E = (_luminance * cosTheta) / glm::pow(rr, 2);
	
	/*testRay.o = testRay.o - testRay.d + (0.0001f * intersection->normal);*/
	for (int i = 0; i < Objects->size(); ++i) {
		if (main != i) {
			Intersection temp = Objects->at(i)->HitTest(testRay);
			if (temp.shape != nullptr && temp.shadow && temp.uvwt.w > 0)
			{
				energia = 0.0f;
				if (temp.shape->PrimId == intersection->shape->PrimId)
				{
					energia = 1.0f;
				}
				break;
			}
		}
	}
	
	intersection->Diffuse += (intersection->shape->Material.GetDiffuse() * _sMaterial.GetDiffuse() * intersection->shape->E) * energia;
	//if (intersection->Diffuse.x < 0.0001f && intersection->Diffuse.y < 0.0001f && intersection->Diffuse.z < 0.0001f)
	//{
	//	intersection->Specular *= 0;
	//} else
		intersection->Specular += intersection->shape->Material.GetSpecular() * _sMaterial.GetSpecular() * rv * intersection->shape->E;
}
