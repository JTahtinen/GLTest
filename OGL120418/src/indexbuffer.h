#pragma once
#include "GL\glew.h"

class IndexBuffer
{
	GLuint	_buffer;
	GLuint	_count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	IndexBuffer();
	void set(const unsigned int* indices, unsigned int count);
	~IndexBuffer();
	void bind() const;

	inline GLuint getCount() const { return _count; }
};