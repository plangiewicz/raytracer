#pragma once

class BufferImage {
private:
	glm::vec4* buffer;
	int w;
	int h;

public:
	BufferImage(int width, int height);
	~BufferImage();
	int GetWidth();
	int GetHeigth();
	void Tmo(float c, float sat, float gamma);
	int Save(const char* plik);

	glm::vec4& operator[](glm::ivec2 index);
};