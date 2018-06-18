#include "MOB_Material_Loader.h"

#include "Util.h"


bool mfile::loadMaterial(mfile::MFile & source, mfile::MOB_Material & target)
{
	if (!source.good())
		return false;

	if (!compareCStr(source.getHeaderData().type, "material"))
		return false;

	target.clear();

	source.goBeginning();

	source.readCStr(target.name);
	source.readCStr(target.program.name);
	source.readCStr(target.program.vertex_path);
	source.readCStr(target.program.fragment_path);
	source.read(target.texture_cnt);

	if (target.textures != nullptr)
		delete[] target.textures;
	target.textures = new MOB_Res[target.texture_cnt];

	for (unsigned long i = 0; i < target.texture_cnt; i++)
	{
		source.readCStr(target.textures[i].name);
		source.readCStr(target.textures[i].path);
	}

	return true;
}