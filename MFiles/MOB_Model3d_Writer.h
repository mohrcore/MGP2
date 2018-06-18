#pragma once

#include "MFile.h"
#include "MOB_Model3d.h"

namespace mfile
{
	bool writeModel3d(MFile & target, MOB_Model3d & source);
	bool writeGMesh3d(MFile & target, const MOB_GMesh3d & source);
}