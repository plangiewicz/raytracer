#include "stdafx.h"



Camera::Camera(glm::vec2 resolution, glm::vec3 position, glm::vec3 lookAt, glm::vec3 up, float fov)
{
	_resolution = resolution;
	_position = position;
	_lookAt = lookAt;
	_up = up;
	_fov = fov;

	glm::mat4x4 v = glm::lookAt(_position, _lookAt, _up);
	glm::mat4x4 p = glm::perspective(_fov, _resolution.x / _resolution.y, 0.1f, 1000.0f);

	_viewProjection = p*v;
}

Ray Camera::GetRayToPixel(glm::vec2 pixel)
{
	Ray tmp;
	tmp.o = _position;
	tmp.d = glm::normalize(glm::inverse(_viewProjection)*glm::vec4(pixel.x, pixel.y, 1, 1));
	return tmp;
}

glm::vec2 const & Camera::resolution() const
{
	return _resolution;
}

glm::mat4x4 const & Camera::viewProjection() const
{
	return _viewProjection;
}

Camera::Camera()
{
}


Camera::~Camera()
{
}
