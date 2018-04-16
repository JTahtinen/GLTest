#pragma once
#include "GL\glew.h"

class VertexBuffer
{
	GLuint		_buffer;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void bind() const;
};