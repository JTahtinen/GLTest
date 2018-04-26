#include "defs.h"
#include "vertexbuffer.h"
#include "GL\glew.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLCALL(glGenBuffers(1, &_buffer));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, _buffer));
	GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCALL(glDeleteBuffers(1, &_buffer));
}

void VertexBuffer::bind() const
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, _buffer));
}

VertexBuffer* VertexBuffer::genVertexBuffer(const void* data, unsigned int size)
{
	return new VertexBuffer(data, size);
}