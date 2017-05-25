#include "stdafx.h"

CScene::CScene(glm::vec2 resolution)
{
	int idCount = 0;


	//dib = nullptr;
	//pixels = nullptr;
	//FREE_IMAGE_FORMAT fif = FreeImage_GetFileType("tile.bmp", 0);
	//if (FreeImage_FIFSupportsReading(fif))
	//	dib = FreeImage_Load(fif, "tile.bmp");
	//widthPix = FreeImage_GetWidth(dib);
	//heightPix = FreeImage_GetHeight(dib);
	//BYTE *pixels = (BYTE *)FreeImage_GetBits(dib);

	//texture = new Texture[widthPix * heightPix];
	//int overalSize = widthPix * heightPix;

	//for (int i = 0; i < overalSize; i+=4) {
	//	texture[i].R = *pixels++;
	//	texture[i].G = *pixels++;
	//	texture[i].B = *pixels++;
	//	texture[i].A = *pixels++;
	//}


	CMaterial lightDefaultMaterial;
	lightDefaultMaterial.SetAmbDiffSpec(glm::vec3(1), glm::vec3(1), glm::vec3(1));

	CMaterial sfera1Mat;
	sfera1Mat.SetAmbDiffSpec(glm::vec3(0.01, 0.01, 0.01), glm::vec3(0.8, 0.01, 0.01), glm::vec3(0.8, 0.8, 0.8));
	CMaterial sfera2Mat;
	sfera2Mat.SetAmbDiffSpec(glm::vec3(0.01, 0.01, 0.01), glm::vec3(0.01, 0.8, 0.01), glm::vec3(0.01, 0.01, 0.01));
	CMaterial trianglesMat;
	trianglesMat.SetAmbDiffSpec(glm::vec3(0.01, 0.01, 0.01), glm::vec3(0.01, 0.01, 0.6), glm::vec3(0.01, 0.01, 0.01));


	Objects = new std::vector<CShape*>;
	Lights = new std::vector<CLight*>;
	//-4 4 -2
	//1 1 -10
	CLight* light = new CLight(vec3(-4, 4, -2), 20, lightDefaultMaterial);
	CLight* light2 = new CLight(vec3(1, 1, -10), 20, lightDefaultMaterial);
	Lights->push_back(light);
	Lights->push_back(light2);

	glm::vec3 position = glm::vec3(3, 15, -16);
	glm::vec3 lookAt = glm::vec3(0, 0, 0);
	glm::vec3 up = glm::vec3(0, 1, 0);
	float fov = 50.0f;
	_camera = Camera(resolution, position, lookAt, up, glm::radians(fov));

	CSfera* c_sfera = new CSfera(false, 2, { 0, 0, 0 }, sfera1Mat, 20, idCount++);
	CSfera* c_sfera2 = new CSfera(false, 1, { 2, 2, 0 }, sfera2Mat, 20, idCount++);
	//CSfera* c_sfera3 = new CSfera(false, 1, { -4, 0, 0 }, trianglesMat, 20);
	Objects->push_back(c_sfera);
	Objects->push_back(c_sfera2);
	//Objects->push_back(c_sfera3);

	CTriangle* triangle = new CTriangle({ -5, -4, -5 }, { -5, -4, 5 }, { 5, -4, 5 }, trianglesMat, 20, idCount++);
	CTriangle* triangle2 = new CTriangle({ 5, -4, 5 }, { 5, -4, -5 }, { -5, -4, -5 }, trianglesMat, 20, idCount++);
	Objects->push_back(triangle);
	Objects->push_back(triangle2);
}


CScene::~CScene()
{
}

Camera const & CScene::camera() const
{
	return _camera;
}

void CScene::camera(Camera const & newCamera)
{
	_camera = newCamera;
}

bool tryVec(glm::vec3 a, float e)
{
	return a.x >= e && a.y >= e && a.z >= e;
}

Intersection CScene::HitTest(Ray ray)
{
	Ray currentRay = ray;
	int rayMax = 6;
	Intersection** intersection = new Intersection*[rayMax];
	Intersection* returnIntersection = new Intersection();
	int mainIntersection = -1;
	bool posibleRay = false;
	for (int E = 0; E < rayMax; E++) {
		intersection[E] = nullptr;
		for (int i = 0; i < Objects->size(); i++) {
			posibleRay = true;
			/*if (E > 0)
			{
				posibleRay = Objects->at(i)->PrimId != intersection[E - 1]->shape->PrimId;
			}*/

			if (posibleRay) {
				Intersection temp = Objects->at(i)->HitTest(currentRay);
				if (temp.shape != nullptr) {
					if (intersection[E] == nullptr || temp.uvwt[3] < intersection[E]->uvwt[3])
					{
						intersection[E] = new Intersection(temp);
						intersection[E]->uvwt.x = temp.uvwt.x;
						intersection[E]->uvwt.y = temp.uvwt.y;
					}
				}
			}

		}
		if (intersection[E] != nullptr)
		{
			int u;
			int v;
			for (int i = 0; i < Lights->size(); i++)
			{
				Lights->at(i)->HitTest(currentRay, intersection[E], Objects, mainIntersection);
			}
			currentRay.d = glm::normalize(currentRay.d);
			currentRay.o = intersection[E]->uvwt.w * currentRay.d + currentRay.o;
			//glm::normalize(1.0f - 2.0f * glm::dot(intersection->normal, testRay.d) * intersection->normal);
			//currentRay.d = currentRay.d - (2.0f * currentRay.d * intersection[E]->normal) * intersection[E]->normal;
			currentRay.d = glm::normalize(currentRay.d - 2.0f * glm::dot(intersection[E]->normal, currentRay.d) * intersection[E]->normal);
			currentRay.o = currentRay.o + currentRay.d + (intersection[E]->normal * 0.0001f);


			returnIntersection->ret = true;
			if (intersection[E]->shape->typ == "sfe")
			{

				u = intersection[E]->uvwt.s * widthPix;
				v = intersection[E]->uvwt.t * heightPix;
				if (v < 0)
				{
					float t = 0.5 + (1.57 / glm::pi<float>());
					v = t * heightPix;
				}

				char r = texture[((v - 1) * widthPix) + u].R;
				char g = texture[((v - 1) * widthPix) + u].G;
				char b = texture[((v - 1) * widthPix) + u].B;

				returnIntersection->Ambient = { r, g, b };
			}
			else
				returnIntersection->Ambient = returnIntersection->Ambient + intersection[E]->Ambient / (E + 1.0f);
			returnIntersection->Diffuse = returnIntersection->Diffuse + intersection[E]->Diffuse / (E + 1.0f);
			returnIntersection->Specular = returnIntersection->Specular + intersection[E]->Specular / (E + 1.0f);
			returnIntersection->normal = intersection[0]->normal;

		}
		else
			break;
	}



	//if (best != nullptr)
	//{
	//	for (int i = 0; i < Lights->size(); ++i)
	//	{
	//		Lights->at(i)->HitTest(ray, best, Objects, bestI);
	//	}
	//}
	//else
	//{
	//	Intersection forReturn;
	//	forReturn.shape = nullptr;
	//	return  forReturn;
	//}

	return *returnIntersection;
}
