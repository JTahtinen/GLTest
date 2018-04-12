#include "shader.h"
#include "util/load_file.h"

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static GLuint createShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& vertSource, const std::string& fragSource)
{
	_program = glCreateProgram();

	GLuint vertexShader = createShader(vertSource, GL_VERTEX_SHADER);
	GLuint fragmentShader = createShader(fragSource, GL_FRAGMENT_SHADER);


	glAttachShader(_program, vertexShader);
	glAttachShader(_program, fragmentShader);

	glLinkProgram(_program);
	glValidateProgram(_program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
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

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	checkShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failure: ");

	return shader;
}

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
	{
		glGetProgramiv(shader, flag, &success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE)
	{
		if (isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}
		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

void Shader::bind()
{
	glUseProgram(_program);
}

Shader Shader::loadShader(std::string& filename)
{
	std::string vertSource = load_text_file(filename + ".vs");
	std::string fragSource = load_text_file(filename + ".fs");
	std::cout << vertSource << std::endl;
	std::cout << fragSource << std::endl;
	return Shader(vertSource, fragSource);
}