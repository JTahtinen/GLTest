#include "indexbuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: _count(count)
{
	glGenBuffers(1, &_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &_buffer);
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer);
}