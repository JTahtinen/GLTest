#pragma once
#include <string>

class Texture
{
	unsigned int _buffer;
	int _width, _height, _bpp;
public:
	Texture(const std::string& filepath);
	~Texture();
	void bind(unsigned int slot = 0) const;

	inline int getWidth() { return _width; }
	inline int getHeight() { return _height; }
};