#pragma once

#include "System.h"

namespace m3dfw
{
	class TaskManager2
	{
	public:

		TaskManager2();
		~TaskManager2();

	private:

		unsigned char _osys_count;

		System * _graphics_sys, * _physics_sys, * _ai_sys, * _audio_sys;
		System * * _other_systems;
	};
}


