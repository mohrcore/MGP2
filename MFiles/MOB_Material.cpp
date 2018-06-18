#include "MOB_Material.h"

#include "Util.h"

mfile::MOB_Material::MOB_Material() : texture_cnt(0), name(nullptr)
{
}

mfile::MOB_Material::MOB_Material(const mfile::MOB_Material & other) : texture_cnt(other.texture_cnt), program(other.program)
{
	copyCStr(other.name, name);

	textures = new MOB_Res[texture_cnt];

	for (unsigned long i = 0; i, texture_cnt; i++)
		textures[i] = other.textures[i];
}

mfile::MOB_Material::~MOB_Material()
{
	clear();
}

mfile::MOB_Material & mfile::MOB_Material::operator=(const mfile::MOB_Material & other)
{
	clear();

	texture_cnt = other.texture_cnt;
	program = other.program;

	copyCStr(other.name, name);


	textures = new MOB_Res[texture_cnt];

	for (unsigned long i = 0; i < texture_cnt; i++)
		textures[i] = other.textures[i];

	return *this;
}

bool mfile::MOB_Material::operator==(const mfile::MOB_Material & other) const
{
	if ((texture_cnt != other.texture_cnt) || (program != other.program))
		return false;

	for (unsigned long i = 0; i < texture_cnt; i++)
		if (textures[i] != other.textures[i])
			return false;

	return true;
}

bool mfile::MOB_Material::operator!=(const mfile::MOB_Material & other) const
{
	return !operator==(other);
}

void mfile::MOB_Material::clear()
{
	if (texture_cnt != 0)
	{
		delete[] textures;
		texture_cnt = 0;
	}

	if (name != nullptr)
	{
		delete[] name;
		name = nullptr;
	}

	program.clear();
}