#pragma once
#include "GL\glew.h"
#include <string>
class Shader
{
	enum
	{
		COLOR_U = 0,
		LIGHTPOS_U,
		NUM_UNIFORMS
	};
	
	GLuint	_program;
	GLint	_uniforms[NUM_UNIFORMS];
public:
	Shader(const std::string& vertSource, const std::string& fragSource);
	void bind();
	void update();
	void setColor(float r, float g, float b);
	static Shader loadShader(std::string& filename);
};
