#include "entity.h"
#include <glm\gtc\matrix_transform.hpp>

Entity::Entity(const glm::vec3& pos, const Mesh* mesh)
	: _pos(pos)
	, _mesh(mesh)
	, _modelMatrix(1)
{

}

Entity::Entity(float x, float y, float z, const Mesh* mesh)
	: Entity(glm::vec3(x, y, z), mesh)
{

}

Entity::Entity(const Mesh* mesh)
	: Entity(glm::vec3(0.0f, 0.0f, 0.0f), mesh)
{

}

void Entity::setMesh(const Mesh* mesh)
{
	_mesh = mesh;
}

void Entity::move(const glm::vec3& dir, float amt)
{
	_pos += glm::normalize(dir) * amt;
}

void Entity::moveTo(const glm::vec3& pos)
{
	_pos = pos;
}

void Entity::update()
{
	_modelMatrix = glm::translate(glm::mat4(1.0f), _pos);
}