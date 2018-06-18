#pragma once
#include "MFile.h"
#include "MOB_Model3d.h"

namespace mfile
{
	bool loadModel3d(MFile & source, MOB_Model3d & target);
	bool loadGMesh3d(MFile & source, MOB_GMesh3d & target);
}
