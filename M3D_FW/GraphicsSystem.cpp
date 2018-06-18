#include "GraphicsSystem.h"



m3dfw::GraphicsSystem::GraphicsSystem() : _o3dr_gl(_shader_mngr)
{
}


m3dfw::GraphicsSystem::~GraphicsSystem()
{
}


void m3dfw::GraphicsSystem::execute() //Mess, testing system functionalities.
{
	addTask(CAST_DSYS_MEMBER(GraphicsSystem::renderEverythingNP)); //First, simplest rendering method, used for testing system and other methods
	addTask(WAIT_FOR_TASK_COMPLETION); //Any task up to this point has to be completed before new task could be executed
}

void m3dfw::GraphicsSystem::renderEverythingNP(m3dfw::SysArg const *)
{
	if (_scenes.empty())
		return;

	GfxScene & current_scene = _scenes[_current_scene_id];

	//Renders everything on the scene
	unsigned int obj_count = current_scene.objects.size();;

	Camera3d cam(Vec3f(0, 0, 0), Vec3f(0, 0, 0));

	for (unsigned int i = 0; i < obj_count; i++)
		_o3dr_gl.render(current_scene.objects[i], cameras[_active_camera_id], current_scene.environment.lights());
}

void m3dfw::GraphicsSystem::setActiveScene(m3dfw::ScID id)
{
	_current_scene_id = id;
}

void m3dfw::GraphicsSystem::setActiveCamera(unsigned int id)
{
	_active_camera_id = id;
}