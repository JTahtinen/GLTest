#include "vertex.h"


Vertex::Vertex(const glm::vec4& pos, const glm::vec4& color)
	: _pos(pos)
	, _color(color)
{

}

Vertex::Vertex()
	: _pos(0.0f, 0.0f, 0.0f, 0.0f)
	, _color(0.0f, 0.0f, 0.0f, 0.0f)
{

}