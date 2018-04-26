#include "defs.h"
#include "renderer.h"
#include <vector>
#include <GL\glew.h>

void Renderer::draw(const VertexArray& vao, const IndexBuffer& ib, const Shader& shader)
{
	vao.bind();
	ib.bind();
	GLCALL(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::draw(const Mesh& mesh, const Shader& shader)
{
	mesh.bind();
	GLCALL(glDrawElements(GL_TRIANGLES, mesh.getIndexBuffer().getCount(), GL_UNSIGNED_INT, nullptr));
}
