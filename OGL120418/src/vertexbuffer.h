#pragma once
#include "GL\glew.h"

class VertexBuffer
{
	GLuint		_buffer;
public:
	~VertexBuffer();

	void bind() const;
	static VertexBuffer* genVertexBuffer(const void* data, unsigned int size);
private:
	VertexBuffer(const void* data, unsigned int size);
};