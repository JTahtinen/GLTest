#pragma once
#include "GL\glew.h"
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"
#include <vector>

class VertexArray
{
	GLuint			_vao;
	unsigned int	_numAttributes;
	std::vector<VertexBuffer*> _vertexBuffers;
public:
	VertexArray();
	~VertexArray();
public:
	void addBuffer(VertexBuffer* buffer, const VertexBufferLayout& layout);
	void bind() const;
};