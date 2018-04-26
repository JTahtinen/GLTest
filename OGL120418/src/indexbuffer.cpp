#include "defs.h"
#include "indexbuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
{
	set(data, count);
}

IndexBuffer::IndexBuffer()
	: _buffer(0)
	, _count(0)
{

}

void IndexBuffer::set(const unsigned int* indices, unsigned int count)
{
	_count = count;
	GLCALL(glGenBuffers(1, &_buffer));
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer));
	GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), indices, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &_buffer);
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer);
}