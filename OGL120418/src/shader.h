#pragma once
#include "GL\glew.h"
#include <string>
#include <unordered_map>
#include <glm\glm.hpp>

class Shader
{	
	GLuint	_program;
	std::unordered_map<std::string, int> _uniformLocations;
public:
	Shader(const std::string& vertSource, const std::string& fragSource);
	void bind();
	void update();
	GLint getUniformLocation(const std::string& u_name);
	void setUniform1i(const std::string& u_name, int v0);
	void setUniform1f(const std::string& u_name, float v0);
	void setUniform2f(const std::string& u_name, float v0, float v1);
	void setUniform3f(const std::string& u_name, float v0, float v1, float v2);
	void setUniform4f(const std::string& u_name, float v0, float v1, float v2, float v3);
	void setUniformMat4f(const std::string& u_name, const glm::mat4& matrix);

	static Shader loadShader(const std::string& filename);
};
