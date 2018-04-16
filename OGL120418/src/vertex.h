#pragma once
#include <glm\glm.hpp>

class Vertex
{
	glm::vec3 _pos;
	glm::vec4 _color;
	glm::vec2 _texCoord;
public:
	Vertex(const glm::vec3& pos, const glm::vec4& color, const glm::vec2& texCoord);
	inline glm::vec3& getPos() { return _pos; }
	inline glm::vec4& getColor() { return _color; }
	inline glm::vec2& getTexCoord() { return _texCoord; }
};