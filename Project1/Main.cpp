
#include "stdafx.h"


int main() {
	FreeImage_Initialise();
	int x = 1000;
	int y = 800;

	
	CScene scena(glm::vec2(x, y));
	BufferImage image = CRayTracer::GetInstance().Render(scena);
	image.Tmo(0.6f, 0.5f, 1.0f / 2.2f);
	image.Save("labki2.png");
	return 0;
}


//image[{i,j}] = vec4 ((i/float xx)