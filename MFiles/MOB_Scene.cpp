#include "MOB_Scene.h"



mfile::MOB_Scene::MOB_Scene() : models(nullptr), light_data(nullptr), camera_data(nullptr), name(nullptr), models_count(0), lights_count(0), cameras_count(0)
{

}

mfile::MOB_Scene::~MOB_Scene()
{
	clear();
}


void mfile::MOB_Scene::clear()
{
	if (models != nullptr)
	{
		delete[] models;
		models = nullptr;
	}
	if (light_data != nullptr)
	{
		delete[] light_data;
		light_data = nullptr;
	}
	if (camera_data != nullptr)
	{
		delete[] camera_data;
		camera_data = nullptr;
	}
	if (name != nullptr)
	{
		delete name;
		name = nullptr;
	}

	models_count = 0;
	lights_count = 0;
	cameras_count = 0;
}

mfile::Vec3f mfile::MOB_Scene::lights(unsigned int id)
{
	return { light_data[id * 3], light_data[id * 3 + 1], light_data[id * 3 + 2] };
}

mfile::Vec3f mfile::MOB_Scene::cameras(unsigned int id)
{
	return { camera_data[id * 3], camera_data[id * 3 + 1], camera_data[id * 3 + 2] };
}