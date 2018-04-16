#include "defs.h"
#include "shader.h"
#include "util/load_file.h"

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static GLuint createShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& vertSource, const std::string& fragSource)
{
	_program = glCreateProgram();

	GLuint vertexShader = createShader(vertSource, GL_VERTEX_SHADER);
	GLuint fragmentShader = createShader(fragSource, GL_FRAGMENT_SHADER);


	GLCALL(glAttachShader(_program, vertexShader));
	GLCALL(glAttachShader(_program, fragmentShader));
	GLCALL(glLinkProgram(_program));
	GLCALL(glValidateProgram(_program));
	GLCALL(glDeleteShader(vertexShader));
	GLCALL(glDeleteShader(fragmentShader));

}

static GLuint createShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
	{
		std::cerr << "Error: Shader creation failed!" << std::endl;
	}

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	GLCALL(glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths));
	GLCALL(glCompileShader(shader));

	checkShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failure: ");

	return shader;
}

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
	{
		GLCALL(glGetProgramiv(shader, flag, &success));
	}
	else
	{
		GLCALL(glGetShaderiv(shader, flag, &success));
	}

	if (success == GL_FALSE)
	{
		if (isProgram)
		{
			GLCALL(glGetProgramInfoLog(shader, sizeof(error), NULL, error));
		}
		else
		{
			GLCALL(glGetShaderInfoLog(shader, sizeof(error), NULL, error));
		}
		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}


void Shader::bind()
{
	GLCALL(glUseProgram(_program));
}

void Shader::update()
{

}

void Shader::setUniform1i(const std::string& u_name, int v0)
{
	GLCALL(glUniform1i(getUniformLocation(u_name), v0));
}

void Shader::setUniform4f(const std::string& u_name, float v0, float v1, float v2, float v3)
{
	GLCALL(glUniform4f(getUniformLocation(u_name), v0, v1, v2, v3));
}

void Shader::setUniformMat4f(const std::string& u_name, glm::mat4& matrix)
{
	GLCALL(glUniformMatrix4fv(getUniformLocation(u_name), 1, GL_FALSE, &matrix[0][0]));
}

GLint Shader::getUniformLocation(const std::string&  u_name)
{
	if (_uniformLocations.find(u_name) != _uniformLocations.end())
	{
		return _uniformLocations[u_name];
	}

	GLCALL(GLint location = glGetUniformLocation(_program, u_name.c_str()));
	if (location == -1)
	{
		std::cout << "[WARNING] Could not find uniform: " << u_name << std::endl;
	}
	_uniformLocations[u_name] = location;
	return location; 
}

Shader Shader::loadShader(const std::string& filename)
{
	std::string vertSource = load_text_file(filename + ".vs");
	std::string fragSource = load_text_file(filename + ".fs");
//	std::cout << vertSource << std::endl;
//	std::cout << fragSource << std::endl;
	return Shader(vertSource, fragSource);
}