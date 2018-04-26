#pragma once
#include <vector>
#include <string>
#include "vertexarray.h"
#include "indexbuffer.h"
#include "assimp\Importer.hpp"
#include "vertex.h"
#include "shader.h"


class Mesh
{
	VertexArray			_vao;
	IndexBuffer			_indexBuffer;
public:
	Mesh(const std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
	void bind() const;
	inline const IndexBuffer& getIndexBuffer() const { return _indexBuffer; }
	inline const VertexArray& getVertexArray() const { return _vao;}
}; 
