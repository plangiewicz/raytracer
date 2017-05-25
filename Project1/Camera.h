#pragma once
class Camera
{
	glm::mat4x4 _viewProjection;
	glm::vec3 _position;
	glm::vec3 _lookAt;
	glm::vec3 _up;
	glm::vec2 _resolution;
	float _fov;

public:
	Camera(glm::vec2 resolution, glm::vec3 position, glm::vec3 lookAt, glm::vec3 up, float fov);
	Ray GetRayToPixel(glm::vec2 pixel);

	glm::vec2 const& resolution() const;
	glm::mat4x4 const& viewProjection() const;

	Camera();
	~Camera();
};

