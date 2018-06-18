#include "MOB_Res.h"

#include "Util.h"

mfile::MOB_Res::MOB_Res() : name(nullptr), path(nullptr)
{
}

mfile::MOB_Res::MOB_Res(const mfile::MOB_Res & other)
{
	copyCStr(other.name, name);
	copyCStr(other.path, path);
}

mfile::MOB_Res::MOB_Res(const char * n, const char * p)
{
	copyCStr(n, name);
	copyCStr(p, path);
}

mfile::MOB_Res::~MOB_Res()
{
	clear();
}

mfile::MOB_Res & mfile::MOB_Res::operator=(const mfile::MOB_Res & other)
{
	clear();

	copyCStr(other.name, name);
	copyCStr(other.path, path);

	return *this;
}

bool mfile::MOB_Res::operator==(const mfile::MOB_Res & other) const
{
	return compareCStr(path, other.path);
}

bool mfile::MOB_Res::operator!=(const mfile::MOB_Res & other) const
{
	return !operator==(other);
}

void mfile::MOB_Res::clear()
{
	if (name != nullptr)
	{
		delete[] name;
		name = nullptr;
	}
	if (path != nullptr)
	{
		delete[] path;
		path = nullptr;
	}
}

mfile::MOB_ShadingProgram::MOB_ShadingProgram() : name(nullptr), vertex_path(nullptr), fragment_path(nullptr)
{
}

mfile::MOB_ShadingProgram::MOB_ShadingProgram(const mfile::MOB_ShadingProgram & other)
{
	copyCStr(other.name, name);
	copyCStr(other.vertex_path, vertex_path);
	copyCStr(other.fragment_path, fragment_path);
}

mfile::MOB_ShadingProgram::MOB_ShadingProgram(const char * n, const char * p_vert, const char * p_frag)
{
	copyCStr(n, name);
	copyCStr(p_vert, vertex_path);
	copyCStr(p_frag, fragment_path);
}

mfile::MOB_ShadingProgram::~MOB_ShadingProgram()
{
	clear();
}

mfile::MOB_ShadingProgram & mfile::MOB_ShadingProgram::operator=(const mfile::MOB_ShadingProgram & other)
{
	clear();

	copyCStr(other.name, name);
	copyCStr(other.vertex_path, vertex_path);
	copyCStr(other.fragment_path, fragment_path);

	return *this;
}

bool mfile::MOB_ShadingProgram::operator==(const mfile::MOB_ShadingProgram & other) const
{
	return compareCStr(vertex_path, other.vertex_path) && compareCStr(fragment_path, other.fragment_path);
}

bool mfile::MOB_ShadingProgram::operator!=(const mfile::MOB_ShadingProgram & other) const
{
	return !operator==(other);
}

void mfile::MOB_ShadingProgram::clear()
{
	if (name != nullptr)
	{
		delete[] name;
		name = nullptr;
	}
	if (vertex_path != nullptr)
	{
		delete[] vertex_path;
		vertex_path = nullptr;
	}
	if (fragment_path != nullptr)
	{
		delete[] fragment_path;
		fragment_path = nullptr;
	}
}