#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>

#include <M3D.h>

class IMP_Asset
{
public:

	IMP_Asset();
	~IMP_Asset();

	void import(std::string path, TextureBank & tb);

	EntityM getEntityM();

private:

	std::string directory;

	EntityM entity;

	void processNodes(aiNode * node, const aiScene * scene, TextureBank & tb);
	Mesh processMesh(aiMesh * mesh, const aiScene * scene, TextureBank & tb);
};

