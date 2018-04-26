#include "game.h"
#include "input.h"

Game::Game()
	: _camera(glm::vec3(0), glm::vec3(0, 0, -1.0f), glm::vec3(0, 1.0f, 0))
{
	_scenes.reserve(5);
	_entities.reserve(100);
	_scenes.emplace_back(new Scene("./res/models/monkey.obj"));
	_scenes.emplace_back(new Scene("./res/models/cube2.obj"));
	_entities.push_back(new Entity(_scenes[0]->getMesh(0)));
	_entities.push_back(new Entity(0, 0, -2.0f, _scenes[1]->getMesh(0)));
}

Game::~Game()
{
	for (unsigned int i = 0; i < _entities.size(); ++i)
	{
		delete _entities[i];
		_entities[i] = nullptr;
	}
	for (unsigned int i = 0; i < _scenes.size(); ++i)
	{
		delete _scenes[i];
		_scenes[i] = nullptr;
	}
}

void Game::update()
{
	std::shared_ptr<Input> input = Input::getInstance();
	static float rotSpeed = 0.6f;
	static float speed = 0.5f;
	if (input->poll(SDLK_w, KEY_DOWN)) {		_camera.move(_camera.getForward(), speed); }
	if (input->poll(SDLK_s, KEY_DOWN)) {		_camera.move(-_camera.getForward(), speed); }
	if (input->poll(SDLK_UP, KEY_DOWN)) {	_camera.rotateX(rotSpeed); }
	if (input->poll(SDLK_DOWN, KEY_DOWN)) {	_camera.rotateX(-rotSpeed); }
	if (input->poll(SDLK_RIGHT, KEY_DOWN)) { _camera.rotateY(-rotSpeed); }
	if (input->poll(SDLK_LEFT, KEY_DOWN)) {	_camera.rotateY(rotSpeed); }
	if (input->poll(SDLK_a, KEY_DOWN)) {		_camera.move(_camera.getLeft(), speed); }
	if (input->poll(SDLK_d, KEY_DOWN)) {		_camera.move(_camera.getRight(), speed); }
	if (input->poll(SDLK_u, KEY_DOWN)) { _entities[0]->move(glm::vec3(0.0f, 0.0f, -1.0f), 0.3f); }
	if (input->poll(SDLK_j, KEY_DOWN)) { _entities[0]->move(glm::vec3(0.0f, 0.0f, 1.0f), 0.3f); }
	if (input->poll(SDLK_h, KEY_DOWN)) {		_entities[0]->move(glm::vec3(-1.0f, 0.0f, 0.0f), 0.3f); }
	if (input->poll(SDLK_k, KEY_DOWN)) {		_entities[0]->move(glm::vec3(1.0f, 0.0f, 0.0f), 0.3f); }

	int mx;
	int my;
	input->getMouseDelta(&mx, &my);
	_camera.rotateY(mx * rotSpeed);
	_camera.rotateX(my * rotSpeed);

	for (unsigned int i = 0; i < _entities.size(); ++i)
	{
		_entities[i]->update();
	}
}