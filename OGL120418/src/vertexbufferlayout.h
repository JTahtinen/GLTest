#pragma once
#include "defs.h"
#include <vector>
#include <GL\glew.h>

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	bool normalized;

	static unsigned int getSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:			return sizeof(float);
		case GL_UNSIGNED_INT:	return sizeof(unsigned int);
		case GL_INT:			return sizeof(int);
		case GL_UNSIGNED_BYTE:	return sizeof(unsigned char);
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
	std::vector<VertexBufferElement>	_elements;
	unsigned int						_stride;
public:
	VertexBufferLayout();

	template <typename T>
	void push(unsigned int count);
	const std::vector<VertexBufferElement>& getElements() const;
	inline unsigned int getStride() const { return _stride; }
};