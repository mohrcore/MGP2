#include "EXT_ModelImporter.h"

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include <vector>
#include <fstream>

#include "Util.h"

void processNodes(aiNode * node, const aiScene * scene, std::vector<aiMesh *> & meshes)
{
	for (int i = 0; i < node->mNumMeshes; i++)
		meshes.push_back(scene->mMeshes[node->mMeshes[i]]);

	for (int i = 0; i < node->mNumChildren; i++)
		processNodes(node->mChildren[i], scene, meshes);
}

void processMesh(aiMesh * source, mfile::MOB_GMesh3d & target)
{
	//Allocate memory for new vertex
	target.vertices_cnt = source->mNumVertices;
	if(source->mTextureCoords[0])
		target.v_data = new float[target.vertices_cnt * 8];
	else
		target.v_data = new float[target.vertices_cnt * 6];
	
	//Allocate memory for new index data
	unsigned int indices_cnt = 0;
	for (int i = 0; i < source->mNumFaces; i++)
		indices_cnt += source->mFaces[i].mNumIndices;
	target.i_data = new unsigned long[indices_cnt];
	target.indices_cnt = indices_cnt;

	//Load vertex data
	for (int i = 0; i < source->mNumVertices; i++)
	{
		float * vpos = target.vec3Data(i, 0);
		float * vnorm = target.vec3Data(i, 1);
		float * vtexc = target.vec2Data(i, 0);

		vpos[0] = source->mVertices[i].x;
		vpos[1] = source->mVertices[i].y;
		vpos[2] = source->mVertices[i].z;

		vnorm[0] = source->mNormals[i].x;
		vnorm[1] = source->mNormals[i].y;
		vnorm[2] = source->mNormals[i].z;

		if (source->mTextureCoords[0])
		{
			vtexc[0] = source->mTextureCoords[0][i].x;
			vtexc[1] = source->mTextureCoords[0][i].y;
		}
	}

	//Load index data
	auto * i_data_ptr = target.i_data;
	for (int i1 = 0; i1 < source->mNumFaces; i1++)
		for (int i2 = 0; i2 < source->mFaces[i1].mNumIndices; i2++)
		{
			*i_data_ptr = source->mFaces[i1].mIndices[i2];
			i_data_ptr++;
		}
}

/*
void processTextureInfo(aiMesh * source, mfile::MOB_GMesh3d & target, const aiScene * scene, std::vector<std::string> & texture_paths)
{
	aiMaterial * material = scene->mMaterials[source->mMaterialIndex];

	std::vector<unsigned char> texture_ids;

	for (int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++)
	{
		aiString str;
		if (material->GetTexture(aiTextureType_DIFFUSE, i, &str) != AI_SUCCESS)
			noteError("An error occured when AssImp was trying to get texture path");
		else
		{
			std::string strr(str.C_Str());
			if (!strr.empty())
				texture_paths.push_back(strr);

			texture_ids.push_back(texture_paths.size() - 1);
		}
	}

	target.texture_cnt = texture_ids.size();
	target.textures = new unsigned char[target.texture_cnt];

	for (int i = 0; i < target.texture_cnt; i++)
		target.textures[i] = texture_ids[i];
}
*/

/*
void optimizeTextureInfo(mfile::MOB_Model3d & model, std::vector<std::string> & texture_paths) //Removes texture duplicates
{
	//Copy the vector
	std::vector<std::string> tp_cpy = texture_paths;

	//Remove all duplicates form the copy
	for (std::vector<std::string>::iterator it = tp_cpy.begin(); it != tp_cpy.end(); it++)
	{
		std::vector<std::string>::iterator it_cpy = it;

		it_cpy++;
		if (it_cpy == tp_cpy.end())
			break;

		while (it_cpy != tp_cpy.end())
		{
			if (*it == *it_cpy)
				it_cpy = tp_cpy.erase(it_cpy);
			else
				it_cpy++;
		}
	}

	//Reassign all texture id's to fit the optimized copy
	for (unsigned long i1 = 0; i1 < model.mesh_cnt; i1++)
		for (unsigned long i2 = 0; i2 < model.meshes[i1].texture_cnt; i2++)
		{
			unsigned char & texture_id = model.meshes[i1].textures[i2];
			texture_id = findIdInVector(tp_cpy, texture_paths[texture_id]);
		}

	//Replace unoptimized vector with it's optimized copy
	texture_paths = tp_cpy;
}
*/

