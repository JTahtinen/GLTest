#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "glm\glm.hpp"

class Camera
{
	static const glm::vec3 yAxis;
	glm::vec3	_position;
	glm::vec3	_forward;
	glm::vec3	_up;
public:
	Camera(const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up);
	void moveTo(const glm::vec3& pos);
	void move(const glm::vec3& dir, float amt);
	void rotateX(float degrees);
	void rotateY(float degrees);

	inline const glm::vec3& getPosition() const		{ return _position; }
	inline const glm::vec3& getForward() const		{ return _forward; }
	inline const glm::vec3& getUp() const			{ return _up; }
	inline const glm::vec3 getLeft() const			{ return glm::normalize(glm::cross(_up, _forward)); }
	inline const glm::vec3 getRight() const			{ return glm::normalize(glm::cross(_forward, _up)); }


};