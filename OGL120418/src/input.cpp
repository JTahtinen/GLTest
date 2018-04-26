#include "input.h"
#include <math.h>

Input::Input() 
	: _currentMouseState(0)
{
	for (int i = 0; i < 2; ++i)
	{
		_mouseX[i] = 0;
		_mouseY[i] = 0;
	}
	keys.reserve(50);
	keysDown.reserve(50);
	keysPressed.reserve(50);
	keysUp.reserve(50);
}

void Input::addKey(SDL_Keycode key)
{
	keys.emplace_back(key);
	keysDown.emplace_back(false);
	keysPressed.emplace_back(false);
	keysUp.emplace_back(false);
}


void Input::update()
{
	for (unsigned int i = 0; i < keysPressed.size(); ++i) {
		keysPressed[i] = false;
		keysUp[i] = false;
	}

	_mouseLeft = false;
	_mouseRight = false;
	SDL_GetMouseState(&_mouseX[_currentMouseState], &_mouseY[_currentMouseState]);
	_currentMouseState = !_currentMouseState;
	

	static SDL_Event ev;
	while (SDL_PollEvent(&ev) != 0) 
	{
		if (ev.type == SDL_MOUSEBUTTONDOWN) 
		{
			switch (ev.button.button)
			{
			case SDL_BUTTON_LEFT:
				_mouseLeft = true;
				break;
			case SDL_BUTTON_RIGHT:
				_mouseRight = true;
				break;
			}
		}
		if (ev.type == SDL_KEYDOWN) 
		{
			SDL_Keycode& key = ev.key.keysym.sym;
			for (unsigned int i = 0; i < keys.size(); ++i) 
			{
				if (key == keys[i]) 
				{
					if (!keysDown[i]) 
					{
						keysPressed[i] = true;
					}
					keysDown[i] = true;
				}
			}
		}
		else if (ev.type == SDL_KEYUP) 
		{
			SDL_Keycode& key = ev.key.keysym.sym;
			for (unsigned int i = 0; i < keys.size(); ++i) 
			{
				if (key == keys[i]) 
				{
					keysUp[i] = true;
					keysDown[i] = false;
				}
			}
		}
	}
}

bool Input::poll(SDL_Keycode key, KeyState state) const
{
	bool keyFound = false;
	unsigned int i;
	for (i = 0; i < keys.size(); ++i) {
		if (keys[i] == key) {
			keyFound = true;
			break;
		}
	}
	if (keyFound) {
		switch (state) {
		case KEY_DOWN:
			return keysDown[i];
			break;
		case KEY_PRESSED:
			return keysPressed[i];
			break;
		case KEY_UP:
			return keysUp[i];
			break;
		}
	}
	return false;
}

bool Input::poll(MouseState state) const
{
	switch (state)
	{
	case LEFT_CLICKED:
		return _mouseLeft;
	case RIGHT_CLICKED:
		return _mouseRight;
	}
	return false;
}

int Input::getMouseX() const
{
	return _mouseX[_currentMouseState];
}

int Input::getMouseY() const
{
	return _mouseY[_currentMouseState];
}

void Input::getMouseDelta(int* x, int* y) const
{
	*x = (_mouseX[_currentMouseState] - _mouseX[!_currentMouseState]);
	*y = (_mouseY[_currentMouseState] - _mouseY[!_currentMouseState]);
}
