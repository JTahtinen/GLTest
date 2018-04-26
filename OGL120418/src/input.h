#pragma once
#include <SDL/SDL.h>
#include <vector>
#include <memory>

enum KeyState { 
	KEY_DOWN, KEY_PRESSED, KEY_UP 
};

enum MouseState
{
	LEFT_CLICKED, RIGHT_CLICKED
};


class Input 
{
	int _mouseX[2];
	int _mouseY[2];
	int _currentMouseState;
	bool _mouseLeft;
	bool _mouseRight;
	std::vector<SDL_Keycode> keys;
	std::vector<bool> keysDown;
	std::vector<bool> keysPressed;
	std::vector<bool> keysUp;
public:
	void addKey(SDL_Keycode key);
	void update();
	bool poll(SDL_Keycode key, KeyState state) const;
	bool poll(MouseState state) const;
	int getMouseX() const;
	int getMouseY() const;
	void getMouseDelta(int* x, int* y) const;
	
	inline static std::shared_ptr<Input> getInstance()
	{
		static std::shared_ptr<Input> input{ new Input };
		return input;
	}
private:
	Input();
};

