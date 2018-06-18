#pragma once

#include <vector>

#include "GfxObject.h"
#include "GfxSceneConfig.h"
#include "GfxEnvironment.h"

namespace m3dfw
{
	class GfxScene
	{
	public:

		GfxScene();
		~GfxScene();

	//	//void load(const void * data_buffer);
	//	void clear();

	//	GfxObject & getObject(unsigned int id);
	//	GfxBasicLight & getLight(unsigned int id);

	//	unsigned int getObjCount() const;
	//	unsigned int getLightsCount() const;

	//	//GfxSceneConfig & getConfiguration();

	//private:

		GfxSceneConfig config;

		std::vector<GfxObject> objects;
		//std::vector<GfxBasicLight> lights;

		GfxEnvironment environment;
	};
}


