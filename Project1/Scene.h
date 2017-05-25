#pragma once

class CScene
{
	Camera _camera;
public:
	CScene();
	CScene::CScene(glm::vec2 resolution);
	~CScene();

	FIBITMAP *dib;
	unsigned int widthPix;
	unsigned int heightPix;
	BYTE *pixels;

	Texture* texture;
	
	std::vector<CShape *> *Objects;
	std::vector<CLight *> *Lights;

	Camera const& camera() const;
	void camera(Camera const& newCamera);

	Intersection HitTest(Ray ray);


};

