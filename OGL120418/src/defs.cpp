#include "defs.h"

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall()
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL ERROR] (" << error << ")" << std::endl;
		return false;
	}
	return true;
}