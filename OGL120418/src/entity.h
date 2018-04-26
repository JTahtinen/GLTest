#pragma once
#include "mesh.h"
#include  <glm\glm.hpp>

class Entity
{
	glm::vec3		_pos;
	const Mesh*		_mesh;
	glm::mat4		_modelMatrix;
public:
	Entity(const glm::vec3& pos, const Mesh* mesh = nullptr);
	Entity(float x, float y, float z, const Mesh* mesh = nullptr);
	Entity(const Mesh* mesh = nullptr);
	void setMesh(const Mesh* mesh);
	void update();
	void move(const glm::vec3& dir, float amt);
	void moveTo(const glm::vec3& pos);

	inline const glm::mat4& getModelMatrix() const { return _modelMatrix; }
	inline const Mesh* getMesh() const { return _mesh; }
};