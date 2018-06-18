#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>

#include <M3D.h>

#include "IMP_Asset.h"



IMP_Asset::IMP_Asset()
{
}


IMP_Asset::~IMP_Asset()
{
}


void IMP_Asset::import(std::string path, TextureBank & tb)
{
	Assimp::Importer import;
	const aiScene * scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices); //Loading scene from file
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) //Error checking
		fatal_error("ASSIMP ERROR: " + std::string(import.GetErrorString()));

	directory = path.substr(0, path.find_last_of('/'));

	processNodes(scene->mRootNode, scene, tb);
}

void IMP_Asset::processNodes(aiNode * node, const aiScene * scene, TextureBank & tb)
{
	for (int i = 0; i < node->mNumMeshes; i++)
		entity.meshes.push_back(processMesh(scene->mMeshes[node->mMeshes[i]], scene, tb));

	for (int i = 0; i < node->mNumChildren; i++)
		processNodes(node->mChildren[i], scene, tb);
}

Mesh IMP_Asset::processMesh(aiMesh * mesh, const aiScene * scene, TextureBank & tb)
{
	Mesh result;
	std::vector<Vertex> vd;
	std::vector<GLuint> id;
	std::vector<Texture *> td;

	vd.resize(mesh->mNumVertices);

	//Loading Vertices
	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		vd[i].pos = Vec3f(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vd[i].normal = Vec3f(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		if (mesh->mTextureCoords[0])
		{
			vd[i].uv = Vec2f(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
			bool nothing = true; //DEBUG
		}
	}

	//Loading Indices
	for (int i1 = 0; i1 < mesh->mNumFaces; i1++)
	{
		for (int i2 = 0; i2 < mesh->mFaces[i1].mNumIndices; i2++)
		{
			id.push_back(mesh->mFaces[i1].mIndices[i2]);
		}
	}

	//Loading Textures
	std::vector<std::string> texture_paths;

	aiMaterial * material = scene->mMaterials[mesh->mMaterialIndex];

	for (int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++)
	{
		aiString str;
		if(material->GetTexture(aiTextureType_DIFFUSE, i, &str) != AI_SUCCESS)
			fatal_error("Assimp could't get texture path");
		const char * txt = str.C_Str();
		std::string strr = std::string(txt);
		if(!strr.empty())
			texture_paths.push_back(std::string(txt));
	}

	td.clear();

	//td.push_back(tb.getTextureByPath("resources/textures/test1.png");
	//texture_paths.clear(); //TEST
	//texture_paths.push_back("resources/textures/test1.png"); //TEST

	result.loadRawDataTP(vd, id, texture_paths, tb);

	return result;
}

EntityM IMP_Asset::getEntityM()
{
	return entity;
}