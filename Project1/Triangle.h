#pragma once

class CTriangle : public CShape
{
public:
	struct Vertex
	{
		Vertex(glm::vec3 vertice) : Vertice(vertice) {}
		Vertex(float x, float y, float z) : Vertice({ x, y, z }) {}
		glm::vec3 Vertice;
	};

	std::vector<Vertex> _vertex;
	glm::vec3 *A;
	glm::vec3 *B;
	glm::vec3 *C;
	CTriangle();
	CTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, CMaterial mateial, float shininess, int idCount);
	~CTriangle();


	virtual Intersection HitTest(Ray ray) override;
};

