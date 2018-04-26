#pragma once
#include "SDL\SDL.h"
#include <string>

class Display
{
	SDL_Window*			_win;
	SDL_GLContext		_glContext;
	int					_width;
	int					_height;
public:
	Display(int width, int height, std::string& title);
	~Display();
	void clear(float r, float g, float b, float a);
	void update();
	inline int getWidth() { return _width; }
	inline int getHeight() { return _height; }
};