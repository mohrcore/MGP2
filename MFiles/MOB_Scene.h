#pragma once

#include "MOB_Res.h"
#include "CT.h"


namespace mfile
{
	struct MOB_SceneObject
	{
		int model_id;


	};

	class MOB_Scene
	{
	public:

		MOB_Scene();
		~MOB_Scene();

		Vec3f lights(unsigned int id);
		Vec3f cameras(unsigned int id);

		void clear();

		const char * name;

		MOB_Res * models;
		unsigned int models_count;

		float * light_data;
		unsigned int lights_count;

		float * camera_data;
		unsigned int cameras_count;
	};
}


