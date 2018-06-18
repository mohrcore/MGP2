#pragma once

#include "MFile.h"
#include "MOB_Scene.h"


namespace mfile
{
	bool writeScene(MFile & target, const MOB_Scene & source);
}