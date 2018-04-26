#include "vertexbufferlayout.h"
#include <gl\glew.h>
VertexBufferLayout::VertexBufferLayout()
	: _stride(0)
{
	_elements.reserve(10);
}

template <>
void VertexBufferLayout::push<float>(unsigned int count)
{
	_elements.push_back({ GL_FLOAT, count, false });
	_stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
}

template <>
void VertexBufferLayout::push<unsigned int>(unsigned int count)
{
	_elements.push_back({ GL_UNSIGNED_INT, count, false });
	_stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
}

template <>
void VertexBufferLayout::push<int>(unsigned int count)
{
	_elements.push_back({ GL_INT, count, false });
	_stride += VertexBufferElement::getSizeOfType(GL_INT) * count;
}

template <>
void VertexBufferLayout::push<unsigned char>(unsigned int count)
{
	_elements.push_back({ GL_UNSIGNED_BYTE, count, false });
	_stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
}

const std::vector<VertexBufferElement>& VertexBufferLayout::getElements() const
{
	return _elements;
}