#pragma once
#include <glm\glm.hpp>

class Vertex
{
	glm::vec4 _pos;
	glm::vec4 _color;
public:
	Vertex(const glm::vec4& pos, const glm::vec4& color);
	Vertex();
	inline glm::vec4& getPos() { return _pos; }
	inline glm::vec4& getColor() { return _color; }
};