void processMaterial(const aiMesh * mesh, const aiScene * scene, mfile::MOB_Material & target)
{
	target.clear();

	const aiMaterial * material = scene->mMaterials[mesh->mMaterialIndex];

	std::vector<std::string> paths;

	for (int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++)
	{
		aiString aistr;
		if(material->GetTexture(aiTextureType_DIFFUSE, i, &aistr) != AI_SUCCESS)
			noteError("An error occured when AssImp was trying to get texture path");
		else
		{
			std::string str(aistr.C_Str());
			if (!str.empty())
				paths.push_back(str);
		}
	}

	mfile::copyCStr("<unknown>", target.program.name);
	mfile::copyCStr("<unknown_vp>", target.program.vertex_path);
	mfile::copyCStr("<unknown_fp>", target.program.fragment_path);

	target.texture_cnt = paths.size();
	target.textures = new mfile::MOB_Res[target.texture_cnt];
	for (int i = 0; i < target.texture_cnt; i++)
	{
		mfile::copyCStr(paths[i].c_str(), target.textures[i].path);
		mfile::copyCStr(paths[i].c_str(), target.textures[i].name);
	}
}

void assignAndOptimizeMaterials(mfile::MOB_Model3d & model, std::vector<mfile::MOB_Material> & materials)
{
	std::vector<mfile::MOB_Material> vec_cpy;
	vec_cpy.resize(materials.size());
	for (int i = 0; i < materials.size(); i++)
		vec_cpy[i] = materials[i];

	//Remove material duplicates
	for (std::vector<mfile::MOB_Material>::iterator it = materials.begin(); it != materials.end(); it++)
	{
		std::vector<mfile::MOB_Material>::iterator it_cpy = it;

		it_cpy++;
		if (it_cpy == materials.end())
			break;

		while (it_cpy != materials.end())
		{
			if (*it == *it_cpy)
				it_cpy = materials.erase(it_cpy);
			else
				it_cpy++;
		}
	}

	//Copy some data
	model.material_cnt = materials.size();
	model.material_names = new char *[model.material_cnt];

	for (unsigned int i = 0; i < model.material_cnt; i++)
	{
		if (materials[i].name != nullptr)
			delete materials[i].name;
		mfile::copyCStr((std::string(model.name) + "_mat_" + std::to_string(i)).c_str(), materials[i].name);
	}

	for (unsigned long i = 0; i < model.material_cnt; i++)
		mfile::copyCStr(materials[i].name, model.material_names[i]);

	//Reassign material id's to match the optimized table
	for (unsigned long i1 = 0; i1 < model.mesh_cnt; i1++)
	{
		auto & mat_id = model.meshes[i1].material;
		mat_id = findIdInVector(materials, vec_cpy[mat_id]);
	}

	bool suff = true;
}

void importExteranalModelToEditableModel3d(const std::string & path, mfile::EditableModel3d & target, std::vector<mfile::MOB_Material> & materials)
{
	Assimp::Importer importer;
	const aiScene * scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) //Error checking
		fatalError("ASSIMP ERROR: \"" + std::string(importer.GetErrorString()) + "\"");

	std::vector<aiMesh *> meshes;

	processNodes(scene->mRootNode, scene, meshes);

	target.setMeshCount(meshes.size());
	materials.resize(meshes.size());

	for (int i = 0; i < meshes.size(); i++)
	{
		target.meshes[i].material = i;

		if (meshes[i]->mTextureCoords[0])
			target.setAttribCount(i, 2, 1, 0);
		else
			target.setAttribCount(i, 2, 0, 0);

		processMesh(meshes[i], target.meshes[i]);
		processMaterial(meshes[i], scene, materials[i]);
	}

	target.mesh_cnt = meshes.size();

	assignAndOptimizeMaterials(target, materials);
}

/*
void generateTextureResources(mfile::EditableModel3d & target, std::vector<std::string> & texture_paths, m3dfw::ResourceLoader & resloader)
{
	target.texture_cnt = texture_paths.size();
	target.texture_names = new char *[target.texture_cnt];

	for (unsigned int i = 0; i < target.texture_cnt; i++)
	{
		mfile::copyCStr(texture_paths[i].c_str(), target.texture_names[i]);

		resloader.importGTexture2d(texture_paths[i], texture_paths[i]);
	}
}
*/

//void generateMaterialMDPFile(const std::vector<mfile::MOB_Material> & materials, const std::string & path)
//{
//	std::ofstream stream(path, std::ofstream::trunc);
//
//	for (auto & mat : materials)
//	{
//		stream << mat.
//	}
//}