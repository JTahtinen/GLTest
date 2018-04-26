#include "application.h"
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
#include "vertexarray.h"
#include "camera.h"
#include "mesh.h"
#include "scene.h"
#include "renderer.h"
#include "input.h"
#include "entity.h"

Application::Application()
	: _display(1920, 1080, (std::string)"GLTest")
{
	
	std::cout << glGetString(GL_VERSION) << std::endl;
}

void Application::run()
{
	{
		std::shared_ptr<Input> input = Input::getInstance();
		bool running = true;

		std::vector<Vertex> vertices;
		vertices.push_back(Vertex(glm::vec4(-4.0f, -4.0f, -4.0f, 1.0f), glm::vec4(1.0f, 0.2f, 0.2f, 1.0f)));
		vertices.push_back(Vertex(glm::vec4(-4.0f, 4.0f, -4.0f, 1.0f), glm::vec4(0.2f, 1.0f, 0.2f, 1.0f)));
		vertices.push_back(Vertex(glm::vec4(4.0f, 4.0f, -4.0f, 1.0f), glm::vec4(0.2f, 0.2f, 1.0f, 1.0f)));
		vertices.push_back(Vertex(glm::vec4(4.0f, -4.0f, -4.0f, 1.0f), glm::vec4(1.0f, 1.0f, 0.2f, 1.0f)));
		vertices.push_back(Vertex(glm::vec4(-4.0f, -4.0f, 4.0f, 1.0f), glm::vec4(1.0f, 0.2f, 0.2f, 1.0f)));
		vertices.push_back(Vertex(glm::vec4(4.0f, -4.0f, 4.0f, 1.0f), glm::vec4(0.2f, 1.0f, 0.2f, 1.0f)));

		glm::vec2 texCoords[]
		{
			glm::vec2(0.0f, 0.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(1.0f, 0.0f),

			glm::vec2(0.0f, 1.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),
		};

		std::vector<unsigned int> indices;
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
		indices.push_back(2);
		indices.push_back(0);
		indices.push_back(3);
		indices.push_back(0);
		indices.push_back(3);
		indices.push_back(4);
		indices.push_back(4);
		indices.push_back(3);
		indices.push_back(5);

		VertexBuffer *texCoordBuffer = VertexBuffer::genVertexBuffer(texCoords, sizeof(texCoords));
		VertexBufferLayout texCoordLayout;

		texCoordLayout.push<float>(2);
		
		VertexArray vao;
		VertexBuffer *vbo = VertexBuffer::genVertexBuffer(&vertices[0], vertices.size() * sizeof(Vertex));
		VertexBufferLayout layout;
		layout.push<float>(4);
		layout.push<float>(4);
		vao.addBuffer(vbo, layout);
		vao.addBuffer(texCoordBuffer, texCoordLayout);
		IndexBuffer ibo;
		ibo.set(&indices[0], indices.size());

		Shader shader = Shader::loadShader((std::string)"./res/shaders/basicShader");
		shader.bind();

		Texture texture("./res/textures/bricks.jpg");
		texture.bind();
		int width = _display.getWidth();
		int height = _display.getHeight();
		//glm::mat4 proj = glm::ortho(-8.0f, 8.0f, -6.0f, 6.0f, -200.0f, 200.0f);
		glm::mat4 proj = glm::perspective(glm::radians(70.0f), (float)width / float(height), 0.1f, 200.0f);
		shader.setUniform1i("u_Texture", 0);

		//Mesh monkey("./res/models/monkey.obj");
		Scene scene("./res/models/monkey.obj");
		const Mesh* monkey = scene.getMesh(0);
		const Mesh platform(vertices, indices);


		glm::vec3 light(0);

		float lIntensity = 50.0f;

		//Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		const Camera& camera = _game.getCamera();


		input->addKey(SDLK_ESCAPE);
		input->addKey(SDLK_a);
		input->addKey(SDLK_b);
		input->addKey(SDLK_c);
		input->addKey(SDLK_d);
		input->addKey(SDLK_e);
		input->addKey(SDLK_f);
		input->addKey(SDLK_g);
		input->addKey(SDLK_h);
		input->addKey(SDLK_i);
		input->addKey(SDLK_j);
		input->addKey(SDLK_k);
		input->addKey(SDLK_l);
		input->addKey(SDLK_m);
		input->addKey(SDLK_n);
		input->addKey(SDLK_o);
		input->addKey(SDLK_p);
		input->addKey(SDLK_q);
		input->addKey(SDLK_r);
		input->addKey(SDLK_s);
		input->addKey(SDLK_t);
		input->addKey(SDLK_u);
		input->addKey(SDLK_v);
		input->addKey(SDLK_w);
		input->addKey(SDLK_x);
		input->addKey(SDLK_y);
		input->addKey(SDLK_z);
		input->addKey(SDLK_UP);
		input->addKey(SDLK_DOWN);
		input->addKey(SDLK_LEFT);
		input->addKey(SDLK_RIGHT);
		shader.setUniform4f("u_Color", 0.1, 0.3f, 0.8f, 1.0f);
		while (running)
		{
			input->update();
			if (input->poll(SDLK_ESCAPE, KEY_DOWN)) { running = false; }
			if (input->poll(SDLK_t, KEY_DOWN)) { light.z -= 0.1f; }
			if (input->poll(SDLK_y, KEY_DOWN)) { light.z += 0.1f; }
			_game.update();
			//light.x = mouseX / 800.0f * 16 - 8.0f;
			//light.y = -(mouseY / 600.0f * 12 - 6.0f);

			const glm::vec3& camPos = camera.getPosition();

			shader.setUniform3f("u_LightPos3D", light.x, light.y, light.z);
			shader.setUniform1f("u_LightIntensity", lIntensity);




			shader.update();
			_display.clear(0.15f, 0.0f, 0.3f, 1.0f);

			const std::vector<Entity*>& entities = _game.getEntities();
			for (unsigned int i = 0; i < entities.size(); ++i)
			{
				Entity* entity = entities[i];
				const glm::mat4 view = glm::lookAt(camPos, camPos + camera.getForward(), camera.getUp());
				const glm::mat4 model = entity->getModelMatrix();
				const glm::mat4 mvp = proj * view * model;
				shader.setUniformMat4f("u_mvp", mvp);
				shader.setUniformMat4f("u_ModelMatrix", entity->getModelMatrix());
				_renderer.draw(*entities[i]->getMesh(), shader);
			}

			_renderer.draw(vao, ibo, shader);
			_display.update();
		}
	}
	SDL_Quit();

}

