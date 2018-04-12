#include <SDL\SDL.h>
#include <iostream>
#include "display.h"
#include "GL\glew.h"
#include "util\load_file.h"
#include "shader.h"


int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "[ERROR] Could not init SDL!" << std::endl;
		std::cin.get();
		return 0;
	}


	Display display(800, 600, (std::string)"OGLTest");
	std::cout << glGetString(GL_VERSION) << std::endl;

	SDL_Event ev;
	bool running = true;

	float vertices[] = 
	{
		-0.5, -0.5,
		-0.5,  0.5,
		 0.5, -0.5,
		 0.5,  0.5
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		2, 1, 3
	};
	
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), vertices, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);


	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	
	
	Shader shader = Shader::loadShader((std::string)"./res/shaders/basicShader");
	shader.bind();

	float b = 0.0f;
	float incr = 0.01f;

	while (running)
	{
		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
			{
				running = false;
			}
			if (ev.type == SDL_KEYDOWN)
			{
				switch (ev.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					running = false;
				}
			}
		}

	if (b >= 1.0f) 
	{
		incr = -0.01f;
	}
	else if (b <= 0) 
	{
		incr = 0.01f;
	}

	b += incr;

	shader.setColor(0.2f, 0.6f, b);
		
	shader.update();
	display.clear(0.15f, 0.0f, 0.3f, 1.0f);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	display.update();
	}

	SDL_Quit();
	return 0;
}