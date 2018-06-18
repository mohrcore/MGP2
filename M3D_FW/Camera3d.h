#pragma once

#include "Matrix.h"

#include "CommonTypes.h"

namespace m3dfw
{
	class Camera3d
	{
	public:

		Camera3d();
		Camera3d(const Vec3f & pos, const Vec3f & ang);
		~Camera3d();

		Vec3f position;
		Vec3f angle;
	};
}
