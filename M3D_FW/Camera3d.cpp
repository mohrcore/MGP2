#include "Camera3d.h"



m3dfw::Camera3d::Camera3d()
{
}

m3dfw::Camera3d::Camera3d(const m3dfw::Vec3f & pos, const m3dfw::Vec3f & ang) : position(pos), angle(ang)
{
}

m3dfw::Camera3d::~Camera3d()
{
}
