#include "defs.h"
#include "GL\glew.h"
#include "texture.h"
#include "stb_image.h"

Texture::Texture(const std::string& filepath)
	: _width(0)
	, _height(0)
	, _bpp(0)
{
	stbi_set_flip_vertically_on_load(true);
	unsigned char* image = stbi_load(filepath.c_str(), &_width, &_height, &_bpp, 4);

	GLCALL(glGenTextures(1, &_buffer));
	GLCALL(glBindTexture(GL_TEXTURE_2D, _buffer));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 
		0, GL_RGBA, GL_UNSIGNED_BYTE, image));
//	GLCALL(glBindTexture(0, GL_TEXTURE_2D));


	if (image)
	{
		stbi_image_free(image);
		image = nullptr;
	}
}

Texture::~Texture()
{
	GLCALL(glDeleteTextures(1, &_buffer));
}

void Texture::bind(unsigned int slot) const
{
	GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
	GLCALL(glBindTexture(GL_TEXTURE_2D, _buffer));
}