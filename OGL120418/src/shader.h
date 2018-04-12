#pragma once
#include "GL\glew.h"
#include <string>
class Shader
{
	GLuint	_program;
public:
	Shader(const std::string& vertSource, const std::string& fragSource);
	void bind();
	static Shader loadShader(std::string& filename);
};
