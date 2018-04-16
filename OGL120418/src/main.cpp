#include <SDL\SDL.h>
#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "display.h"
#include "GL\glew.h"
#include "util\load_file.h"
#include "shader.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertex.h"
#include "defs.h"
#include "texture.h"


int main(int argc, char** argv)
{
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

		/*float vertices[] =
		{
			-0.5, -0.5,
			-0.5,  0.5,
			 0.5, -0.5,
			 0.5,  0.5
		};*/

		Vertex vertices[]
		{
			Vertex(glm::vec3(-4.0f, -4.0f, 0.0f), glm::vec4(1.0f, 0.2f, 0.2f, 1.0f), glm::vec2(0, 0)),
			Vertex(glm::vec3(-4.0f,  4.0f, 0.0f), glm::vec4(0.2f, 1.0f, 0.2f, 1.0f), glm::vec2(0, 1)),
			Vertex(glm::vec3( 4.0f, -4.0f, 0.0f), glm::vec4(0.2f, 0.2f, 1.0f, 1.0f), glm::vec2(1, 0)),
			Vertex(glm::vec3( 4.0f,  4.0f, 0.0f), glm::vec4(1.0f, 1.0f, 0.2f, 1.0f), glm::vec2(1, 1))
		};

		unsigned int indices[] =
		{
			0, 1, 2,
			2, 1, 3
		};

		GLuint vao;
		GLCALL(glGenVertexArrays(1, &vao));
		GLCALL(glBindVertexArray(vao));


		//VertexBuffer vbo(vertices, 8 * sizeof(float));
		VertexBuffer vbo(vertices, sizeof(vertices));

		GLCALL(glEnableVertexAttribArray(0));
		GLCALL(glEnableVertexAttribArray(1));
		GLCALL(glEnableVertexAttribArray(2));
		//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
		GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0));
		GLCALL(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(3 * sizeof(float))));
		GLCALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(7* sizeof(float))));
		IndexBuffer ibo(indices, 6);
		vbo.bind();
		ibo.bind();

		Shader shader = Shader::loadShader((std::string)"./res/shaders/basicShader");
		shader.bind();

		Texture texture("./res/textures/bricks.jpg");
		texture.bind();
		glm::mat4 proj = glm::ortho(-8.0f, 8.0f, -6.0f, 6.0f, -1.0f, 1.0f);

		shader.setUniform1i("u_Texture", 0);
		shader.setUniformMat4f("u_mvp", proj);
		

		float b = 0.0f;
		float r = 0.0f;
		float bIncr = 0.01f;
		float rIncr = 0.02f;
		float mouseX = 0.0f;
		float mouseY = 0.0f;
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
				if (ev.type == SDL_MOUSEMOTION)
				{
					mouseX = ev.motion.x / 800.0f * 16 - 8.0f; 
					mouseY = -(ev.motion.y / 600.0f * 12 - 6.0f);
				}
			}
			shader.setUniform2f("u_LightPos", mouseX, mouseY);

			if (b >= 1.0f)
			{
				b = 1.0f;
				bIncr = -0.01f;
			}
			else if (b <= 0)
			{
				b = 0.0f;
				bIncr = 0.01f;
			}

			b += bIncr;

			if (r >= 1.0f)
			{
				r = 1.0f;
				rIncr = -0.02f;
			}
			else if (r <= 0)
			{
				r = 0.0f;
				rIncr = 0.02f;
			}

			r += rIncr;

			shader.setUniform4f("u_Color", r, 0.3, 0.2, 1.0f);

			shader.update();
			display.clear(0.15f, 0.0f, 0.3f, 1.0f);
			GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
			//glDrawArrays(GL_QUADS, 0, 4);
			display.update();
		}
	}
	SDL_Quit();
	return 0;
}