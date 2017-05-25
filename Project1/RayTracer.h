#pragma once
#include "BufferImage.h"

class CRayTracer
{
	CRayTracer();
	~CRayTracer();

	glm::vec3 rayTrace(Ray r, CScene scene);
public:

	static CRayTracer& GetInstance();
	BufferImage Render(CScene scene);
	CRayTracer(CRayTracer const&) = delete;
	void operator=(CRayTracer const&) = delete;
};

