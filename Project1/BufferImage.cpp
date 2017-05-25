#include "stdafx.h"




BufferImage::~BufferImage()
{
}


BufferImage::BufferImage(int width, int heigth) {
	w = width;
	h = heigth;
	buffer = new vec4[w*h];
}

int BufferImage::GetHeigth() {
	return h;
}

int BufferImage::GetWidth() {
	return w;
}

void BufferImage::Tmo(float c, float sat, float gamma)
{
	//hdr - obraz wejœciowy
	//	c - sta³a kompresji
	//	sat - sta³a saturacji

	//	hdr_lum = hdr.x * 0.212656f + hdr.y * 0.71515f + hdr.z * 0.072186f;
	//ldr_lum = hdr_lum^c;

	////obliczenie wartoœci max/min luminancji pikseli w obrazie
	//mmin = min(ldr_lum);
	//mmax = max(ldr_lum);

	////normalizacja do przedzia³u 0-1
	//ldr_lum = (ldr_lum - mmin) / (mmax - mmin);

	////saturacja  
	//ldr = ldr_lum * (hdr / hdr_lum) ^ sat;
	//ldr = clamp(ldr, 0, 1);

	////korekcja gamma
	//ldr = ldr^gamma;

	
	float* hdr_lum = new float[w*h];
	float* ldr_lum = new float[w*h];
	glm::vec3* ldr = new vec3[w*h];
	float mmin = 9999;
	float mmax = 0;

	int wh = w * h;

	for (unsigned i = 0; i < wh; i++) {
			hdr_lum[i] = buffer[i].r * 0.212656f + buffer[i].g * 0.71515f + buffer[i].b * 0.072186f;
			ldr_lum[i] = glm::pow(hdr_lum[i], c);

			if (ldr_lum[i] < mmin && ldr_lum[i] > 0)
				mmin = ldr_lum[i];
			if (ldr_lum[i] > mmax)
				mmax = ldr_lum[i];
	}
	for (unsigned i = 0; i < wh; i++) {
			ldr_lum[i] = (ldr_lum[i] - mmin) / (mmax - mmin);

			ldr[i] = { 
				ldr_lum[i] * glm::pow((buffer[i].r / hdr_lum[i]), sat),
				ldr_lum[i] * glm::pow((buffer[i].g / hdr_lum[i]), sat),
				ldr_lum[i] * glm::pow((buffer[i].b / hdr_lum[i]), sat)
			};
			
		    ldr[i] = glm::clamp(ldr[i], glm::vec3(0.0f), glm::vec3(1.0f));
			buffer[i].x = glm::pow(ldr[i].r, gamma) * 255;
			buffer[i].y = glm::pow(ldr[i].g, gamma) * 255;
			buffer[i].z = glm::pow(ldr[i].b, gamma) * 255;
			/*if (ldr_lum[i] > 0)
			{
				std::cout << ldr_lum[i] << "\n";
				std::cout << buffer[i].x << " " << buffer[i].y << " " << buffer[i].z << "\n";
			}*/
		
	}
}

int BufferImage::Save(const char* plik) {
	FIBITMAP *dib = FreeImage_Allocate(w, h, 32, FI_RGBA_RED_MASK,
		FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);
	// Calculate the number of bytes per pixel (3 for 24-bit or 4 for 32-bit)
	int bytespp = FreeImage_GetLine(dib) / FreeImage_GetWidth(dib);
	for (unsigned y = 0; y < FreeImage_GetHeight(dib); y++) {
		BYTE *bits = FreeImage_GetScanLine(dib, y);
		for (unsigned x = 0; x < FreeImage_GetWidth(dib); x++) {
			// Set pixel color to green with a transparency of 128 
			bits[FI_RGBA_RED] = (int)buffer[y + (w - x - 1)*h].x;
			bits[FI_RGBA_GREEN] = (int)buffer[y + (w - x - 1)*h].y;
			bits[FI_RGBA_BLUE] = (int)buffer[y + (w - x - 1)*h].z;
			bits[FI_RGBA_ALPHA] = (int)buffer[y + (w - x - 1)*h].w;
			// jump to next pixel
			bits += bytespp;
		}
	}

	FreeImage_Save(FIF_BMP, dib, plik, 0);

	if (dib) {
		FreeImage_Unload(dib);
	}

	return 0;
}

vec4 & BufferImage::operator[](ivec2 index)
{
	return buffer[index.x * h + index.y];
}

