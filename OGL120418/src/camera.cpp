#include "camera.h"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\rotate_vector.hpp"

const glm::vec3 Camera::yAxis(0.0f, 1.0f, 0.0f);

Camera::Camera(const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up)
	: _position(position)
	, _forward(forward)
	, _up(up)
{
	glm::normalize(_forward);
	glm::normalize(_up);
}

void Camera::moveTo(const glm::vec3& pos)
{
	_position = pos;
}

void Camera::move(const glm::vec3& dir, float amt)
{
	_position += glm::normalize(dir) * amt;
}


void Camera::rotateX(float degrees)
{
	_forward = glm::rotateX(_forward, glm::radians(degrees));
}

void Camera::rotateY(float degrees)
{
	_forward = glm::rotateY(_forward, glm::radians(degrees));
}