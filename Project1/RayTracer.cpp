#include "stdafx.h"



CRayTracer::CRayTracer()
{
}


CRayTracer::~CRayTracer()
{
}

CRayTracer & CRayTracer::GetInstance()
{
	static CRayTracer instance;
	return instance;
}

BufferImage CRayTracer::Render(CScene scene)
{
	Camera camera = scene.camera();
	glm::vec2 resolution = camera.resolution();
	BufferImage image(resolution.x, resolution.y);
	
	for (int i = 0; i < resolution.x; i++)
		for (int j = 0; j < resolution.y; j++)
		{
			float n_x = (i / (resolution.x)) * 2 - 1;
			float n_y = (j / (resolution.y)) * 2 - 1;

			Ray tempRay = camera.GetRayToPixel(glm::vec2(n_x, n_y)); 

			//tempRay.d = glm::clamp(tempRay.d, vec3(0.0f), vec3(1.0f));
			float x = (tempRay.d.x);
			float y = (tempRay.d.y);
			float z = (tempRay.d.z);

			Intersection intersection = scene.HitTest(tempRay);


			if (intersection.ret) {
				glm::vec3 light = intersection.Ambient + intersection.Diffuse + intersection.Specular;// +intersection.shape->E;
				//glm::vec3 light = intersection.normal;
				light = glm::clamp(light, vec3(0.0f), vec3(1.0f));
				image[{i, j}] = vec4(light * 255.0f, 255);
				//std::cout << light.x << " " << light.y << " " << light.z << "\n";
			}
			else
				image[{i, j}] = vec4(0, 0, 0, 255);

			//image[{i, j}] = vec4(x * 255, y * 255, z * 255, 255);
		}

	return image;
}
