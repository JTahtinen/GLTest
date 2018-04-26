#pragma once
#include "mesh.h"
#include <vector>
#include <string>
#include "assimp\scene.h"

class Scene
{
	std::vector<Mesh*> _meshes;
public:
	Scene(const std::string& filepath);
	~Scene();
	const Mesh* getMesh(unsigned int index) const;
private:
	void processNode(aiNode* node, const aiScene* scene);
};