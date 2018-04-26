#include "defs.h"
#include "vertexarray.h"

VertexArray::VertexArray()
	: _numAttributes(0)
{
	GLCALL(glGenVertexArrays(1, &_vao));
}

VertexArray::~VertexArray()
{
	for (unsigned int i = 0; i < _vertexBuffers.size(); ++i)
	{
		delete _vertexBuffers[i];
	//	_vertexBuffers[i] = nullptr;
	}
	GLCALL(glDeleteVertexArrays(1, &_vao));
}

void VertexArray::addBuffer(VertexBuffer* buffer, const VertexBufferLayout& layout)
{
	const auto& elements = layout.getElements();
	bind();
	buffer->bind();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); ++i)
	{ 

		const auto& element = elements[i];
		GLCALL(glEnableVertexAttribArray(_numAttributes));
		GLCALL(glVertexAttribPointer(_numAttributes++, element.count, element.type, element.normalized ? GL_TRUE : GL_FALSE, layout.getStride(), (const void*)offset));
		offset += element.count * element.getSizeOfType(element.type);
	}
	_vertexBuffers.push_back(buffer);
}


void VertexArray::bind() const
{
	GLCALL(glBindVertexArray(_vao));
}