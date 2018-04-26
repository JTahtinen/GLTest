#pragma once
#include "vertexarray.h"
#include "indexbuffer.h"
#include "mesh.h"
#include "game.h"

class Renderer
{
public:
	void draw(const VertexArray& vao, const IndexBuffer& ib, const Shader& shader);
	void draw(const Mesh& mesh, const Shader& shader);
};