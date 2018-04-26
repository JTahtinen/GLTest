#include "scene.h"
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"
#include "vertex.h"
#include <iostream>

Scene::Scene(const std::string& filepath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

	if (!scene)
	{
		std::cerr << "[ERROR] Could not load scene: " << filepath << std::endl;
	}

	aiNode* rootNode = scene->mRootNode;
	processNode(rootNode, scene);
}

void Scene::processNode(aiNode* node, const aiScene* scene)
{
	unsigned int i;
	for (i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		unsigned int j;
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		for (j = 0; j < mesh->mNumVertices; ++j)
		{
			aiVector3D* aiVertex = &mesh->mVertices[j];
			Vertex vertex(
				glm::vec4(aiVertex->x, aiVertex->y, aiVertex->z, 1.0f),
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			vertices.push_back(vertex);
		}

		for (j = 0; j < mesh->mNumFaces; ++j)
		{
			aiFace* face = &mesh->mFaces[j];
			for (unsigned int k = 0; k < face->mNumIndices; ++k)
			{
				indices.push_back(face->mIndices[k]);
			}
		}
		Mesh* finalMesh = new Mesh(vertices, indices);
		_meshes.emplace_back(finalMesh);
	}

	for (i = 0; i < node->mNumChildren; ++i)
	{
		processNode(node->mChildren[i], scene);
	}
}

Scene::~Scene()
{
	for (unsigned int i = 0; i < _meshes.size(); ++i)
	{
		delete _meshes[i];
		_meshes[i] = nullptr;
	}
}

const Mesh* Scene::getMesh(unsigned int index) const
{
	if (index < _meshes.size())
	{
		return _meshes[index];
	}
	return nullptr;
}