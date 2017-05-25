#pragma once
class CSfera : public CShape
{

	float _radius;
	glm::vec3 _center;

public:
	CSfera();
	CSfera(bool light, float radius, glm::vec3 center, CMaterial material, float shininess, int idCount);
	~CSfera();


	virtual Intersection HitTest(Ray ray) override;
};

