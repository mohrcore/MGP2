#include "MOB_Model3d.h"


mfile::MOB_Model3d::MOB_Model3d() : meshes(nullptr), material_names(nullptr), mesh_cnt(0), material_cnt(0), name(nullptr)
{
}

mfile::MOB_Model3d::~MOB_Model3d()
{
	clear();
}

void mfile::MOB_Model3d::clear()
{
	if (meshes != nullptr)
		delete[] meshes;

	if (material_names != nullptr)
	{
		for (unsigned long i = 0; i < material_cnt; i++)
			delete[] material_names[i];
		delete[] material_names;
	}

	if (name != nullptr)
		delete[] name;

	mesh_cnt = 0;
	material_cnt = 0;

	meshes = nullptr;
	material_names = nullptr;
	name = nullptr;
}


mfile::MOB_GMesh3d::MOB_GMesh3d() : v_data(nullptr), i_data(nullptr), material(0), indices_cnt(0), vertices_cnt(0)
{
}

mfile::MOB_GMesh3d::~MOB_GMesh3d()
{
	clear();
}

void mfile::MOB_GMesh3d::clear()
{
	if (v_data != nullptr)
		delete[] v_data;

	if (i_data != nullptr)
		delete[] i_data;

	vertices_cnt = 0;
	indices_cnt = 0;

	v_data = nullptr;
	i_data = nullptr;
}

const float * mfile::MOB_GMesh3d::getVec3Data(unsigned int vertex, unsigned int id) const
{
	unsigned int v_pos = vertex * (vec3_per_vertex * 3 + vec2_per_vertex * 2 + f_per_vertex) + id * 3;

	return v_data + v_pos;
}

const float * mfile::MOB_GMesh3d::getVec2Data(unsigned int vertex, unsigned int id) const
{
	unsigned int v_pos = vertex * (vec3_per_vertex * 3 + vec2_per_vertex * 2 + f_per_vertex) + vec3_per_vertex * 3 + id * 2;

	return v_data + v_pos;
}

float mfile::MOB_GMesh3d::getFloatData(unsigned int vertex, unsigned int id) const
{
	unsigned int v_pos = vertex * (vec3_per_vertex * 3 + vec2_per_vertex * 2 + f_per_vertex) + vec3_per_vertex * 3 + vec2_per_vertex * 2 + id;

	return v_data[v_pos];
}

float * mfile::MOB_GMesh3d::vec3Data(unsigned int vertex, unsigned int id)
{
	unsigned int v_pos = vertex * (vec3_per_vertex * 3 + vec2_per_vertex * 2 + f_per_vertex) + id * 3;

	return v_data + v_pos;
}

float * mfile::MOB_GMesh3d::vec2Data(unsigned int vertex, unsigned int id)
{
	unsigned int v_pos = vertex * (vec3_per_vertex * 3 + vec2_per_vertex * 2 + f_per_vertex) + vec3_per_vertex * 3 + id * 2;

	return v_data + v_pos;
}

float & mfile::MOB_GMesh3d::floatData(unsigned int vertex, unsigned int id)
{
	unsigned int v_pos = vertex * (vec3_per_vertex * 3 + vec2_per_vertex * 2 + f_per_vertex) + vec3_per_vertex * 3 + vec2_per_vertex * 2 + id;

	return v_data[v_pos];
}

unsigned int mfile::MOB_GMesh3d::getVertexSize() const
{
	return (vec3_per_vertex * 3 + vec2_per_vertex * 2 + f_per_vertex) * sizeof(float);
}