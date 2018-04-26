#pragma once
#include "display.h"
#include "renderer.h"

class Application
{
	Display		_display;
	Game		_game;
	Renderer	_renderer;
public:
	Application();
	void run();
};