#include "defs.h"
#include "mesh.h"
#include <glm\glm.hpp>
#include <iostream>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include "vertex.h"
#include "indexbuffer.h"



Mesh::Mesh(const std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
	VertexBufferLayout vertexLayout;
	vertexLayout.push<float>(4);
	vertexLayout.push<float>(4);

	VertexBuffer *vbo = VertexBuffer::genVertexBuffer(&vertices[0], vertices.size() * sizeof(Vertex));
	_vao.addBuffer(vbo, vertexLayout);
	_indexBuffer.set(&indices[0], indices.size());
}

void Mesh::bind() const
{
	_vao.bind();
	_indexBuffer.bind();
}