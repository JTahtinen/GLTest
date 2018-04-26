#include "defs.h"
#include "display.h"
#include "GL\glew.h"
#include <iostream>

Display::Display(int width, int height, std::string& title)
	: _width(width)
	, _height(height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "[ERROR] Could not init SDL!" << std::endl;
	}
	SDL_ShowCursor(SDL_DISABLE);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	
	_win = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	_glContext = SDL_GL_CreateContext(_win);
	SDL_GL_SetSwapInterval(1);
	GLenum status = glewInit();


	if (status != GLEW_OK)
	{
		std::cerr << "Glew failed to initialize!" << std::endl;
	}

	GLCALL(glEnable(GL_DEPTH_TEST));
//	GLCALL(glEnable(GL_CULL_FACE));
//	GLCALL(glCullFace(GL_BACK));
	GLCALL(glDepthFunc(GL_LESS));
}

Display::~Display()
{
	SDL_GL_DeleteContext(_glContext);
	SDL_DestroyWindow(_win);
	_win = nullptr;
}

void Display::clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::update()
{
	SDL_GL_SwapWindow(_win);
}