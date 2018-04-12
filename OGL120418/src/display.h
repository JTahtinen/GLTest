#pragma once
#include "SDL\SDL.h"
#include <string>

class Display
{
	SDL_Window*			_win;
	SDL_GLContext		_glContext;
public:
	Display(int width, int height, std::string& title);
	~Display();
	void clear(float r, float g, float b, float a);
	void update();
};