#pragma once

#include <vector>

#include "System.h"
#include "GfxScene.h"
#include "Camera3d.h"
#include "O3DRendererGL.h"
#include "ShaderManager.h"


namespace m3dfw
{
	typedef unsigned int ScID; // SCID Stand for Scene ID

	class GraphicsSystem
		: public System
	{
	public:

		GraphicsSystem();
		~GraphicsSystem();

		virtual void execute();

		void setActiveScene(ScID id);
		void setActiveCamera(unsigned int id);

		//Public members:

		std::vector<Camera3d> cameras;

	private:

		void renderEverythingNP(SysArg const *); //Renders the whole scene without any shader sorting, occlusion culling etc. Used mainly for testing purpouses.

		std::vector<GfxScene> _scenes;
		ScID _current_scene_id;

		unsigned int _active_camera_id;

		//Renderers:

		O3DRendererGL _o3dr_gl; //GfxObject renderer

		ShaderManager _shader_mngr;
	};
}
