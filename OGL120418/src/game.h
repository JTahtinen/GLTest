#pragma once
#include <vector>
#include "entity.h"
#include "scene.h"
#include "camera.h"
#include "shader.h"

class Game
{
	std::vector<Scene*>		_scenes;
	std::vector<Entity*>	_entities;
	Camera					_camera;
public:
	Game();
	~Game();
	void update();
	inline const std::vector<Entity*>& getEntities() const { return _entities; }
	inline const Camera& getCamera() const { return _camera; }
};